#ifndef CHAT_PRESENTER_H
#define CHAT_PRESENTER_H

#include "chat_model.h"

#include "QTextBrowser"
#include "QTextEdit"
#include "QLabel"

class chat_presenter
{
    QTextBrowser *messages_browser_;
    QTextEdit *message_edit_;
    QLabel *info_label_;

    chat_model *chat_model_;

public:
    chat_presenter();
    ~chat_presenter();

    void set_browser(QTextBrowser *browser);
    void set_message_edit(QTextEdit *text_edit);
    void set_info_label(QLabel *label);

};

#endif // CHAT_PRESENTER!++++++++_H
