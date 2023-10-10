#ifndef ORDER_S
#define ORDER_S
#include <string>
#include "Stock.h"

class Order
{
public:
    	virtual void make_order(std::string company, int count) = 0;
    	virtual ~Order();
};

#endif
