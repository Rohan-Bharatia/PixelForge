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

// std
#include <functional>
#include <memory>
#include <vector>

#define pf_detail_signal(keyword, signal_name, ...) using signal_name ## Type = pf::Signal<__VA_ARGS__>; \
                                                    keyword signal_name ## Type signal_name

#define pf_signal(signal_name, ...) pf_detail_signal(mutable, signal_name, __VA_ARGS__)
#define pf_static_signal(signal_name, ...) pf_detail_signal(static, signal_name, __VA_ARGS__)
#define pf_static_signal_impl(_class, signal_name) _class :: signal_name ## Type _class :: signal_name

#define pf_slot_type(_class, signal_name) _class::signal_name ## Type::ConnectionGuard
#define pf_slot(_class, signal_name, slot_name) pf_slot_type(_class, signal_name) slot_name

namespace pf
{
    template<typename... Args>
	class Signal
	{
	public:
		using callback = std::function<void(Args...)>;
		class Connection;
		class ConnectionGuard;

		Signal();
		Signal(const Signal&);
		Signal(Signal&& signal) noexcept;
		~Signal() = default;

		void clear();

		Connection connect(const callback& func);
		Connection connect(callback&& func);
		template<typename O>
        Connection connect(O& object, void (O::*method)(Args...));
		template<typename O>
        Connection connect(O* object, void (O::*method)(Args...));
		template<typename O>
        Connection connect(const O& object, void (O::*method)(Args...) const);
		template<typename O>
        Connection connect(const O* object, void (O::*method)(Args...) const);

		void operator () (Args... args) const;

		Signal& operator = (const Signal&);
		Signal& operator = (Signal&& signal) noexcept;

	private:
		struct Slot;

		using slot_ptr        = std::shared_ptr<Slot>;
		using slot_list       = std::vector<slot_ptr>;
		using slot_list_index = typename SlotList::size_type;

		struct Slot
		{
			Slot(Signal* me) : signal(me)
			{}

			callback call;
			Signal* signal;
			slot_list_index index;
		};

		void disconnect(const slot_ptr& slot) noexcept;

		slot_list m_slots;
		mutable slot_list_index m_slot_iterator;
	};

    template<typename... Args>
	class Signal<Args...>::Connection
	{
		using base = Signal<Args...>;
		friend base;

	public:
		Connection() = default;
		Connection(const Connection& connection) = default;
		Connection(Connection&& connection) noexcept;
		~Connection() = default;

		template<typename... ConnectArgs>
		void connect(base& signal, ConnectArgs&&... args);
		void disconnect() noexcept;

		bool is_connected() const;

		Connection& operator = (const Connection& connection) = default;
		Connection& operator = (Connection&& connection) noexcept;

	private:
		connection(const slot_ptr& slot);

		std::weak_ptr<Slot> m_ptr;
	};

    template<typename... Args>
	class Signal<Args...>::ConnectionGuard
	{
		using base = Signal<Args...>;
		using Connection = typename base::Connection;

	public:
		ConnectionGuard() = default;
		ConnectionGuard(const Connection& connection);
		ConnectionGuard(const ConnectionGuard& connection) = delete;
		ConnectionGuard(Connection&& connection);
		ConnectionGuard(ConnectionGuard&& connection) noexcept = default;
		~ConnectionGuard();

		template<typename... ConnectArgs>
		void connect(base& signal, ConnectArgs&&... args);
		void disconnect() noexcept;

		Connection& get_connection();

		bool is_connected() const;

		ConnectionGuard& operator = (const Connection& connection);
		ConnectionGuard& operator = (const ConnectionGuard& connection) = delete;
		ConnectionGuard& operator = (Connection&& connection);
		ConnectionGuard& operator = (ConnectionGuard&& connection) noexcept;

	private:
		Connection m_connection;
	};
} // namespace pf

#include "src/utils/signal.inl"

#endif // _PF_UTILS_SIGNAL_hpp_