#ifndef AlgorithmsMAINWINDOW_H
#define AlgorithmsMAINWINDOW_H

#include <QMainWindow>


class DataStructureWidget;
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
    void on_actionGenerateRandomStructure_triggered();
    void on_actionRun_Algorithm_triggered(bool isOn);

private:
    void setupUi();
    void setDataStructureWidget(DataStructureWidget* widget);

    QString getSelectedAlgorithmName() const;

    Ui::AlgorithmVisualizationWindow *ui;
    DataStructureWidget* dataStructureWidget;
};

#endif // AlgorithmsMAINWINDOW_H
