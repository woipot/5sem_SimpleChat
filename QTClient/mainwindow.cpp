#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    presenter_ = new chat_presenter();
}

MainWindow::~MainWindow()
{
    delete presenter_;
    delete ui;
}
