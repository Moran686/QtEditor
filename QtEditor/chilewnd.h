#ifndef CHILEWND_H
#define CHILEWND_H

#include <QWidget>
#include <QTextEdit>

class ChileWnd : public QTextEdit
{
    Q_OBJECT
public:
    //ChileWnd();
    explicit ChileWnd(QWidget *parent = nullptr);
    QString m_CurDocPath; // 当前文档路径
    void newDoc(); // 新建文档
    QString getCurDocName(); // 从路径中提取文档名
    bool loadDoc(const QString& docName); //加载文档验证
    void setCurDoc(const QString& docName); //设置文档名字
    bool saveDoc(); //保存文档
    bool saveAsDoc(); //另存为
    bool saveDocOpt(QString docName); //保存文件的操作逻辑
    void setFormatOnSelectedWord(const QTextCharFormat &fmt);//对选中的字体格式进行设置
    void setAlignOfDocumentText(int aligntype); //设置段落对齐方式
    void setParaSyle(int pstyle); //设置项目符号

    void findText(const QString &searchText, bool searchDown);
    void replaceText(const QString &replaceText);

protected:
    void closeEvent(QCloseEvent *event); //关闭事件发生时，进行未保存该文档提示

signals:
    void copyAvailble(bool available);
    void statusInfoChanged(const QString &statusInfo); // 新信号，传递状态信息


private:
    bool promptSave(); //提示未保存但是要关闭的时候进行保存

private slots:
    void docBeModified(); // 文档修改时，窗口的标题栏加‘*’
    void onCursorPositionChanged(); // 光标位置变化时调用的槽函数

private:
    bool m_bSaved; // 文档是否保存
    QTextCharFormat highlightFormat;
    QString lastSearchText;
    QTextCursor lastSearchCursor;// 存储上次查找的光标位置
};

#endif // CHILEWND_H
