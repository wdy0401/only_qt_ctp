#ifndef CTP_QUOTE_QTHREAD
#define CTP_QUOTE_QTHREAD
#include<QThread>

class ctp_quote_qthread:public QThread
{
    Q_OBJECT
public:
    ctp_quote_qthread();
protected:
    void run();
};

#endif // CTP_QUOTE_QTHREAD
