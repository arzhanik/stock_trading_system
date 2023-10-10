#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "LimitFactory.h"
#include "OrderFactory.h"
#include "LimitOrder.h"
#include "Order.h"


LimitOrder::LimitOrder(double price) 
	: limit_price{price} 
{}


std::unordered_map<std::string, std::unordered_map<int, double>> LimitOrder::get_order_list() const { return order_list; }
void LimitOrder::make_order(std::string company_name, int stock_count) /*override*/ {
        order_list[company_name][stock_count] = limit_price;
}

