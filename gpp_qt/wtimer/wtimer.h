#ifndef WTIMER
#define WTIMER

//根据数据输入数据设定时间

class wtimer
{
public:
	double nowtic(){return _nowtic;};
	void settic(double nt){_nowtic =nt;};
private:
	double _nowtic;
};

#endif
