#ifndef TASK_H
#define TASK_H

#include <QRunnable>
#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

class Socket;

class Task : public QObject, public QRunnable
{
    Q_OBJECT

public:
    Task(QString info, Socket *client);
    ~Task();

protected:
    void run();

private:
    void databaseConnection();
    void authentication(QString login, QString pass);
    void sendToClient(QString message);

signals:
    void result(QString output);

private:
    QString str;
    QSqlDatabase database;
    Socket* client;
};

#endif // TASK_H
