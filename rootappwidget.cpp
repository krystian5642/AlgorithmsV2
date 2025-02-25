#include "algorithmvisializationwindow.h"
#include "Core/algorithmbenchmarkwindow.h"
#include "rootappwidget.h"
#include "ui_rootappwidget.h"

RootAppWidget::RootAppWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RootAppWidget)
{
    ui->setupUi(this);

    AlgorithmVisualizationWindow* visualizationTab = new AlgorithmVisualizationWindow;
    ui->appTabsWidget->addTab(visualizationTab, "Visualization");

    AlgorithmBenchmarkWindow* bechmarkTab = new AlgorithmBenchmarkWindow;
    ui->appTabsWidget->addTab(bechmarkTab, "Benchmark");

    QWidget* singleRunTab = new QWidget;
    ui->appTabsWidget->addTab(singleRunTab, "Single run");
}

RootAppWidget::~RootAppWidget()
{
    delete ui;
}
