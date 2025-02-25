#ifndef GRAPHBENCHMARK_H
#define GRAPHBENCHMARK_H

#include "graphalgorithms.h"

#include <QObject>
#include <QRunnable>

class GraphBenchmark : public QObject, public QRunnable
{
    Q_OBJECT
public:
    GraphBenchmark(const QString& inAlgorithmName, const QSharedPointer<GraphAlgorithm>& inGraphAlgorithm);

signals:
    void finished(const QString& algorithmName, const QList<QPointF>& result);
    void updated(const QPointF& point);

    // QRunnable interface
public:
    void run() override;

private:
    QString algorithmName;
    QSharedPointer<GraphAlgorithm> graphAlgorithm;
};

#endif // GRAPHBENCHMARK_H
