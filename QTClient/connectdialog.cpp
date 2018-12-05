#include "connectdialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(button_accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(button_close()));

    connect(ui->localhostButton, SIGNAL(clicked()), this, SLOT(button_set_localhost()));
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

CONNECT_PARAMS ConnectDialog::get_result()
{
    auto host_name = ui->hostEdit->text().toLower();
    unsigned short port = ui->portSpinBox->value();

    auto username = ui->nameEdit->text();

    CONNECT_PARAMS params = {host_name, port, username};

    return params;
}

//--------------private methods
bool ConnectDialog::check_host(const QString &host_name)
{
    const QRegExp re("\\b(?:\\d{1,3}\\.){3}\\d{1,3}\\b");
    const QRegExp re_l("localhost" );

    bool is_ip = re.exactMatch(host_name);
    bool is_localhost = re_l.exactMatch(host_name);

    return is_ip || is_localhost;
}


//-------------------private slots
void ConnectDialog::button_accept()
{
    auto host_name = ui->hostEdit->text().toLower();
    if (!check_host(host_name))
    {
        QMessageBox msg;
        msg.setInformativeText("#Error: vrong host name");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
    else if(ui->nameEdit->text().trimmed().isEmpty())
    {
        QMessageBox msg;
        msg.setInformativeText("#Error: empty field <name>");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
    else
    {
        accept();
    }
}

void ConnectDialog::button_close()
{
    close();
}

void ConnectDialog::button_set_localhost()
{
    ui->hostEdit->setText("localhost");
}


