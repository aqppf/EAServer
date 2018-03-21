//+------------------------------------------------------------------+
//|                                                        Bulls.mq4 |
//|                   Copyright 2005-2014, MetaQuotes Software Corp. |
//|                                              http://www.mql4.com |
//+------------------------------------------------------------------+
#property copyright   "2005-2014, MetaQuotes Software Corp."
#property link        "http://www.mql4.com"
#property description "Bulls Power"
#property strict
#property indicator_separate_window

#import "time.dll"
uint timeGetTime(int);
#import

uint    last_move_time = 0;
double  last_price = 0;
long    last_volume = 0;

double ExtBullsBuffer[];
//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+
void OnInit(void)
{
   string short_name = "aqppf";
   IndicatorBuffers(1);
   IndicatorDigits(Digits+2);
   SetIndexStyle(0,DRAW_HISTOGRAM);
   SetIndexBuffer(0,ExtBullsBuffer);
}
int OnCalculate(const int rates_total,
                const int prev_calculated,
                const datetime &time[],
                const double &open[],
                const double &high[],
                const double &low[],
                const double &close[],
                const long &tick_volume[],
                const long &volume[],
                const int &spread[])
{
   int limit=rates_total-prev_calculated;

   if (last_price == 0) { 
        last_price = close[0]; 
        last_volume = tick_volume[0];
        last_move_time = timeGetTime(0);
        return 0; 
    }

   //方向（看多还是看空）
   double diff_price = close[0] - last_price; 

   last_price = close[0];

   //时间系数
   double var_time = 1 / (timeGetTime(0) - last_move_time);

   last_move_time = timeGetTime(0);

   //交易系数
   long var_vol = tick_volume[0] - last_volume > 0 ? (tick_volume[0] - last_volume) : tick_volume[0];

   last_volume = tick_volume[0];

   ExtBullsBuffer[0] += var_vol * var_time * diff_price;
   
   Print("value:",ExtBullsBuffer[0]);

   return(rates_total);
}