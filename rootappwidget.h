#ifndef ROOTAPPWIDGET_H
#define ROOTAPPWIDGET_H

#include <QWidget>

namespace Ui {
class RootAppWidget;
}

class RootAppWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RootAppWidget(QWidget *parent = nullptr);
    ~RootAppWidget();

private:
    Ui::RootAppWidget *ui;
};

#endif // ROOTAPPWIDGET_H
