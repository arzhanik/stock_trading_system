#include <iostream>
#include <string>
#include <unordered_map>
#include <thread>
#include <mutex>
#include "LimitFactory.h"
#include "MarketOrder.h"
#include "OrderBook.h"
#include "OrderFactory.h"
#include "Stock.h"
#include "LimitOrder.h"
#include "MarketFactory.h"
#include "Order.h"
#include "Trader.h"


Trader::Trader(const std::string& name, const std::string& id) {
	if (valid_trader(name, id)) {
		trader_name = name;
		trader_id = id;
	}
}


std::unique_ptr<Trader> Trader::create_trader_by_name(const std::string& name, const std::string& id) {
        return std::make_unique<Trader>(name, id);
    }


bool Trader::valid_trader(const std::string& name, const std::string& id) {
	if ((name[0] < 65) || (name[0] > 90)) {
		std::cout << "Please input valid name, starting capital letter.\n";
		return false;
	}
	for (int i = 1; name[i] != '\0'; ++i) {
		if ((name[i] < 97) || (name[i] > 122)) {
			std::cout << "Please input correct name.\n";
			return false;
		}
	}
        if (id.size() != 12) {
                std::cout << "ID length should be 12.\n";
                return false;
        }
        for (int i = 0; id[i] != '\0'; ++i) {
                if ((id[i] < 48) || (id[i] > 57)) {
                        std::cout << "Please input only numbers.\n";
                        return false;
                }
        }
	return true;
}


void Trader::add_balance(double cash) { trader_balance += cash; }


void Trader::by_stock(OrderBook& book, std::string order_type, std::string company, int count) {
	std::lock_guard<std::mutex> lock(trader_mutex);
	if ((book.order_type(order_type, company, count)) && 
			(trader_balance >= (book.get_stock(company))->get_stock_value() / 100 * count)) { 
		trader_property[company] = count;
		trader_balance -= (book.get_stock(company))->get_stock_value() / 100 * count;
		std::cout << trader_name << "\tSuccessed bying.\n";
		return;
	}
	std::cout << trader_name << "\tOrder not successed.\n";
}


void Trader::print_trader_info() const {
        std::cout << "Trader name: " << trader_name << "\t Trader balance: " <<
                trader_balance << "\tTrader property: \n";
        for (const auto& pair : trader_property) {
                std::cout << "Company: " << pair.first << ", Trade count: " << pair.second << std::endl;
        }
}


void Trader::start_trading_thread(OrderBook& book) {
        trading_thread = std::thread([this, &book]() {
            	while (trading_enabled) {
                	std::this_thread::sleep_for(std::chrono::seconds(2)); 
            	}
        });
}


void Trader::stop_trading_thread() {
        trading_enabled = false;
        if (trading_thread.joinable()) {
            	trading_thread.join();
        }
}

