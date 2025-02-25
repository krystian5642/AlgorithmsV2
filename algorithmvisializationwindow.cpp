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
    ui->statusbar->showMessage(QString("Last paint time : %1 ms").arg(graphWidget->getLastPaintTime()));
}

void AlgorithmVisualizationWindow::on_actionSave_triggered()
{
    graphWidget->saveAction();
}

void AlgorithmVisualizationWindow::on_actionLoad_triggered()
{
    graphWidget->loadAction();
}

void AlgorithmVisualizationWindow::on_actionClear_triggered()
{
    graphWidget->clearAction();
}

void AlgorithmVisualizationWindow::on_actionRun_Algorithm_triggered(bool isOn)
{
    //graphWidget->visualizeAlgorithmAction(algorithmComboBox->currentText(), !isOn);
}

void AlgorithmVisualizationWindow::on_actionGenerateRandomGraph_triggered()
{
    graphWidget->generateRandomAction();
}

void AlgorithmVisualizationWindow::on_actionGenerateRandomGridGraph_triggered()
{
    // graphWidget->clearGraph();

    // // this info will be taken from UI later
    // constexpr int columns = 20;
    // constexpr int rows = 20;
    // constexpr int nodeSpace = 50;
    // constexpr QPoint startLoc(50, 50);

    // QList<int> prevRow(columns);
    // for(int i = 0; i < rows; i++)
    // {
    //     int prevValue = -1;
    //     for(int j = 0; j < columns; j++)
    //     {
    //         const int randomValue = QRandomGenerator::global()->bounded(10000);

    //         if(graphWidget->addNode(randomValue, QPoint(startLoc.x()  + nodeSpace * j, startLoc.y() + nodeSpace * i)))
    //         {
    //             if(j > 0 && prevValue != -1)
    //             {
    //                 graphWidget->addEdge(prevValue, randomValue);
    //             }

    //             if(i > 0 && prevRow[j] != -1)
    //             {
    //                 graphWidget->addEdge(prevRow[j], randomValue);
    //             }

    //             prevRow[j] = randomValue;

    //             prevValue = randomValue;
    //         }
    //         else
    //         {
    //             prevRow[j] = -1;
    //         }
    //     }
    // }
    // graphWidget->update();
    // graphWidget->updateGraphProperites();
}

void AlgorithmVisualizationWindow::on_actionAlgorithm_benchmark_triggered()
{
    graphWidget->runBenchmarkAction(getSelectedAlgorithmName());
}

void AlgorithmVisualizationWindow::setupUi()
{
    ui->setupUi(this);

    graphWidget = new GraphWidget(this);
    setAlgorithmWidget(graphWidget);

    QStringList algorithmNames;
    graphWidget->getAlgorithmNames(algorithmNames);

    QStandardItemModel* model = new QStandardItemModel;
    model->setHorizontalHeaderLabels({"All algorithms"});

    QStandardItem* graphsCategory = new QStandardItem("Graphs");
    foreach(const QString& algorithmName, algorithmNames)
    {
        QStandardItem* algorithmItem = new QStandardItem(algorithmName);
        graphsCategory->appendRow(algorithmItem);
    }

    model->appendRow(graphsCategory);

    ui->treeView->setModel(model);
}

void AlgorithmVisualizationWindow::setAlgorithmWidget(QWidget *widget)
{
    ui->horizontalLayout->replaceWidget(ui->horizontalLayout->itemAt(1)->widget(), widget);
}

QString AlgorithmVisualizationWindow::getSelectedAlgorithmName() const
{
    const auto modelIndex = ui->treeView->selectionModel()->currentIndex();
    return modelIndex.isValid() ? modelIndex.data().toString() : QString{};
}










