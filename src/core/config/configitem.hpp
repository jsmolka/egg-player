#ifndef CONFIGITEM_HPP
#define CONFIGITEM_HPP

#include <QJsonObject>
#include <QJsonValue>

class ConfigItem
{
public:
    ConfigItem();
    explicit ConfigItem(const QJsonObject &object);
    virtual ~ConfigItem() = default;

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

#endif // CONFIGITEM_HPP
