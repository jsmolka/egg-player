#ifndef ICONBUTTON_HPP
#define ICONBUTTON_HPP

#include <QPushButton>
#include <QStyle>

class IconButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(bool locked READ isLocked WRITE setLocked)

public:
    IconButton(QWidget *parent = 0);
    ~IconButton();

    void setIcon1(const QIcon &icon);
    QIcon icon1() const;

    void setIcon2(const QIcon &icon);
    QIcon icon2() const;

    void setSelected(bool selected);
    void setSelected(int selected);
    bool isSelected() const;

    void setLocked(bool locked);
    bool isLocked() const;

    void setLockable(bool lockable);

    void init(const QIcon &icon, const QSize &size);
    void init(const QIcon &icon1, const QIcon &icon2, const QSize &size);

    void switchIcon();

public slots:
    void switchLocked();

signals:
    void locked(bool locked);

private:
    void setSelectedIcon();

    QIcon m_icon1;
    QIcon m_icon2;
    bool m_selected;
    bool m_lockable;
    bool m_locked;
};

#endif // ICONBUTTON_HPP
