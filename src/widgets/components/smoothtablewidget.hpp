#ifndef SMOOTHTABLEWIDGET_HPP
#define SMOOTHTABLEWIDGET_HPP

#include <QApplication>
#include <QDateTime>
#include <QPair>
#include <QQueue>
#include <QScrollBar>
#include <QTableWidget>
#include <QTimer>
#include <QtMath>
#include <QVector>
#include <QWheelEvent>

class SmoothTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    SmoothTableWidget(QWidget *parent = nullptr);
    ~SmoothTableWidget();

protected:
    void wheelEvent(QWheelEvent *event);

private slots:
    void onTimeout();

private:
    double subDelta(double delta, int stepsLeft);

    int m_fps;
    int m_duration;
    double m_acceleration;

    int m_totapSteps;
    QVector<QPair<double, int>> m_stepsLeft;

    QTimer m_smoothTimer;
    QWheelEvent *pm_lastEvent;
};

#endif // SMOOTHTABLEWIDGET_HPP
