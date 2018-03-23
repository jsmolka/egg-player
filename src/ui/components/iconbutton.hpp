#ifndef ICONBUTTON_HPP
#define ICONBUTTON_HPP

#include <QPushButton>
#include <QIcon>

class IconButton : public QPushButton
{
    Q_OBJECT

public:
    explicit IconButton(QWidget *parent = 0);

    void setIcon1(QIcon icon);
    void setIcon1(QString path);
    QIcon icon1() const;

    void setIcon2(QIcon icon);
    void setIcon2(QString path);
    QIcon icon2() const;

    void setSelected(bool selected);
    bool selected() const;

    void init(QString path, QSize size);
    void init(QString path1, QString path2, QSize size);

public slots:
    void switchIcon();

private:
    void setSelectedIcon();

    QIcon m_icon1;
    QIcon m_icon2;
    bool m_selected;
};

#endif // ICONBUTTON_HPP
