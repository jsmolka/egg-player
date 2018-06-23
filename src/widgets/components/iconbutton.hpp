#ifndef ICONBUTTON_HPP
#define ICONBUTTON_HPP

#include <QIcon>
#include <QPushButton>
#include <QStyle>
#include <QVector>

class IconButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(bool locked READ isLocked WRITE setLocked)

public:
    IconButton(QWidget *parent = nullptr);
    ~IconButton();

    void setIcons(const QVector<QIcon> &icons);
    QVector<QIcon> icons() const;

    void setIndex(int index);
    int index() const;

    void setLocked(bool locked);
    bool isLocked() const;

    void setLockable(bool lockable);
    bool isLockable() const;

    void setSize(const QSize &size);

signals:
    void locked(bool locked);

private slots:
    void onClicked();

private:
    void setup();

    QVector<QIcon> m_icons;
    int m_index;
    bool m_lockable;
    bool m_locked;
};

#endif // ICONBUTTON_HPP
