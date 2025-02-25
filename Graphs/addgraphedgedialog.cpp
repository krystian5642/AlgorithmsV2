#include "addgraphedgedialog.h"

#include <sstream>

AddGraphEdgeDialog::AddGraphEdgeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddGraphEdgeDialog)
{
    ui->setupUi(this);
    ui->weightLineEdit->setText("0");
    adjustLayoutWidgetPositionToCenter();
}

AddGraphEdgeDialog::~AddGraphEdgeDialog()
{
    delete ui;
}

int AddGraphEdgeDialog::getStartValue(bool* ok) const
{
    std::istringstream stream(ui->startLineEdit->text().toStdString());
    int value = 0;

    if(ok)
    {
        *ok = !stream.fail() && stream.eof();
        stream >> value;
    }

    return value;
}

int AddGraphEdgeDialog::getEndValue(bool* ok) const
{
    std::istringstream stream(ui->endLineEdit->text().toStdString());
    int value = 0;

    if(ok)
    {
        *ok = !stream.fail() && stream.eof();
        stream >> value;
    }

    return value;
}

void AddGraphEdgeDialog::adjustLayoutWidgetPositionToCenter()
{
    const auto& widgetGeometry = ui->layoutWidget->geometry();
    const int newX = geometry().size().width() / 2 - widgetGeometry.size().width() / 2;
    const int newY = geometry().size().height() / 2 - widgetGeometry.size().height() / 2;

    ui->layoutWidget->setGeometry(QRect(newX, newY, widgetGeometry.size().width(), widgetGeometry.size().height()));
}

void AddGraphEdgeDialog::on_addEdgeButton_clicked()
{
    accept();
}

double AddGraphEdgeDialog::getEdgeWeight(bool* ok) const
{
    return ui->weightLineEdit->text().toFloat(ok);
}


