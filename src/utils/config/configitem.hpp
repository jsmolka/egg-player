#ifndef CONFIGITEM_HPP
#define CONFIGITEM_HPP

#include <ShellScalingApi.h>

#include <QJsonObject>
#include <QJsonValue>

/*!
 * Represents an abstract config item.
 */
class ConfigItem
{
public:
    /*!
     * Constructor.
     */
    ConfigItem();
    /*!
     * Constructor.
     */
    ConfigItem(const QJsonObject &object);
    /*!
     * Destructor.
     */
    ~ConfigItem();
    /*!
     * Getter for object property.
     */
    QJsonObject object() const;
    /*!
     * Virtual function for settings defaults.
     */
    virtual void setDefaults() = 0;

protected:
    /*!
     * Sets the value at a key.
     */
    void set(const QString &key, const QJsonValue &value);
    /*!
     * Gets the value at a key.
     */
    QJsonValue get(const QString &key);
    /*!
     * Sets a value if it does not exist already.
     */
    void setDefault(const QString &key, const QJsonValue &value);
    /*!
     * Scales a value.
     */
    float scale(float value);
    /*!
     * Scales a value.
     */
    int scale(int value);
    /*!
     * Makes a value even.
     */
    int makeEven(int value);

private:
    /*!
     * Member variables.
     */
    QJsonObject m_object;
};

#endif // CONFIGITEM_HPP
