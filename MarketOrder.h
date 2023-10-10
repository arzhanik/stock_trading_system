#ifndef MARKET_ORDER_H
#define MARKET_ORDER_H
#include <unordered_map>
#include <string>
#include "Order.h"
#include "Stock.h"

class MarketOrder : public Order
{
public:
    	std::unordered_map<std::string, int> get_order() const;
    	void make_order(std::string company_name, int stock_count);

private:
    	std::unordered_map<std::string, int> order;
};


#endif
