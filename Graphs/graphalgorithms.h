#ifndef GRAPHAlgorithmS_H
#define GRAPHAlgorithmS_H

#include "graph.h"
#include "../Core/algorithm.h"

#include <QList>
#include <QQueue>
#include <QObject>
#include <QTimer>

class GraphAlgorithm : public Algorithm
{
    Q_OBJECT
public:
    GraphAlgorithm() = default;
    explicit GraphAlgorithm(const Graph* inGraph);
    explicit GraphAlgorithm(int inStart, const Graph* inGraph);
    virtual ~GraphAlgorithm();

    void setPauseVisualization(bool pause) override;

    virtual void setGraph(const Graph *newGraph);

protected:
    int start = 0;
    const Graph* graph = nullptr;

    QTimer visualizationUpdateTimer;
    int showEdgeInterval = 1000;
};

class BFS : public GraphAlgorithm
{
    Q_OBJECT
public:
    BFS() = default;
    explicit BFS(const Graph* inGraph);

    void run() override;
    void visualize(QWidget* widget) override;
};

class DFS : public GraphAlgorithm
{
    Q_OBJECT
public:
    DFS() = default;
    explicit DFS(const Graph* inGraph);

    void run() override;
    void visualize(QWidget* widget) override;

private:
    void DFSHelper(int begin, QHash<int, bool>& visited);

};

class BFSShortestPath : public GraphAlgorithm
{
    Q_OBJECT
public:
    BFSShortestPath() = default;
    explicit BFSShortestPath(const Graph* inGraph);

    void run() override;
    void visualize(QWidget* widget) override;

    void setGraph(const Graph *newGraph) override;

protected:
    int end = 0;
};

class TreeCenters : public GraphAlgorithm
{
    Q_OBJECT
public:
    TreeCenters() = default;
    explicit TreeCenters(const Graph* inGraph);
    
    void run() override;
    void visualize(QWidget* widget) override;
};

#endif // GRAPHAlgorithmS_H
