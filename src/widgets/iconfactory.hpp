#ifndef ICONFACTORY_HPP
#define ICONFACTORY_HPP

#include <QIcon>
#include <QPixmap>
#include <QVector>

#include "core/types.hpp"

class IconFactory
{
public:
    static QVector<QIcon> make(const QString &file);
    static QVector<QIcon> make(const QStrings &files);

private:
    static QPixmap makeActive(const QPixmap &pixmap);
};

#endif // ICONFACTORY_HPP
