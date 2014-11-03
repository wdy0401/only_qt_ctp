#ifndef DATAFEED
#define DATAFEED

/////////////////////////////////////////
//#include"../match_engine/match_engine.h"
#include<string>
#include<fstream>

#include<map>
#include<list>

/////////////////////////////////////////
//合并数据已经实现，由于涉及到string的比较问题，效率较低
//这里仍旧涉及到标准数据的表示方式问题，如标准化则可以利用更有效的方式来进行比较



#define FILE_RECORD_BUFFER 10

//class match_engine; 
class datafeed
{
public:
	//void updatemessage(match_engine &);
	void setfile(const std::string & filename);//增添cache文件
	void run();//开始cache
	void checkfilecache();//按时间顺序合并文件cache 
	void reloadcache();//发现cache空，则补充
	void sendmessage(const std::string & message);//可扩展的中间件
	void feedcache(const std::string & );//补充文件cache

	std::list<std::string> _filenames;//文件名列表 一旦文件读取完毕 会被文件列表除名
	std::map<long,std::string> _quotecache;//系统可用的数据cache 用map的原因是map自动排序功能

	std::map<std::string,std::list<std::string> > _filecache;//每个文件的cache 任意时刻_quotecache与_filecache都没有逻辑冲突
	std::map<std::string,std::ifstream * > _filehandle;//每个文件的handle


//tiny part	
	std::map<std::string,std::map<long,std::string> > _tiny;
	void find_next();
	std::string _retstring;
	std::string _nowfile;
	long getsize();
	

private:

};

#endif

/*
如果打开n个文件
原则 设定缓存阈值 
	每次读到某文件queue最后一条记录 则更新缓存。仅更新未达到阈值的数据，而且更新的量为亦为阈值。

时序
	首次更新缓存。
	
	发现需要再次更新缓存。
	处理读完文件的情况。

发布
	读取queue数据并排序 fifo
	一旦有queue空则发布数据
	通知更新缓存
		
	两个cache中的数据不重不漏 也就是queue中的顺序即便放在全数据集中也是成团的，中间不会有数据

	声明某函数为match_engine友员 目前这么做 有更好的机制么？
*/

