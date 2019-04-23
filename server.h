#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>
#include <QPlainTextEdit>
#include <QCryptographicHash>
#include <QList>
/* Сообщение */
struct Message
{
    quint32 number;       //Номер сообщения
    bool protocol;  //Номер протокола
    QString text;     //Текст сообщения
    QString checkSum; //Контрольная сумма
    //Конструктор
    Message(quint32 _number,bool _protocol, QString _text, QString _checkSum)
    {
        number = _number;
        protocol = _protocol;
        text = _text;
        checkSum =_checkSum;
    }
};


class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);





public slots:
    //Чтение датаграмм
    void ReadDatagrams();
    void SendMessage();
    void SetIsCheckedSum(bool Box);
    void SetIsCheckedNumber(bool Box);
    //Адрес сервера
    QString GetServerAdrress();
    //Номер порта
    QString GetServerPort();
signals:
    //Сигнал, возвращающий входящее сообщение
    void array(QByteArray arr);

private:
    QList<Message*> *List = nullptr;
    int count_send;
    int count_rec;
    QUdpSocket *udpsocket = nullptr;
    bool isCheckedSum = false;
    bool isCheckedNumber = false;
    int mistakesSum =0;
    int mistakesNum = 0;

private slots:
    bool CheckSum(QString data, QString sum);
    bool CheckNumber(int index);
//    QHostAddress dir;
//    quint16 puertoPar;

};

#endif // SERVER_H
