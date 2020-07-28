#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mTcpServer = new QTcpServer(this);
    mTcpServer->setMaxPendingConnections(1);//允许设置最大连接数
    connect(mTcpServer,SIGNAL(newConnection()),this,SLOT(tcpNewConnection()));

    mTcpServer->listen(QHostAddress::Any,1234);


    ui->label->setText("disconnected");//显示无连接
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tcpNewConnection()
{
    mSocket = mTcpServer->nextPendingConnection();
    if(mSocket)
    {
        connect(mSocket,SIGNAL(readyRead()),this,SLOT(tcpReadyRead()));
        connect(mSocket,SIGNAL(disconnected()),this,SLOT(tcpDisconnect()));
        ui->label->setText("connected");//显示建立连接
    }
}

void MainWindow::tcpReadyRead()
{
    ui->textEdit->append(mSocket->readAll());
}

void MainWindow::tcpDisconnect()
{
    mSocket->deleteLater();
    mSocket = 0;
    ui->label->setText("disconnected");//显示无连接
}


void MainWindow::on_pushButton_clicked()
{
     mSocket->write(ui->lineEdit->text().toLatin1());
}
