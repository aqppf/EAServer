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

int need_period = 8;
int cur_bars[9];
int order_period[9] = {PERIOD_M1,PERIOD_M5,PERIOD_M15,PERIOD_M30,PERIOD_H1,PERIOD_H4,PERIOD_D1,PERIOD_W1,PERIOD_MN1};

void copy(int period)
{
   MqlRates rates[];
   int bars;

   bars = ArrayCopyRates(rates, NULL, period);
   if (bars == -1) {
      MessageBox("copy rates error");
      return;
   }
   SendInitData(rates, bars, period);

   for (int i = 0; i < need_period; ++i) {
      if (period == order_period[i]) cur_bars[i] = bars;
   }
}

int OnInit()
{  
   copy(PERIOD_M1);
   copy(PERIOD_M5);
   copy(PERIOD_M15);
   copy(PERIOD_M30);
   copy(PERIOD_H1);
   copy(PERIOD_H4);
   copy(PERIOD_D1);
   copy(PERIOD_W1);
   copy(PERIOD_MN1);

   return(INIT_SUCCEEDED);
}
void OnDeinit(const int reason)
{
   //todo
}
void OnTick()
{
   double data[2];
   data[0] = Bid;
   data[1] = (double)Volume[0];
   
   Print("Returned value is ", SendTickData(data)); // 打印并计算

   int bars = 0;
   MqlRates rates[];

   for (int i=0; i<need_period; i++) {
      bars = iBars(NULL, order_period[i]);
      if (cur_bars[i] >= bars) continue;
      bars = ArrayCopyRates(rates, NULL, order_period[i]);
      if (bars == -1) {
         MessageBox("copy rates error");
         return;
      }
      cur_bars[i] = bars;
      SendInitData(rates, bars, order_period[i]);
   }
}
