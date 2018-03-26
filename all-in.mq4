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

	int many = MathFloor(margin / one_lot);
	
	int ticket = 0;

	for (int i = 0; i < many / 20; i++) {

		if (isBuy > 0)
		   ticket = OrderSend(symbol,OP_BUY,20,Ask,5,0,0);
		else
	      ticket = OrderSend(symbol,OP_SELL,20,Bid,5,0,0);
	      
		if(ticket<0) Print("OrderSend 失败错误 #",GetLastError());
	}
	
	if (many % 20 == 0)  return;
	
	if (isBuy > 0)
		ticket = OrderSend(symbol,OP_BUY,many % 20,Ask,5,0,0);
	else
	   ticket = OrderSend(symbol,OP_SELL,many % 20,Bid,5,0,0);
	   
	if(ticket<0) Print("OrderSend 失败错误 #",GetLastError());
	
	
}