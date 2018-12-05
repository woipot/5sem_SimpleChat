#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QDialogButtonBox>
#include <QRegExp>
#include <QMessageBox>
#include <QFont>
#include <QPair>

#include "connect_params.h"

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = nullptr);
    ~ConnectDialog();

public:
    CONNECT_PARAMS get_result();

private:
    Ui::ConnectDialog *ui;

private:
    bool static check_host(const QString &host_name);

private slots:
    void button_accept();
    void button_close();

    void button_set_localhost();
};

#endif // CONNECTDIALOG_H
