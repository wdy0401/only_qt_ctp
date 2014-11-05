#ifndef SENDER_H
#define SENDER_H

#include <QWidget>
#include <string>
class QUdpSocket;

class Sender : public QWidget
{
    Q_OBJECT

public:
    Sender(QWidget *parent = 0);
    void broadcastString(const std::string &);

signals:
    void broadcastSignal(const std::string &);

private:
    QUdpSocket *udpSocket;
};

#endif
