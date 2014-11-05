#include <QtWidgets>
#include <QtNetwork>
#include<string>

#include "sender.h"

Sender::Sender(QWidget *parent)
    : QWidget(parent)
{
    udpSocket = new QUdpSocket(this);
}

void Sender::broadcastString(const std::string & str)
{
     QByteArray datagram = QString::fromStdString(str).toLatin1();
     udpSocket->writeDatagram(datagram.data(), datagram.size(),QHostAddress::Broadcast, 45454);
     emit broadcastSignal(str);
}
