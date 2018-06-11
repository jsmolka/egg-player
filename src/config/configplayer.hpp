#ifndef CONFIGPLAYER_HPP
#define CONFIGPLAYER_HPP

#include "configitem.hpp"

/*!
 * Represents a player item.
 */
class ConfigPlayer : public ConfigItem
{
public:
    /*!
     * Constructor.
     */
    ConfigPlayer();
    /*!
     * Constructor.
     */
    ConfigPlayer(const QJsonObject &object);
    /*!
     * Destructor.
     */
    ~ConfigPlayer();
    /*!
     * Sets defaults.
     */
    void setDefaults() override;
    /*!
     * Setter for loop.
     */
    void setLoop(bool loop);
    /*!
     * Getter for loop.
     */
    bool loop();
    /*!
     * Setter for shuffle.
     */
    void setShuffle(bool shuffle);
    /*!
     * Getter for shuffle.
     */
    bool shuffle();
    /*!
     * Setter for volume.
     */
    void setVolume(int volume);
    /*!
     * Getter for volume.
     */
    int volume();
};

#endif // CONFIGPLAYER_HPP
