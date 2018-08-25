#ifndef ICONFACTORY_HPP
#define ICONFACTORY_HPP

#include <QIcon>
#include <QPixmap>

class IconFactory
{
public:
    static QIcon make(const QString &file);

private:
    static QPixmap makeActive(const QPixmap &pixmap);
};

#endif // ICONFACTORY_HPP
