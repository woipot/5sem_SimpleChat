#include "chat_presenter.h"

chat_presenter::chat_presenter()
{
    chat_model_ = new chat_model();
    QObject::connect(chat_model_, SIGNAL(new_msg(QString)), this, SLOT(print_msg(QString)));
    QObject::connect(chat_model_, SIGNAL(error(QString)), this, SLOT(take_error(QString)));

    QObject::connect(chat_model_, SIGNAL(connection_success()), this, SLOT(on_connect()));
    QObject::connect(chat_model_, SIGNAL(disconnection_success()), this, SLOT(on_disconnect()));
}

chat_presenter::~chat_presenter()
{
    delete chat_model_;
}


//-------------------seters
void chat_presenter::set_browser(QTextBrowser *browser)
{
    messages_browser_ = browser;
}

void chat_presenter::set_message_edit(QTextEdit *text_edit)
{
    message_edit_ = text_edit;
}

void chat_presenter::set_info_label(QLabel *label)
{
    info_label_ = label;
}

void chat_presenter::set_connect_action(QAction *connect_action)
{
    connect_action_ = connect_action;
}

void chat_presenter::set_disconnect_action(QAction *disconnect_action)
{
    disconnect_action_ = disconnect_action;
}

//------------------public methods
void chat_presenter::clear_chat()
{
    messages_browser_->clear();
}

bool chat_presenter::save_dialogs(QString patch)
{
    bool is_successful = false;
    QFile fileOut(patch); // Связываем объект с файлом fileout.txt
    if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writeStream(&fileOut);
        writeStream << messages_browser_->toPlainText() << "\n";
        fileOut.close(); // Закрываем файл
        is_successful = true;
    }

    return is_successful;
}

void chat_presenter::connect_to(const QString &host, unsigned short port,const QString &username)
{
    chat_model_->connect_as(username, host, port);
}

void chat_presenter::disconnect()
{
    chat_model_->disconnect();
}

void chat_presenter::send_message()
{
    auto msg = message_edit_->toPlainText().trimmed();

    if (!msg.isEmpty())
    {
        chat_model_->send(msg);
        message_edit_->clear();
    }
}


//-----------------------punblic slots
void chat_presenter::print_msg(QString msg)
{
    auto command = msg.at(0);
    auto proccessed_msg = msg.remove(0, 1);

    if(command == '0')
        messages_browser_->append(proccessed_msg);
    else
        take_error(proccessed_msg);
}

void chat_presenter::take_error(QString msg)
{
    QMessageBox mb;
    mb.setIcon(QMessageBox::Critical);
    mb.setInformativeText(msg);
    mb.exec();
}

void chat_presenter::on_connect()
{
    connect_action_->setEnabled(false);
    disconnect_action_->setEnabled(true);

    auto port_str = QString::number(chat_model_->get_port());
    auto host = chat_model_->get_host();

    info_label_->setText(host + " : " + port_str);
}

void chat_presenter::on_disconnect()
{
    connect_action_->setEnabled(true);
    disconnect_action_->setEnabled(false);

    info_label_->setText("No connection");
}
