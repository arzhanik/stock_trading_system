#include <string>
#include <unordered_map>
#include "MarketOrder.h"
#include "OrderFactory.h"
#include "MarketFactory.h"
#include "Order.h"


std::unordered_map<std::string, int> MarketOrder::get_order() const { return order; }


void MarketOrder::make_order(std::string company_name, int stock_count) {
        order[company_name] = stock_count;
}
