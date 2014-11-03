#ifndef ORDERBOOK
#define ORDERBOOK

#include<string>
#include<vector>
//主要功能
//实时更新orderbook，以便match_engine使用

//目前未实现full book信息
//接口已预留

#define MAXLEVEL 10

class orderbook
{
public:

	orderbook();
	void updateorderbook(const std::string &,long,double,long);//string bidask, long level, double price, long size
	
	void setsymbol(const std::string &);
	std::string getsymbol();
	
	double getbidprice(long);
	double getaskprice(long);
	double getbidprice();
	double getaskprice();
	
	long getbidsize(long);
	long getasksize(long);	
	long getbidsize();
	long getasksize();

	long getfillsize();
	
	
private:
	//name
	std::string _symbol;
	
	//ordinary book
	double	_bidlevelprice[MAXLEVEL];
	long	_bidlevelsize[MAXLEVEL];
	double	_asklevelprice[MAXLEVEL];
	long	_asklevelsize[MAXLEVEL];
	
	//nbbo
	double _bidprice;
	double _askprice;
	long _bidsize;
	long _asksize;

	//fill
	long _fillsize;
	long _lastfillsize;
	
	//full book
	std::vector< std::vector<long> > _bidlevelmap;//存储每级level的order信息
	std::vector< std::vector<long> > _asklevelmap;//存储每级level的order信息
};

#endif
