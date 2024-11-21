#include "chilewnd.h"
#include <QFileInfo>
#include<QFileDialog>
#include<QTextDocumentWriter>
#include<QMessageBox>
#include<QCloseEvent>
#include<QTextBlock>
#include<QTextList>
#include<QtWidgets>
#include <QTextDocument>

ChileWnd::ChileWnd(QWidget *parent) : QTextEdit(parent)
{
    // 子窗口关闭时销毁该类的对象
    setAttribute(Qt::WA_DeleteOnClose);
    //
    m_bSaved = false;

    connect(this, &QTextEdit::cursorPositionChanged, this, &ChileWnd::onCursorPositionChanged);
}

// 新建文档
void ChileWnd::newDoc()
{
    static int wndSeqNum = 1; // 新建文档序号
    m_CurDocPath = QString("文档 %1").arg(wndSeqNum++); // 实现新建文档序号自加

    // 设置窗体标题，文档改动后名称后加‘*’
    setWindowTitle(m_CurDocPath + "[*]" + "- MyEditor");
    connect(document(), SIGNAL(contentsChanged()), this, SLOT(docBeModified())); // 连接槽函数
}

// 获取文件名字
QString ChileWnd::getCurDocName()
{
    return QFileInfo(m_CurDocPath).fileName();
}

//加载指定名称的文档
bool ChileWnd::loadDoc(const QString &docName)
{
    if(!docName.isEmpty())
    {
        QFile file(docName);
        if(!file.exists()) //文件是否存在
            return false;
        if(!file.open(QFile::ReadOnly)) // 打开文档并检查是否只读
            return false;               //如果文件不能以只读方式打开
        QByteArray text = file.readAll(); //读取文件内容
        if(Qt::mightBeRichText(text)) // 是否是富文本类型并设置文本内容
            setHtml(text);
        else
            setPlainText(text); //设置为纯文本

        setCurDoc(docName); //设置当前文档路径
        connect(document(),SIGNAL(contentsChanged()),this,SLOT(docBeModified()));

        return true;
    }
}

//设置当前文档路径及相关状态
void ChileWnd::setCurDoc(const QString &docName)
{
    //返回标准名称路径，可以过滤“.”和“..”
    m_CurDocPath = QFileInfo(docName).canonicalFilePath();
    m_bSaved = true;                            //文档已被保存
    document()->setModified(false);             //文档未被改动
    setWindowModified(false);                   //窗口不显示改动标识
    setWindowTitle(getCurDocName() + "[*]");    //设置子窗口标题
}

//保存文档
bool ChileWnd::saveDoc()
{
    //查询文档当前是否保存的状态（全局变量）
    if(m_bSaved)
        return saveDocOpt(m_CurDocPath);
    else
        saveAsDoc();
}

//另存为
bool ChileWnd::saveAsDoc()
{
    QString docName = QFileDialog::getSaveFileName(this,
                                     "另存为",
                                     "文档.txt", // 默认保存为 txt 格式
                                     "文本文件(*.txt);;"
                                     "HTML文件(*.html *.htm);;"
                                     "Word文件(*.doc *.docx);;"
                                     "PDF文件(*.pdf);;"
                                     "图片文件(*.png *.jpg *.jpeg *.bmp);;"
                                     "所有文件(*.*)");
    if(docName.isEmpty())
        return false;
    else
        return saveDocOpt(docName);
}

//保存文件的操作逻辑
bool ChileWnd::saveDocOpt(QString docName)
{
    /*
    //CaseInsensitive大小写都可以
    if( !(docName.endsWith(".htm",Qt::CaseInsensitive)||
                        docName.endsWith(".html",Qt::CaseInsensitive)))
    {
        //如果没有后缀就添加
        docName += ".html";
    }
*/
    //创建一个 QTextDocumentWriter 对象 writer，用于写入文档
    QTextDocumentWriter writer(docName);
    bool isSuccess = writer.write(this->document());
    //如果成功写入，就设置文档名字
    if(isSuccess)
    {
        setCurDoc(docName);
    }
    return isSuccess;
}

void ChileWnd::setFormatOnSelectedWord(const QTextCharFormat &fmt)
{
    //获取文档光标
    QTextCursor tcursor = textCursor();
    if(!tcursor.hasSelection())
        tcursor.select(QTextCursor::WordUnderCursor);//选中模式
    tcursor.mergeCharFormat(fmt);
    //合并格式
    mergeCurrentCharFormat(fmt);
}

//设置段落对齐方式
void ChileWnd::setAlignOfDocumentText(int aligntype)
{
    //给传入的参数设置编号，1-->左端对齐，2-->右端对齐，3-->居中对齐，4-->两端对齐
    if(aligntype == 1)
    {
        setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    }
    else if(aligntype == 2)
    {
        setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    }
    else if(aligntype == 3)
    {
        setAlignment(Qt::AlignCenter);
    }
    else if(aligntype == 4)
    {
        setAlignment(Qt::AlignJustify);
    }
}

