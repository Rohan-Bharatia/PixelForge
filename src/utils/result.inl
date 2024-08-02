#pragma region LICENSE

//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
// 
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
// 
//                                   ...
// 
//                    Copyright (C) Rohan Bharatia 2024

#pragma endregion LICENSE

#pragma once

#ifndef _PF_UTILS_RESULT_inl_
#define _PF_UTILS_RESULT_inl_

// std
#include <functional>
#include <stdexcept>

#include "include/utils/result.hpp"

namespace pf
{
    constexpr ResultValue<void> ok()
	{
		return {};
	}

	template<typename V>
	constexpr auto ok(V&& value)
	{
		if constexpr(std::is_rvalue_reference_v<decltype(value)>)
			return ResultValue<V&&>{ std::move(value) };

		else
			return ResultValue<V&>{ value };
	}

	template<typename E>
	constexpr auto err(E&& err)
	{
		if constexpr(std::is_rvalue_reference_v<decltype(err)>)
			return Resulterror<E&&>{ std::move(err) };

		else
			return Resulterror<E&>{ err };
	}

    template<typename V, typename E>
	template<typename T, typename>
	constexpr Result<V, E>::Result(T&& value) : m_value(std::in_place_index_t<value_index>{}, std::forward<T>(value))
	{}

    template<typename V, typename E>
	template<typename T>
	constexpr Result<V, E>::Result(ResultValue<T> value) : m_value(std::in_place_index_t<value_index>{}, std::forward<T>(value.value))
	{}

	template<typename V, typename E>
	template<typename T>
	constexpr Result<V, E>::Result(ResultError<T> error) : m_value(std::in_place_index_t<error_index>{}, std::forward<T>(error.value))
	{}

	template<typename V, typename E>
	template<typename... Args>
	constexpr Result<V, E>::Result(value_tag, Args&&... args) : m_value(std::in_place_index_t<value_index>{}, std::forward<Args>(args)...)
	{}

	template<typename V, typename E>
	template<typename... Args>
	constexpr Result<V, E>::Result(error_tag, Args&&... args) : m_value(std::in_place_index_t<error_index>{}, std::forward<Args>(args)...)
	{}

    template<typename V, typename E>
	template<typename V2, typename E2, typename>
	constexpr Result<V, E>::Result(const Result<V2, E2>& result)
	{
		if(result.is_ok())
			m_value.template emplace<value_index>(result.get_value());

		else
			m_value.template emplace<error_index>(result.get_error());
	}

	template<typename V, typename E>
	template<typename V2, typename E2, typename>
	constexpr Result<V, E>::Result(Result<V2, E2>&& result)
	{
		if(result.is_ok())
			m_value.template emplace<value_index>(std::move(result).get_value());

		else
			m_value.template emplace<error_index>(std::move(result).get_error());
	}

    template<typename V, typename E>
	constexpr void Result<V, E>::expect(const char* err) const
	{
		if(is_err())
			throw std::runtime_error(err);
	}

	template<typename V, typename E>
	constexpr void Result<V, E>::expect(const std::string& err) const
	{
		if(is_err())
			throw std::runtime_error(err);
	}

    template<typename V, typename E>
	constexpr E& Result<V, E>::get_error() &
	{
		ensure_error();

		return std::get<error_index>(m_value);
	}

	template<typename V, typename E>
	constexpr const E& Result<V, E>::get_error() const &
	{
		ensure_error();

		return std::get<error_index>(m_value);
	}

	template<typename V, typename E>
	constexpr E&& Result<V, E>::get_error() &&
	{
		ensure_error();

		return std::get<error_index>(std::move(m_value));
	}

    template<typename V, typename E>
	constexpr bool Result<V, E>::is_err() const noexcept
	{
		return m_value.index() == error_index;
	}

	template<typename V, typename E>
	constexpr bool Result<V, E>::is_ok() const noexcept
	{
		return m_value.index() == value_index;
	}

	template<typename V, typename E>
	constexpr V& Result<V, E>::get_value() &
	{
		ensure_value();

		return std::get<value_index>(m_value);
	}

	template<typename V, typename E>
	constexpr const V& Result<V, E>::get_value() const&
	{
		ensure_value();

		return std::get<value_index>(m_value);
	}

    template<typename V, typename E>
	template<typename T>
	constexpr V Result<V, E>::get_value_or(T&& default_value) const &
	{
		if(is_ok())
			return std::get<value_index>(m_value);

		else
			return std::forward<T>(default_value);
	}

