#include "smoothtablewidget.hpp"

SmoothTableWidget::SmoothTableWidget(QWidget *parent)
    : QTableWidget(parent)
    , m_fps(144)
    , m_duration(145)
    , m_acceleration(0.1)
    , m_smallStepRatio(0.33)
    , m_bigStepRatio(3.0)
    , m_smallStepModifier(Qt::ControlModifier)
    , m_bigStepModifier(Qt::ShiftModifier)
    , m_stepsLeft(0)
    , m_smoothTimer(this)
    , pm_lastEvent(nullptr)
{
    setup();

    connect(&m_smoothTimer, &QTimer::timeout, this, &SmoothTableWidget::onTimeout);
}

SmoothTableWidget::~SmoothTableWidget()
{

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
    qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();
    scrollStamps.enqueue(now);
    while (now - scrollStamps.front() > 600)
        scrollStamps.dequeue();
    double accerationRatio = qMin(scrollStamps.size() / 15.0, 1.0);

    if (!pm_lastEvent)
        pm_lastEvent = new QWheelEvent(*event);
    else
        *pm_lastEvent = *event;

    double multiplier = 0.8;
    if (QApplication::keyboardModifiers() & m_smallStepModifier)
        multiplier *= m_smallStepRatio;
    if (QApplication::keyboardModifiers() & m_bigStepModifier)
        multiplier *= m_bigStepRatio;
    double delta = (double)event->delta() *  multiplier;
    if (m_acceleration > 0)
        delta += delta * m_acceleration * accerationRatio;

    m_totalSteps = m_fps * m_duration / 1000;
    m_stepsLeft << qMakePair(delta, m_totalSteps);
    m_smoothTimer.start(1000 / m_fps);
}

void SmoothTableWidget::onTimeout()
{
    double totalDelta = 0;

    QVector<QPair<double, int>>::Iterator iter;
    for (iter = m_stepsLeft.begin(); iter != m_stepsLeft.end(); ++iter)
    {
        totalDelta += subDelta(iter->first, iter->second);
        --(iter->second);
    }

    while (!m_stepsLeft.empty() && m_stepsLeft.begin()->second == 0)
        m_stepsLeft.pop_front();

    if (m_stepsLeft.empty())
        m_smoothTimer.stop();

    QWheelEvent event(
        pm_lastEvent->pos(),
        pm_lastEvent->globalPos(),
        qRound(totalDelta),
        pm_lastEvent->buttons(),
        0,
        pm_lastEvent->orientation()
    );

    QApplication::sendEvent(verticalScrollBar(), &event);
}

void SmoothTableWidget::setup()
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

double SmoothTableWidget::subDelta(double delta, int stepsLeft)
{
    double m = m_totalSteps / 2.0;
    double x = abs(m_totalSteps - stepsLeft - m);

    return (cos(x * M_PI / m) + 1.0) / (2.0 * m) * delta;
}
