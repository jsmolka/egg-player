#ifndef ICONBUTTON_HPP
#define ICONBUTTON_HPP

#include <QIcon>
#include <QPushButton>
#include <QVector>

class IconButton : public QPushButton
{
    Q_OBJECT

public:
    explicit IconButton(QWidget *parent = nullptr);

    void setIcons(const QVector<QIcon> &icons);
    QVector<QIcon> icons() const;

    void setIconIndex(int index);
    int iconIndex() const;

    void setSize(const QSize &size);

protected:
    bool event(QEvent *event);

private:
    void init();

    QVector<QIcon> m_icons;
    int m_iconIndex;
};

#endif // ICONBUTTON_HPP
