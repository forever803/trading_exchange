#ifndef  __EXCHANGE_DEF_H__
#define  __EXCHANGE_DEF_H__

#include<cstdint>
#include<chrono>
#include<vector>

//买卖方向
enum direction_type_t : int8_t
{
	BUY = 0, //买
	SELL,    //卖
};

// 卖档key
class ask_key_t {
public:
	ask_key_t(int64_t p, int64_t id) : price(p), orderid(id) { }
	~ask_key_t() { }

public:
	int64_t price;		// 价格
	int64_t orderid;	// 委托编号

public:
	bool operator < (const ask_key_t &key) const {
		// 结构体内比较 价格优先，时间优先
		// price 越小排序越靠前 orderid 越小排序越靠前
		if (this->price < key.price) {
			return true;
		} else if (this->price == key.price) {
			return this->orderid < key.orderid;
		} else {
			return false;
		}
	}
};

// 买档key
class bid_key_t {
public:
	bid_key_t(int64_t p, int64_t id) : price(p), orderid(id) { }
	~bid_key_t() { }

public:
	int64_t price;		// 价格
	int64_t orderid;	// 委托编号

public:
	bool operator < (const bid_key_t &key) const {
		// 结构体内比较 价格优先，时间优先
		// price 越大排序越靠前 orderid 越小排序越靠前
		if (this->price > key.price) {
			return true;
		} else if (this->price == key.price) {
			return this->orderid < key.orderid;
		} else {
			return false;
		}

	}
};

// 报单信息
class order_info_t {
public:
	order_info_t(int64_t id, direction_type_t d, int64_t p, int32_t v): 
		orderid(id), direction(d), 
		price(p), volume(v),
		completed_vol(0) 
	{
	}
	~order_info_t() { }

public:
	// 成交
	void exchange(int64_t price, int32_t volume) {
		details_t d {price, volume};
		completed_vol += volume;
		details_vect.push_back(d);
	}	

public:
	struct details_t {
		int64_t price;
		int32_t volume;
	};

public:
	int64_t orderid;				// 报单id
	direction_type_t direction;		// 买卖方向
	int64_t price;					// 报单价格
	int32_t volume;					// 报单数量
	int32_t completed_vol;			// 成交数量
	std::vector<details_t> details_vect;	// 成交明细
};

// order
class orderid_gen_t {
public:
	// @brief orderid 生成(规则: 64位整数, 高32位为当前时间,低32位为1秒内自增长字段)
	static int64_t gen() {
		// 获取当前时间秒数
		using namespace std::chrono;
		system_clock::time_point tp = system_clock::now();
		system_clock::duration dtn = tp.time_since_epoch();
		int32_t seconds
			= dtn.count() * system_clock::period::num / system_clock::period::den;
		
		static int32_t incr = 0;
		static int32_t incr_update_time = seconds;
		if (seconds > incr_update_time) {
			// 不在同一秒内, incr 重新计数
			incr = 0;
			incr_update_time = seconds;
		}
		
		// orderid 生成
		int64_t orderid = seconds; 
		orderid <<= 32;
		orderid |= incr++;

		return orderid;
	}
};



#endif  /*__EXCHANGE_DEF_H__*/
