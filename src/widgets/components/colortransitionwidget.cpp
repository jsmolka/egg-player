#include "colortransitionwidget.hpp"

ColorTransitionWidget::ColorTransitionWidget(QWidget *parent)
    : QWidget(parent)
    , m_duration(250)
    , m_fps(60)
    , m_transitionTimer(this)
{
    setup();

    connect(&m_transitionTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

ColorTransitionWidget::~ColorTransitionWidget()
{

}

void ColorTransitionWidget::stopTransition()
{
    m_transitionTimer.stop();
}

void ColorTransitionWidget::setTransitionDuration(int duration)
{
    m_duration = duration;
}

int ColorTransitionWidget::transitionDuration() const
{
    return m_duration;
}

void ColorTransitionWidget::setTransitionFps(int fps)
{
    m_fps = fps;
}

int ColorTransitionWidget::transitionFps() const
{
    return m_fps;
}

void ColorTransitionWidget::setColor(const QColor &color)
{
    QPalette palette;
    palette.setColor(QPalette::Background, color);
    setPalette(palette);
}

QColor ColorTransitionWidget::color() const
{
    return palette().color(QPalette::Background);
}

void ColorTransitionWidget::startTransition(const QColor &color)
{
    m_currentStep = 0;
    m_totalSteps = static_cast<double>(m_fps * m_duration) / 1000.0;

    QColor current = this->color();
    m_r = current.red();
    m_g = current.green();
    m_b = current.blue();

    m_stepR = (static_cast<double>(color.red()) - m_r) / static_cast<double>(m_totalSteps);
    m_stepG = (static_cast<double>(color.green()) - m_g) / static_cast<double>(m_totalSteps);
    m_stepB = (static_cast<double>(color.blue()) - m_b) / static_cast<double>(m_totalSteps);

    m_transitionTimer.start(1.0 / static_cast<double>(m_fps) * 1000.0);
    emit transitionStarted();
}

void ColorTransitionWidget::onTimeout()
{
    m_currentStep++;

    m_r += m_stepR;
    m_g += m_stepG;
    m_b += m_stepB;

    setColor(QColor(m_r, m_g, m_b));

    if (m_currentStep == m_totalSteps)
    {
        m_transitionTimer.stop();
        emit transitionFinished();
    }
}

void ColorTransitionWidget::setup()
{
    setAutoFillBackground(true);
}
