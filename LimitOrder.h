#ifndef LIMIT_ORDER_H
#define LIMIT_ORDER_H
#include <unordered_map>
#include <string>
#include "Order.h"
#include "Stock.h"

class LimitOrder : public Order
{
public:
    	LimitOrder(double price);
    	std::unordered_map<std::string, std::unordered_map<int, double>> get_order_list() const;
    	void make_order(std::string company_name, int stock_count) override;

private:
    	std::unordered_map<std::string, std::unordered_map<int, double>> order_list;
    	double limit_price;
};

#endif
