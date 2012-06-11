#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QClipboard>
#include <QString>
#include <QtGui/QApplication>

class Server : public QObject
{
    Q_OBJECT

public:
    Server();
    bool start(int port);
    bool stop();
    void setis_Read(bool f);
    bool is_Read();
private:
    QTcpServer* tcp;
    quint16 nblock;
    bool is_read;
public slots:
    void newConnection();
    void readSocket();

};

#endif // SERVER_H
