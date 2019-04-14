#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString info;
    QString data;

public slots:
    void showText();
    void showArray(QByteArray arr);
private slots:


    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    Server *server;
};

#endif // MAINWINDOW_H
