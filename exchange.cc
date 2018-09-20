#include <iostream>
#include "exchange.h"

int64_t exchange_t::order_insert(direction_type_t direction, double price, int32_t volume)
{
	int64_t orderid = orderid_gen_t::gen();

	order_info_t *info = new order_info_t(orderid, direction, price, volume);
	// 1.保存报单信息
	completed_map_[orderid] = info;
	// 2.报单撮合
	switch(direction) {
		case direction_type_t::BUY:
			bid_order_exchange(info);
			break;
		case direction_type_t::SELL:
			ask_order_exchange(info);
			break;
		default:
			break;
	}
	
	test_print();
	return orderid;
}

order_info_t *exchange_t::query_order_info(int64_t orderid)
{
	auto it = completed_map_.find(orderid);
	if (it != completed_map_.end()) {
		return it->second;
	} else {
		return nullptr;
	}

}

void exchange_t::ask_order_exchange(order_info_t *order_info)
{
	int32_t uncompleted_vol = order_info->volume;
	while(bid_map_.size()) {
		bid_map_t::iterator it = bid_map_.begin();
		// 全部成交
		if (uncompleted_vol <= 0) break;
		// 买一价 小于卖价
		if (it->first.price < order_info->price) break;
		// 撮合
		if (it->second < uncompleted_vol) {
			// 买一价全部成交 当前报单部分成交
			uncompleted_vol -= it->second;
			// 成交明细记录
			order_deal(it->first.orderid, it->first.price, it->second);
			order_deal(order_info->orderid, it->first.price, it->second);

			bid_map_.erase(it);
		} else if (it->second == uncompleted_vol) {
			// 买一价全部成交 当前报单全部成交
			uncompleted_vol -= it->second;
			// 成交明细记录
			order_deal(it->first.orderid, it->first.price, it->second);
			order_deal(order_info->orderid, it->first.price, it->second);

			bid_map_.erase(it);
			break;
		} else {
			// 买一价部分成交 当前报单全部成交
			// 买档未成交数量修改
			it->second -= uncompleted_vol;
			
			// 成交明细记录
			order_deal(it->first.orderid, it->first.price, uncompleted_vol);
			order_deal(order_info->orderid, it->first.price, uncompleted_vol);
			
			uncompleted_vol = 0;
		}
	}

	// 报单未成交进入卖档
	if (uncompleted_vol > 0) {
		ask_map_[ask_key_t(order_info->price, order_info->orderid)] = uncompleted_vol;
	}
}

void exchange_t::bid_order_exchange(order_info_t *order_info)
{
	int32_t uncompleted_vol = order_info->volume;
	while(ask_map_.size()) {
		ask_map_t::iterator it = ask_map_.begin();
		// 全部成交
		if (uncompleted_vol <= 0) break;
		// 卖一价 大于买价
		if (it->first.price > order_info->price) break;
		// 撮合
		if (it->second < uncompleted_vol) {
			// 卖一价全部成交 当前报单部分成交
			uncompleted_vol -= it->second;
			// 成交明细记录
			order_deal(it->first.orderid, it->first.price, it->second);
			order_deal(order_info->orderid, it->first.price, it->second);

			ask_map_.erase(it);
		} else if (it->second == uncompleted_vol) {
			// 卖一价全部成交 当前报单全部成交
			uncompleted_vol -= it->second;
			// 成交明细记录
			order_deal(it->first.orderid, it->first.price, it->second);
			order_deal(order_info->orderid, it->first.price, it->second);

			ask_map_.erase(it);
			break;
		} else {
			// 卖一价部分成交 当前报单全部成交
			// 卖档未成交数量修改
			it->second -= uncompleted_vol;
			
			// 成交明细记录
			order_deal(it->first.orderid, it->first.price, uncompleted_vol);
			order_deal(order_info->orderid, it->first.price, uncompleted_vol);
			
			uncompleted_vol = 0;
		}
	}

	// 报单未成交进入卖档
	if (uncompleted_vol > 0) {
		bid_map_[bid_key_t(order_info->price, order_info->orderid)] = uncompleted_vol;
	}

}

void exchange_t::order_deal(int64_t orderid, double price, int32_t volume)
{
	order_info_t *order_info = query_order_info(orderid);
	if (order_info) {
		order_info->completed_vol += volume;
		order_info->details_vect.push_back(order_info_t::details_t{price, volume});
	}
}

void exchange_t::test_print()
{
	std::cout << "----------------------start---------------------------" << std::endl;
	
	std::cout << "ask_map info ex.orderid, volume, price" << std::endl;
	for(auto it : ask_map_) {
		std::cout << it.first.orderid << ", " << it.second << ", " << it.first.price << std::endl;
	}

	std::cout << "bid_map info ex.orderid, volume, price" << std::endl;
	for(auto it : bid_map_) {
		std::cout << it.first.orderid << ", " << it.second << ", " << it.first.price << std::endl;
	}

	std::cout << "completed_map info ex.orderid, volume, price, completed_vol" << std::endl;
	for(auto it : completed_map_) {
		std::cout << it.first << ", " << it.second->volume<< ", " 
			<< it.second->price << ", " << it.second->completed_vol
			<< std::endl;
	}


	std::cout << "-----------------------end----------------------------" << std::endl;
}
