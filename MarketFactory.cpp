#include <memory>
#include "MarketOrder.h"
#include "OrderFactory.h"
#include "MarketFactory.h"
#include "Order.h"


std::unique_ptr<Order> MarketFactory::create() {
        return std::make_unique<MarketOrder>();
}

