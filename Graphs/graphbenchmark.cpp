#include "graphbenchmark.h"

#include <QElapsedTimer>
#include <QRandomGenerator>
#include <QThread>

GraphBenchmark::GraphBenchmark(const QString& inAlgorithmName, const QSharedPointer<GraphAlgorithm>& inGraphAlgorithm)
    : algorithmName(inAlgorithmName)
    , graphAlgorithm(inGraphAlgorithm)
{

}

void GraphBenchmark::run()
{
    constexpr int runNum = 1000;

    QList<QPointF> result;
    result.reserve(runNum);

    for(int i = 1; i <= runNum; i++)
    {
        Graph testGraph;
        for(int j = 0; j < i; j++)
        {
            const int randomValueX = QRandomGenerator::global()->bounded(100000);
            const int randomValueY = QRandomGenerator::global()->bounded(100000);

            testGraph.addEdge(randomValueX, testGraph.getRandomValue());
            testGraph.addEdge(randomValueY, testGraph.getRandomValue());
        }

        graphAlgorithm->setGraph(&testGraph);

        QElapsedTimer executionTime;
        executionTime.start();

        graphAlgorithm->run();

        emit updated(QPointF(static_cast<qreal>(testGraph.getEdgesNum() + testGraph.getNodesNum()), static_cast<qreal>(executionTime.nsecsElapsed())));

        //result.append(QPointF(static_cast<qreal>(testGraph.getEdgesNum() + testGraph.getNodesNum()), static_cast<qreal>(executionTime.nsecsElapsed())));

        if(i < 300)
        {
            QThread::msleep(20);
        }
    }

    emit finished(algorithmName, result);
}
