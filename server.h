#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>
#include <QPlainTextEdit>
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);





public slots:
    //Чтение датаграмм
    void ReadDatagrams();
    void SendMessage();

    //Адрес сервера
    QString GetServerAdrress();
    //Номер порта
    QString GetServerPort();
signals:
    //Сигнал, возвращающий входящее сообщение
    void array(QByteArray arr);

private:
    int count_send;
    int count_rec;
    QUdpSocket *udpsocket = nullptr;

//    QHostAddress dir;
//    quint16 puertoPar;

};

#endif // SERVER_H
