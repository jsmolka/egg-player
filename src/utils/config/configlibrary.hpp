#ifndef CONFIGLIBRARY_HPP
#define CONFIGLIBRARY_HPP

#include <QJsonArray>
#include <QStandardPaths>
#include <QVariant>
#include <QVector>

#include "configabstract.hpp"

class ConfigLibrary : public ConfigAbstract
{
public:
    using ConfigAbstract::ConfigAbstract;

    void setDefaults() override;

    void setCellPadding(int padding);
    int cellPadding();

    void setItemHeight(int height);
    int itemHeight();

    void setPaths(const QVector<QString> &paths);
    QVector<QString> paths();

    void setScrollBarWidth(int width);
    int scrollBarWidth();
};

#endif // CONFIGLIBRARY_HPP
