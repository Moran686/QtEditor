#ifndef REPLACEWINDOW_H
#define REPLACEWINDOW_H

#include <QDialog>
#include "ui_replacewindow.h"

namespace Ui {
class replacewindow;
}

class ReplaceWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceWindow(QWidget *parent = nullptr);
    ~ReplaceWindow();
    QString getSearchText() const { return ui->findText->text(); }
    QString getReplaceText() const { return ui->replaceText->text(); }
    bool isSearchDown() const { return ui->findDownRadioButton->isChecked(); }

private slots:
    void on_findButton_clicked();

    void on_replaceButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // REPLACEWINDOW_H
