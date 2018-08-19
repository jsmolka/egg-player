#ifndef CONFIGITEM_HPP
#define CONFIGITEM_HPP

#include <QJsonObject>
#include <QJsonValue>

class ConfigAbstract
{
public:
    ConfigAbstract();
    ConfigAbstract(const QJsonObject &object);
    ~ConfigAbstract();

    QJsonObject object() const;

    virtual void setDefaults() = 0;

protected:
    void set(const QString &key, const QJsonValue &value);
    QJsonValue get(const QString &key);

    void setDefault(const QString &key, const QJsonValue &value);

    float scale(float value);
    int scale(int value);

private:
    QJsonObject m_object;
};

#endif // CONFIGITEM_HPP
