#include "smoothtablewidget.hpp"

#include <QApplication>
#include <QDateTime>
#include <QQueue>
#include <QtMath>
#include <QWheelEvent>

SmoothTableWidget::SmoothTableWidget(QWidget *parent)
    : QTableWidget(parent)
    , m_fps(144)
    , m_duration(145)
    , m_acceleration(0.1)
    , m_smallStepRatio(0.33)
    , m_bigStepRatio(3.33)
    , m_smallStepModifier(Qt::ControlModifier)
    , m_bigStepModifier(Qt::ShiftModifier)
    , m_totalSteps(0)
    , m_stepsLeft(0)
    , m_smoothTimer(this)
    , m_lastEvent(nullptr)
{
    init();

    connect(&m_smoothTimer, &QTimer::timeout, this, &SmoothTableWidget::onTimeout);
}

void SmoothTableWidget::wheelEvent(QWheelEvent *event)
{
    static QQueue<qint64> scrollStamps;
    const qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();
    scrollStamps.enqueue(now);
    while (now - scrollStamps.front() > 600)
        scrollStamps.dequeue();
    const double accerationRatio = qMin(scrollStamps.size() / 15.0, 1.0);

    if (!m_lastEvent)
        m_lastEvent = new QWheelEvent(*event);
    else
        *m_lastEvent = *event;

    double multiplier = 0.8;
    if (QApplication::keyboardModifiers() & m_smallStepModifier)
        multiplier *= m_smallStepRatio;
    if (QApplication::keyboardModifiers() & m_bigStepModifier)
        multiplier *= m_bigStepRatio;
    double delta = static_cast<double>(event->delta()) *  multiplier;
    if (m_acceleration > 0)
        delta += delta * m_acceleration * accerationRatio;

    m_totalSteps = m_fps * m_duration / 1000;
    m_stepsLeft << qMakePair(delta, m_totalSteps);
    m_smoothTimer.start(1000 / m_fps);
}

void SmoothTableWidget::onTimeout()
{
    double totalDelta = 0;

    for (QPair<double, int> &step : m_stepsLeft)
    {
        totalDelta += subDelta(step.first, step.second);
        --step.second;
    }

    while (!m_stepsLeft.empty() && m_stepsLeft.begin()->second == 0)
        m_stepsLeft.pop_front();

    if (m_stepsLeft.empty())
        m_smoothTimer.stop();

    QWheelEvent event(
        m_lastEvent->pos(),
        m_lastEvent->globalPos(),
        qRound(totalDelta),
        m_lastEvent->buttons(),
        nullptr,
        m_lastEvent->orientation()
    );

    QApplication::sendEvent(verticalScrollBar(), &event);
}

void SmoothTableWidget::init()
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

double SmoothTableWidget::subDelta(double delta, int stepsLeft) const
{
    const double m = m_totalSteps / 2.0;
    const double x = abs(m_totalSteps - stepsLeft - m);

    return (cos(x * M_PI / m) + 1.0) / (2.0 * m) * delta;
}
