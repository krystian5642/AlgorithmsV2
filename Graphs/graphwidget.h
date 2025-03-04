#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include "../Core/datastructurewidget.h"
#include "graph.h"

#include <QComboBox>
#include <QDialog>

class GraphNodePropertiesWidget;

QT_BEGIN_NAMESPACE

class GraphAlgorithm;
namespace Ui
{
class GraphWidget;
}
QT_END_NAMESPACE

struct GraphNodeVisualData
{
    QPoint location;
    QColor color = Qt::black;
};

struct GraphEdgeVisualData
{
    QColor color = Qt::black;
};

class RandomGraphPropertiesWindow : public QDialog
{
    Q_OBJECT

public:
    RandomGraphPropertiesWindow(QWidget *parent = nullptr);

    QString getSelectedGraphTypeName() const;

private:
    QComboBox* graphTypesBox;
};

class GraphWidget : public DataStructureWidget
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr);
    ~GraphWidget();

    void clearGraph();

    // graph serialization
    QJsonObject toJsonObject() const;
    void fromJsonObject(const QJsonObject& jsonObj);

    void setNodeColor(int value, const QColor& color, bool callUpdate = true);
    void setEdgeColor(int start, int end, const QColor& color, bool callUpdate = true);
    void setNodesAndEdgesToBlack();

    bool addNode(int value, const QPoint& location);
    void addEdge(int startValue, int endValue, float weight = 0.f);

    void updateGraphProperites();

    // DataStructureWidget interface
    void getAlgorithmNames(QStringList& names) const override;
    QSharedPointer<Algorithm> getAlgorithmToExecute(const QString& algorithmName) const override;
    void saveAction() override;
    void loadAction() override;
    void clearAction() override;
    void generateRandomStructureAction() override;
    void visualizeAlgorithmAction(const QString& algorithmName, bool pause) override;
    void runBenchmarkAction(const QString& algorithmName) override;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;

    QHash<int, GraphNodeVisualData> graphNodeVisualData;
    QHash<QPair<int, int>, GraphEdgeVisualData> graphEdgeVisualData;

private:
    void paintDataStructure(QPainter& painter) override;

    void paintEdges(QPainter& painter);
    void paintNodes(QPainter& painter);
    void paintNodeValues(QPainter& painter);

    bool saveGraph();
    bool loadGraph();

    bool saveGraphNodeLocations();
    bool loadGraphNodeLocations();

    void generateRandomGraph();
    void generateRandomGridGraph();

    Ui::GraphWidget *ui;
    Graph graph;

    void clearAlgorithm();
    GraphAlgorithm* algorithm;

private slots:
    void benchmarkFinished(const QString& algorithmName, const QList<QPointF>& result);
};

#endif // GRAPHWIDGET_H
