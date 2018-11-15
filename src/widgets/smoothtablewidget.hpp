#ifndef SMOOTHTABLEWIDGET_HPP
#define SMOOTHTABLEWIDGET_HPP

#include <QLinkedList>
#include <QTableWidget>
#include <QTimer>

#include "core/macros.hpp"

class SmoothTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit SmoothTableWidget(QWidget *parent = nullptr);

    EGG_PPROP(int, fps, setFps, fps)
    EGG_PPROP(int, duration, setDuration, duration)

protected:
    void wheelEvent(QWheelEvent *event);

private slots:
    void sendEvent();

private:
    struct Step
    {
        double delta;
        int total;
    };
    void init();

    double subDelta(double delta, int left) const;

    QLinkedList<Step> m_steps;
    QTimer m_timer;
    QWheelEvent *m_event;
    int m_total;
};

#endif // SMOOTHTABLEWIDGET_HPP
