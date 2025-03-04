#include "graphwidget.h"

#include <QComboBox>
#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QThreadPool>

#include "../Core/algorithmwidgetlibrary.h"

#include "./ui_graphwidget.h"
#include "addgraphedgedialog.h"

#include "graphalgorithms.h"
#include "graphbenchmark.h"

namespace GraphTypeNames
{
    const QString AllRandom("All random");
    const QString Grid("Grid");
}

RandomGraphPropertiesWindow::RandomGraphPropertiesWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Random Graph");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* layout = new QHBoxLayout;
    mainLayout->addLayout(layout);

    QLabel* label = new QLabel(this);
    label->setText("Graph type : ");

    graphTypesBox = new QComboBox(this);
    graphTypesBox->addItem(GraphTypeNames::AllRandom);
    graphTypesBox->addItem(GraphTypeNames::Grid);

    layout->addWidget(label);
    layout->addWidget(graphTypesBox);

    QPushButton* okButton = new QPushButton("ok", this);
    mainLayout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, this, [this]()
    {
        accept();
    });
}

QString RandomGraphPropertiesWindow::getSelectedGraphTypeName() const
{
    return graphTypesBox->currentText();
}

GraphWidget::GraphWidget(QWidget *parent)
    : DataStructureWidget(parent)
    , ui(new Ui::GraphWidget)
    , algorithm(nullptr)
{
    ui->setupUi(this);

    setMinimumWidth(1100);
    const QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
    setSizePolicy(sizePolicy);
}

GraphWidget::~GraphWidget()
{
    delete ui;
}

void GraphWidget::clearGraph()
{
    graph.clear();
    graphNodeVisualData.clear();
    graphEdgeVisualData.clear();
    update();
}

QJsonObject GraphWidget::toJsonObject() const
{
    QJsonObject locationsAsJsonObject;
    for(auto it = graphNodeVisualData.constBegin(); it != graphNodeVisualData.constEnd(); it++)
    {
        QJsonObject locationAsJsonObject;
        locationAsJsonObject["x"] = it.value().location.x();
        locationAsJsonObject["y"] = it.value().location.y();

        locationsAsJsonObject[QString::number(it.key())] = locationAsJsonObject;
    }
    return locationsAsJsonObject;
}

void GraphWidget::fromJsonObject(const QJsonObject &jsonObj)
{
    graphNodeVisualData.clear();
    for (auto it = jsonObj.constBegin(); it != jsonObj.constEnd(); ++it)
    {
        const QJsonObject jsonObject = it.value().toObject();
        const QPoint graphNodeLocation(jsonObject["x"].toInt(), jsonObject["y"].toInt());

        graphNodeVisualData[it.key().toInt()].location = graphNodeLocation;
    }
    update();
}

void GraphWidget::setNodeColor(int value, const QColor& color, bool callUpdate)
{
    auto it = graphNodeVisualData.find(value);
    if(it != graphNodeVisualData.end() && it->color != color)
    {
        it->color = color;

        if(callUpdate)
        {
            update();
        }
    }
}

void GraphWidget::setEdgeColor(int start, int end, const QColor &color, bool callUpdate)
{
    const QPair<int, int> edge(qMin(start, end), qMax(start, end));
    auto it = graphEdgeVisualData.find(edge);
    if(it != graphEdgeVisualData.end() && it->color != color)
    {
        it->color = color;

        if(callUpdate)
        {
            update();
        }
    }
}

void GraphWidget::setNodesAndEdgesToBlack()
{
    for(auto it = graphNodeVisualData.begin(); it != graphNodeVisualData.end(); it++)
    {
        if(it->color != Qt::black)
        {
            it->color = Qt::black;
        }
    }

    for(auto it = graphEdgeVisualData.begin(); it != graphEdgeVisualData.end(); it++)
    {
        if(it->color != Qt::black)
        {
            it->color = Qt::black;
        }
    }

    update();
}

bool GraphWidget::addNode(int value, const QPoint& location)
{
    if(graph.addNode(value))
    {
        graphNodeVisualData[value].location = location;
        return true;
    }
    return false;
}

void GraphWidget::addEdge(int startValue, int endValue, float weight)
{
    graph.addEdge(startValue, endValue, weight);
}

void GraphWidget::updateGraphProperites()
{
    ui->listWidget->clear();

    QList<QString> properties;
    properties.reserve(3);

    properties.append(QString("Number of nodes : %1").arg(graph.getNodesNum()));
    properties.append(QString("Number of edges : %1").arg(graph.getEdgesNum()));

    for(const auto& property : properties)
    {
        ui->listWidget->addItem(property);
    }
}

void GraphWidget::getAlgorithmNames(QStringList &names) const
{
    names.append("Breadth First Search");
    names.append("Depth First Search");
    names.append("Breadth First Search : Shortest Path");
    names.append("Tree Centers");
}

