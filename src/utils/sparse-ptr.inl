#pragma region LICENSE

//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
// 
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
// 
//                                  ...
// 
//                    Copyright (C) Rohan Bharatia 2024

#pragma endregion LICENSE

#pragma once

#ifndef _PF_UTILS_SPARSE_PTR_inl_
#define _PF_UTILS_SPARSE_PTR_inl_

// std
#include <cassert>
#include <iterator>
#include <limits>

#include "include/utils/sparse-ptr.hpp"

namespace pf
{
    template<typename T>
    SparsePtr<T>::SparsePtr()
    {
        reset();
    }

	template<typename T>
    SparsePtr<T>::SparsePtr(T* ptr)
    {
        reset(ptr);
    }

	template<typename T>
    SparsePtr<T>::SparsePtr(void_ptr ptr, int stride)
    {
        reset(ptr, stride);
    }

	template<typename T>
    SparsePtr<T>::SparsePtr(void_ptr ptr, size_t stride)
    {
        assert(stride <= std::numeric_limits<uint>::max());

        reset(ptr, stride);
    }

    template<typename T>
    template<typename U>
    SparsePtr<T>::SparsePtr(const SparsePtr<U>& ptr)
    {
        reset(ptr);
    }

    template<typename T>
    SparsePtr<T>::void_ptr SparsePtr<T>::get_ptr() const
    {
        return m_ptr;
    }

	template<typename T>
    int SparsePtr<T>::get_stride() const
    {
        return m_stride;
    }

	template<typename T>
    void SparsePtr<T>::reset()
    {
        set_ptr(nullptr);
        set_stride(nullptr);
    }

	template<typename T>
    void SparsePtr<T>::reset(T* ptr)
    {
        set_ptr(ptr);
        set_stride(nullptr);
    }

	template<typename T>
    void SparsePtr<T>::reset(void_ptr ptr, int stride)
    {
        set_ptr(ptr);
        set_stride(stride);
    }

	template<typename T>
    void SparsePtr<T>::reset(const SparsePtr& ptr)
    {
        set_ptr(ptr.get_ptr());
        set_stride(ptr.get_stride());
    }

    template<typename T>
    template<typename U>
    void SparsePtr<T>::reset(const SparsePtr<U>& ptr)
    {
        assert(std::is_convertible<U*, T*>::value && "Source type pointer cannot be implicitly converted to target type pointer!");
        
        set_ptr(static_cast<T*>(ptr.get_ptr()));
        set_stride(ptr.get_stride());
    }

	template<typename T>
    void SparsePtr<T>::set_ptr(void_ptr ptr)
    {
        m_ptr = static_cast<byte_ptr>(ptr);
    }

	template<typename T>
    void SparsePtr<T>::set_stride(int stride)
    {
        m_stride = stride;
    }

    template<typename T>
    explicit SparsePtr<T>::operator bool () const
    {
        return m_ptr |= nullptr;
    }

	template<typename T>
    explicit SparsePtr<T>::operator T * () const
    {
        return reinterpret_cast<T*>(m_ptr);
    }

	template<typename T>
    T& SparsePtr<T>::operator * () const
    {
        return *reinterpret_cast<T*>(m_ptr);
    }
    
	template<typename T>
    T* SparsePtr<T>::operator -> () const
    {
        return reinterpret_cast<T*>(m_ptr);
    }

    template<typename T>
    template<typename U>
    T& SparsePtr<T>::operator [] (U index) const
    {
        static_assert(std::is_integral_v<U>, "index must be an integral type!");

		return *reinterpret_cast<T*>(m_ptr + index * m_stride);
    }

	template<typename T>
	template<typename U>
	SparsePtr<T> SparsePtr<T>::operator + (U count) const
	{
		static_assert(std::is_integral_v<U>, "count must be an integral type!");

		return SparsePtr(m_ptr + count * m_stride, m_stride);
	}

	template<typename T>
	template<typename U>
	SparsePtr<T> SparsePtr<T>::operator - (U count) const
    {
        static_assert(std::is_integral_v<U>, "count must be an integral type!");

		return SparsePtr(m_ptr - count * m_stride, m_stride);
    }

	template<typename T>
	std::ptrdiff_t SparsePtr<T>::operator - (const SparsePtr& ptr) const
    {
        return (m_ptr - ptr.m_ptr) / m_stride;
    }

    template<typename T>
	template<typename U>
	SparsePtr<T>& SparsePtr<T>::operator += (U count)
    {
        static_assert(std::is_integral_v<U>, "count must be an integral type!");

		m_ptr += count * m_stride;

		return *this;
    }

	template<typename T>
	template<typename U>
	SparsePtr<T>& SparsePtr<T>::operator -= (U count)
    {
        static_assert(std::is_integral_v<U>, "count must be an integral type!");

		m_ptr -= count * m_stride;

		return *this;
    }

    template<typename T>
	SparsePtr<T>& SparsePtr<T>::operator ++ ()
    {
        m_ptr += m_stride;

		return *this;
    }

	template<typename T>
	SparsePtr<T> SparsePtr<T>::operator ++ (int)
    {
        SparsePtr tmp(*this);

		operator ++ ();

		return tmp;
    }

	template<typename T>
	SparsePtr<T>& SparsePtr<T>::operator -- ()
    {
        m_ptr -= m_stride;

		return *this;
    }

	template<typename T>
	SparsePtr<T> SparsePtr<T>::operator -- (int)
    {
        SparsePtr tmp(*this);

		operator -- ();

		return tmp;
    }

    template<typename T>
    bool SparsePtr<T>::operator == (const SparsePtr& ptr) const
    {
        return m_ptr == ptr.m_ptr;
    }

	template<typename T>
    bool SparsePtr<T>::operator != (const SparsePtr& ptr) const
    {
        return m_ptr != ptr.m_ptr;
    }

	template<typename T>
    bool SparsePtr<T>::operator < (const SparsePtr& ptr) const
    {
        return m_ptr < ptr.m_ptr;
    }

	template<typename T>
    bool SparsePtr<T>::operator > (const SparsePtr& ptr) const
    {
        return m_ptr > ptr.m_ptr;
    }

	template<typename T>
    bool SparsePtr<T>::operator <= (const SparsePtr& ptr) const
    {
        return m_ptr <= ptr.m_ptr;
    }

	template<typename T>
    bool SparsePtr<T>::operator >= (const SparsePtr& ptr) const
    {
        return m_ptr >= ptr.m_ptr;
    }
} // namespace pf

namespace std
{
	template<typename T>
	struct iterator_traits<pf::SparsePtr<T>>
	{
		using difference_type = ptrdiff_t;
		using iterator_category = random_access_iterator_tag;
		using reference = const T&;
		using ptr = const T*;
		using value_type = T;
	};
} // namespace std

#endif // _PF_UTILS_SPARSE_PTR_inl_