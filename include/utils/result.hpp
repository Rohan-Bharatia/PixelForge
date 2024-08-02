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

#ifndef _PF_UTILS_RESULT_hpp_
#define _PF_UTILS_RESULT_hpp_

// std
#include <optional>
#include <string_view>
#include <type_traits>
#include <variant>

#include "prerequisites.h"

#define PF_TRY(expr)                                                                   \
    do                                                                                 \
    {                                                                                  \
        auto pf_suffix_macro(result_, __LINE__) = (expr);                              \
        if PF_UNLIKELY(!pf_suffix_macro(result_, __LINE__).is_ok())                    \
            return pf::err(std::move(pf_suffix_macro(result_, __LINE__)).get_error()); \
    }                                                                                  \
    while(false)

#define PF_TRY_VALUE(var, expr)                                                          \
    auto pf_suffix_macro(result_, __LINE__) = (expr);                                    \
    if PF_UNLIKELY(!pf_suffix_macro(result_, __LINE__).is_ok())                          \
        return pf::err(std::move(pf_suffix_macro(result_, __LINE__)).get_error());       \
    var = std::move(pf_suffix_macro(result_, __LINE__)).get_value()

namespace pf
{
    template<typename V>
	struct ResultValue
	{
		V value;
	};

    template<>
	struct ResultValue<void>
	{};

    template<typename E>
	struct ResultError
	{
		E value;
	};

    constexpr ResultValue<void> ok();
	template<typename V>
    constexpr auto ok(V&& value);
	template<typename E>
    constexpr auto err(E&& err);

    template<typename V, typename E>
	class Result
	{
		static_assert(!std::is_void_v<E>, "error type cannot be void!");

	public:
		struct value_tag {};
		struct error_tag {};

		template<typename T, typename = std::enable_if_t<std::is_same_v<std::decay_t<T>, V> && !std::is_same_v<V, E>>>
        constexpr Result(T&& value);
		template<typename T>
        constexpr Result(ResultValue<T> value);
		template<typename T>
        constexpr Result(ResultError<T> error);
		template<typename... Args>
        constexpr Result(value_tag, Args&&... args);
		template<typename... Args>
        constexpr Result(error_tag, Args&&... args);
		template<typename V2, typename E2, typename = std::enable_if_t<std::is_convertible_v<V2, V> && std::is_convertible_v<E2, E>>>
        constexpr Result(const Result<V2, E2>& result);
		template<typename V2, typename E2, typename = std::enable_if_t<std::is_convertible_v<V2, V> && std::is_convertible_v<E2, E>>>
        constexpr Result(Result<V2, E2>&& result);
		constexpr Result(const Result&) = default;
		constexpr Result(Result&&) = default;
		~Result() = default;

		constexpr void expect(const char* err) const;
		constexpr void expect(const std::string& err) const;

		constexpr E& get_error() &;
		constexpr const E& get_error() const &;
		constexpr E&& get_error() &&;
			
		constexpr V& get_value() &;
		constexpr const V& get_value() const&;
		constexpr V&& get_value() &&;
			
		template<typename T> constexpr V get_value_or(T&& default_value) const &;
		template<typename T> constexpr V get_value_or(T&& default_value) &&;

		constexpr bool is_err() const noexcept;
		constexpr bool is_ok() const noexcept;

		template<typename F> Result<std::invoke_result_t<F, const V&>, E>
        constexpr map(F&& functor) const& noexcept(std::is_nothrow_invocable_v<F, const V&>);
		template<typename F> Result<std::invoke_result_t<F, V&&>, E>
        constexpr map(F&& functor) && noexcept(std::is_nothrow_invocable_v<F, V&&>);

		constexpr explicit operator bool () const noexcept;

		constexpr Result& operator = (const Result&) = default;
		constexpr Result& operator = (Result&&) = default;

	private:
		constexpr void ensure_error() const;
		constexpr void ensure_value() const;

			static constexpr size_t value_index = 0;
			static constexpr size_t error_index = 1;
			std::variant<V, E> m_value;
	};

    template<typename E>
	class Result<void, E>
	{
	static_assert(!std::is_void_v<E>, "error type cannot be void!");

	public:
		struct error_tag {};
		struct value_tag {};

		constexpr Result(ResultValue<void> value);
		template<typename T>
        constexpr Result(ResultError<T> error);
		constexpr Result(value_tag);
		template<typename... Args>
        constexpr Result(error_tag, Args&&... args);
		template<typename E2, typename = std::enable_if_t<std::is_convertible_v<E2, E>>>
        constexpr Result(const Result<void, E2>& result);
		template<typename E2, typename = std::enable_if_t<std::is_convertible_v<E2, E>>>
        constexpr Result(Result<void, E2>&& result);
		constexpr Result(const Result&) = default;
		constexpr Result(Result&&) = default;
		~Result() = default;

		constexpr void expect(const char* err) const;
		constexpr void expect(const std::string& err) const;
			
		constexpr E& get_error() &;
		constexpr const E& get_error() const&;
		constexpr E&& get_error() &&;

        constexpr bool is_err() const noexcept;
        constexpr bool is_ok() const noexcept;

		template<typename F> Result<std::invoke_result_t<F>, E>
        constexpr map(F&& functor) const& noexcept(std::is_nothrow_invocable_v<F>);
		template<typename F> Result<std::invoke_result_t<F>, E>
        constexpr map(F&& functor) && noexcept(std::is_nothrow_invocable_v<F>);

		constexpr explicit operator bool () const noexcept;

		Result& operator = (const Result&) = default;
		Result& operator = (Result&&) = default;

	private:
		constexpr void ensure_error() const;
			
		std::optional<E> m_error;
	};
} // namespace pf

#include "src/utils/result.inl"

#endif // _PF_UTILS_RESULT_hpp_