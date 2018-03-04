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
double SendTickData(double &arr[]);
void SendInitData(double &arr[], int, int);
#import

int OnInit()
{
   double data[2];
   while(true) {
      data[0] = Bid;
      data[1] = Bars;
      Print("Returned value is ", SendTickData(data));
      Sleep(1000);
   }
   return(INIT_SUCCEEDED);
}
void OnDeinit(const int reason)
{
}
void OnTick()
{
   Print("Returned value is ");
}
