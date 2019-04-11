#include "server.h"
#include <QDebug>

#define port 5000
#define address QHostAddress::LocalHost

server::server(QObject *parent) : QObject(parent)
{
    udpsocket = new QUdpSocket(this);
    udpsocket->bind(address,port);

    connect(udpsocket,SIGNAL(readyRead()),this,SLOT(ReadMessage()));

}


void server::ReadMessage()
{
    int count= 0;
    while(udpsocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        quint32 current_number;
        QString msg;
        QHostAddress sender;
        quint16 senderPort;


        datagram.resize(udpsocket->pendingDatagramSize());


       QDataStream in(datagram);

       udpsocket->readDatagram(datagram.data(),datagram.size(),
               &sender,&senderPort);


        in>>current_number>>msg;

        emit id(QString::number(current_number));
        emit message(msg);

        udpsocket->writeDatagram(datagram,sender,senderPort);

         count++;



    }
 //pt->plainTextEdit->appendPlainText("Received: " + QString("%1").arg(count));
}





void server::SendMessage()
{

}

//QString server::TTT()
//{
//    return
//}

QString server::GetServerAdrress()
{
    return QHostAddress(address).toString();
}

QString server::GetServerPort()
{
    return QString::number(port);
}
