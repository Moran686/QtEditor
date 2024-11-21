// FindWindow.cpp

#include "findwindow.h"
#include "MainWindow.h"

FindWindow::FindWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("查找"));
    //connect(ui->findButton, &QPushButton::clicked, this, &FindWindow::on_findButton_clicked);
}

void FindWindow::on_findButton_clicked()
{
    qDebug() << "on_findButton_clicked entered";
    QString searchText = getSearchText();
    bool searchDown = isSearchDown();

    ChileWnd *activeChildWnd = qobject_cast<MainWindow*>(parent())->activateChildWnd();

    if (activeChildWnd) {
        qDebug() << "findText";
        activeChildWnd->findText(searchText, searchDown); // 调用 ChileWnd 的 findText 方法
    }
}

