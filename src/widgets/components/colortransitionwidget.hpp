#ifndef COLORTRANSITIONWIDGET_HPP
#define COLORTRANSITIONWIDGET_HPP

#include <QColor>
#include <QWidget>

class ColorTransitionWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit ColorTransitionWidget(QWidget *parent = nullptr);
    ~ColorTransitionWidget();

    void setDuration(int duration);
    int duration() const;

    void setColor(const QColor &color);
    QColor color() const;

    void colorTransition(const QColor &color);

private:
    void setup();

    int m_duration;
};

#endif // COLORTRANSITIONWIDGET_HPP
