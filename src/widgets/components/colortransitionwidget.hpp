#ifndef COLORTRANSITIONWIDGET_HPP
#define COLORTRANSITIONWIDGET_HPP

#include <QColor>
#include <QPalette>
#include <QPropertyAnimation>
#include <QWidget>

class ColorTransitionWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    ColorTransitionWidget(QWidget *parent = nullptr);
    ~ColorTransitionWidget();

    void setTransitionDuration(int duration);
    int transitionDuration() const;

    void setColor(const QColor &color);
    QColor color() const;

    void startTransition(const QColor &color);

private:
    void setup();

    int m_duration;
};

#endif // COLORTRANSITIONWIDGET_HPP
