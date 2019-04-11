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
    void showMessage(QString msg);
    void showID(QString id);
    void showText();

private slots:


    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    server *serv;
};

#endif // MAINWINDOW_H
