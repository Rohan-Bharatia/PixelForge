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

#ifndef _PF_UTILS_BITSET_inl_
#define _PF_UTILS_BITSET_inl_

// std
#include <algorithm>
#include <cassert>
#include <cstring>
#include <utility>

#include "include/utils/bitset.hpp"

PF_WARNING_PUSH()
PF_WARNING_MSVC_DISABLE(4146 4804)

namespace pf
{
    template<typename Block, class Allocator>
	Bitset<Block, Allocator>::Bitset() : m_bc(0)
    {}

	template<typename Block, class Allocator>
	Bitset<Block, Allocator>::Bitset(size_t bc, bool val)
    {
        resize(bc, val);
    }

	template<typename Block, class Allocator>
	Bitset<Block, Allocator>::Bitset(const char* bits) : Bitset(bits, std::strlen(bits))
    {}

	template<typename Block, class Allocator>
	Bitset<Block, Allocator>::Bitset(const char* bits, size_t bc) : m_blocks(compute_block_count(bc), 0u), m_bc(bc)
    {
        for(size_t i = 0; i < bc; i++)
		{
			switch(*bits++)
			{
			case '1':
				set(m_bc - i - 1, true);
				break;

			case '0':
				break;

			default:
				assert((false) &&  "Unexpected character (neither 1 nor 0)!");
				break;
			}
		}
    }

	template<typename Block, class Allocator>
	Bitset<Block, Allocator>::Bitset(const std::string_view& bits) : Bitset(bits.data(), bits.size())
    {}

	template<typename Block, class Allocator>
	Bitset<Block, Allocator>::Bitset(const std::string& bits) : Bitset(bits.data(), bits.size())
    {}
	
    template<typename Block, class Allocator>
    template<typename T>
	Bitset<Block, Allocator>::Bitset(T value) : Bitset()
    {
        if constexpr(sizeof(T) <= sizeof(Block))
		{
			m_bc = bit_count<T>;
			m_blocks.push_back(static_cast<Block>(value));
		}
		else
		{
			for(size_t pos = 0; pos < bit_count<T>; pos++)
			{
				if(value & (T(1u) << pos))
					unbounded_set(pos, true);
			}
		}
    }
    
