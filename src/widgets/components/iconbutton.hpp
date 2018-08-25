#ifndef ICONBUTTON_HPP
#define ICONBUTTON_HPP

#include <QEvent>
#include <QIcon>
#include <QPushButton>
#include <QVector>

using Icons = QVector<QIcon>;

class IconButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(bool locked READ isLocked WRITE setLocked)

public:
    explicit IconButton(QWidget *parent = nullptr);

    void setIcons(const Icons &icons);
    Icons icons() const;

    void setIconIndex(int iconIndex);
    int iconIndex() const;

    void setLockable(bool lockable);
    bool isLockable() const;

    void setLocked(bool locked);
    bool isLocked() const;

    void setSize(const QSize &size);

signals:
    void locked(bool locked);

protected:
    bool event(QEvent *event);

private slots:
    void onClicked();

private:
    void setup();

    Icons m_icons;

    int m_iconIndex;
    bool m_lockable;
    bool m_locked;
};

#endif // ICONBUTTON_HPP
