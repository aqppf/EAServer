//+------------------------------------------------------------------+
//|                                                         MyEA.mq4 |
//|                                                            aqppf |
//|                                                https://aqppf.com |
//+------------------------------------------------------------------+
#property copyright "aqppf"
#property link      "https://aqppf.com"
#property version   "1.00"
#property strict

#import "EAServer.dll"
double GetDoubleValue(double);
#import

int OnInit()
{
   return(INIT_SUCCEEDED);
}
void OnDeinit(const int reason)
{
}
void OnTick()
{
   Print("Returned value is ", GetDoubleValue(Bid));
}
