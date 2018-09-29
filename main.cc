#include <iostream>
#include "exchange.h"


int main() {
	exchange_t exchange;

	exchange.order_insert(direction_type_t::BUY, 1012, 100);
	exchange.order_insert(direction_type_t::BUY, 1111, 100);
	exchange.order_insert(direction_type_t::BUY, 1245, 100);
	exchange.order_insert(direction_type_t::BUY, 1012, 100);
	exchange.order_insert(direction_type_t::BUY, 1012, 100);
	exchange.order_insert(direction_type_t::BUY, 1012, 100);
	exchange.order_insert(direction_type_t::SELL, 1012, 200);
	exchange.order_insert(direction_type_t::SELL, 1012, 100);


	exchange.order_insert(direction_type_t::SELL, 1224, 400);
	exchange.order_insert(direction_type_t::SELL, 1332, 600);
	exchange.order_insert(direction_type_t::SELL, 1440, 800);
	exchange.order_insert(direction_type_t::BUY, 1224, 100);
	exchange.order_insert(direction_type_t::BUY, 1440, 400);
	exchange.order_insert(direction_type_t::BUY, 1111, 100);

	return 0;
}
