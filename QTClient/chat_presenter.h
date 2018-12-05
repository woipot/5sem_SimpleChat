#ifndef CHAT_PRESENTER_H
#define CHAT_PRESENTER_H

#include "chat_model.h"

#include "QTextBrowser"
#include "QTextEdit"
#include "QLabel"
#include "QAction"
#include "QString"
#include "QFile"
#include "QTextStream"
#include "QObject"

#include "QMessageBox"


class chat_presenter : public QObject
{
    Q_OBJECT

    QTextBrowser *messages_browser_;
    QTextEdit *message_edit_;
    QLabel *info_label_;
    QAction *connect_action_;
    QAction *disconnect_action_;


    chat_model *chat_model_;



public:
    chat_presenter();
    ~chat_presenter();

    void set_browser(QTextBrowser *browser);
    void set_message_edit(QTextEdit *text_edit);
    void set_info_label(QLabel *label);
    void set_connect_action(QAction *connect_action);
    void set_disconnect_action( QAction *disconnect_action);


    void clear_chat();
    bool save_dialogs(QString patch);

    void connect_to(const QString &host, unsigned short port, const QString &username);
    void disconnect();

    void send_message();

public slots:
    void print_msg(QString msg);
    void take_error(QString msg);

    void on_connect();
    void on_disconnect();

};

#endif // CHAT_PRESENTER!++++++++_H
