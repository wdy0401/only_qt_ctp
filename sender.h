#ifndef SENDER_H
#define SENDER_H

#include <QWidget>
#include <string>
QT_BEGIN_NAMESPACE
class QUdpSocket;
QT_END_NAMESPACE

class Sender : public QWidget
{
    Q_OBJECT

public:
    Sender(QWidget *parent = 0);
    void broadcastString(const std::string &);

signals:
    void broadcastSignal(const std::string &);

private slots:

private:
    QUdpSocket *udpSocket;
};

#endif
