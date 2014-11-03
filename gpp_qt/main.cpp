#include<map>
#include<iostream>
#include<fstream>
#include<stdlib.h>

#include"./option/vnoption.h"
#include"./option/vnsnapshot.h"
#include"./option/spread_error_check.h"

#include"./cfg/cfg.h"
#include"./wtimer/wtimer.h"
#include"./wfunction/wfunction.h"

#include"./log_info/log_info.h"

#include"./future/futurerecord.h"
#include"./future/futuresnapshot.h"

#include"./bar/bar.h"
#include"./datafeed/datafeed.h"
#include"./trans_event/trans_event.h"
#include"./fillpolicy/fillpolicy.h"

#include"./match_engine/match_engine.h"
#include"./match_engine/order.h"
#include"./match_engine/orderlist.h"
#include"./match_engine/orderbook.h"

//g++ main.cpp  ./cfg/cfg.cpp ./wtimer/wtimer.cpp ./wfunction/wfunction.cpp ./log_info/log_info.cpp  ./datafeed/datafeed.cpp ./trans_event/trans_event.cpp  ./fillpolicy/fillpolicy.cpp  ./match_engine/order.cpp ./match_engine/orderlist.cpp ./match_engine/orderbook.cpp ./match_engine/match_engine.cpp  
//20140723 g++ 可正常运行   vs编译后 运行出错 失效的迭代器
//20140723 均可正常运行 问题出在match_engine.cpp第47行，find处 原因是当时_nowsymbol 尚未定义便开始查找，返回的end迭代器。g++对end迭代器处理有误 ==end 仍有对应的second


//dll导出类未搞定 导致写tactic时需要把交互的函数放在class外面  class中放非交互内容
using namespace std;

cfg simucfg;		//配置信息
wtimer tm;			//时间戳
log_info loginfo;	//记录log
match_engine me;	//撮合系统
datafeed df;		//数据源
trans_event te;		//信息传递器

int main()
{
	simucfg.loadfile();
	string quotefiles=	simucfg.getparam("datafeedfile");
	string fpname	=	simucfg.getparam("fillpolicy");

	me.loadfillpolicy(fpname);
	df.setfile(quotefiles);

	df.run();
}
/*
int main()
{
	
	//定义option数据类型 注意与vnsnapshot中的一致
	string InstrumentID;//eg IO1401
	string callput;		//eg C
	long tm;			//eg 
	double StrikePrice;	//eg 2350
	double BidPrice1;	//eg 20
	double AskPrice1;	//eg 25
	double BidSize1;	//eg 20
	double AskSize1;	//eg 25
	
	
	ifstream infile;
	string filename="C:\\Users\\dell\\Desktop\\testlogic.txt";
	infile.open(filename.c_str());
	if(! infile.is_open()) //检测文件存在性
	{
		cerr << "Cannot openfile " << filename.c_str() << endl;
		getchar();
		return 1;
	}
	string tp;
	while(getline(infile,tp))
	{
		int count=0;
		while(tp.size())
		{		
			static int index=0;
			count++;
			index=tp.find_first_of("\t");

			string tmpstring=tp.substr(0,index);
			switch(count)
			{
				case 1:InstrumentID	=tmpstring;					break;
				case 2:callput		=tmpstring;					break;
				case 3:tm			=atol(tmpstring.c_str());	break;
				case 4:StrikePrice	=atof(tmpstring.c_str());	break;
				case 5:BidPrice1	=atof(tmpstring.c_str());	break;
				case 6:AskPrice1	=atof(tmpstring.c_str());	break;
				case 7:BidSize1		=atof(tmpstring.c_str());	break;
				case 8:AskSize1		=atof(tp.c_str());			break;
			}
			if(index==-1)
			{
				break;
			}
			tp=tp.substr(index+1);

		}
	//	vo.updaterecord(InstrumentID, callput , tm, StrikePrice, BidPrice1 , AskPrice1, BidSize1 , AskSize1);
	//	sec.eachfunction(vo);
	//	cout<<" "<<tm<<" "<<StrikePrice<<" "<<BidPrice1<<" "<<AskPrice1<<endl;
	}
	//getchar();
	return 0;
}

*/
/*
关于既能模拟又可以ctp的问题
1.		ctp相当于模拟中的datafeed fp 
2.		模拟中是否需要实现中断的方式，如何实现or如何不实现仍能进行模拟 是不是涉及到主次问题， 先写个模拟程序 然后在ctp中相应函数里调用模拟程序？或反之  效率会不会出问题
3.		需要包装接口		
*/

