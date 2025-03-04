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

    Q_PROPERTY(int start READ getStart WRITE setStart NOTIFY startChanged FINAL)
    Q_PROPERTY(bool randomStart READ getRandomStart WRITE setRandomStart NOTIFY randomStartChanged FINAL)
public:
    GraphAlgorithm() = default;
    explicit GraphAlgorithm(const Graph* inGraph);
    explicit GraphAlgorithm(int inStart, const Graph* inGraph);
    virtual ~GraphAlgorithm();

    QWidget *getPropertiesWidget() override;

    void setPauseVisualization(bool pause) override;

    virtual void setGraph(const Graph *newGraph);

    int getStart() const;
    void setStart(int newStart);

    bool getRandomStart() const;
    void setRandomStart(bool newRandomStart);

signals:
    void startChanged();

    void randomStartChanged();

protected:
    int start = 0;
    bool randomStart = true;

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

    Q_PROPERTY(int end READ getEnd WRITE setEnd NOTIFY endChanged FINAL)
    Q_PROPERTY(bool randomEnd READ getRandomEnd WRITE setRandomEnd NOTIFY randomEndChanged FINAL)
public:
    BFSShortestPath() = default;
    explicit BFSShortestPath(const Graph* inGraph);

    void run() override;
    void visualize(QWidget* widget) override;

    void setGraph(const Graph *newGraph) override;

    int getEnd() const;
    void setEnd(int newEnd);

    bool getRandomEnd() const;
    void setRandomEnd(bool newRandomEnd);

signals:
    void endChanged();

    void randomEndChanged();

protected:
    int end = 0;
    bool randomEnd = true;
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
