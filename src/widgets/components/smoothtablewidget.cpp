#include "smoothtablewidget.hpp"

#include <QApplication>
#include <QDateTime>
#include <QQueue>
#include <QtMath>

SmoothTableWidget::SmoothTableWidget(QWidget *parent)
    : QTableWidget(parent)
    , m_smallStepModifier(Qt::ControlModifier)
    , m_bigStepModifier(Qt::ShiftModifier)
    , m_totalSteps(0)
    , m_stepsLeft(0)
    , m_smoothTimer(this)
    , m_lastEvent(nullptr)
{
    setup();

    connect(&m_smoothTimer, &QTimer::timeout, this, &SmoothTableWidget::onTimeout);
}

void SmoothTableWidget::setFps(int fps)
{
    m_fps = fps;
}

int SmoothTableWidget::fps() const
{
    return m_fps;
}

void SmoothTableWidget::setDuration(int duration)
{
    m_duration = duration;
}

int SmoothTableWidget::duration() const
{
    return m_duration;
}

void SmoothTableWidget::setAcceleration(double acceleration)
{
    m_acceleration = acceleration;
}

double SmoothTableWidget::acceleration() const
{
    return m_acceleration;
}

void SmoothTableWidget::setSmallStepRatio(double ratio)
{
    m_smallStepRatio = ratio;
}

double SmoothTableWidget::smallStepRatio() const
{
    return m_smallStepRatio;
}

void SmoothTableWidget::setBigStepRatio(double ratio)
{
    m_bigStepRatio = ratio;
}

double SmoothTableWidget::bigStepRatio() const
{
    return m_bigStepRatio;
}

void SmoothTableWidget::setSmallStepModifier(Qt::KeyboardModifier modifier)
{
    m_smallStepModifier = modifier;
}

Qt::KeyboardModifier SmoothTableWidget::smallStepModifier() const
{
    return m_smallStepModifier;
}

void SmoothTableWidget::setBigStepModifier(Qt::KeyboardModifier modifier)
{
    m_bigStepModifier = modifier;
}

Qt::KeyboardModifier SmoothTableWidget::bigStepModifier() const
{
    return m_bigStepModifier;
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

void SmoothTableWidget::setup()
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

double SmoothTableWidget::subDelta(double delta, int stepsLeft) const
{
    const double m = m_totalSteps / 2.0;
    const double x = abs(m_totalSteps - stepsLeft - m);

    return (cos(x * M_PI / m) + 1.0) / (2.0 * m) * delta;
}
