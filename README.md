# trading_exchange
单品种撮合交易系统，撮合规则：价格优先，时间优先

1.orderid 保证唯一(生成规则: 64位整数, 高32位为当前时间,低32位为1秒内自增长字段)

2.ask_map 保证price越小排序越靠前，相同price越早入队报单排序越靠前

3.bid_map 保证price越大排序越靠前，相同price越早入队报单排序越靠前

4.order_map 采用hash_map存储，通过orderid 在O(1)时间内找到对应报单信息



