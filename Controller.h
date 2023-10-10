#ifndef CONTROLLER_H
#define CONTROLLER_H
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

class Controller
{
public:
	static Controller& get_controller();
	void operations();
	
private:
	Controller();
	~Controller();
	Controller(const Controller&);
	Controller& operator=(const Controller&);
	
private:
	OrderBook& book = OrderBook::get_book();
	std::unordered_map<std::string, std::unique_ptr<Trader>> traders;
	std::unordered_map<std::string, std::unique_ptr<Stock>> stocks;
};

#endif
