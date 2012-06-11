#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtGui/QApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QClipboard>
#include <QString>
#include <QMessageBox>

class Client : public QObject
{
public:
    Client();
    void setServer(QString nip, int nport);
    void setSend(bool s);
    bool isSend();
    void sendData();
private:
    QTcpSocket* tcp;
    bool send;
    int port;
    QString ip;
};

#endif // CLIENT_H
