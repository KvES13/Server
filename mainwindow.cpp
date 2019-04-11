#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "server.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serv = new server();


    ui->lineAddress->setText((serv->GetServerAdrress()));
    ui->linePort->setText((serv->GetServerPort()));

    //serv->ReadMessage();

    connect(serv,SIGNAL(id(QString)),this,SLOT(showID(QString)));
    connect(serv,SIGNAL(message(QString)),this,SLOT(showMessage(QString)));

//    ui->plainTextEdit->appendPlainText(serv->info);
//    ui->plainTextEdit->appendPlainText(serv->data);
    showText();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showMessage(QString msg)
{
   ui->plainTextEdit->appendPlainText(msg);
}

void MainWindow::showID(QString id)
{
  ui->plainTextEdit->appendPlainText(id);
}




void MainWindow::showText()
{
   // ui->plainTextEdit->appendPlainText(data);
}






void MainWindow::on_clearButton_clicked()
{
 ui->plainTextEdit->clear();
}
