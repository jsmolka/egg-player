#include "iconfactory.hpp"

IconFactory::IconFactory()
{

}

IconFactory::~IconFactory()
{

}

QIcon IconFactory::make(const QString &file)
{
    QIcon icon;

    QPixmap normal = QPixmap(file);
    icon.addPixmap(normal, QIcon::Normal, QIcon::Off);
    icon.addPixmap(makeActive(normal), QIcon::Active, QIcon::Off);

    return icon;
}

QPixmap IconFactory::makeActive(const QPixmap &pixmap)
{
    QPixmap hoverPixmap(pixmap.size());
    hoverPixmap.fill(Qt::transparent);

    QPainter painter(&hoverPixmap);
    painter.setBackground(QBrush(Qt::transparent));
    painter.setBackgroundMode(Qt::TransparentMode);
    painter.eraseRect(pixmap.rect());

    painter.setOpacity(0.4);
    painter.drawPixmap(0, 0, pixmap);
    painter.end();

    return hoverPixmap;
}
