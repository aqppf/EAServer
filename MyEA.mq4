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
   int bars;

   bars = ArrayCopyRates(rates, NULL, PERIOD_M1);
   if (bars == -1) MessageBox("copy m1 error");
   SendInitData(rates, bars, PERIOD_M1);

   bars = ArrayCopyRates(rates, NULL, PERIOD_M5);
   if (bars == -1) MessageBox("copy m5 error");
   SendInitData(rates, bars, PERIOD_M5);

   bars = ArrayCopyRates(rates, NULL, PERIOD_M15);
   if (bars == -1) MessageBox("copy m15 error");
   SendInitData(rates, bars, PERIOD_M15);

   bars = ArrayCopyRates(rates, NULL, PERIOD_M30);
   if (bars == -1) MessageBox("copy m30 error");
   SendInitData(rates, bars, PERIOD_M30);

   bars = ArrayCopyRates(rates, NULL, PERIOD_H1);
   if (bars == -1) MessageBox("copy h1 error");
   SendInitData(rates, bars, PERIOD_H1);

   bars = ArrayCopyRates(rates, NULL, PERIOD_H4);
   if (bars == -1) MessageBox("copy h4 error");
   SendInitData(rates, bars, PERIOD_H4);

   bars = ArrayCopyRates(rates, NULL, PERIOD_D1);
   if (bars == -1) MessageBox("copy d1 error");
   SendInitData(rates, bars, PERIOD_D1);


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
