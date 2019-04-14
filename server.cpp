#include "server.h"
#include <QDebug>

#define port 5000
#define address QHostAddress::LocalHost

Server::Server(QObject *parent) : QObject(parent)
{
    udpsocket = new QUdpSocket(this);
    udpsocket->bind(address,port);

    connect(udpsocket,SIGNAL(readyRead()),this,SLOT(ReadDatagrams()));

}


void Server::ReadDatagrams()
{
    int count= 0;
    while(udpsocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        quint32 current_number;
        QString msg ;
        QHostAddress sender;
        quint16 senderPort;
        quint8 current_protocol;

        datagram.resize(udpsocket->pendingDatagramSize());

       QDataStream in(&datagram, QIODevice::ReadOnly);

       udpsocket->readDatagram(datagram.data(),
                               datagram.size(),
                               &sender,
                               &senderPort);


        in>>current_number>> current_protocol>>msg;

        qDebug()<<current_number<<current_protocol<<msg;


         QByteArray arr;
         QDataStream out(&arr, QIODevice::WriteOnly);
         out<<current_number<<current_protocol<<msg;

        udpsocket->writeDatagram(arr,sender,senderPort);
        out<<sender<<senderPort;

        emit array(arr);
         count++;
    }

}





void Server::SendMessage()
{

}


QString Server::GetServerAdrress()
{
    return QHostAddress(address).toString();
}

QString Server::GetServerPort()
{
    return QString::number(port);
}
