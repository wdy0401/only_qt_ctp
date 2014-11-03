#include"../match_engine/orderbook.h"
#include"../match_engine/orderlist.h"
#include"../wtimer/wtimer.h"

#ifndef FILLPOLICY
#define FILLPOLICY

//过价成交的fp
//

//fp需要维护一份snapshot信息 以便对照之前的snapshot来了解更新内容
//由于此fp是过价成交，故不需要前一份snapshot

//fp中存一个父ME的指针,以此调用父ME中 针对te的callback
class match_engine;

class fillpolicy
{
public:
	void updateorderlist(orderlist & ,orderbook & );
	match_engine * pme;	
private:
};

#endif
