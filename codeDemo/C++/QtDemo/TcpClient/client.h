#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class QTcpSocket;
class Client : public QDialog
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private:
    Ui::Client *ui;

    QTcpSocket *tcpSocket;
};
#endif // CLIENT_H
