#ifndef CONFIGAPP_HPP
#define CONFIGAPP_HPP

#include "configitem.hpp"

/*!
 * Represents an app item.
 */
class ConfigApp : public ConfigItem
{
public:
    /*!
     * Constructor.
     */
    ConfigApp();
    /*!
     * Constructor.
     */
    ConfigApp(const QJsonObject &object);
    /*!
     * Destructor.
     */
    ~ConfigApp();
    /*!
     * Sets defaults.
     */
    void setDefaults() override;
    /*!
     * Setter for font size.
     */
    void setFontSize(double size);
    /*!
     * Getter for font size.
     */
    double fontSize();
    /*!
     * Setter for log.
     */
    void setLog(bool log);
    /*!
     * Getter for log.
     */
    bool log();
};

#endif // CONFIGAPP_HPP
