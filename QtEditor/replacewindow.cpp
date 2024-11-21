#include "replacewindow.h"
#include "MainWindow.h"
#include<QMessageBox>

ReplaceWindow::ReplaceWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("替换"));
}

ReplaceWindow::~ReplaceWindow()
{
    delete ui;
}

void ReplaceWindow::on_findButton_clicked()
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


void ReplaceWindow::on_replaceButton_clicked()
{
    // 获取替换文本和查找文本
    QString searchText = getSearchText();
    QString replaceText = getReplaceText();
    if(replaceText.isEmpty()){
        QMessageBox::information(this, tr("替换"), tr("请输入替换字段"));
        return;
    }
    // 检查是否已经找到了文本
    if (!searchText.isEmpty()) {
        // 假设您的主窗口（MainWindow）有一个方法可以获取当前活动的 ChileWnd 实例
        ChileWnd *activeChildWnd = qobject_cast<MainWindow*>(parent())->activateChildWnd();

        if (activeChildWnd) {
            // 调用 ChileWnd 的替换方法
            activeChildWnd->replaceText(replaceText);
        }
    } else {
        QMessageBox::information(this, tr("替换"), tr("请先查找"));
    }
}

