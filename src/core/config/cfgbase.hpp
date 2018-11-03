#ifndef CFGBASE_HPP
#define CFGBASE_HPP

#include <QJsonObject>
#include <QJsonValue>

#include "core/macros.hpp"

namespace cfg
{
class Base
{
public:
    virtual ~Base() = default;

    static float scale(float value);
    static int scale(int value);

    EGG_CPROP(QJsonObject, object, setObject, object)

    virtual void loadObject(const QJsonObject &object) = 0;
    virtual QJsonObject toObject() const = 0;

    virtual void setDefaults() = 0;

protected:
    void set(const QString &key, const QJsonValue &value);
    QJsonValue get(const QString &key) const;

    void setDefault(const QString &key, const QJsonValue &value);
};
}

#endif // CFGBASE_HPP
