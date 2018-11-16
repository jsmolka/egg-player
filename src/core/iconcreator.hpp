#ifndef ICONCREATOR_HPP
#define ICONCREATOR_HPP

#include <QIcon>
#include <QPixmap>
#include <QVector>

#include "core/types.hpp"

class IconCreator
{
public:
    static QVector<QIcon> create(const QString &file);
    static QVector<QIcon> create(const QStrings &files);

private:
    static QPixmap createActive(const QPixmap &pixmap);
};

#endif // ICONCREATOR_HPP
