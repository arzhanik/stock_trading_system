#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H
#include <string>
#include <unordered_map>

class OrderBook
{
public:
	static OrderBook& get_book();
        void new_stock(Stock* stock);
        void change_stock(Stock* stock);
        std::unordered_map<Stock*, int> get_order_book();
	Stock* get_stock(std::string company) const;
	bool order_type(const std::string& order, const std::string& company, int count);
	void print_book();

private:
	OrderBook();
	~OrderBook();
	OrderBook(Stock* stock);
	OrderBook(const OrderBook& orderbook);
	OrderBook operator=(const OrderBook& orderbook);

private:
	Stock* m_stock;
	int m_count;
        std::unordered_map<Stock*, int> order_book;
};


#endif
