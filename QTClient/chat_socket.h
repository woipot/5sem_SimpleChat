#ifndef CHAT_SOCKET_H
#define CHAT_SOCKET_H

#include <iostream>

#include "QObject"
#include "QString"
#include <QTcpSocket>
#include <QDataStream>

class chat_socket : public QObject
{
public:
    Q_OBJECT

    QTcpSocket *tcp_socket_;
    bool credentials_sent_;

    unsigned short port_;
    QString host_;
public:
    chat_socket();
    ~chat_socket();

    unsigned short get_port();
    QString get_host();

     void disconnect();

signals:
    void new_msg(const QString &msg);
    void error(const QString &er);
    void connection_success();
    void disconnection_success();

protected:
    void send_msg(const QString &msg);
    void send_command(const QString &cmd, const QString &msg);

    void connect(QString host, unsigned short port);

private slots:
    void handle_messages();
    void handle_errors(QAbstractSocket::SocketError socketError);

    void on_connect();
    void on_disconnect();
};

#endif // CHAT_SOCKET_H
