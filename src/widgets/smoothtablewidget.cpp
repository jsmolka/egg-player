#include "smoothtablewidget.hpp"

#include <QApplication>
#include <QDateTime>
#include <QScrollBar>
#include <QtMath>
#include <QWheelEvent>

#include "core/config.hpp"

SmoothTableWidget::SmoothTableWidget(QWidget *parent)
    : QTableWidget(parent)
    , m_fps(175)
    , m_duration(175)
    , m_slowMultiplier(0.33)
    , m_fastMultiplier(3.33)
    , m_slowModifier(Qt::ControlModifier)
    , m_fastModifier(Qt::ShiftModifier)
    , m_timer(this)
    , m_event(nullptr)
    , m_total(0)
{
    init();

    connect(&m_timer, &QTimer::timeout, this, &SmoothTableWidget::sendEvent);
}

void SmoothTableWidget::wheelEvent(QWheelEvent *event)
{
    if (!cfg_library.smoothScrolling())
        return QTableWidget::wheelEvent(event);

    static QLinkedList<qint64> stamps;
    stamps << QDateTime::currentMSecsSinceEpoch();
    while (stamps.last() - stamps.first() > 600)
        stamps.removeFirst();

    m_event = event;
    m_total = m_fps * m_duration / 1000;

    double multiplier = 0.8;
    if (QApplication::keyboardModifiers() & m_slowModifier)
        multiplier *= m_slowMultiplier;
    if (QApplication::keyboardModifiers() & m_fastModifier)
        multiplier *= m_fastMultiplier;

    Step step;
    step.delta = multiplier * static_cast<double>(event->delta());;
    step.total = m_total;
    m_steps << step;

    m_timer.start(1000 / m_fps);
}

void SmoothTableWidget::sendEvent()
{
    double delta = 0;
    for (Step &step : m_steps)
    {
        delta += subDelta(step.delta, step.total);
        step.total--;
    }

    while (!m_steps.empty() && m_steps.begin()->total == 0)
        m_steps.removeFirst();

    if (m_steps.empty())
        m_timer.stop();

    QWheelEvent event(
        m_event->pos(),
        m_event->globalPos(),
        qRound(delta),
        m_event->buttons(),
        nullptr,
        m_event->orientation()
    );

    QApplication::sendEvent(verticalScrollBar(), &event);
}

void SmoothTableWidget::init()
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

double SmoothTableWidget::subDelta(double delta, int left) const
{
    const double m = m_total / 2.0;
    const double x = abs(m_total - left - m);

    return (cos(x * M_PI / m) + 1.0) / (2.0 * m) * delta;
}
