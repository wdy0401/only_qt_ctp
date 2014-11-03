#include"spread_error_check.h"

using namespace std;


void Spread_error_check::eachfunction(Vnoption vo)
{
	_updatelist(vo.get_lastsnapshot());
	_check_error(vo);
}

void Spread_error_check::_check_error(Vnoption vo)
{
	for(map<string, set<string> >::const_iterator iter = _eachoptiongroup.begin(); iter != _eachoptiongroup.end(); ++iter)
	{
		//对于每个
		for(set<string>::const_iterator setiter=iter->second.begin() ; setiter != iter->second.end() ; 1)
		{
			string s1=iter->first+"_"+setiter->c_str();
			setiter++;
			if(setiter == iter->second.end())
			{
				break;
			}
			string s2=iter->first+"_"+setiter->c_str();
			
			double lbid=vo.get_optionsnapshot().find(s1)->second.get_BidPrice1();
			double lask=vo.get_optionsnapshot().find(s1)->second.get_AskPrice1();
			double lskp=vo.get_optionsnapshot().find(s1)->second.get_StrikePrice();
			
			double hbid=vo.get_optionsnapshot().find(s2)->second.get_BidPrice1();
			double hask=vo.get_optionsnapshot().find(s2)->second.get_AskPrice1();
			double hskp=vo.get_optionsnapshot().find(s2)->second.get_StrikePrice();

			
		}
	}

}
	
void Spread_error_check::_updatelist(Vnsnapshot vs)
{
	string thisgroup=	vs.get_InstrumentID()+"_"+vs.get_callput();	//eg IO1401
	string sprice	=	wfunction::itos((int) vs.get_StrikePrice());
	
	if(_eachoptiongroup.find(thisgroup)==_eachoptiongroup.end())	//还没这个group
	{
		set<string> newset;
		newset.insert(sprice);
		_eachoptiongroup.insert(map<string,set<string> >::value_type(thisgroup,newset));
	}
	else
	{
		_eachoptiongroup.find(thisgroup)->second.insert(sprice);
	}
}

//		std::map<std::string,std::list<std::string> >	_eachoptiongroup; //将IO1401C中各个执行价格的都放到一个group里面

