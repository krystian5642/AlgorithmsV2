#ifndef AlgorithmsMAINWINDOW_H
#define AlgorithmsMAINWINDOW_H

#include <QMainWindow>

class GraphWidget;
class GraphAlgorithm;
class QComboBox;

class AlgorithmBenchmarkWindow;

namespace Ui
{
class AlgorithmVisualizationWindow;
}

class AlgorithmVisualizationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AlgorithmVisualizationWindow(QWidget *parent = nullptr);
    ~AlgorithmVisualizationWindow();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void on_actionClear_triggered();
    void on_actionRun_Algorithm_triggered(bool isOn);
    void on_actionGenerateRandomGraph_triggered();
    void on_actionGenerateRandomGridGraph_triggered();
    void on_actionAlgorithm_benchmark_triggered();

private:
    void setupUi();
    void setAlgorithmWidget(QWidget* widget);

    QString getSelectedAlgorithmName() const;

    Ui::AlgorithmVisualizationWindow *ui;
    GraphWidget* graphWidget;
};

#endif // AlgorithmsMAINWINDOW_H
