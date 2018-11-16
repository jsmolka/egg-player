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
    ~SmoothTableWidget();

    EGG_PPROP(int, fps, setFps, fps)
    EGG_PPROP(int, duration, setDuration, duration)
    EGG_PPROP(double, slowMultiplier, setSlowMultiplier, slowMultiplier)
    EGG_PPROP(double, fastMultiplier, setFastMultiplier, fastMultiplier)
    EGG_PPROP(Qt::KeyboardModifier, slowModifier, setSlowModifier, slowModifier)
    EGG_PPROP(Qt::KeyboardModifier, fastModifier, setFastModifier, fastModifier)

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