QSharedPointer<Algorithm> GraphWidget::getAlgorithmToExecute(const QString &algorithmName) const
{
    if(algorithmName == "Breadth First Search")
    {
        return QSharedPointer<Algorithm>(new BFS);
    }
    else if(algorithmName == "Depth First Search")
    {
        return QSharedPointer<Algorithm>(new DFS);
    }
    else if(algorithmName == "Breadth First Search : Shortest Path")
    {
        return QSharedPointer<Algorithm>(new BFSShortestPath);
    }
    else if(algorithmName == "Tree Centers")
    {
        return QSharedPointer<Algorithm>(new TreeCenters);
    }
    return nullptr;
}

void GraphWidget::saveAction()
{
    const auto reply = QMessageBox::question(this, "Confirmation", "Do you want to save this graph and override the saved graph?"
                                             , QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes)
    {
        if(saveGraph())
        {
            saveGraphNodeLocations();
        }
    }
}

void GraphWidget::loadAction()
{
    clearAlgorithm();
    clearGraph();

    if(loadGraph())
    {
        updateGraphProperites();
        loadGraphNodeLocations();
        update();
    }
}

void GraphWidget::clearAction()
{
    clearAlgorithm();
    clearGraph();
    updateGraphProperites();
}

void GraphWidget::generateRandomStructureAction()
{
    RandomGraphPropertiesWindow randomGraphProperities;
    randomGraphProperities.exec();

    if(randomGraphProperities.result() == QDialog::DialogCode::Accepted)
    {
        clearAlgorithm();
        clearGraph();

        const QString selectedGraphTypeName = randomGraphProperities.getSelectedGraphTypeName();

        if(selectedGraphTypeName == GraphTypeNames::AllRandom)
        {
            generateRandomGraph();
        }
        else if(selectedGraphTypeName == GraphTypeNames::Grid)
        {
            generateRandomGridGraph();
        }

        update();
        updateGraphProperites();
    }
}

void GraphWidget::visualizeAlgorithmAction(const QString& algorithmName, bool pause)
{
    if(!pause)
    {
        if(algorithm)
        {
            algorithm->setPauseVisualization(false);
        }
        else
        {
            setNodesAndEdgesToBlack();

            algorithm = qSharedPointerCast<GraphAlgorithm>(getAlgorithmToExecute(algorithmName)).get();
            algorithm->setGraph(&graph);

            connect(algorithm, &Algorithm::visualizationFinished, this, &GraphWidget::clearAlgorithm);

            algorithm->visualize(this);
        }
    }
    else if(algorithm)
    {
        algorithm->setPauseVisualization(true);
    }
}

#include "../Core/algorithmbenchmarkwindow.h"
void GraphWidget::runBenchmarkAction(const QString& algorithmName)
{  
    GraphBenchmark* benchmark = new GraphBenchmark(algorithmName, qSharedPointerCast<GraphAlgorithm>(getAlgorithmToExecute(algorithmName)));
    benchmark->setAutoDelete(true);

    QThreadPool::globalInstance()->start(benchmark);

    AlgorithmBenchmarkWindow* algorithmBenchmarkResultWindow = new AlgorithmBenchmarkWindow;
    algorithmBenchmarkResultWindow->setAttribute(Qt::WA_DeleteOnClose);
    //algorithmBenchmarkResultWindow->setChartTitle(chartTitle);
    algorithmBenchmarkResultWindow->show();

    connect(benchmark, &GraphBenchmark::updated, algorithmBenchmarkResultWindow, &AlgorithmBenchmarkWindow::appendResultPoint);

    //connect(benchmark, &GraphBenchmark::finished, this, &GraphWidget::benchmarkFinished);
}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        AddGraphEdgeDialog addGraphEdgeDialog;
        const int returnCode = addGraphEdgeDialog.exec();

        QPoint nodeLocation = event->pos();

        if(returnCode == QDialog::DialogCode::Accepted)
        {
            bool startValueOk = false;
            const int startValue = addGraphEdgeDialog.getStartValue(&startValueOk);
            if(startValueOk)
            {
                addNode(startValue, nodeLocation);
                nodeLocation += QPoint(50, 50);
            }

            bool endValueOk = false;
            const int endValue = addGraphEdgeDialog.getEndValue(&endValueOk);
            if(endValueOk)
            {
                addNode(endValue, nodeLocation);
            }

            if(startValueOk && endValueOk)
            {
                const double weightValue = addGraphEdgeDialog.getEdgeWeight();
                addEdge(startValue, endValue, weightValue);
            }

            update();

            updateGraphProperites();
        }
    }
    else
    {
        DataStructureWidget::mousePressEvent(event);
    }
}

void GraphWidget::paintDataStructure(QPainter &painter)
{
    painter.save();

    paintEdges(painter);
    paintNodes(painter);
    paintNodeValues(painter);

    painter.restore();
}

