#ifndef ORDER_FACTORY
#define ORDER_FACTORY
#include <memory>
#include "Order.h"

class OrderFactory
{
public:
    	virtual std::unique_ptr<Order> create() = 0;
    	virtual ~OrderFactory();
};

#endif
