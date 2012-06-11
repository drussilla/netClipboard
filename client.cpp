#include "client.h"

Client::Client()
{
    send = false;
    ip = "";
    port = 12345;
}
void Client::setServer(QString nip, int nport)
{
    port = nport;
    ip=nip;
}
void Client::setSend(bool s)
{
    send = s;
}
bool Client::isSend()
{
    return send;
}
void Client::sendData()
{
    tcp = new QTcpSocket(this);
    tcp->connectToHost(QHostAddress(ip), port);
    QClipboard* clip = QApplication::clipboard();
    QString str = clip->text();
    QByteArray arr;
    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_5);
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(arr.size() - sizeof(quint16));
    tcp->write(arr);
}

