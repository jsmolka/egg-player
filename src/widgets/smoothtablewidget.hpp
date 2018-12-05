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

    EGG_P_PROP(int, fps, setFps, fps)
    EGG_P_PROP(int, duration, setDuration, duration)
    EGG_P_PROP(double, slowMultiplier, setSlowMultiplier, slowMultiplier)
    EGG_P_PROP(double, fastMultiplier, setFastMultiplier, fastMultiplier)
    EGG_P_PROP(Qt::KeyboardModifier, slowModifier, setSlowModifier, slowModifier)
    EGG_P_PROP(Qt::KeyboardModifier, fastModifier, setFastModifier, fastModifier)

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
    double subDelta(double delta, int left) const;

    void init();

    QLinkedList<Step> m_steps;
    QTimer m_timer;
    QWheelEvent *m_event;
    int m_total;
};

#endif // SMOOTHTABLEWIDGET_HPP
