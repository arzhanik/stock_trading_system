#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include "Stock.h"


Stock::Stock(std::string company, double value)
                : company_name { company }
                , stock_value { value }
		, free_stock_count { 100 }
{
        stock_info[company] = value;
}

std::unique_ptr<Stock> Stock::create_stock_by_name(const std::string& name, int balance) {
        return std::make_unique<Stock>(name, balance);
}

void Stock::change_stock_value (double new_value) {
        if (new_value <= 0) {
                stock_info.erase(company_name);
                return;
        }
        stock_info[company_name] = new_value;
        stock_value = new_value;
}


void Stock::change_stock_count (int stocks) {
	if (stocks >= 0) {
		free_stock_count = stocks;
	} else {
		std::cout << "Invalid count for stocks.\n";
	}
}

	
int Stock::get_stock_count() const { return free_stock_count; }


std::string Stock::get_company_name() const { return company_name; }


double Stock::get_stock_value() const { return stock_value; }

