#include "iconbutton.hpp"

IconButton::IconButton(QWidget *parent) :
    QPushButton(parent)
{
    mToggle = true;

    setFlat(true);
    connect(this, SIGNAL(clicked(bool)), this, SLOT(toggleIcon()));
}

void IconButton::setIcon1(QString path)
{
    mIcon1 = QIcon(path);
}

QIcon IconButton::icon1() const
{
    return mIcon1;
}

void IconButton::setIcon2(QString path)
{
    mIcon2 = QIcon(path);
}

QIcon IconButton::icon2() const
{
    return mIcon2;
}

void IconButton::init(QString path, QSize size)
{
   init(path, QString(), size);
}

void IconButton::init(QString path1, QString path2, QSize size)
{
    setIcon1(path1);
    setIcon2(path2);
    setIconSize(size);

    setIcon(mIcon1);
}

void IconButton::toggleIcon()
{
    mToggle = !mToggle;

    if (mToggle && !mIcon1.isNull())
    {
        setIcon(mIcon1);
    }
    else if (!mIcon2.isNull())
    {
        setIcon(mIcon2);
    }
}
