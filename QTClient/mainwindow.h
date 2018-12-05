#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chat_presenter.h"
#include "connectdialog.h"

#include "QFileDialog"
#include "QMessageBox"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    chat_presenter *presenter_;

private slots:
    void on_save();
    void on_clear();
    void on_connect();
    void on_disconnect();
    void on_show_about();

    void on_send();
};

#endif // MAINWINDOW_H