	template<typename V, typename E>
	template<typename T>
	constexpr V Result<V, E>::get_value_or(T&& default_value) &&
	{
		if(is_ok())
			return std::get<value_index>(std::move(m_value));
		else
			return std::forward<T>(default_value);
	}

	template<typename V, typename E>
	constexpr V&& Result<V, E>::get_value() &&
	{
		ensure_value();

		return std::get<value_index>(std::move(m_value));
	}

	template<typename V, typename E>
	template<typename F>
	constexpr Result<std::invoke_result_t<F, const V&>, E> Result<V, E>::map(F&& functor) const& noexcept(std::is_nothrow_invocable_v<F, const V&>)
	{
		using mapped_value = std::invoke_result_t<F, const V&>;
		using mapped_result = Result<mapped_value, E>;
		
		if(is_ok())
		{
			if constexpr(!std::is_void_v<mapped_value>)
				return mapped_result(typename mapped_result::value_tag{}, std::invoke(std::forward<F>(functor), get_value()));
                
			else
			{
				std::invoke(std::forward<F>(functor), get_value());
                
				return mapped_result(typename mapped_result::value_tag{});
			}
		}

		else
			return mapped_result(typename mapped_result::error_tag{}, get_error());
	}

    template<typename V, typename E>
	template<typename F>
	constexpr Result<std::invoke_result_t<F, V&&>, E> Result<V, E>::map(F&& functor) && noexcept(std::is_nothrow_invocable_v<F, V&&>)
	{
		using mapped_value = std::invoke_result_t<F, V&&>;
		using mapped_result = Result<mapped_value, E>;

		if(is_ok())
		{
			if constexpr(!std::is_void_v<mapped_value>)
				return mapped_result(typename mapped_result::value_tag{}, std::invoke(std::forward<F>(functor), std::move(*this).get_value()));

			else
			{
				std::invoke(std::forward<F>(functor), std::move(*this).get_value());

				return mapped_result(typename mapped_result::value_tag{});
			}
		}

		else
			return mapped_result(typename mapped_result::error_tag{}, std::move(*this).get_error());
	}

    template<typename V, typename E>
	constexpr Result<V, E>::operator bool () const noexcept
	{
		return is_ok();
	}

	template<typename V, typename E>
	constexpr void Result<V, E>::ensure_error() const
	{
		if(!is_err())
			throw std::runtime_error("Result is not an error!");
	}

	template<typename V, typename E>
	constexpr void Result<V, E>::ensure_value() const
	{
		if(!is_ok())
			throw std::runtime_error("Result is not a value!");
	}


	template<typename E> 
	constexpr Result<void, E>::Result(ResultValue<void>)
	{}

	template<typename E>
	template<typename T>
	constexpr Result<void, E>::Result(ResultError<T> error) : m_error(std::move(error.value))
	{}

	template<typename E>
	constexpr Result<void, E>::Result(value_tag)
	{}

	template<typename E>
	template<typename... Args>
	constexpr Result<void, E>::Result(error_tag, Args&&... args) : m_error(std::forward<Args>(args)...)
	{}

	template<typename E>
	template<typename E2, typename>
	constexpr Result<void, E>::Result(const Result<void, E2>& result)
	{
		if(!result.is_ok())
			m_error.emplace(result.get_error());
	}
	
	template<typename E>
	template<typename E2, typename>
	constexpr Result<void, E>::Result(Result<void, E2>&& result)
	{
		if(!result.is_ok())
			m_error.emplace(std::move(result).get_error());
	}
	
	template<typename E>
	constexpr E& Result<void, E>::get_error() &
	{
		ensure_error();
        
		return *m_error;
	}

	template<typename E>
	constexpr const E& Result<void, E>::get_error() const &
	{
		ensure_error();

		return *m_error;
	}

	template<typename E>
	constexpr E&& Result<void, E>::get_error() &&
	{
		ensure_error();

		return *std::move(m_error);
	}

	template<typename E>
	constexpr void Result<void, E>::expect(const char* err) const
	{
		if(is_err())
			throw std::runtime_error(err);
	}

	template<typename E>
	constexpr void Result<void, E>::expect(const std::string& err) const
	{
		if(is_err())
			throw std::runtime_error(err);
	}

	template<typename E>
	constexpr bool Result<void, E>::is_err() const noexcept
	{
		return m_error.has_value();
	}

	template<typename E>
	constexpr bool Result<void, E>::is_ok() const noexcept
	{
		return !is_err();
	}
} // namespace pf

#endif // _PF_UTILS_RESULT_inl_