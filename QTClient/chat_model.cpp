#include "chat_model.h"


chat_model::chat_model() : chat_socket ()
{
    error_bufer_ = "";
}

chat_model::~chat_model()
{

}

void chat_model::connect_as(const QString &username, QString host, unsigned short port)
{
    connect(host, port);
    send_command(QString::number(chat_model::Validate), username);
}

void chat_model::send(const QString &msg)
{
    send_command(QString::number(chat_model::Msg), msg);
}

