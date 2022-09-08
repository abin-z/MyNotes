#include "client.h"
#include "ui_client.h"
#include <QTcpSocket>

Client::Client(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
}

Client::~Client()
{
    delete ui;
}


