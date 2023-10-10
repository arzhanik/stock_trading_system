#include <memory>
#include "LimitFactory.h"
#include "OrderFactory.h"
#include "LimitOrder.h"
#include "Order.h"


std::unique_ptr<Order> LimitFactory::create() {
	return std::make_unique<LimitOrder>(limit_order);
}

void LimitFactory::operator()(double limit) { limit_order = limit; }