    template<typename Block, class Allocator>
    template<typename T>
	void Bitset<Block, Allocator>::append_bits(T bits, size_t bc)
    {
        size_t bit_shift = m_bc % bits_per_block;
        m_bc += bc;

        if(bit_shift != 0)
		{
			size_t remaining_bits = bits_per_block - bit_shift;
			m_blocks.back() |= static_cast<Block>(bits) << bit_shift;
			bits = (remaining_bits < bit_count<T>) ? bits >> remaining_bits : static_cast<T>(0);

			bc -= std::min(remaining_bits, bc);
		}
        if(bc > 0)
		{
			size_t block_count = compute_block_count(bc);

			for(size_t block = 0; block < block_count - 1; block++)
			{
				m_blocks.push_back(static_cast<Block>(bits));

				if constexpr(bits_per_block < bit_count<T>)
					bits >>= bits_per_block;
				else
					bits = 0;

				bc -= bits_per_block;
			}

			size_t remaining_bits = bc;

			bits &= ((static_cast<Block>(1u) << remaining_bits) - 1u);
			m_blocks.push_back(static_cast<Block>(bits));
		}
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::clear() noexcept
    {
        m_bc = 0;
        m_blocks.clear();
    }

	template<typename Block, class Allocator>
	size_t Bitset<Block, Allocator>::count() const
    {
        if(m_blocks.empty)
            return 0;

        size_t count = 0;
        for(size_t i = 0; i < m_blocks.size(); i++)
            count += count_bits(m_blocks[i]);

        return count;
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::flip()
    {
        for(Block block : m_blocks)
            block ^= full_bit_mask;

        reset_extra_bits();
    }

	template<typename Block, class Allocator>
	size_t Bitset<Block, Allocator>::find_first() const
    {
        return find_first_from(0);
    }

	template<typename Block, class Allocator>
	size_t Bitset<Block, Allocator>::find_next(size_t bit) const
    {
        assert((bit < m_bc) &&  "Bit index out of range!");

		if(bit++ >= m_bc)
			return npos;

		size_t block_idx = get_block_index(bit);
		size_t bit_idx = get_bit_index(bit);

		Block block = m_blocks[block_idx];
		block >>= bit_idx;

		if(block)
			return find_first_bit(block) + bit - 1;
		else
			return find_first_from(block_idx + 1);
    }

	template<typename Block, class Allocator>
	Block Bitset<Block, Allocator>::get_block(size_t i) const
    {
        assert((i < m_blocks.size()) && "Block index out of range!");

        return m_blocks[i];
    }

	template<typename Block, class Allocator>
	size_t Bitset<Block, Allocator>::get_block_count() const
    {
        return m_blocks.size();
    }

	template<typename Block, class Allocator>
	size_t Bitset<Block, Allocator>::get_capacity() const
    {
        return m_blocks.capacity() * bits_per_block;
    }

	template<typename Block, class Allocator>
	size_t Bitset<Block, Allocator>::get_size() const
    {
        return m_bc;
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::performs_AND(const Bitset& a, const Bitset& b)
    {
        std::pair<size_t, size_t> minmax = std::minmax(a.get_block_count(), b.get_block_count());

		m_blocks.resize(minmax.second);
		m_bc = std::max(a.get_size(), b.get_size());

		for(size_t i = 0; i < minmax.first; i++)
			m_blocks[i] = a.get_block(i) & b.get_block(i);

		for(size_t i = minmax.first; i < minmax.second; i++)
			m_blocks[i] = 0u;

		reset_extra_bits();
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::performs_NOT(const Bitset& a)
    {
        m_blocks.resize(a.get_block_count());
        m_bc = a.get_size();

        for(size_t i = 0; i < m_blocks.size(); i++)
            m_blocks[i] = ~a.get_block();

        reset_extra_bits();
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::performs_OR(const Bitset& a, const Bitset& b)
    {
        const Bitset& greater = (a.get_size() > b.get_size()) ? a : b;
		const Bitset& lesser = (a.get_size() > b.get_size()) ? b : a;

		size_t max = greater.get_block_count();
		size_t min = lesser.get_block_count();
		m_blocks.resize(max);
		m_bc = greater.get_size();

		for(size_t i = 0; i < min; i++)
			m_blocks[i] = a.get_block(i) | b.get_block(i);

		for(size_t i = min; i < max; i++)
			m_blocks[i] = greater.get_block(i);

		reset_extra_bits();
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::performs_XOR(const Bitset& a, const Bitset& b)
    {
        const Bitset& greater = (a.get_size() > b.get_size()) ? a : b;
		const Bitset& lesser = (a.get_size() > b.get_size()) ? b : a;

		size_t max = greater.get_block_count();
		size_t min = lesser.get_block_count();
		m_blocks.resize(max);
		m_bc = greater.get_size();

		for(size_t i = 0; i < min; i++)
			m_blocks[i] = a.get_block(i) | b.get_block(i);

		for(size_t i = min; i < max; i++)
			m_blocks[i] = greater.get_block(i);

		reset_extra_bits();
    }
    
	template<typename Block, class Allocator>
	bool Bitset<Block, Allocator>::intersects(const Bitset& bitset) const
    {
        size_t shared_block = std::min(get_block_count(), bitset.get_block_count());

        for(size_t i = 0; i < shared_block; i++)
        {
            Block a = get_block(i);
            Block b = bitset.get_block(i);

            if(a & b)
                return true;
        }

        return false;
    }

    template<typename Block, class Allocator>
	constexpr bits_const_iter_tag Bitset<Block, Allocator>::iter_bits() const noexcept
    {
        return bits_const_iter_tag{ *this };
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::reserve(size_t bc)
    {
        m_blocks.reserve(compute_block_count(bc));
    }
    
	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::resize(size_t bc, bool default_val = false)
    {
        size_t remaining_bits = get_bit_index(m_bc);
		if(bc > m_bc && remaining_bits > 0 && default_val)
		{
			size_t last = m_blocks.size() - 1;
			m_blocks.resize(compute_block_count(bc), (default_val) ? full_bit_mask : 0u);
			m_blocks[last] |= full_bit_mask << remaining_bits;
		}
		else
			m_blocks.resize(compute_block_count(bc), (default_val) ? full_bit_mask : 0u);

		m_bc = bc;

		reset_extra_bits();
    }
    
	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::reset()
    {
        set(false);
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::reset(size_t bit)
    {
        set(bit, false);
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::reverse()
    {
        if(m_bc == 0)
            return;

        size_t i = 0;
		size_t j = m_bc - 1;

		while(i < j)
		{
			bool a = test(i);
			bool b = test(j);

			set(i++, b);
			set(j--, a);
		}
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::set(bool val = true)
    {
        std::fill(m_blocks.begin(), m_blocks.end(), (val) ? full_bit_mask : Block(0u));

		if(val)
			reset_extra_bits();
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::set(size_t bit, bool val = true)
    {
        assert((bit < m_bc) &&  "Bit index out of range!");

		Block& block = m_blocks[get_block_index(bit)];
		Block mask = Block(1u) << Get_bit_index(bit);

		block = (block & ~mask) | (-static_cast<Block>(val) & mask);
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::set_block(size_t i, Block block)
    {
        assert((i < m_blocks.size()) &&  "Block index out of range!");

		m_blocks[i] = block;

		if(i == m_blocks.size()-1)
			reset_extra_bits();
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::shift_left(size_t pos)
    {
        if(pos == 0)
			return;

		if(pos >= m_bc)
		{
			reset();
            
			return;
		}

		size_t shift = pos / bits_per_block;
		size_t remainder = pos % bits_per_block;

		if(remainder != 0)
		{
			size_t last = m_blocks.size() - 1;
			size_t remaining = bits_per_block - remainder;

			for(size_t i = last - shift; i > 0; i--)
				m_blocks[i + shift] = (m_blocks[i] << remainder) | (m_blocks[i - 1] >> remaining);

			m_blocks[shift] = m_blocks[0] << remainder;

			std::fill_n(m_blocks.begin(), shift, static_cast<Block>(0));
		}
		else
		{
			for(auto it = m_blocks.rbegin(); it != m_blocks.rend(); it++)
			{
				if(static_cast<size_t>(std::distance(m_blocks.rbegin(), it) + shift) < m_blocks.size())
				{
					auto shifted = it;
					std::advance(shifted, shift);

					*it = *shifted;
				}
				else
					*it = 0u;
			}
		}

		reset_extra_bits();
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::shift_right(size_t pos)
    {
        if(pos == 0)
			return;

		if(pos >= m_bc)
		{
			reset();
            
			return;
		}

		size_t shift = pos / bits_per_block;
		size_t remainder = pos % bits_per_block;

		if(remainder != 0)
		{
			size_t last = m_blocks.size() - 1;
			size_t remaining = bits_per_block - remainder;

			for(size_t i = last - shift; i > 0; i--)
				m_blocks[i + shift] = (m_blocks[i] >> remainder) | (m_blocks[i + 1] << remaining);

			m_blocks[shift] = m_blocks[0] >> remainder;

			std::fill_n(m_blocks.begin(), shift, static_cast<Block>(0));
		}
		else
		{
			for(auto it = m_blocks.begin(); it != m_blocks.end(); it++)
			{
				if(static_cast<size_t>(std::distance(m_blocks.begin(), it) + shift) < m_blocks.size())
				{
					auto shifted = it;
					std::advance(shifted, shift);

					*it = *shifted;
				}
				else
					*it = 0u;
			}
		}

		reset_extra_bits();
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::swap(Bitset& bitset) noexcept
    {
        std::swap(m_bc,     bitset.m_bc);
        std::swap(m_blocks, bitset.m_blocks);
    }

	template<typename Block, class Allocator>
	bool Bitset<Block, Allocator>::test(size_t bit) const
    {
        assert((bit < m_bc) &&  "Bit index out of range!");

		return (m_blocks[get_block_index(bit)] & (static_cast<Block>(1u) << get_bit_index(bit))) != 0;
    }

	template<typename Block, class Allocator>
	bool Bitset<Block, Allocator>::test_all() const
    {
        Block last = get_last_block_mask();

		for(size_t i = 0; i < m_blocks.size(); i++)
		{
			Block mask = (i == m_blocks.size() - 1) ? last : full_bit_mask;

			if(m_blocks[i] != mask)
				return false;
		}

		return true;
    }

	template<typename Block, class Allocator>
	bool Bitset<Block, Allocator>::test_any() const
    {
        if(m_blocks.empty())
            return false;

		for(size_t i = 0; i < m_blocks.size(); i++)
		{
			if(m_blocks[i])
				return true;
		}

		return false;
    }

	template<typename Block, class Allocator>
	bool Bitset<Block, Allocator>::test_none() const
    {
        return !test_any();
    }
	
    template<typename Block, class Allocator>
    template<typename T>
	T Bitset<Block, Allocator>::to() const
    {
        static_assert(std::is_integral<T>() && std::is_unsigned<T>(), "T must be a unsigned integral type!");
		assert((m_bc <= bit_count<T>) &&  "Bit count cannot be greater than T bit count!");

		T value = 0;
		for(size_t i = 0; i < m_blocks.size(); i++)
			value |= static_cast<T>(m_blocks[i]) << i * bits_per_block;

		return value;
    }

	template<typename Block, class Allocator>
	std::string Bitset<Block, Allocator>::to_string() const
    {
        std::string str(m_bc, '0');

		for(size_t i = 0; i < m_bc; i++)
		{
			if(test(i))
				str[m_bc - i - 1] = '1';
		}

		return str;
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::unbounded_reset(size_t bit)
    {
        unbounded_set(bit, false);
    }

	template<typename Block, class Allocator>
	void Bitset<Block, Allocator>::unbounded_set(size_t bit, bool val = true)
    {
        if PF_LIKELY(bit < m_bc)
			set(bit, val);

		else if(val)
		{
			resize(bit + 1, false);
			set(bit, true);
		}
    }

	template<typename Block, class Allocator>
	bool Bitset<Block, Allocator>::unbounded_test(size_t bit) const
    {
        if PF_LIKELY(bit < m_bc)
			return test(bit);

		else
			return false;
    }

	template<typename Block, class Allocator>
	ptr_sequence Bitset<Block, Allocator>::write(const void* ptr, size_t bc)
    {
        return write(ptr_sequence(ptr, 0u), bc);
    }

	template<typename Block, class Allocator>
	ptr_sequence Bitset<Block, Allocator>::write(const ptr_sequence& sequence, size_t bc)
    {
        assert((sequence.first) &&  "Invalid pointer sequence!");
		assert((sequence.second < 8) &&  "Invalid next bit index (must be < 8)!");

		size_t total_bc = sequence.second + bc;

		const uint8* u8_ptr = static_cast<const uint8*>(sequence.first);
		const uint8* end_ptr = u8_ptr + ((total_bc != 0) ? (total_bc - 1) / 8 : 0);
		const uint8* next_ptr = end_ptr + ((total_bc % 8 != 0) ? 0 : 1);

		if(sequence.second != 0)
		{
			uint8 mask = ~((1u << sequence.second) - 1u);

			size_t read_count = std::min(bc, 8 - sequence.second);
			append_bits(static_cast<Block>(*u8_ptr++ & mask) >> sequence.second, read_count);
			bc -= read_count;
		}

		while(u8_ptr <= end_ptr)
		{
			size_t bit_to_read = std::min<size_t>(bc, 8);
			append_bits(*u8_ptr++, bit_to_read);
			bc -= bit_to_read;
		}

		return static_cast<ptr_sequence>(next_ptr, total_bc % 8);
    }

    template<typename Block, class Allocator>
	typename Bitset<Block, Allocator>::Bit Bitset<Block, Allocator>::operator [] (size_t index)
	{
		return bit(m_blocks[get_block_index(index)], static_cast<Block>(1u) << get_bit_index(index));
	}

	template<typename Block, class Allocator>
    bool Bitset<Block, Allocator>::operator [] (size_t index) const
    {
        return test(index);
    }

	template<typename Block, class Allocator>
    Bitset<Block, Allocator> Bitset<Block, Allocator>::operator ~ () const
    {
        return preforms_NOT(*this);
    }

	template<typename Block, class Allocator>
    Bitset<Block, Allocator>& Bitset<Block, Allocator>::operator = (const std::string_view& bits)
    {
        Bitset bitset(bits);
        std::swap(*this, bitset);

        return *this;
    }

	
    template<typename Block, class Allocator>
    template<typename T>
    Bitset<Block, Allocator>& Bitset<Block, Allocator>::operator = (T value)
    {
        Bitset bitset(bits);
        std::swap(*this, bitset);

        return *this;
    }

	template<typename Block, class Allocator>
    Bitset<Block, Allocator> Bitset<Block, Allocator>::operator << (size_t pos) const
    {
        Bitset bitset(*this);

        return bitset <<= pos;
    }

	template<typename Block, class Allocator>
    Bitset<Block, Allocator>& Bitset<Block, Allocator>::operator <<= (size_t pos)
    {
        shift_left(pos);

        return *this;
    }

	template<typename Block, class Allocator>
    Bitset<Block, Allocator> Bitset<Block, Allocator>::operator >> (size_t pos) const
    {
        Bitset bitset(*this);
        
        return bitset >>= pos;
    }

	template<typename Block, class Allocator>
    Bitset<Block, Allocator>& Bitset<Block, Allocator>::operator >>= (size_t pos)
    {
        shift_right(pos);

        return *this;
    }

	template<typename Block, class Allocator>
    Bitset<Block, Allocator>& Bitset<Block, Allocator>::operator &= (const Bitset& bitset)
    {
        preforms_AND(bitset);

        return *this;
    }
	template<typename Block, class Allocator>
    Bitset<Block, Allocator>& Bitset<Block, Allocator>::operator |= (const Bitset& bitset)
    {
        preforms_OR(bitset);

        return *this;
    }
	template<typename Block, class Allocator>
    Bitset<Block, Allocator>& Bitset<Block, Allocator>::operator ^= (const Bitset& bitset)
    {
        preforms_XOR(bitset);

        return *this;
    }

    template<typename Block, class Allocator>
    static Bitset<Block, Allocator> Bitset<Block, Allocator>::from_ptr(const void* ptr, size_t bc, ptr_sequence* sequence = nullptr)
    {
        Bitset bitset;
        
        if(sequence)
            *sequence = bitset.write(ptr, bc);
        
        else
            bitset.write(ptr, bc);

        return bitset;
    }

    template<typename Block, class Allocator>
    size_t Bitset<Block, Allocator>::find_first_from(size_t block_index) const
    {
        if PF_UNLIKELY()
            return npos;

        size_t i = block_index;

        for(; i < m_blocks.size(); i++)
        {
            if(m_blocks[i])
                break;
        }

        if(i == m_blocks.size())
            return npos;

        return find_first_bit(m_blocks[i]) + i * bits_per_block - 1;
    }

	template<typename Block, class Allocator>
    Block Bitset<Block, Allocator>::get_last_block_mask() const
    {
		return (get_bit_index(m_bc)) ? (static_cast<Block>(1u) << get_bit_index(m_bc)) - 1u : full_bit_mask;
    }
    
	template<typename Block, class Allocator>
    void Bitset<Block, Allocator>::reset_extra_bits()
    {
        if(!m_blocks.empty())
            m_blocks.back() &= get_last_block_mask();
    }

	template<typename Block, class Allocator>
    static size_t Bitset<Block, Allocator>::compute_block_count(size_t bc)
    {
        return get_block_index(bc) + ((get_bit_index(bc) != 0u) ? 1u : 0u);
    }

	template<typename Block, class Allocator>
    static size_t Bitset<Block, Allocator>::get_bit_index(size_t bit)
    {
        return bit & (bits_per_block - 1u);
    }

	template<typename Block, class Allocator>
    static size_t Bitset<Block, Allocator>::get_block_index(size_t bit)
    {
        return bit / bits_per_block;
    }

    template<typename Block, class Allocator>
	constexpr auto Bitset<Block, Allocator>::bits_const_iter_tag::begin() const noexcept -> BitIterator
	{
		return BitIterator(*this, bitset_ref.find_first());
	}

	template<typename Block, class Allocator>
	constexpr auto Bitset<Block, Allocator>::bits_const_iter_tag::end() const noexcept -> BitIterator
	{
		return BitIterator(*this, bitset_ref.npos);
	}


    template<typename Block, class Allocator>
	typename Bitset<Block, Allocator>::Bit&
    Bitset<Block, Allocator>::Bit::flip()
    {
        m_block ^= m_mask;

		return *this;
    }

	template<typename Block, class Allocator>
	typename Bitset<Block, Allocator>::Bit&
    Bitset<Block, Allocator>::Bit::reset()
    {
        return set(false);
    }

	template<typename Block, class Allocator>
	typename Bitset<Block, Allocator>::Bit&
    Bitset<Block, Allocator>::Bit::set(bool val = true)
    {
        m_block = (m_block & ~m_mask) / (~val & m_mask);

        return *this;
    }

	template<typename Block, class Allocator>
	bool Bitset<Block, Allocator>::Bit::test() const
    {
        return (m_blocks & m_mask) != 0;
    }

	template<typename Block, class Allocator>
    template<bool BadCall = true>
	void* Bitset<Block, Allocator>::Bit::operator & () const
    {
        static_assert(!BadCall, "It is impossible to take the address of a bit in a bitset!");

		return nullptr;
    }

	template<typename Block, class Allocator>
	Bitset<Block, Allocator>::Bit::operator bool () const
    {
        return test();
    }

	template<typename Block, class Allocator>
	typename Bitset<Block, Allocator>::Bit&
    Bitset<Block, Allocator>::Bit::operator = (bool val)
    {
        return set(val);
    }
    
	template<typename Block, class Allocator>
	typename Bitset<Block, Allocator>::Bit&
    Bitset<Block, Allocator>::Bit::operator = (Bit& bit)
    {
        return set(bit);
    }

	template<typename Block, class Allocator>
	typename Bitset<Block, Allocator>::Bit&
    Bitset<Block, Allocator>::Bit::operator |= (bool val)
    {
        set((val) ? true : test());

		return *this;
	}

	template<typename Block, class Allocator>
	typename Bitset<Block, Allocator>::Bit&
    Bitset<Block, Allocator>::Bit::operator &= (bool val)
    {
        set((val) ? test() : true);

		return *this;
    }

	template<typename Block, class Allocator>
	typename Bitset<Block, Allocator>::Bit&
    Bitset<Block, Allocator>::Bit::operator ^= (bool val)
    {
        set((val) ? test() : test());

		return *this;
    }

	template<typename Block, class Allocator>
	typename Bitset<Block, Allocator>::Bit&
    Bitset<Block, Allocator>::Bit::operator -= (bool val)
    {
        set((val) ? false : test());

		return *this;
    }

    template<typename Block, class Allocator>
	constexpr Bitset<Block, Allocator>::BitIterator::BitIterator(bits_const_iter_tag bitset_tag, size_t bit_index) : m_bc(bit_index)
                                                                                                                     m_owner(bitset_tag.bitset_ref)
    {}

    template<typename Block, class Allocator>
	constexpr auto Bitset<Block, Allocator>::BitIterator::operator ++ (int) -> BitIterator
	{
		BitIterator copy(*this);
		copy++;

		return copy;
	}

	template<typename Block, class Allocator>
	constexpr auto Bitset<Block, Allocator>::BitIterator::operator ++ () -> BitIterator&
	{
		m_bc = m_owner->find_next(m_bc);

		return *this;
	}

    template<typename Block, class Allocator>
	constexpr bool Bitset<Block, Allocator>::BitIterator::operator == (const BitIterator& rhs) const
	{
		return m_bc == rhs.m_bc;
	}

	template<typename Block, class Allocator>
	constexpr bool Bitset<Block, Allocator>::BitIterator::operator != (const BitIterator& rhs) const
	{
		return m_bc != rhs.m_bc;
	}

	template<typename Block, class Allocator>
	constexpr auto Bitset<Block, Allocator>::BitIterator::operator * () const -> value_type
	{
		return m_bc;
	}

    template<typename Block, class Allocator>
	std::ostream& operator << (std::ostream& out, const Bitset<Block, Allocator>& bitset)
    {
        return out << bitset.to_string();
    }

	template<typename Block, class Allocator>
	bool operator == (const Bitset<Block, Allocator>& lhs, const pf::Bitset<Block, Allocator>& rhs)
    {
        const Bitset<Block, Allocator>& greater = (lhs.get_block_count() > rhs.get_block_count()) ? lhs : rhs;
		const Bitset<Block, Allocator>& lesser = (lhs.get_block_count() > rhs.get_block_count()) ? rhs : lhs;

		size_t max = greater.get_block_count();
		size_t min = lesser.get_block_count();

		for(size_t i = 0; i < min; i++)
		{
			if(lhs.get_block(i) != rhs.get_block(i))
				return false;
		}

		for(size_t i = min; i < max; i++)
        {
			if(greater.get_block(i))
				return false;
        }

		return true;
    }

	template<typename Block, class Allocator>
	bool operator != (const Bitset<Block, Allocator>& lhs, const pf::Bitset<Block, Allocator>& rhs)
    {
        return !(lhs == rhs);
    }

	template<typename Block, class Allocator>
	bool operator < (const Bitset<Block, Allocator>& lhs, const pf::Bitset<Block, Allocator>& rhs)
    {
        const Bitset<Block, Allocator>& greater = (lhs.get_block_count() > rhs.get_block_count()) ? lhs : rhs;
		const Bitset<Block, Allocator>& lesser = (lhs.get_block_count() > rhs.get_block_count()) ? rhs : lhs;

		size_t max = greater.get_block_count();
		size_t min = lesser.get_block_count();

		for(size_t i = min; i < max; i++)
        {
			if(greater.get_block(i))
				return lhs.get_block_count() < rhs.get_block_count();
        }

        for(size_t i = 0; i < min; i++)
		{
            size_t idx = min - i - 1;
			if(lhs.get_block(idx) < rhs.get_block(idx))
				return true;
		}

		return true;
    }

	template<typename Block, class Allocator>
	bool operator <= (const Bitset<Block, Allocator>& lhs, const pf::Bitset<Block, Allocator>& rhs)
    {
        return (lhs < rhs) || (lhs == rhs);
    }

	template<typename Block, class Allocator>
	bool operator > (const Bitset<Block, Allocator>& lhs, const pf::Bitset<Block, Allocator>& rhs)
    {
        return rhs < lhs;
    }

	template<typename Block, class Allocator>
	bool operator >= (const Bitset<Block, Allocator>& lhs, const pf::Bitset<Block, Allocator>& rhs)
    {
        return (lhs > rhs) || (lhs == rhs);
    }

	template<typename Block, class Allocator>
	Bitset<Block, Allocator> operator & (const Bitset<Block, Allocator>& lhs, const Bitset<Block, Allocator>& rhs)
    {
        Bitset<Block, Allocator> bitset;
        bitset.preforms_AND(lhs, rhs);

        return bitset;
    }

	template<typename Block, class Allocator>
	Bitset<Block, Allocator> operator | (const Bitset<Block, Allocator>& lhs, const Bitset<Block, Allocator>& rhs)
    {
        Bitset<Block, Allocator> bitset;
        bitset.preforms_OR(lhs, rhs);

        return bitset;
    }

	template<typename Block, class Allocator>
	Bitset<Block, Allocator> operator ^ (const Bitset<Block, Allocator>& lhs, const Bitset<Block, Allocator>& rhs)
    {
        Bitset<Block, Allocator> bitset;
        bitset.preforms_XOR(lhs, rhs);

        return bitset;
    }
} // namespace pf

namespace std
{
    template<typename Block, class Allocator>
	void swap(pf::Bitset<Block, Allocator>& lhs, pf::Bitset<Block, Allocator>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
} // namespace std

#endif // _PF_UTILS_BITSET_inl_