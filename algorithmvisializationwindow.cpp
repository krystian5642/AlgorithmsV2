#include "algorithmvisializationwindow.h"
#include "Graphs/graphwidget.h"

#include "ui_algorithmvisializationwindow.h"

#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QComboBox>
#include <QTimer>
#include <QElapsedTimer>
#include <QLineSeries>
#include <QChartView>
#include <QStandardItemModel>

AlgorithmVisualizationWindow::AlgorithmVisualizationWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AlgorithmVisualizationWindow)
{
    setupUi();
}

AlgorithmVisualizationWindow::~AlgorithmVisualizationWindow()
{
    delete ui;
}

void AlgorithmVisualizationWindow::paintEvent(QPaintEvent *event)
{
    ui->statusbar->showMessage(QString("Last paint time : %1 ms").arg(dataStructureWidget->getLastPaintTime()));
}

void AlgorithmVisualizationWindow::on_actionSave_triggered()
{
    dataStructureWidget->saveAction();
}

void AlgorithmVisualizationWindow::on_actionLoad_triggered()
{
    dataStructureWidget->loadAction();
}

void AlgorithmVisualizationWindow::on_actionClear_triggered()
{
    dataStructureWidget->clearAction();
}

void AlgorithmVisualizationWindow::on_actionGenerateRandomStructure_triggered()
{
    dataStructureWidget->generateRandomStructureAction();
}

void AlgorithmVisualizationWindow::on_actionRun_Algorithm_triggered(bool isOn)
{
    //graphWidget->visualizeAlgorithmAction(algorithmComboBox->currentText(), !isOn);
}

void AlgorithmVisualizationWindow::setupUi()
{
    ui->setupUi(this);

    dataStructureWidget = new GraphWidget(this);
    setDataStructureWidget(dataStructureWidget);

    QStringList algorithmNames;
    dataStructureWidget->getAlgorithmNames(algorithmNames);

    QStandardItemModel* model = new QStandardItemModel;
    model->setHorizontalHeaderLabels({"All algorithms"});

    QStandardItem* graphsCategory = new QStandardItem("Graphs");
    for(const auto& algorithmName : algorithmNames)
    {
        QStandardItem* algorithmItem = new QStandardItem(algorithmName);
        graphsCategory->appendRow(algorithmItem);
    }

    model->appendRow(graphsCategory);

    connect(ui->treeView, &QTreeView::clicked, this, [&](const QModelIndex& index)
    {
        const QString algorithmName = index.data().toString();
        if(const QSharedPointer<Algorithm> algorithm = dataStructureWidget->getAlgorithmToExecute(algorithmName))
        {
            QWidget* propertyWidget = algorithm->getPropertiesWidget();
            auto* layoutItem = ui->verticalLayout_2->replaceWidget(ui->verticalLayout_2->itemAt(1)->widget(), propertyWidget);
            delete layoutItem->widget();
        }
        else
        {
            auto* layoutItem = ui->verticalLayout_2->replaceWidget(ui->verticalLayout_2->itemAt(1)->widget(), new QWidget);
            delete layoutItem->widget();
        }
    });

    ui->treeView->setModel(model);
}

void AlgorithmVisualizationWindow::setDataStructureWidget(DataStructureWidget *widget)
{
    ui->horizontalLayout->replaceWidget(ui->horizontalLayout->itemAt(1)->widget(), widget);
}

QString AlgorithmVisualizationWindow::getSelectedAlgorithmName() const
{
    const auto modelIndex = ui->treeView->selectionModel()->currentIndex();
    return modelIndex.isValid() ? modelIndex.data().toString() : QString{};
}










