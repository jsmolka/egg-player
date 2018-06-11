#ifndef CFGABSTRACT_HPP
#define CFGABSTRACT_HPP

#include <ShellScalingApi.h>

#include <QJsonObject>
#include <QJsonValue>

/*!
 * Represents the abstract parent class for every config item.
 */
class CfgAbstract
{
public:
    /*!
     * Constructor.
     */
    CfgAbstract();
    /*!
     * Constructor.
     */
    CfgAbstract(QJsonObject object);
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
    /*!
     * Member variables.
     */
    QJsonObject m_object;
};

#endif // CFGABSTRACT_HPP
