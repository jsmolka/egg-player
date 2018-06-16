#ifndef CONFIGITEM_HPP
#define CONFIGITEM_HPP

#include <ShellScalingApi.h>

#include <QJsonObject>
#include <QJsonValue>

class ConfigItem
{
public:
    ConfigItem();
    ConfigItem(const QJsonObject &object);
    ~ConfigItem();

    QJsonObject object() const;

    virtual void setDefaults() = 0;

protected:
    void set(const QString &key, const QJsonValue &value);
    QJsonValue get(const QString &key);

    void setDefault(const QString &key, const QJsonValue &value);

    float scale(float value);
    int scale(int value);
    int makeEven(int value);

private:
    QJsonObject m_object;
};

#endif // CONFIGITEM_HPP
