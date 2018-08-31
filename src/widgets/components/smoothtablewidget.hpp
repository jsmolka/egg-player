#ifndef SMOOTHTABLEWIDGET_HPP
#define SMOOTHTABLEWIDGET_HPP

#include <QPair>
#include <QScrollBar>
#include <QTableWidget>
#include <QTimer>
#include <QVector>
#include <QWheelEvent>

class SmoothTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit SmoothTableWidget(QWidget *parent = nullptr);

    void setFps(int fps);
    int fps() const;

    void setDuration(int duration);
    int duration() const;

    void setAcceleration(double acceleration);
    double acceleration() const;

    void setSmallStepRatio(double ratio);
    double smallStepRatio() const;

    void setBigStepRatio(double ratio);
    double bigStepRatio() const;

    void setSmallStepModifier(Qt::KeyboardModifier modifier);
    Qt::KeyboardModifier smallStepModifier() const;

    void setBigStepModifier(Qt::KeyboardModifier modifier);
    Qt::KeyboardModifier bigStepModifier() const;

protected:
    void wheelEvent(QWheelEvent *event);

private slots:
    void onTimeout();

private:
    void setup();

    double subDelta(double delta, int stepsLeft) const;

    int m_fps{144};
    int m_duration{145};
    double m_acceleration{0.1};
    double m_smallStepRatio{0.33};
    double m_bigStepRatio{3.33};

    Qt::KeyboardModifier m_smallStepModifier;
    Qt::KeyboardModifier m_bigStepModifier;

    int m_totalSteps;
    QVector<QPair<double, int>> m_stepsLeft;

    QTimer m_smoothTimer;
    QWheelEvent *m_lastEvent;
};

#endif // SMOOTHTABLEWIDGET_HPP
