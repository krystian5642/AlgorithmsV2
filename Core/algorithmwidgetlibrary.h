#ifndef ALGORITHMWIDGETLIBRARY_H
#define ALGORITHMWIDGETLIBRARY_H

#include <QPointF>
#include <QString>


class AlgorithmWidgetLibrary
{
public:
    static void showBenchmarkResultWindow(const QString& chartTitle, const QList<QPointF>& result);

private:
    AlgorithmWidgetLibrary();
};

#endif // ALGORITHMWIDGETLIBRARY_H
