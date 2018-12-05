#include "chat_model.h"

chat_model::chat_model()
{
    host_= "";
    port_ = 0;
    tcp_socket_ = new QTcpSocket(this);

    credentials_sent_ = false;

    QObject::connect(tcp_socket_, SIGNAL(readyRead()), this, SLOT(handle_messages()));
    QObject::connect(tcp_socket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handle_errors(QAbstractSocket::SocketError)));
    QObject::connect(tcp_socket_, SIGNAL(connected()), this, SLOT(on_connect()));
    QObject::connect(tcp_socket_, SIGNAL(disconnected()), this, SLOT(on_disconnect()));
}

chat_model::~chat_model()
{
    tcp_socket_->abort();
    delete tcp_socket_;
}


//------------------------------Public methods
void chat_model::send_msg(const QString &msg)
{
    if (!msg.isEmpty())
    {
        tcp_socket_->write(msg.toUtf8());
    }
}


void chat_model::send_command(const QString &msg)
{
    if(!tcp_socket_->isOpen()) return;

    if(!msg.isEmpty())
    {
        auto command_msg = "_UCD_ " + msg;

        tcp_socket_->write(command_msg.toUtf8());
    }
}

void chat_model::connect(QString host, unsigned short port)
{
    host_ = host;
    port_ = port;
    QDataStream in(tcp_socket_);

    std::cout <<  tr("#Info: -> Connecting to %1 on port %2.").arg(host).arg(port).toStdString() << std::endl;
    tcp_socket_->abort();
    tcp_socket_->connectToHost(host, port);

}

void chat_model::disconnect()
{
    tcp_socket_->abort();
    std::cout << tr("#Info: -> Disconnecting from %1.").arg(host_).toStdString() << std::endl;
}

unsigned short chat_model::get_port()
{
    return port_;
}

QString chat_model::get_host()
{
    return host_;
}

//-----------------------------------------private slots
void chat_model::handle_messages()
{
    auto byte_arr = tcp_socket_->readAll();

    QString message = QString::fromUtf8(byte_arr);

    emit new_msg(message);
}

void chat_model::handle_errors(QAbstractSocket::SocketError socketError)
{
    QString msg = "#Error: ";
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        msg += tr("Disconnect from server <%1>").arg(host_);
        break;

    case QAbstractSocket::HostNotFoundError:
        msg += tr("The host <%1, %2> was not found").arg(host_).arg(port_);
        break;

    case QAbstractSocket::ConnectionRefusedError:
        msg += tr("The connection was refused by the peer.\n"
                "Make sure the server is running,\n"
                "and check that the host name and port\n"
                "settings are correct.");
        break;

    default:
        msg += tr("The following error occurred: %1.").arg(tcp_socket_->errorString());
    }

    std::cout << msg.toStdString() << std::endl;

    emit error(msg);
}

void chat_model::on_connect()
{
    std::cout << "#Info: Success conection to host: " << host_.toStdString() << std::endl;

    emit connection_success();
}

void chat_model::on_disconnect()
{
    std::cout << "#Info: Success disconection from host: " << host_.toStdString() << std::endl;

    emit disconnection_success();
}
