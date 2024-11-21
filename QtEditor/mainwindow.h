#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"chilewnd.h"
#include"findwindow.h"
#include"replacewindow.h"
#include"aboutwindow.h"

#include <QMainWindow>
#include<QCloseEvent>
#include<QSignalMapper>
#include<QMdiSubWindow>
#include<QtPrintSupport/QPrinter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initMainWindow();
    void docNew(); //新建
    void docOpen(); //打开
    void docSave(); //保存
    void docSaveAs(); //另存为
    void docPrint();//文档打印
    void docPrintPreview(); //打印预览
    void docUndo(); //撤销（上一步）
    void docRedo(); //重写(下一步)
    void docCut(); //剪切
    void docCopy(); //复制
    void docPaste(); //粘贴
    void textBold(); //加粗
    void textItalic(); //倾斜
    void textUnderline(); //下划线
    void textFamily(const QString &fmly); //设置字体
    void textSize(const QString &ps); //设置字号
    void textColor(); //设置字体颜色
    void textBackgroundColor();//设置字体背景颜色
    void paraStyle(int nStyle); //设置项目符号

    ChileWnd* activateChildWnd();
    void updateStatusBar(const QString &statusInfo); // 更新状态栏的函数

//槽函数
private slots:
    void on_newAction_triggered();

    void refreshMenus();

    void addSubWndListMenu();

    void on_closeAction_triggered();

    void on_closeAllAction_triggered();

    void on_tileAction_triggered();

    void on_cascadeAction_triggered();

    //设置活动子窗口
    void setActiveSubWindow(QWidget* wnd);

    //关闭事件
    void closeEvent(QCloseEvent *event);


    void on_openAction_triggered();

    void on_saveAction_triggered();

    void on_saveOther_triggered();

    void on_undoAction_triggered();

    void on_redoAction_triggered();

    void on_cutAction_triggered();

    void on_copyAction_triggered();

    void on_pasteAction_triggered();

    void on_blodAction_triggered();

    void on_inclineAction_triggered();

    void on_underlineAction_triggered();

    void on_fontComboBox_activated(const QString &arg1);

    void on_sizeComboBox_activated(const QString &arg1);

    void on_leftAction_triggered();

    void on_rightAction_triggered();

    void on_centerAction_triggered();

    void on_justifyAction_triggered();

    void on_textcolorAction_triggered();

    void on_comboBox_activated(int index);

    void on_textbackgroundcolorAction_triggered();

    void on_wndcolorAction_triggered();

    void on_findAction_triggered();

    void on_replaceAction_triggered();

    void on_toolAction_triggered();

    void on_statusAction_triggered();

    void on_aboutAction_triggered();

private:
    void formatEnable();
    //匹配子窗口是否存在
    QMdiSubWindow* findChileWnd(const QString &docName);

private:
    Ui::MainWindow *ui;
    QSignalMapper* m_WndMapper; //信号映射器
    //ChileWnd *activeChildWnd;
    QLabel *statusLabel; // QLabel 实例
};
#endif // MAINWINDOW_H
