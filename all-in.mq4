//+------------------------------------------------------------------+
//|                                               Moving Average.mq4 |
//|                   Copyright 2005-2014, MetaQuotes Software Corp. |
//|                                              http://www.mql4.com |
//+------------------------------------------------------------------+
#property copyright   "2005-2014, MetaQuotes Software Corp."
#property link        "http://www.mql4.com"
#property description "Moving Average sample expert advisor"

input int isBuy = 1;

void OnTick()
{
	//todo
}

void OnInit()
{
	//获取当前交易货币
	string symbol = Symbol();
	if (symbol != "EURUSD") {Print("非 EURUSD"); return; }	
	
	int Leverage = AccountLeverage(); // 杠杆比例

	double price = iClose(symbol,0,0); //当前价格

	double one_lot = 100000.0 / Leverage * price; //一手需要的佣金

	double margin = AccountFreeMargin();

	double many = MathFloor(margin / one_lot);

	int isBuy = isBuy > 0 ? OP_BUY : OP_SELL;

	for (int i = 0; i < many; i += 20) {

		int lots = i <= many ? 20 : (many - 20*i);

		int ticket = OrderSend(symbol,isBuy,20,Ask,5,0,0);
	
		if(ticket<0) Print("OrderSend 失败错误 #",GetLastError());
	}
}