void ChileWnd::setParaSyle(int pstyle)
{
    // 获取当前文本光标
    QTextCursor tcursor = textCursor();
    // 声明一个 QTextListFormat::Style 变量，用于存储列表样式
    QTextListFormat::Style sname;
    // 如果 pstyle 不为 0，设置列表样式
    if(pstyle != 0)
    {
        // 根据 pstyle 的值设置不同的列表样式
        switch (pstyle) {
        case 1:
            sname = QTextListFormat::ListDisc; //黑心实心圆
            break;
        case 2:
            sname = QTextListFormat::ListCircle; //空心圆
            break;
        case 3:
            sname = QTextListFormat::ListSquare; //方形
            break;
        case 4:
            sname = QTextListFormat::ListDecimal; //十进制整数
            break;
        case 5:
            sname = QTextListFormat::ListLowerAlpha; //小写字母
            break;
        case 6:
            sname = QTextListFormat::ListUpperAlpha; //大写字母
            break;
        case 7:
            sname = QTextListFormat::ListLowerRoman; //小写罗马字母
            break;
        case 8:
            sname = QTextListFormat::ListUpperRoman; //大写罗马字母
            break;
        default:
            sname = QTextListFormat::ListDisc;
        }

        // 开始编辑块
        tcursor.beginEditBlock();
        // 获取当前段落格式
        QTextBlockFormat tBlockFmt = tcursor.blockFormat();
        // 声明一个 QTextListFormat 变量，用于存储列表格式
        QTextListFormat tListFmt;
        // 如果当前光标所在位置已经有列表
        if(tcursor.currentList())
        {
            // 获取当前列表的格式
            // 使用format方法需要添加头文件QtWidgets
            tListFmt = tcursor.currentList()->format();
        }
        else
        {
            // 如果没有列表，设置新的列表格式
            tListFmt.setIndent(tBlockFmt.indent()+1);
            tBlockFmt.setIndent(0);
            tcursor.setBlockFormat(tBlockFmt);
        }

        // 设置列表样式
        tListFmt.setStyle(sname);
        // 创建列表
        tcursor.createList(tListFmt);
        // 结束编辑块
        tcursor.endEditBlock();
    }
    else
    {
        // 如果 pstyle 为 0，清除列表格式
        QTextBlockFormat tbfmt;
        tbfmt.setObjectIndex(-1);
        tcursor.mergeBlockFormat(tbfmt);
    }
}

void ChileWnd::closeEvent(QCloseEvent *event)
{
    if(promptSave())
        event->accept();
    else
        event->ignore();

}

//提示未保存但是要关闭的时候进行保存
bool ChileWnd::promptSave()
{
    if(!document()->isModified())
        return true;
    //提示消息框
    QMessageBox::StandardButton result;
    result = QMessageBox::warning(this,
                                  QString("系统提示"),
                                  QString("文档%1已修改，是否保存？")
                                  .arg(getCurDocName()),
                                  QMessageBox::Yes | QMessageBox::Discard | QMessageBox::Cancel);
    if(result == QMessageBox::Yes)
        return saveDoc();
    else if(result == QMessageBox::Cancel)
        return false;
    return true;

    if(!document()->isModified())
        return true;

}

// 文档修改时，窗口的标题栏加‘*’
void ChileWnd::docBeModified()
{
    setWindowModified(document()->isModified());
}


void ChileWnd::findText(const QString &searchText, bool searchDown)
{
    if (searchText.isEmpty()) return;

    QTextCursor cursor = this->textCursor();
    QTextDocument *document = this->document();

    QTextCursor foundCursor = document->find(searchText, cursor, searchDown ? QTextDocument::FindFlag(0) : QTextDocument::FindBackward);

    if (!foundCursor.isNull()) {
        this->setTextCursor(foundCursor);
        this->ensureCursorVisible();

        // 更新 lastSearchText 和 lastSearchCursor
        lastSearchText = searchText;
        lastSearchCursor = foundCursor;
        lastSearchCursor.movePosition(QTextCursor::End);
    } else {
        qDebug() << "Text not found:" << searchText;
        QMessageBox::information(this, tr("查找"), tr("没有找到"));
    }
}

void ChileWnd::replaceText(const QString &replaceText)
{
    if (lastSearchCursor.isNull()) {
        QMessageBox::information(this, tr("替换"), tr("请先查找"));
        return;
    }

    // 替换找到的文本
    QTextCursor cursor = this->textCursor();
    cursor.removeSelectedText(); // 移除选中的文本
    cursor.insertText(replaceText); // 插入替换的文本
    cursor.mergeCharFormat(highlightFormat); // 高亮显示替换后的文本

    // 更新 lastSearchCursor 为新的位置
    lastSearchCursor = cursor;
    lastSearchCursor.clearSelection(); // 清除选择，以便光标位于替换文本之后

    this->setTextCursor(cursor); // 设置新的光标位置
    this->ensureCursorVisible(); // 确保光标可见
}

void ChileWnd::onCursorPositionChanged()
{
    QTextCursor cursor = textCursor();
    int line = cursor.blockNumber() + 1; // 获取当前行数，从1开始
    int column = cursor.columnNumber() + 1; // 获取当前列数，从1开始

    // 构建状态信息字符串
    QString statusInfo = tr("%1  | Line: %2 |Column: %3 " ).arg(getCurDocName()).arg(line).arg(column);
    emit statusInfoChanged(statusInfo); // 发出信号，传递状态信息
}
