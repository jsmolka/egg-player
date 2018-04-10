#ifndef ICONBUTTON_HPP
#define ICONBUTTON_HPP

#include <QIcon>
#include <QPushButton>
#include <QStyle>

class IconButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(bool locked READ isLocked WRITE setLocked)

public:
    IconButton(QWidget *parent = 0);
    ~IconButton();

    void setIcons(const QList<QIcon> &icons);
    QList<QIcon> icons() const;

    void setSelectedIcon(int selected);
    int selectedIcon() const;

    void setLocked(bool locked);
    bool isLocked() const;

    void setLockable(bool lockable);
    bool isLockable() const;

    void init(const QList<QIcon> &icons, int size, bool lockable = false);

signals:
    void locked(bool locked);

private slots:
    void onClicked();

private:
    QList<QIcon> m_icons;
    bool m_selected;
    bool m_lockable;
    bool m_locked;
};

#endif // ICONBUTTON_HPP
