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

#ifndef _PF_UTILS_SPARSE_PTR_hpp_
#define _PF_UTILS_SPARSE_PTR_hpp_

// std
#include <cstddef>
#include <type_traits>

#include "prerequisites.h"

namespace pf
{
    template<typename T>
	class SparsePtr
	{
	public:
		using byte_ptr = std::conditional_t<std::is_const<T>::value, const uint8*, uint8*>;
		using void_ptr = std::conditional_t<std::is_const<T>::value, const void*, void*>;

		SparsePtr();
		SparsePtr(T* ptr);
		SparsePtr(void_ptr ptr, int stride);
		SparsePtr(void_ptr ptr, size_t stride);
		template<typename U>
        SparsePtr(const SparsePtr<U>& ptr);
		SparsePtr(const SparsePtr& ptr) = default;
		~SparsePtr() = default;

		void_ptr get_ptr() const;
		int get_stride() const;

		void reset();
		void reset(T* ptr);
		void reset(void_ptr ptr, int stride);
		void reset(const SparsePtr& ptr);
		template<typename U>
        void reset(const SparsePtr<U>& ptr);

		void set_ptr(void_ptr ptr);
		void set_stride(int stride);

		explicit operator bool () const;
		explicit operator T * () const;
		T& operator * () const;
		T* operator -> () const;
		template<typename U>
        T& operator [] (U index) const;

		SparsePtr& operator = (const SparsePtr& ptr) = default;

		template<typename U>
        SparsePtr operator + (U count) const;
		template<typename U>
        SparsePtr operator - (U count) const;
		std::ptrdiff_t operator - (const SparsePtr& ptr) const;

		template<typename U>
        SparsePtr& operator += (U count);
		template<typename U>
        SparsePtr& operator -= (U count);

		SparsePtr& operator ++ ();
		SparsePtr operator ++ (int);

		SparsePtr& operator -- ();
		SparsePtr operator -- (int);

		bool operator == (const SparsePtr& ptr) const;
		bool operator != (const SparsePtr& ptr) const;
		bool operator < (const SparsePtr& ptr) const;
		bool operator > (const SparsePtr& ptr) const;
		bool operator <= (const SparsePtr& ptr) const;
		bool operator >= (const SparsePtr& ptr) const;

	private:
		byte_ptr m_ptr;
		int m_stride;
	};

    template<typename T>
	SparsePtr(T*) -> SparsePtr<T>;

	template<typename T>
	SparsePtr(T*, int) -> SparsePtr<T>;

	template<typename T>
	SparsePtr(T*, size_t) -> SparsePtr<T>;
} // namespace pf

namespace std
{
	template<typename T>
	struct iterator_traits<pf::SparsePtr<T>>;
} // namespace std

#include "src/utils/sparse-ptr.inl"

#endif // _PF_UTILS_SPARSE_PTR_hpp_