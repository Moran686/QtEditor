#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::aboutwindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("关于"));
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
