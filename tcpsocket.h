#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>

class TcpSocket : public QTcpSocket
{
public:
    TcpSocket(QObject *parent = nullptr);

public slots:
    void onWrite(QString message);
};

#endif // TCPSOCKET_H
