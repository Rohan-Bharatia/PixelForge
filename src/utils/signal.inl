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

#ifndef _PF_UTILS_SIGNAL_hpp_
#define _PF_UTILS_SIGNAL_hpp_

#include "include/utils/signal.hpp"

namespace pf
{
    template<typename... Args>
	Signal<Args...>::Signal() :	m_slot_iterator(0)
	{}

	template<typename... Args>
	Signal<Args...>::Signal(const Signal&) : Signal()
	{}

	template<typename... Args>
	Signal<Args...>::Signal(Signal&& signal) noexcept
	{
		operator = (std::move(signal));
	}

    template<typename... Args>
	void Signal<Args...>::clear()
	{
		m_slots.clear();
		m_slot_iterator = 0;
	}

    template<typename... Args>
	typename Signal<Args...>::Connection Signal<Args...>::connect(const callback& func)
	{
		return connect(callback(func));
	}

	template<typename... Args>
	typename Signal<Args...>::Connection Signal<Args...>::connect(callback&& func)
	{
		assert((func) &&  "Invalid function!");

		bool reset = (m_slot_iterator >= m_slots.size());

		auto temp = std::make_shared<Slot>(this);
		temp->call = std::move(func);
		temp->index = m_slots.size();

		m_slots.emplace_back(std::move(temp));

		if(reset)
			m_slot_iterator = m_slots.size();

		return connection(m_slots.back());
	}

	template<typename... Args>
	template<typename O>
	typename Signal<Args...>::Connection Signal<Args...>::connect(O& object, void (O::*method) (Args...))
	{
		return connect([&object, method] (Args&&... args)
		{
			return (object .* method) (std::forward<Args>(args)...);
		});
	}

	template<typename... Args>
	template<typename O>
	typename Signal<Args...>::Connection Signal<Args...>::connect(O* object, void (O::*method)(Args...))
	{
		return connect([object, method] (Args&&... args)
		{
			return (object ->* method) (std::forward<Args>(args)...);
		});
	}

	template<typename... Args>
	template<typename O>
	typename Signal<Args...>::Connection Signal<Args...>::connect(const O& object, void (O::*method) (Args...) const)
	{
		return connect([&object, method] (Args&&... args)
		{
			return (object .* method) (std::forward<Args>(args)...);
		});
	}

	template<typename... Args>
	template<typename O>
	typename Signal<Args...>::Connection Signal<Args...>::connect(const O* object, void (O::*method)(Args...) const)
	{
		return connect([object, method] (Args&&... args)
		{
			return (object ->* method) (std::forward<Args>(args)...);
		});
	}

    template<typename... Args>
	void Signal<Args...>::operator () (Args... args) const
	{
		for(m_slot_iterator = 0; m_slot_iterator < m_slots.size(); m_slot_iterator++)
			m_slots[m_slot_iterator]->call(args...);
	}

	template<typename... Args>
	Signal<Args...>& Signal<Args...>::operator = (const Signal&)
	{
		return *this;
	}

	template<typename... Args>
	Signal<Args...>& Signal<Args...>::operator = (Signal&& signal) noexcept
	{
		m_slots = std::move(signal.m_slots);
		m_slot_iterator = signal.m_slot_iterator;

		for(slot_ptr& slot : m_slots)
			slot->signal = this;

		return *this;
	}

	template<typename... Args>
	void Signal<Args...>::disconnect(const slot_ptr& slot) noexcept
	{
		assert((slot) &&  "Invalid slot pointer!");
		assert((slot->index < m_slots.size()) &&  "Invalid slot index!");
		assert((slot->signal == this) &&  "Slot is not attached to this signal!");

		if(m_slot_iterator >= (m_slots.size() - 1) || slot->index > m_slot_iterator)
		{
			slot_ptr& new_slot = m_slots[slot->index];
			new_slot = std::move(m_slots.back());
			new_slot->index = slot->index;
		}
		else
		{
			slot_ptr& current = m_slots[m_slot_iterator];
			slot_ptr& new_slot = m_slots[slot->index];

			new_slot = std::move(current);
			new_slot->index = slot->index;

			current = std::move(m_slots.back());
			current->index = m_slot_iterator;

			m_slot_iterator--;
		}

		m_slots.pop_back();
	}

    template<typename... Args>
	Signal<Args...>::Connection::connection(Connection&& connection) noexcept : m_ptr(std::move(connection.m_ptr))
	{
		connection.m_ptr.reset();
	}

	template<typename... Args>
	Signal<Args...>::Connection::Connection(const slot_ptr& slot) : m_ptr(slot)
	{}

	template<typename... Args>
	template<typename... ConnectArgs>
	void Signal<Args...>::Connection::connect(BaseClass& signal, ConnectArgs&&... args)
	{
		operator = (signal.connect(std::forward<ConnectArgs>(args)...));
	}

	template<typename... Args>
	void Signal<Args...>::Connection::Disconnect() noexcept
	{
		if(slot_ptr ptr = m_ptr.lock())
			ptr->signal->disconnect(ptr);
	}

	template<typename... Args>
	bool Signal<Args...>::Connection::is_connected() const
	{
		return !m_ptr.expired();
	}

    template<typename... Args>
	typename Signal<Args...>::Connection& Signal<Args...>::Connection::operator = (Connection&& connection) noexcept
	{
		m_ptr = std::move(connection.m_ptr);
		connection.m_ptr.reset();

		return *this;
	}

    template<typename... Args>
	Signal<Args...>::ConnectionGuard::ConnectionGuard(const Connection& connection) : m_connection(connection)
	{}

	template<typename... Args>
	Signal<Args...>::ConnectionGuard::ConnectionGuard(Connection&& connection) : m_connection(std::move(connection))
	{}

	template<typename... Args>
	Signal<Args...>::ConnectionGuard::~ConnectionGuard()
	{
		m_connection.Disconnect();
	}

	template<typename... Args>
	template<typename... ConnectArgs>
	void Signal<Args...>::ConnectionGuard::connect(BaseClass& signal, ConnectArgs&&... args)
	{
		m_connection.disconnect();
		m_connection.connect(signal, std::forward<ConnectArgs>(args)...);
	}

	template<typename... Args>
	void Signal<Args...>::ConnectionGuard::Disconnect() noexcept
	{
		m_connection.disconnect();
	}

	template<typename... Args>
	typename Signal<Args...>::Connection& Signal<Args...>::ConnectionGuard::get_disconnection()
	{
		return m_connection;
	}

	template<typename... Args>
	bool Signal<Args...>::ConnectionGuard::is_connected() const
	{
		return m_connection.is_connected();
	}

    template<typename... Args>
	typename Signal<Args...>::ConnectionGuard& Signal<Args...>::ConnectionGuard::operator = (const Connection& connection)
	{
		m_connection.disconnect();
		m_connection = connection;

		return *this;
	}

	template<typename... Args>
	typename Signal<Args...>::ConnectionGuard& Signal<Args...>::ConnectionGuard::operator = (Connection&& connection)
	{
		if(&connection != this)
		{
			m_connection.disconnect();
			m_connection = std::move(connection);
		}

		return *this;
	}

	template<typename... Args>
	typename Signal<Args...>::ConnectionGuard& Signal<Args...>::ConnectionGuard::operator = (ConnectionGuard&& connection) noexcept
	{
		if(&connection != this)
		{
			m_connection.disconnect();
			m_connection = std::move(connection.m_connection);
		}

		return *this;
	}
} // namespace pf

#endif // _PF_UTILS_SIGNAL_hpp_