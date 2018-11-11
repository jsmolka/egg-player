#ifndef CFG_JSONOBJECT_HPP
#define CFG_JSONOBJECT_HPP

#include <QJsonObject>
#include <QJsonValue>

#include "core/macros.hpp"

namespace cfg
{

class JsonObject
{
public:
    virtual ~JsonObject() = default;

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

#endif // CFG_JSONOBJECT_HPP
