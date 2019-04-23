#include "server.h"
#include <QDebug>

#define port 5000
#define address QHostAddress::LocalHost

Server::Server(QObject *parent) : QObject(parent)
{
    udpsocket = new QUdpSocket(this);
    udpsocket->bind(address,port);
    List = new QList<Message*>();
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
        quint32 number;
        //Текст сообщения
        QString msg ;
        //Адрес отправителя
        QHostAddress sender;
        //Порт отправителя
        quint16 senderPort;
        //Номер протокола сообщения (0 - udp, 1 - tcp)
        bool protocol;
        QString sum;
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
        in>>number>> protocol>>msg>>sum;
        List->append(new Message(number,protocol,msg,sum));

        qDebug()<<number<<protocol<<msg<<sum;

        if((isCheckedSum) && (!CheckSum(msg,sum)) )
        {
            mistakesSum++;
        }
        if((isCheckedNumber ))
        {

        }

         QByteArray arr;
         QDataStream out(&arr, QIODevice::WriteOnly);
         out<<number<<protocol<<msg;

        //Отправка ответа
        udpsocket->writeDatagram(arr,sender,senderPort);
        out<<sender<<senderPort;

        emit array(arr);
         count++;
    }

}

bool Server::CheckNumber(int index)
{

    if ((List->at(index)->number) < (List->at(index-1)->number))
    {
        qDebug()<<List->at(index)->number<<List->at(index-1)->number;
        return true;
    }
    else
    {
        return  false;
    }

}

bool Server::CheckSum(QString data, QString sum)
{

    QByteArray checksum = data.toUtf8();
    QString MD5sum = QCryptographicHash::hash(checksum, QCryptographicHash::Md5).toHex();

    if (MD5sum == sum)
    {
        return  true;
    }
    else
    {
        return false;
    }
}

void Server::SetIsCheckedSum(bool Box)
{
    isCheckedSum = Box;
}
void Server::SetIsCheckedNumber(bool Box)
{
    isCheckedNumber = Box;
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

