#ifndef ICONBUTTON_HPP
#define ICONBUTTON_HPP

#include <QIcon>
#include <QPushButton>
#include <QStyle>

class IconButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(bool locked READ locked WRITE setLocked)

public:
    IconButton(bool autoSwitch, QWidget *parent = 0);

    void setIcon1(QIcon icon);
    void setIcon1(QString path);
    QIcon icon1() const;

    void setIcon2(QIcon icon);
    void setIcon2(QString path);
    QIcon icon2() const;

    void setSelected(bool selected);
    bool selected() const;

    void setLockable(bool lockable);

    void setLocked(bool locked);
    bool locked() const;

    void init(QString path, QSize size);
    void init(QString path1, QString path2, QSize size);

public slots:
    void switchIcon();

private:
    void setSelectedIcon();

    QIcon m_icon1;
    QIcon m_icon2;
    bool m_selected;
    bool m_lockable;
    bool m_locked;
    bool m_autoSwitch;
};

#endif // ICONBUTTON_HPP
