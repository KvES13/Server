#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>
#include <QPlainTextEdit>
class server : public QObject
{
    Q_OBJECT
public:
    explicit server(QObject *parent = nullptr);



    int count_send;
    int count_rec;

public slots:
    void ReadMessage();
    void SendMessage();

    QString GetServerAdrress();
    QString GetServerPort();
signals:
    void id(QString curr);
    void message(QString mess);

private:

    QUdpSocket *udpsocket;
//    QHostAddress dir;
//    quint16 puertoPar;

};

#endif // SERVER_H
