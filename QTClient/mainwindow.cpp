#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    presenter_ = new chat_presenter();
    presenter_->set_browser(ui->messagesBrowser);
    presenter_->set_message_edit(ui->messageEdit);
    presenter_->set_info_label(ui->infoLabel);

    presenter_->set_connect_action(ui->actionConnect);
    presenter_->set_disconnect_action(ui->actionDisconnect);

    QObject::connect(ui->actionClear_chat_area, SIGNAL(triggered()), this, SLOT(on_clear()));
    QObject::connect(ui->actionSave_dialog_as, SIGNAL(triggered()), this, SLOT(on_save()));

    QObject::connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(on_connect()));
    QObject::connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(on_disconnect()));

    QObject::connect(ui->actionabout, SIGNAL(triggered()), this, SLOT(on_show_about()));

    QObject::connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(on_send()));
}

MainWindow::~MainWindow()
{
    delete presenter_;
    delete ui;
}


//------------------private slots
void MainWindow::on_save()
{
    QString str = QFileDialog::getSaveFileName(nullptr, "Save to", "", "*.txt");

    if(str != "")
    {
        auto is_successful = presenter_->save_dialogs(str);
        if(!is_successful)
        {
            QMessageBox msg;
            msg.setInformativeText("#Error: cannot saave to this file");
            msg.exec();
        }
    }
}

void MainWindow::on_clear()
{
    presenter_->clear_chat();
}

void MainWindow::on_connect()
{
    ConnectDialog* pInputDialog = new ConnectDialog();
    if (pInputDialog->exec() == QDialog::Accepted) {

        auto res = pInputDialog->get_result();
        presenter_->connect_to(res.host, res.port, res.username);

    }
    delete pInputDialog;
}

void MainWindow::on_disconnect()
{
    presenter_->disconnect();
}

void MainWindow::on_show_about()
{
    QMessageBox msg;
    msg.setInformativeText("Powered by woipot");
    msg.exec();
}

void MainWindow::on_send()
{
    presenter_->send_message();
}
