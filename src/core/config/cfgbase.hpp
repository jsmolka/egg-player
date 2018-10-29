#ifndef CFGBASE_HPP
#define CFGBASE_HPP

#include <QJsonObject>
#include <QJsonValue>

namespace cfg
{
class Base
{
public:
    explicit Base();
    explicit Base(const QJsonObject &object);
    virtual ~Base() = default;

    QJsonObject object() const;

    virtual void setDefaults() = 0;

protected:
    void set(const QString &key, const QJsonValue &value);
    QJsonValue get(const QString &key) const;

    void setDefault(const QString &key, const QJsonValue &value);

    float scale(float value) const;
    int scale(int value) const;

private:
    QJsonObject m_object;
};
}

#endif // CFGBASE_HPP
