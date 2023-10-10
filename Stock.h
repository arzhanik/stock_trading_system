#ifndef STOCK_H
#define STOCK_H
#include <string>
#include <unordered_map>
#include <memory>

class Stock
{
public:
        Stock(std::string company, double value);
        void change_stock_value (double new_value);
	void change_stock_count (int stocks);
	int get_stock_count() const;
	std::string get_company_name() const;
	double get_stock_value() const;
	static std::unique_ptr<Stock> create_stock_by_name(const std::string& name, int balance);

private:
        std::string company_name;
        double stock_value;
	int free_stock_count;
        std::unordered_map<std::string, double> stock_info;
};

#endif
