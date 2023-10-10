#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "LimitFactory.h"
#include "MarketOrder.h"
#include "OrderBook.h"
#include "OrderFactory.h"
#include "Stock.h"
#include "LimitOrder.h"
#include "MarketFactory.h"
#include "Order.h"
#include "Trader.h"


OrderBook& OrderBook::get_book() {
        static OrderBook instance;
        return instance;
}


void OrderBook::new_stock(Stock* stock) {
        if (stock->get_stock_count() == 0) { return; }
        order_book[stock] = stock->get_stock_count();
}


void OrderBook::change_stock(Stock* stock) {
        if(order_book.find(stock) != order_book.end()) {
                if (stock->get_stock_count() == 0) {
                        order_book.erase(stock);
                        return;
                }
                order_book[stock] = stock->get_stock_count();
        }
}


std::unordered_map<Stock*, int> OrderBook::get_order_book() { return order_book; }

		
Stock* OrderBook::get_stock(std::string company) const {
        for (const auto& pair : order_book) {
                Stock* stockPtr = pair.first;
                if (stockPtr && stockPtr->get_company_name() == company) {
                        return stockPtr;
                }
        }
        return nullptr;
}


bool OrderBook::order_type(const std::string& order, const std::string& company, int count) {		
	if (get_stock(company) == nullptr) { 
		std::cout << "No such a company available. \n";
		return false;
	}
	m_stock = get_stock(company);
        std::unique_ptr<OrderFactory> market_factory = std::make_unique<MarketFactory>();
        std::unique_ptr<OrderFactory> limit_factory = std::make_unique<LimitFactory>();
        std::unique_ptr<Order> market_order = market_factory->create();
        std::unique_ptr<Order> limit_order = limit_factory->create();
        if (order == "Market") {
		if (m_stock->get_stock_count() - count >= 0) {
                	market_order->make_order(company, count);
                	auto marketOrderData = dynamic_cast<MarketOrder*>(market_order.get());
                	if (marketOrderData) {
                        	std::cout << "Choosen Market order type: ";
                        	for (const auto &pair : marketOrderData->get_order()) {
                               		std::cout << pair.first << " - " << pair.second << " ";
                        	}
                        	std::cout << std::endl;
                	}
			m_stock->change_stock_count(m_stock->get_stock_count() - count);
			return true;
		}
		if (m_stock->get_stock_count() == 0) {
			order_book.erase(m_stock);
		}
		if (m_stock->get_stock_count() - count < 0) {
			std::cout << "Invalid count of stocks.\n";
			return false;
		}

        }

        if (order == "Limit") {
                std::cout << "Please mark limit value: ";
                double limit_value;
                std::cin >> limit_value;
                limit_order->make_order(company, count);
                auto limitOrderData = dynamic_cast<LimitOrder*>(limit_order.get());
                if (limitOrderData) {
                        std::cout << "Choosen Limit order type: ";
                        for (const auto &pair : limitOrderData->get_order_list()) {
                                for (const auto &nested_pair : pair.second) {
                                        std::cout << pair.first << " - " << nested_pair.first << " - " << nested_pair.second << " ";
                                }
                        }
                        std::cout << std::endl;
			if ((m_stock->get_stock_count() > 0) && (m_stock->get_stock_value() == limit_value)) { 
                        	m_stock->change_stock_count(m_stock->get_stock_count() - count);
                	}
			if (m_stock->get_stock_count() == 0) { order_book.erase(m_stock); }
        	}
       	}
	return true;
}


void OrderBook::print_book() {
	std::cout << "\n\n\nOrder book with all available trades: Company name, stock value, available count of stocks. Start.\n";
	for (const auto& pair : order_book) {
        	m_stock = pair.first;
        	m_count = pair.second;
		if (m_count != 0) {
        		std::cout << "Company: " << m_stock->get_company_name()
                  		<< ", Value: " << m_stock->get_stock_value()
                  		<< ", Count: " << m_stock->get_stock_count() << std::endl;
		}
    	}
	std::cout << "End. \n\n\n";
}


OrderBook::OrderBook() {};


OrderBook::~OrderBook() {};


OrderBook::OrderBook(Stock* stock) {
        m_stock = stock;
        order_book[stock] = stock->get_stock_count();
}

	
OrderBook::OrderBook(const OrderBook& orderbook) = delete;


OrderBook OrderBook::operator=(const OrderBook& orderbook) = delete;

