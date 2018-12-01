#include "chat_presenter.h"

chat_presenter::chat_presenter()
{
    chat_model_ = new chat_model();
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
