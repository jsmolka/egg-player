#include "iconfactory.hpp"

#include <QPainter>

IconFactory::IconFactory()
{

}

IconFactory::~IconFactory()
{

}

QIcon IconFactory::make(const QString &file)
{
    QIcon icon;

    const QPixmap normal = QPixmap(file);
    icon.addPixmap(normal, QIcon::Normal, QIcon::Off);
    icon.addPixmap(makeActive(normal), QIcon::Active, QIcon::Off);

    return icon;
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
