#include <iostream>
#include <memory>
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
#include "Controller.h"


Controller& Controller::get_controller() {
	static Controller controller;
	return controller;
}
void Controller::operations() {
	std::string operation;
	while (operation != "exit") {
		book.print_book();
		std::cout << "Enter operation: 1 - 'add stock', 2 - 'add trader', 3 - 'add trader balance', 4 - 'by stock', 5 - 'print trader info' or 0 - 'exit': ";
		std::getline(std::cin, operation);
		if ((operation == "add stock") || (operation == "1")) {
			std::string company_name;
			int company_balance;
			std::cout << "Company name: ";
			std::getline(std::cin, company_name);
			std::cout << "Company balance: ";
			std::cin >> company_balance;
			stocks[company_name] = std::make_unique<Stock>(company_name, company_balance);
			if (stocks.find(company_name) != stocks.end()) {
    				Stock& stock = *(stocks[company_name]);
    				book.new_stock(&stock);
			} else {
    				std::cout << "Unknown company: " << company_name << std::endl;
			}
		} else if ((operation == "add trader") || (operation == "2")) {
			std::string trader_name;
			std::string trader_id;
			std::cout << "Trader name: ";
			std::getline(std::cin, trader_name);
			std::cout << "Trader ID(12 symbol number): ";
			std::cin >> trader_id;
			traders[trader_name] = std::make_unique<Trader>(trader_name, trader_id);
		} else if ((operation == "add trader balance") || (operation == "3")) {
			std::string traders_name;
			int traders_balance;
			std::cout << "Trader name: ";
			std::getline(std::cin, traders_name);
			std::cout << "Trader balance: ";
			std::cin >> traders_balance;
			if (traders.find(traders_name) != traders.end()) {
    				Trader& trader = *(traders[traders_name]);
    				trader.add_balance(traders_balance);
    				trader.start_trading_thread(book);
			} else {
    				std::cout << "Unknown trader: " << traders_name << std::endl;
			}
		} else if ((operation == "by stock") || (operation == "4"))  {
			std::string name;
			std::string type;
			std::string company;
			int count;
			std::cout << "Trader name: ";
			std::getline(std::cin, name);
			std::cout << "Type of order(Market or Limit): ";
			std::cin >> type;
			std::cout << "Company name: ";
			std::getline(std::cin, company);
			std::cout << "Count of bying stocks: ";
			std::cin >> count;
			if (traders.find(name) != traders.end()) {
    				Trader& trader = *(traders[name]);
    				trader.by_stock(book, type, company, count);
			} else {
    				std::cout << "Unknown trader: " << name << std::endl;
			}
		} else if ((operation == "print trader info") || (operation == "5")) {
			std::string traderName;
			std::cout << "Trader name: ";
			std::getline(std::cin, traderName);
			if (traders.find(traderName) != traders.end()) {
    				Trader& trader = *(traders[traderName]);
    				trader.print_trader_info();
			} else {
    				std::cout << "Unknown trader: " << traderName << std::endl;
			}
		} else if ((operation == "exit") || (operation == "0")) {
			for (auto it = traders.begin(); it != traders.end(); ++it) {
        			const std::string& traderName = it->first;
        			Trader& traderInstance = *(it->second);
        			traderInstance.stop_trading_thread();
    			}				
    			break;
		} else {
			std::cout << "Invalid input, please try again.\n";
		}
	}
}

Controller::Controller() {};
Controller::~Controller() {};
Controller::Controller(const Controller&) = delete;
Controller& Controller::operator=(const Controller&) = delete;