void GraphWidget::paintEdges(QPainter &painter)
{
    QSet<QPair<int, int>> drawnEdges;
    drawnEdges.reserve(qMax(0, graph.getEdgesNum()));

    for (auto it = graph.constBegin(); it != graph.constEnd(); ++it)
    {
        const auto& value = it.key();
        const auto& neighbours = it.value();

        for(const auto& neighbour : neighbours)
        {
            const QPair<int, int> edge(qMin(value, neighbour.getEndValue()), qMax(value, neighbour.getEndValue()));
            if(drawnEdges.contains(edge))
            {
                continue;
            }

            QPen edgePen;
            edgePen.setBrush(graphEdgeVisualData[edge].color);
            painter.setPen(edgePen);

            painter.drawLine(graphNodeVisualData[value].location, graphNodeVisualData[neighbour.getEndValue()].location);
            drawnEdges.insert(edge);
        }
    }
}

void GraphWidget::paintNodes(QPainter &painter)
{
    for (auto it = graph.constBegin(); it != graph.constEnd(); ++it)
    {
        const auto& value = it.key();

        QPen nodePen;
        nodePen.setBrush(graphNodeVisualData[value].color);
        painter.setPen(nodePen);
        painter.setBrush(graphNodeVisualData[value].color);

        painter.drawEllipse(graphNodeVisualData[value].location, 15, 15);
    }
}

void GraphWidget::paintNodeValues(QPainter &painter)
{
    QPen textPen;
    textPen.setBrush(Qt::white);
    painter.setPen(textPen);

    for (auto it = graph.constBegin(); it != graph.constEnd(); ++it)
    {
        const auto& value = it.key();
        const auto& neighbours = it.value();

        painter.drawText(graphNodeVisualData[value].location + QPointF(-3.5, 3), QString("%1").arg(value));
    }
}

bool GraphWidget::saveGraph()
{
    QFile saveFile("graph.txt");
    if(!saveFile.open(QIODevice::WriteOnly))
    {
        return false;
    }

    const QJsonObject graphAsJsonObject = graph.toJsonObject();
    const QJsonDocument jsonDoc(graphAsJsonObject);

    saveFile.write(jsonDoc.toJson());
    saveFile.close();

    return true;
}

bool GraphWidget::loadGraph()
{
    QFile loadFile("graph.txt");
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        return false;
    }

    const QByteArray jsonData = loadFile.readAll();
    loadFile.close();

    const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    graph.fromJsonObject(jsonDoc.object());

    return true;
}

bool GraphWidget::saveGraphNodeLocations()
{
    QFile saveFile("graph visuals.txt");
    if(!saveFile.open(QIODevice::WriteOnly))
    {
        return false;
    }

    const QJsonDocument jsonDoc(graph.toJsonObject());

    saveFile.write(jsonDoc.toJson());
    saveFile.close();

    return true;
}

bool GraphWidget::loadGraphNodeLocations()
{
    QFile loadFile("graph visuals.txt");
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        return false;
    }

    const QByteArray jsonData = loadFile.readAll();
    loadFile.close();

    const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    const QJsonObject locationsAsJsonObject = jsonDoc.object();

    fromJsonObject(locationsAsJsonObject);

    return true;
}

void GraphWidget::generateRandomGraph()
{
    for(int i=0; i<=1000; i++)
    {
        const int randomValueX = QRandomGenerator::global()->bounded(600);
        const int randomValueY = QRandomGenerator::global()->bounded(600);

        const QPoint randomLocationX(QRandomGenerator::global()->bounded(10000), QRandomGenerator::global()->bounded(10000));
        const QPoint randomLocationY(QRandomGenerator::global()->bounded(10000), QRandomGenerator::global()->bounded(10000));

        addNode(randomValueX, randomLocationX);
        addNode(randomValueY, randomLocationY);

        addEdge(randomValueX, graph.getRandomValue());
        addEdge(randomValueY, graph.getRandomValue());
    }
}

void GraphWidget::generateRandomGridGraph()
{
    // this info will be taken from UI later
    constexpr int columns = 20;
    constexpr int rows = 20;
    constexpr int nodeSpace = 50;
    constexpr QPoint startLoc(50, 50);

    QList<int> prevRow(columns);
    for(int i = 0; i < rows; i++)
    {
        int prevValue = -1;
        for(int j = 0; j < columns; j++)
        {
            const int randomValue = QRandomGenerator::global()->bounded(10000);

            if(addNode(randomValue, QPoint(startLoc.x()  + nodeSpace * j, startLoc.y() + nodeSpace * i)))
            {
                if(j > 0 && prevValue != -1)
                {
                    addEdge(prevValue, randomValue);
                }

                if(i > 0 && prevRow[j] != -1)
                {
                    addEdge(prevRow[j], randomValue);
                }

                prevRow[j] = randomValue;

                prevValue = randomValue;
            }
            else
            {
                prevRow[j] = -1;
            }
        }
    }
}

void GraphWidget::clearAlgorithm()
{
    if(algorithm)
    {
        algorithm->setPauseVisualization(true);
        algorithm->deleteLater();
        algorithm = nullptr;
    }
}

void GraphWidget::benchmarkFinished(const QString &algorithmName, const QList<QPointF> &result)
{
    AlgorithmWidgetLibrary::showBenchmarkResultWindow(algorithmName, result);
}
