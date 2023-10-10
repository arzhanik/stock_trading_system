#ifndef MARKET_FACTORY_H
#define MARKET_FACTORY_H
#include <memory>

class MarketFactory : public OrderFactory
{
public:
    	std::unique_ptr<Order> create() override;
};

#endif
