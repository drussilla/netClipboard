#include "server.h"

Server::Server()
{
    is_read = false;
}
bool Server::start(int port)
{
    tcp = new QTcpServer();
    if(!tcp->listen(QHostAddress::Any, port))
    {
        tcp->close();
        return false;
    }
    connect(tcp, SIGNAL(newConnection()), SLOT(newConnection()));
    nblock = 0;
    return true;
}
void Server::newConnection()
{
    QTcpSocket* tcpcli = tcp->nextPendingConnection();
    connect(tcpcli, SIGNAL(disconnected()), tcpcli, SLOT(deleteLater()));
    connect(tcpcli, SIGNAL(readyRead()), SLOT(readSocket()));
}
void Server::readSocket()
{
    QTcpSocket* client = (QTcpSocket*)sender();
    QDataStream in(client);
    in.setVersion(QDataStream::Qt_4_5);
    for(;;)
    {
        if(!nblock)
        {
            if(client->bytesAvailable() < sizeof(quint16))
                break;
            in >> nblock;
        }
        if(client->bytesAvailable() < nblock)
            break;
        QString dat;
        in >> dat;
        nblock = 0;
        is_read = true;
        QClipboard *cl = QApplication::clipboard();
        cl->setText(dat);

    }
}
bool Server::is_Read()
{
    return is_read;
}
void Server::setis_Read(bool f)
{
    is_read = f;
}
bool Server::stop()
{
    tcp->close();
    return true;
}
