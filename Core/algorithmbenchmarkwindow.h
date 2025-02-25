#ifndef AlgorithmBenchmarkWindow_H
#define AlgorithmBenchmarkWindow_H

#include <QMainWindow>

class QLineSeries;
class QChart;
class QChartView;

namespace Ui
{
class AlgorithmBenchmarkWindow;
}

class AlgorithmBenchmarkWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AlgorithmBenchmarkWindow(QWidget *parent = nullptr);
    ~AlgorithmBenchmarkWindow();

    void setChartTitle(const QString& title);
    void appendResultPoint(const QPointF& resultPoint);
    void setResult(const QList<QPointF>& result);

private slots:
    void on_actionSave_result_to_file_triggered();
    void on_actionLoad_result_from_file_triggered();

private:
    void setupUi();

    Ui::AlgorithmBenchmarkWindow *ui;
    QLineSeries *defaultSeries;
    QChart *chart;
    QChartView *chartView;

    void saveResultToFile();
    void loadResultFromFile();
};

#endif // AlgorithmBenchmarkWindow_H
