#include "server.h"
#include "ui_server.h"
#include <QTcpServer>
#include <QDataStream>
#include <QDebug>

Server::Server(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::LocalHost, 9999);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::sendMessage);
}

Server::~Server()
{
    delete ui;
}

void Server::sendMessage(){
    //
}
