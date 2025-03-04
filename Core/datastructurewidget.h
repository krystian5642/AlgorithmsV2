#ifndef ALGORITHMWIDGET_H
#define ALGORITHMWIDGET_H

#include <QWidget>

#include "algorithm.h"

struct ScaleData
{
    qreal currentScale = 1.0;
    qreal minScale = 0.1;
    qreal maxScale = 15.0;
    qreal scaleMultiplier = 1.1;
};

struct RuntimeMouseDragData
{
    bool isDragging = false;
    QPointF dragDelta;
    QPointF lastMousePos;
};

class DataStructureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataStructureWidget(QWidget *parent = nullptr);
    ~DataStructureWidget();

    virtual void getAlgorithmNames(QStringList& names) const = 0;
    virtual QSharedPointer<Algorithm> getAlgorithmToExecute(const QString& algorithmName) const = 0;

    // actions
    virtual void saveAction() = 0;
    virtual void loadAction() = 0;
    virtual void clearAction() = 0;
    virtual void generateRandomStructureAction() = 0;
    virtual void visualizeAlgorithmAction(const QString& algorithmName, bool pause) = 0;
    virtual void runBenchmarkAction(const QString& algorithmName) = 0;

    int getLastPaintTime() const;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    virtual void paintDataStructure(QPainter& painter);

    RuntimeMouseDragData dragData;

    ScaleData scaleData;

    QPointF scaleOffset;

    //paint time in ms
    int lastPaintTime;
};

#endif // ALGORITHMWIDGET_H
