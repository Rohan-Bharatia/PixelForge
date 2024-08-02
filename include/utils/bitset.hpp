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

#ifndef _PF_UTILS_BITSET_hpp_
#define _PF_UTILS_BITSET_hpp_

// std
#include <limits>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "prerequisites.h"
#include "math-utils.hpp"

namespace pf
{
    template<typename Block = uint32, class Allocator = std::allocator<Block>>
    class Bitset
    {
        static_assert(std::is_integral<Block>::value && std::is_unsigned<Block>::value, "Block must be a unsigned integral type!");

    public:
        Bitset();
		explicit Bitset(size_t bc, bool val);
		explicit Bitset(const char* bits);
		Bitset(const char* bits, size_t bc);
		Bitset(const Bitset& bitset) = default;
		explicit Bitset(const std::string_view& bits);
		explicit Bitset(const std::string& bits);
		template<typename T>
        Bitset(T value);
		Bitset(Bitset&& bitset) noexcept = default;
		~Bitset() noexcept = default;

        template<typename T>
        void append_bits(T bits, size_t bc);

		void clear() noexcept;
		size_t count() const;
		void flip();

		size_t find_first() const;
		size_t find_next(size_t bit) const;

		Block get_block(size_t i) const;
		size_t get_block_count() const;
		size_t get_capacity() const;
		size_t get_size() const;

		void performs_AND(const Bitset& a, const Bitset& b);
		void performs_NOT(const Bitset& a);
		void performs_OR(const Bitset& a, const Bitset& b);
		void performs_XOR(const Bitset& a, const Bitset& b);

		bool intersects(const Bitset& bitset) const;

		constexpr bits_const_iter_tag iter_bits() const noexcept;

		void reserve(size_t bc);
		void resize(size_t bc, bool default_val = false);

		void reset();
		void reset(size_t bit);

		void reverse();

		void set(bool val = true);
		void set(size_t bit, bool val = true);
		void set_block(size_t i, Block block);

		void shift_left(size_t pos);
		void shift_right(size_t pos);

		void swap(Bitset& bitset) noexcept;

		bool test(size_t bit) const;
		bool test_all() const;
		bool test_any() const;
		bool test_none() const;

		template<typename T>
        T to() const;
		std::string to_string() const;

		void unbounded_reset(size_t bit);
		void unbounded_set(size_t bit, bool val = true);
		bool unbounded_test(size_t bit) const;

		ptr_sequence write(const void* ptr, size_t bc);
		ptr_sequence write(const ptr_sequence& sequence, size_t bc);

		Bit operator [] (size_t index);
		bool operator [] (size_t index) const;

		Bitset operator ~ () const;

		Bitset& operator = (const Bitset& bitset) = default;
		Bitset& operator = (const std::string_view& bits);
		template<typename T>
        Bitset& operator = (T value);
		Bitset& operator = (Bitset&& bitset) noexcept = default;

		Bitset operator << (size_t pos) const;
		Bitset& operator <<= (size_t pos);

		Bitset operator >> (size_t pos) const;
		Bitset& operator >>= (size_t pos);

		Bitset& operator &= (const Bitset& bitset);
		Bitset& operator |= (const Bitset& bitset);
		Bitset& operator ^= (const Bitset& bitset);

		static constexpr Block full_bit_mask = std::numeric_limits<Block>::max();
		static constexpr size_t bits_per_block = bit_count<Block>;
		static constexpr size_t npos = std::numeric_limits<size_t>::max();

		static Bitset from_ptr(const void* ptr, size_t bc, ptr_sequence* sequence = nullptr);

		struct bits_const_iter_tag
		{
			constexpr BitIterator begin() const noexcept;
			constexpr BitIterator end() const noexcept;

			const Bitset& bitset_ref;
		};

		class Bit;
		class BitIterator;
		using ptr_sequence = std::pair<const void*, size_t>;
		struct bits_const_iter_tag;

