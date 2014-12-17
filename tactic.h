#ifndef TACTIC_H
#define TACTIC_H
#include<QObject>
#include<string>
class ctp_order_manager;
class tactic: public QObject
{
    Q_OBJECT
public:
    tactic();
//    void set_ctp_order_manager(ctp_order_manager * p){ctpom=p;}
    void sample_tactic(){}

public slots:
    virtual void quote(const std::string & symbol, const std::string & ba, long level, double price, long size){}
    virtual void ack(const std::string & ordername,const std::string & type,const std::string & info){}
    virtual void done(const std::string & ordername,const std::string & type,const std::string & info){}
    virtual void rej(const std::string & ordername,const std::string & type,const std::string & info){}
    virtual void fill(const std::string & ordername,long size){}
private:
//    ctp_order_manager * ctpom;
};

#endif // TACTIC_H
