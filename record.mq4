//+------------------------------------------------------------------+
//|                                                       Record.mq4 |
//|                        Copyright 2020, MetaQuotes Software Corp. |
//|                                             https://www.mql5.com |
//+------------------------------------------------------------------+
#property strict
//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+

int handle;
int num = 0;
string file = "my-data-";

int OnInit()
  {
      string tmp = file;
      StringAdd(tmp, TimeToString(TimeLocal(), TIME_DATE|TIME_SECONDS));
      StringAdd(tmp, ".csv");
      StringReplace(tmp, ":", ".");
      StringReplace(tmp, " ", "-");
      handle=FileOpen(tmp, FILE_CSV|FILE_READ|FILE_WRITE, ',');
      if(handle<1)
          {
           Print("未找到文件，错误",tmp, GetLastError());
           return(false);
          }
      return(INIT_SUCCEEDED);
  }
//+------------------------------------------------------------------+
//| Expert deinitialization function                                 |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
  {
//---
   
  }
//+------------------------------------------------------------------+
//| Expert tick function                                             |
//+------------------------------------------------------------------+
void OnTick()
  {
      MqlTick last_tick;
      if(SymbolInfoTick(Symbol(),last_tick))
      {
         FileWrite(handle, last_tick.time, GetTickCount(), last_tick.bid, last_tick.ask, last_tick.volume);
         num++;
      }
      else Print("SymbolInfoTick() failed, error = ",GetLastError());
      
      //记录入另外一个新文件1W一个文件
      if (num >= 10000) 
      {
         FileClose(handle);
         // 新建文件
         string tmp = file;
         StringAdd(tmp, TimeToString(TimeLocal(), TIME_DATE|TIME_SECONDS));
         StringAdd(tmp, ".csv");
         StringReplace(tmp, ":", ".");
         StringReplace(tmp, " ", "-");
         handle=FileOpen(tmp, FILE_CSV|FILE_READ|FILE_WRITE, ',');
         num = 0;
      }
      
   
  }
//+------------------------------------------------------------------+
