#include "iconfactory.hpp"

#include <QPainter>

QVector<QIcon> IconFactory::make(const QString &file)
{
    QIcon icon;

    const QPixmap normal = QPixmap(file);
    if (normal.isNull())
        EGG_LOG("Cannot create pixmap %1", file);

    icon.addPixmap(normal, QIcon::Normal, QIcon::Off);
    icon.addPixmap(makeActive(normal), QIcon::Active, QIcon::Off);

    return QVector<QIcon>() << icon;
}

QVector<QIcon> IconFactory::make(const QStrings &files)
{
    QVector<QIcon> icons;

    for (const QString &file : files)
        icons << make(file);

    return icons;
}

QPixmap IconFactory::makeActive(const QPixmap &pixmap)
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
