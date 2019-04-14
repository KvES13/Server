#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "server.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new Server();


    ui->lineAddress->setText((server->GetServerAdrress()));
    ui->linePort->setText((server->GetServerPort()));

    //serv->ReadMessage();

    connect(server,SIGNAL(array(QByteArray)),this,SLOT(showArray(QByteArray)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showArray(QByteArray arr)
{
  QDataStream in(&arr, QIODevice::ReadOnly);
  quint32 number;
  quint8 protocol;
  QString msg;
  QHostAddress sender;
  quint16 senderPort;

  in>>number>>protocol>>msg>>sender>>senderPort;
  ui->plainTextEdit->appendPlainText("IP: "+ sender.toString()+"  Port:" + QString::number(senderPort)
                                     +"  Номер: " + QString::number(number)
                                     + "  Протокол: "+ QString::number(protocol)
                                     + "  Сообщение: " + msg);
}


void MainWindow::showText()
{
   // ui->plainTextEdit->appendPlainText(data);
}






void MainWindow::on_clearButton_clicked()
{
 ui->plainTextEdit->clear();
}
