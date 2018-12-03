#include "iconcreator.hpp"

#include <QPainter>

#include "core/logger.hpp"

QVector<QIcon> IconCreator::create(const QString &file)
{
    QIcon icon;

    const QPixmap normal(file);
    if (normal.isNull())
        egg_log() << "Cannot create pixmap" << file;

    icon.addPixmap(normal, QIcon::Normal, QIcon::Off);
    icon.addPixmap(createActive(normal), QIcon::Active, QIcon::Off);

    return QVector<QIcon>() << icon;
}

QVector<QIcon> IconCreator::create(const QStrings &files)
{
    QVector<QIcon> icons;

    for (const QString &file : files)
        icons << create(file);

    return icons;
}

QPixmap IconCreator::createActive(const QPixmap &pixmap)
{
    QPixmap active(pixmap.size());
    active.fill(Qt::transparent);

    QPainter painter(&active);
    painter.setBackground(QBrush(Qt::transparent));
    painter.setBackgroundMode(Qt::TransparentMode);
    painter.eraseRect(pixmap.rect());

    painter.setOpacity(0.4);
    painter.drawPixmap(0, 0, pixmap);
    painter.end();

    return active;
}
