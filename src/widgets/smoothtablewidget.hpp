#ifndef SMOOTHTABLEWIDGET_HPP
#define SMOOTHTABLEWIDGET_HPP

#include <QPair>
#include <QScrollBar>
#include <QTableWidget>
#include <QTimer>
#include <QVector>

#include "core/macros.hpp"

class SmoothTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit SmoothTableWidget(QWidget *parent = nullptr);

    EGG_PPROP(int, fps, setFps, fps)
    EGG_PPROP(int, duration, setDuration, duration)
    EGG_PPROP(double, acceleration, setAcceleration, acceleration)
    EGG_PPROP(double, smallStepRatio, setSmallStepRatio, smallStepRatio)
    EGG_PPROP(double, bigStepRatio, setBigStepRatio, bigStepRatio)
    EGG_PPROP(Qt::KeyboardModifier, smallStepModifier, setSmallStepModifier, smallStepModifier)
    EGG_PPROP(Qt::KeyboardModifier, bigStepModifier, bigSmallStepModifier, bigStepModifier)

protected:
    void wheelEvent(QWheelEvent *event);

private slots:
    void onTimeout();

private:
    void init();

    double subDelta(double delta, int stepsLeft) const;

    int m_totalSteps;
    QVector<QPair<double, int>> m_stepsLeft;

    QTimer m_smoothTimer;
    QWheelEvent *m_lastEvent;
};

#endif // SMOOTHTABLEWIDGET_HPP
