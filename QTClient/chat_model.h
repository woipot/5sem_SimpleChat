#ifndef CHAT_MODEL_H
#define CHAT_MODEL_H

#include <iostream>

#include "QObject"
#include "QString"
#include <QTcpSocket>
#include <QDataStream>

class chat_model : public QObject
{
    Q_OBJECT

    QTcpSocket *tcp_socket_;
    bool credentials_sent_;

    unsigned short port_;
    QString host_;
public:
    chat_model();
    ~chat_model();

    void send_msg(const QString &msg);
    void send_command(const QString &msg);

    void connect(QString host, unsigned short port);
    void disconnect();

    unsigned short get_port();
    QString get_host();

signals:
    void new_msg(const QString &msg);
    void error(const QString &er);
    void connection_success();
    void disconnection_success();

private slots:
    void handle_messages();
    void handle_errors(QAbstractSocket::SocketError socketError);

    void on_connect();
    void on_disconnect();

};


#endif // CHAT_MODEL_H