    private:
        size_t find_first_from(size_t block_index) const;
		Block get_last_block_mask() const;
		void reset_extra_bits();

		static size_t compute_block_count(size_t bc);
		static size_t get_bit_index(size_t bit);
		static size_t get_block_index(size_t bit);

		std::vector<Block, Allocator> m_blocks;
		size_t m_bc;
    };

    template<typename Block, class Allocator>
	class Bitset<Block, Allocator>::Bit
	{
	    friend Bitset<Block, Allocator>;

	public:
		Bit(const Bit& bit) = default;

		Bit& flip();
		Bit& reset();
		Bit& set(bool val = true);
		bool test() const;

		template<bool BadCall = true>
		void* operator & () const;

		operator bool () const;
		Bit& operator = (bool val);
		Bit& operator = (const Bit& bit);

		Bit& operator |= (bool val);
		Bit& operator &= (bool val);
		Bit& operator ^= (bool val);
		Bit& operator -= (bool val);

	private:
	    Bit(Block& block, Block mask);

		Block& m_block;
		Block m_mask;
	};

    template<typename Block, class Allocator>
	class Bitset<Block, Allocator>::BitIterator
	{
		friend Bitset;

	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = size_t;

		constexpr BitIterator(const BitIterator&) = default;
		constexpr BitIterator(BitIterator&&) noexcept = default;

		constexpr BitIterator& operator = (const BitIterator&) = default;
		constexpr BitIterator& operator = (BitIterator&&) noexcept = default;

		constexpr BitIterator operator ++ (int);
		constexpr BitIterator& operator ++ ();

		constexpr bool operator == (const BitIterator& rhs) const;
		constexpr bool operator != (const BitIterator& rhs) const;
		constexpr value_type operator * () const;

	private:
		constexpr BitIterator(bits_const_iter_tag bitset_tag, size_t bc);

		size_t m_bc;
		const Bitset* m_owner;
	};

    template<typename Block, class Allocator>
	std::ostream& operator << (std::ostream& out, const Bitset<Block, Allocator>& bitset);

	template<typename Block, class Allocator>
	bool operator == (const Bitset<Block, Allocator>& lhs, const pf::Bitset<Block, Allocator>& rhs);

	template<typename Block, class Allocator>
	bool operator != (const Bitset<Block, Allocator>& lhs, const pf::Bitset<Block, Allocator>& rhs);

	template<typename Block, class Allocator>
	bool operator < (const Bitset<Block, Allocator>& lhs, const pf::Bitset<Block, Allocator>& rhs);

	template<typename Block, class Allocator>
	bool operator <= (const Bitset<Block, Allocator>& lhs, const pf::Bitset<Block, Allocator>& rhs);

	template<typename Block, class Allocator>
	bool operator > (const Bitset<Block, Allocator>& lhs, const pf::Bitset<Block, Allocator>& rhs);

	template<typename Block, class Allocator>
	bool operator >= (const Bitset<Block, Allocator>& lhs, const pf::Bitset<Block, Allocator>& rhs);

	template<typename Block, class Allocator>
	Bitset<Block, Allocator> operator & (const Bitset<Block, Allocator>& lhs, const Bitset<Block, Allocator>& rhs);

	template<typename Block, class Allocator>
	Bitset<Block, Allocator> operator | (const Bitset<Block, Allocator>& lhs, const Bitset<Block, Allocator>& rhs);

	template<typename Block, class Allocator>
	Bitset<Block, Allocator> operator ^ (const Bitset<Block, Allocator>& lhs, const Bitset<Block, Allocator>& rhs);
} // namespace pf

namespace std
{
	template<typename Block, class Allocator>
	void swap(pf::Bitset<Block, Allocator>& lhs, pf::Bitset<Block, Allocator>& rhs) noexcept;
} // namespace std

#include "src/utils/bitset.inl"

#endif // _PF_UTILS_BITSET_hpp_