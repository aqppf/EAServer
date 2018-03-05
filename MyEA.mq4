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
double SendInitData(MqlRates &rates[],int,int);
double SendTickData(double &arr[]);
#import

int OnInit()
{  
   MqlRates rates[];
   int res = ArrayCopyRates(rates, NULL, PERIOD_M30);
   if (res == -1) MessageBox("copy PERIOD_M30 err");
   double aaa = SendInitData(rates,Bars,PERIOD_M30);
   
   Print("test", SendInitData(rates,0,0));
   
   return(INIT_SUCCEEDED);
}
void OnDeinit(const int reason)
{
}
void OnTick()
{
   double data[2];
   data[0] = Bid;
   data[1] = Volume[0];
   
   Print("Returned value is ", SendTickData(data));
}
