#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "server.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Создание объекта класса
    server = new Server();

    //Вывод текущего адреса
    ui->lineAddress->setText((server->GetServerAdrress()));
    //Вывод текущего номера порта
    ui->linePort->setText((server->GetServerPort()));


    //?
    connect(server,SIGNAL(array(QByteArray)),this,SLOT(showArray(QByteArray)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Вывод сообщения на экран
void MainWindow::showArray(QByteArray arr)
{
  QDataStream in(&arr, QIODevice::ReadOnly);
  //Номер сообщения
  quint32 number;
  //Номер протокола (0 - udp, 1 - tcp)
  quint8 protocol;
  //Текст сообщения
  QString msg;
  //Адрес отправителя
  QHostAddress sender;
  //Адрес получателя
  quint16 senderPort;

  //
  in>>number>>protocol>>msg>>sender>>senderPort;
  //Вывод сообщения на экран
  ui->plainTextEdit->appendPlainText("IP: "+ sender.toString()+"  Port:" + QString::number(senderPort)
                                     +"  Номер: " + QString::number(number)
                                     + "  Протокол: "+ QString::number(protocol)
                                     + "  Сообщение: " + msg);
}


void MainWindow::showText()
{
   // ui->plainTextEdit->appendPlainText(data);
}





//Обработка нажанитя кнопки "Удалить"
void MainWindow::on_clearButton_clicked()
{
 ui->plainTextEdit->clear();
}
