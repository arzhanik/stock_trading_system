#ifndef LIMIT_FACTORY_H
#define LIMIT_FACTORY_H
#include <memory>
#include "Order.h"
#include "OrderFactory.h"

class LimitFactory : public OrderFactory 
{
public:
    	std::unique_ptr<Order> create() override;

	void operator()(double limit);

private:
	double limit_order;
};

#endif
