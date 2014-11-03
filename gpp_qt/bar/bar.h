#ifndef BAR
#define BAR

class bar
{
public:
	bar();
	
	void setnowtime(double );
	void setnowtime();
	void setvalue(double );
	void setvalue(double,double);
	void setvolume(double );
	
	double getbegtime();
	double getendtime();
	double getopen();
	double gethigh();
	double getlow();
	double getclose();
	double getvolume();
	
private:

	double _nowtime;
	double _begtime;
	double _endtime;
	
	double _value;

	double _open;
	double _high;
	double _low;
	double _close;

	double _volume;
};

#endif