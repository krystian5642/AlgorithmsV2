#include "algorithmwidgetlibrary.h"
#include "algorithmbenchmarkwindow.h"

void AlgorithmWidgetLibrary::showBenchmarkResultWindow(const QString &chartTitle, const QList<QPointF> &result)
{
    AlgorithmBenchmarkWindow* algorithmBenchmarkResultWindow = new AlgorithmBenchmarkWindow;
    algorithmBenchmarkResultWindow->setAttribute(Qt::WA_DeleteOnClose);
    algorithmBenchmarkResultWindow->setChartTitle(chartTitle);
    algorithmBenchmarkResultWindow->setResult(result);
    algorithmBenchmarkResultWindow->show();
}

AlgorithmWidgetLibrary::AlgorithmWidgetLibrary()
{

}
