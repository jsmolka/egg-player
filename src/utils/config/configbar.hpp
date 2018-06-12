#ifndef CONFIGBAR_HPP
#define CONFIGBAR_HPP

#include "configitem.hpp"

/*!
 * Represents a bar item.
 */
class ConfigBar : public ConfigItem
{
public:
    /*!
     * Constructor.
     */
    ConfigBar();
    /*!
     * Constructor.
     */
    ConfigBar(const QJsonObject &object);
    /*!
     * Destructor.
     */
    ~ConfigBar();
    /*!
     * Sets defaults.
     */
    void setDefaults() override;
    /*!
     * Setter for groove height.
     */
    void setGrooveHeight(int height);
    /*!
     * Getter for groove height.
     */
    int grooveHeight();
    /*!
     * Setter for handle size.
     */
    void setHandleSize(int size);
    /*!
     * Getter for handle size.
     */
    int handleSize();
    /*!
     * Setter for height.
     */
    void setHeight(int height);
    /*!
     * Getter for height.
     */
    int height();
    /*!
     * Setter for icon size.
     */
    void setIconSize(int size);
    /*!
     * Getter for icon size.
     */
    int iconSize();
    /*!
     * Setter for margin.
     */
    void setMargin(int margin);
    /*!
     * Getter for margin.
     */
    int margin();
    /*!
     * Setter for spacing.
     */
    void setSpacing(int spacing);
    /*!
     * Getter for spacing.
     */
    int spacing();
    /*!
     * Getter for cover size.
     */
    int coverSize();
    /*!
     * Setter for time width.
     */
    void setTimeWidth(int width);
    /*!
     * Getter for time width.
     */
    int timeWidth();
    /*!
     * Setter for track width.
     */
    void setTrackWidth(int width);
    /*!
     * Getter for track width.
     */
    int trackWidth();
};

#endif // CONFIGBAR_HPP
