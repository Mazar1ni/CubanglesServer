#include "tcpsocket.h"
#include <QDataStream>

TcpSocket::TcpSocket(QObject *parent) : QTcpSocket(parent)
{

}

void TcpSocket::onWrite(QString message)
{
    QByteArray  arr;

    QDataStream out(&arr, QIODevice::WriteOnly);
    out << message;

    write(arr);
    flush();
}
