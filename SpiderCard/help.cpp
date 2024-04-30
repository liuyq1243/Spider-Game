#include "help.h"
#include "ui_help.h"

help::help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
    setWindowTitle("help");

    ui->tabWidget->setTabText(0, "Spider");
    ui->tabWidget->setTabText(1, "More");
}

help::~help()
{
    delete ui;
}
