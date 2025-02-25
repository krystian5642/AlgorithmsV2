#ifndef ADDGRAPHEDGEDIALOG_H
#define ADDGRAPHEDGEDIALOG_H

#include "ui_addgraphedgedialog.h"

#include <QDialog>

class AddGraphEdgeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddGraphEdgeDialog(QWidget *parent = nullptr);
    ~AddGraphEdgeDialog();

    int getStartValue(bool* ok = nullptr) const;
    int getEndValue(bool* ok = nullptr) const;
    double getEdgeWeight(bool* ok = nullptr) const;

private slots:
    void on_addEdgeButton_clicked();

private:
    void adjustLayoutWidgetPositionToCenter();

    Ui::AddGraphEdgeDialog *ui;
};

#endif // ADDGRAPHEDGEDIALOG_H
