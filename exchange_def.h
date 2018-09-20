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
	ask_key_t(double p, int64_t id) : price(p), orderid(id) { }
	~ask_key_t() { }

public:
	double price;		// 价格
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
	bid_key_t(double p, int64_t id) : price(p), orderid(id) { }
	~bid_key_t() { }

public:
	double price;		// 价格
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
	order_info_t(int64_t id, direction_type_t d, double p, int32_t v): 
		orderid(id), direction(d), 
		price(p), volume(v),
		completed_vol(0) 
	{
	}
	~order_info_t() { }

public:
	// 成交
	void exchange(double price, int32_t volume) {
		details_t d {price, volume};
		completed_vol += volume;
		details_vect.push_back(d);
	}	

public:
	struct details_t {
		double price;
		int32_t volume;
	};

public:
	int64_t orderid;				// 报单id
	direction_type_t direction;		// 买卖方向
	double price;					// 报单价格
	int32_t volume;					// 报单数量
	int32_t completed_vol;			// 成交数量
	std::vector<details_t> details_vect;	// 成交明细
};

// order
class orderid_gen_t {
public:
	static int64_t gen() {
		static int32_t incr = 0;

		using namespace std::chrono;
		system_clock::time_point tp = system_clock::now();
		system_clock::duration dtn = tp.time_since_epoch();
		int64_t orderid 
			= dtn.count() * system_clock::period::num / system_clock::period::den;
		orderid <<= 32;
		orderid |= incr++;

		return orderid;
	}
};



#endif  /*__EXCHANGE_DEF_H__*/
