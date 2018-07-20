#ifndef ICONFACTORY_HPP
#define ICONFACTORY_HPP

#include <QIcon>
#include <QPainter>
#include <QPixmap>

class IconFactory
{
public:
    IconFactory();
    ~IconFactory();

    static QIcon make(const QString &file);

private:
    static QPixmap makeActive(const QPixmap &pixmap);
};

#endif // ICONFACTORY_HPP
