#include"datafeed.h"
#include"../wtimer/wtimer.h"
#include<string>
#include<map>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>


/////////////////////////////////////////
//#include"../match_engine/match_engine.h"

wtimer tm;

//»¹ÒªÐ´getooption
//http://baike.baidu.com/link?url=sdpL1D5m3EHJVv_m4tMKNqmYiIoHvcthEDfESVMWZU1M17ZNtz2ZAVQUPV3go0B4

using namespace std;
int main(int argc,char *argv[])
{
	
	datafeed df;

	if (argc>1)
	{
		for(int i=1;i<argc;i++)
		{
			df.setfile(argv[i]);
		}
	}
	else
	{
		df.setfile("d:\\6.csv");
		df.setfile("d:\\1.csv");
	}
			
	df.run();
	getchar();
	return 0;
}