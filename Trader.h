#ifndef TRADER_H
#define TRADER_H
#include <string>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <memory>

class Trader
{
public:
	Trader(const std::string& name, const std::string& id);
	bool valid_trader(const std::string& name, const std::string& id);
	void add_balance(double cash);
	void by_stock(OrderBook& book, std::string order_type, std::string company, int count);
	void print_trader_info() const;
    	void start_trading_thread(OrderBook& book);
    	void stop_trading_thread();
    	static std::unique_ptr<Trader> create_trader_by_name(const std::string& name, const std::string& id);

private:
	std::string trader_name;
	std::string trader_id;
	double trader_balance = 0;
	std::unordered_map<std::string, int> trader_property;
	std::thread trading_thread;
    	bool trading_enabled = true;
	std::mutex trader_mutex;

};

#endif
