#ifndef COLORTRANSITIONWIDGET_HPP
#define COLORTRANSITIONWIDGET_HPP

#include <QColor>
#include <QPalette>
#include <QTimer>
#include <QWidget>

class ColorTransitionWidget : public QWidget
{
    Q_OBJECT

public:
    ColorTransitionWidget(QWidget *parent = nullptr);
    ~ColorTransitionWidget();

    void setTransitionDuration(int duration);
    int transitionDuration() const;

    void setTransitionFps(int fps);
    int transitionFps() const;

    void setColor(const QColor &color);
    QColor color() const;

    void startTransition(const QColor &color);
    void stopTransition();

signals:
    void transitionStarted();
    void transitionFinished();

private slots:
    void onTimeout();

private:
    void setup();

    int m_duration;
    int m_fps;
    int m_totalSteps;
    int m_currentStep;

    double m_stepR;
    double m_stepG;
    double m_stepB;

    double m_r;
    double m_g;
    double m_b;

    QTimer m_transitionTimer;
};

#endif // COLORTRANSITIONWIDGET_HPP
