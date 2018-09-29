#ifndef  __EXCHANGE_H__
#define  __EXCHANGE_H__

#include<map>
#include<unordered_map>

#include "exchange_def.h"


class exchange_t {
public:
	// 卖档map <ask_key_t, volume>
	using ask_map_t = std::map<ask_key_t, int32_t>;
	// 买档map <bid_key_t, volume>
	using bid_map_t = std::map<bid_key_t, int32_t>;
	// 已成交map <orderid, order_info_t>
	using completed_map_t = std::unordered_map<int64_t, order_info_t*>;

public:
	exchange_t() { }
	~exchange_t() { clear(); }

public:
	// @brief 报单
	// @param direction 买卖方向
	// @param price 报单价格
	// @param volume 报单数量
	// @return 报单编号
	int64_t order_insert(direction_type_t direction, int64_t price, int32_t volume);

	// @brief 查询报单信息
	order_info_t *query_order_info(int64_t orderid);

public:
	// @brief test 打印
	void test_print();

private:
	// ask报单撮合
	void ask_order_exchange(order_info_t *order_info);
	// bid报单撮合
	void bid_order_exchange(order_info_t *order_info);
	
	// @brief 报单成交
	// @param orderid 报单编号
	// @param price 成交价格
	// @param volume 成交数量
	void order_deal(int64_t orderid, int64_t price, int32_t volume);

private:
	void clear() {
		for(auto it : completed_map_) {
			delete it.second;
		}
		completed_map_.clear();
	}

private:
	ask_map_t ask_map_;
	bid_map_t bid_map_;
	completed_map_t completed_map_;
};


#endif  /*__EXCHANGE_H__*/
