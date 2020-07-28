#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void tcpNewConnection(); //用来绑定sever的newconnection信号
    void tcpReadyRead(); //用来绑定socket的readyread信号
    void tcpDisconnect();//用来绑定socket的disconnect信号

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer *mTcpServer;
    QTcpSocket *mSocket;
};
#endif // MAINWINDOW_H
