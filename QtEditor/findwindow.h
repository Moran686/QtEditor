#ifndef FINDWINDOW_H
#define FINDWINDOW_H

// FindWindow.h

#include <QDialog>
#include "ui_findwindow.h"
#include "ChileWnd.h"

class FindWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FindWindow(QWidget *parent = nullptr);
    QString getSearchText() const { return ui->findText->text(); }
    bool isSearchDown() const { return ui->findDownRadioButton->isChecked(); }

private slots:
    void on_findButton_clicked();

private:
    Ui::dialog *ui;
};

#endif // FINDWINDOW_H
