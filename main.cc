#include <iostream>
#include "exchange.h"


int main() {
	exchange_t exchange;

	exchange.order_insert(direction_type_t::BUY, 10.0, 100);
	exchange.order_insert(direction_type_t::BUY, 11.0, 100);
	exchange.order_insert(direction_type_t::BUY, 12.0, 100);
	exchange.order_insert(direction_type_t::BUY, 10.0, 100);
	exchange.order_insert(direction_type_t::BUY, 10.0, 100);
	exchange.order_insert(direction_type_t::BUY, 10.0, 100);
	exchange.order_insert(direction_type_t::SELL, 10.0, 200);
	exchange.order_insert(direction_type_t::SELL, 10.0, 100);


	exchange.order_insert(direction_type_t::SELL, 12.0, 400);
	exchange.order_insert(direction_type_t::SELL, 13.0, 600);
	exchange.order_insert(direction_type_t::SELL, 14.0, 800);
	exchange.order_insert(direction_type_t::BUY, 12.0, 100);
	exchange.order_insert(direction_type_t::BUY, 14.0, 400);
	exchange.order_insert(direction_type_t::BUY, 11.0, 100);

	return 0;
}
