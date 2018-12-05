#ifndef CHAT_MODEL_H
#define CHAT_MODEL_H

#include "chat_socket.h"

class chat_model : public chat_socket
{
    QString error_bufer_;
public:
    chat_model();
    ~chat_model();

    enum commands { Msg, Validate};

    void connect_as(const QString &username, QString host, unsigned short port);
    void send(const QString &msg);
};


#endif // CHAT_MODEL_H
