#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QWidget>

class Algorithm : public QObject
{
    Q_OBJECT
public:
    explicit Algorithm();
    virtual ~Algorithm() = 0;

    virtual void run() = 0;
    virtual void visualize(QWidget* widget) = 0;
    virtual void setPauseVisualization(bool pause) = 0;
    virtual QWidget *getPropertiesWidget() = 0;

signals:
    void visualizationFinished();
};

#endif // ALGORITHM_H
