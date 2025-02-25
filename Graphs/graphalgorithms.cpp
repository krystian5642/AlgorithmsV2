#include "graphalgorithms.h"
#include "graphwidget.h"
#include "edgelist.h"

GraphAlgorithm::GraphAlgorithm(const Graph* inGraph)
    : graph(inGraph)
    , showEdgeInterval(1000)
{
    start = graph->getRandomValue();

    visualizationUpdateTimer.setInterval(showEdgeInterval);
}

GraphAlgorithm::GraphAlgorithm(int inStart, const Graph* inGraph)
    : start(inStart)
    , graph(inGraph)
    , showEdgeInterval(1000)
{
    visualizationUpdateTimer.setInterval(showEdgeInterval);
}

GraphAlgorithm::~GraphAlgorithm()
{
}

void GraphAlgorithm::setPauseVisualization(bool pause)
{
    if(pause)
    {
        visualizationUpdateTimer.stop();
    }
    else
    {
        visualizationUpdateTimer.start();
    }
}

void GraphAlgorithm::setGraph(const Graph *newGraph)
{
    graph = newGraph;

    start = graph->getRandomValue();
}

BFS::BFS(const Graph* inGraph)
    : GraphAlgorithm(inGraph)
{

}

void BFS::run()
{
    QQueue<int> nodeQueue;
    nodeQueue.enqueue(start);

    QHash<int, bool> visited;
    visited[start] = true;

    while(!nodeQueue.empty())
    {
        const int first = nodeQueue.dequeue();
        const auto& neighbourValues = graph->getNeighbourValues(first);

        for(const auto& value : neighbourValues)
        {
            if(!visited[value])
            {
                visited[value] = true;
                nodeQueue.enqueue(value);
            }
        }
    }
}

void BFS::visualize(QWidget *widget)
{

}

DFS::DFS(const Graph* inGraph)
    : GraphAlgorithm(inGraph)
{

}

void DFS::run()
{
    QHash<int, bool> visited;
    visited[start] = true;

    const auto& neighbourValues = graph->getNeighbourValues(start);
    for(const auto& value : neighbourValues)
    {
        if(!visited[value])
        {
            visited[value] = true;
            DFSHelper(value, visited);
        }
    }
}

void DFS::visualize(QWidget *widget)
{

}

void DFS::DFSHelper(int begin, QHash<int, bool>& visited)
{
    const auto& neighbourValues = graph->getNeighbourValues(begin);
    for(const auto& value : neighbourValues)
    {
        if(!visited[value])
        {
            visited[value] = true;
            DFSHelper(value, visited);
        }
    }
}

BFSShortestPath::BFSShortestPath(const Graph* inGraph)
    : GraphAlgorithm(inGraph)
    , end(5)
{
    end = graph->getRandomValue();
}

void BFSShortestPath::run()
{
    EdgeList path;

    QQueue<int> nodeQueue;
    nodeQueue.enqueue(start);

    QHash<int, bool> visited;
    visited[start] = true;

    constexpr int intMin = std::numeric_limits<int>::min();

    QHash<int, int> prev;
    prev[start] = intMin;

    while(!nodeQueue.empty())
    {
        const int first = nodeQueue.dequeue();
        const auto& neighbourValues = graph->getNeighbourValues(first);

        for(const auto& value : neighbourValues)
        {
            if(!visited[value])
            {
                visited[value] = true;
                nodeQueue.enqueue(value);

                prev[value] = first;
                if(value == end)
                {
                    nodeQueue.clear();
                    break;
                }
            }
        }
    }

    if(prev.contains(end))
    {
        int step = end;
        while(step != intMin)
        {
            path.add(step, prev[step]);
            step = prev[step];
        }

        std::reverse(path.begin(), path.end());
    }
}

void BFSShortestPath::visualize(QWidget *widget)
{

}

void BFSShortestPath::setGraph(const Graph *newGraph)
{
    GraphAlgorithm::setGraph(newGraph);
    end = graph->getRandomValue();
}

TreeCenters::TreeCenters(const Graph* inGraph)
    : GraphAlgorithm(inGraph)
{
}

void TreeCenters::run()
{
    QList<int> centers;
    centers.reserve(2);

    const qsizetype nodesNum = graph->getNodesNum();

    QHash<int, qsizetype> nodeDegrees;
    nodeDegrees.reserve(nodesNum);

    QList<int> leaves;

    for(auto it = graph->constBegin(); it != graph->constEnd(); it++)
    {
        const auto& nodeValue = it.key();
        const auto& nodeNeighbours = it.value();

        qsizetype degree = nodeNeighbours.size();
        if(degree == 0 || degree == 1)
        {
            leaves.append(nodeValue);
            degree = 0;
        }

        nodeDegrees[nodeValue] = degree;
    }

    qsizetype count = leaves.size();
    bool canFindCenters = count != 0;

    while(canFindCenters && count < nodesNum)
    {
        QList<int> newLeaves;
        for(const auto& leaf : leaves)
        {
            const auto& nodeNeighbours = graph->getNeighbourValues(leaf);
            for(const auto& neighbour : nodeNeighbours)
            {
                auto& degree = nodeDegrees[neighbour];
                if(degree > 0)
                {
                    degree--;

                    if(degree == 1)
                    {
                        newLeaves.append(neighbour);
                    }
                }
            }
            nodeDegrees[leaf] = 0;
        }
        leaves = newLeaves;
        count += leaves.size();

        canFindCenters = leaves.size() != 0;
    }
    centers = leaves;
}

void TreeCenters::visualize(QWidget *widget)
{

}
