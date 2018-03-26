#ifndef ICONBUTTON_HPP
#define ICONBUTTON_HPP

#include <QIcon>
#include <QPushButton>
#include <QStyle>

class IconButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(QIcon icon1 READ icon1 WRITE setIcon1)
    Q_PROPERTY(QIcon icon2 READ icon2 WRITE setIcon2)
    Q_PROPERTY(bool selected READ isSelected WRITE setSelected)
    Q_PROPERTY(bool locked READ isLocked WRITE setLocked)

public:
    IconButton(QWidget *parent = 0);

    void setIcon1(QIcon icon);
    QIcon icon1() const;

    void setIcon2(QIcon icon);
    QIcon icon2() const;

    void setSelected(bool selected);
    void setSelected(int selected);
    bool isSelected() const;

    void setLocked(bool locked);
    bool isLocked() const;

    void setLockable(bool lockable);

    void init(QIcon icon, QSize size);
    void init(QIcon icon1, QIcon icon2, QSize size);

    void switchIcon();

public slots:
    void switchLocked();

signals:
    void locked();

private:
    void setSelectedIcon();

    QIcon m_icon1;
    QIcon m_icon2;
    bool m_selected;
    bool m_lockable;
    bool m_locked;
};

#endif // ICONBUTTON_HPP
