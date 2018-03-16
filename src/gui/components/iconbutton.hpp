#ifndef ICONBUTTON_HPP
#define ICONBUTTON_HPP

#include <QPushButton>
#include <QIcon>

class IconButton : public QPushButton
{
    Q_OBJECT

public:
    explicit IconButton(QWidget *parent = 0);

    void setIcon1(QString path);
    void setIcon2(QString path);

    QIcon icon1() const;
    QIcon icon2() const;

    void init(QString path, QSize size);
    void init(QString path1, QString path2, QSize size);

public slots:
    void toggleIcon();

private:
    QIcon mIcon1;
    QIcon mIcon2;
    bool mToggle;
};

#endif // ICONBUTTON_HPP
