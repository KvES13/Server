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

//Чтение датаграмм
void Server::ReadDatagrams()
{
    int count= 0;
    while(udpsocket->hasPendingDatagrams())
    {
        //Массив, содержащий сообщение
        QByteArray datagram;
        //Номер текущего сообщения
        quint32 current_number;
        //Текст сообщения
        QString msg ;
        //Адрес отправителя
        QHostAddress sender;
        //Порт отправителя
        quint16 senderPort;
        //Номер протокола сообщения (0 - udp, 1 - tcp)
        quint8 current_protocol;

        //
        datagram.resize(udpsocket->pendingDatagramSize());

        //
       QDataStream in(&datagram, QIODevice::ReadOnly);

       //Чтение датаграммы
       udpsocket->readDatagram(datagram.data(),
                               datagram.size(),
                               &sender,
                               &senderPort);

        //
        in>>current_number>> current_protocol>>msg;

        qDebug()<<current_number<<current_protocol<<msg;


         QByteArray arr;
         QDataStream out(&arr, QIODevice::WriteOnly);
         out<<current_number<<current_protocol<<msg;

        //Отправка ответа
        udpsocket->writeDatagram(arr,sender,senderPort);
        out<<sender<<senderPort;

        emit array(arr);
         count++;
    }

}





void Server::SendMessage()
{

}

//Адрес сервева
QString Server::GetServerAdrress()
{
    return QHostAddress(address).toString();
}
//Номер порта
QString Server::GetServerPort()
{
    return QString::number(port);
}
