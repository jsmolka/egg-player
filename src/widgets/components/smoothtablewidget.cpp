#include "smoothtablewidget.hpp"

SmoothTableWidget::SmoothTableWidget(QWidget *parent)
    : QTableWidget(parent)
    , m_fps(144)
    , m_duration(145)
    , m_acceleration(0.1)
    , m_stepsLeft(0)
    , m_smoothTimer(this)
    , pm_lastEvent(nullptr)
{
    setup();

    connect(&m_smoothTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

SmoothTableWidget::~SmoothTableWidget()
{

}

void SmoothTableWidget::setFps(int fps)
{
    m_fps = fps;
}

int SmoothTableWidget::fps()
{
    return m_fps;
}

void SmoothTableWidget::setDuration(int duration)
{
    m_duration = duration;
}

int SmoothTableWidget::duration()
{
    return m_duration;
}

void SmoothTableWidget::setAcceleration(double acceleration)
{
    m_acceleration = acceleration;
}

double SmoothTableWidget::acceleration()
{
    return m_acceleration;
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

    m_totalSteps = m_fps * m_duration / 1000;
    double delta = (double)event->delta() * 0.8 ;
    if (m_acceleration > 0)
        delta += delta * m_acceleration * accerationRatio;

    m_stepsLeft.push_back(qMakePair(delta, m_totalSteps));
    m_smoothTimer.start(1000 / m_fps);
}

void SmoothTableWidget::onTimeout()
{
    double totalDelta = 0;

    for (QVector< QPair<double, int> >::Iterator it = m_stepsLeft.begin(); it != m_stepsLeft.end(); ++it)
    {
        totalDelta += subDelta(it->first, it->second);
        --(it->second);
    }
    while (!m_stepsLeft.empty() && m_stepsLeft.begin()->second == 0)
        m_stepsLeft.pop_front();

    Qt::Orientation orientation = pm_lastEvent->orientation();

    QWheelEvent event(
        pm_lastEvent->pos(),
        pm_lastEvent->globalPos(),
        qRound(totalDelta),
        pm_lastEvent->buttons(),
        0,
        orientation
    );

    QApplication::sendEvent(verticalScrollBar(), &event);

    if (m_stepsLeft.empty()) {
        m_smoothTimer.stop();
    }
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
