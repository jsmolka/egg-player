#ifndef CONFIGLIBRARY_HPP
#define CONFIGLIBRARY_HPP

#include <QJsonArray>
#include <QStandardPaths>
#include <QVariant>

#include "configitem.hpp"
#include "types.hpp"

/*!
 * Represents a library item.
 */
class ConfigLibrary : public ConfigItem
{
public:
    /*!
     * Constructor.
     */
    ConfigLibrary();
    /*!
     * Constructor.
     */
    ConfigLibrary(const QJsonObject &object);
    /*!
     * Destructor.
     */
    ~ConfigLibrary();
    /*!
     * Sets defaults.
     */
    void setDefaults() override;
    /*!
     * Setter for cell padding.
     */
    void setCellPadding(int padding);
    /*!
     * Getter for cell padding.
     */
    int cellPadding();
    /*!
     * Setter for item height.
     */
    void setItemHeight(int height);
    /*!
     * Getter for item height.
     */
    int itemHeight();
    /*!
     * Setter for paths.
     */
    void setPaths(const StringList &paths);
    /*!
     * Getter for paths.
     */
    StringList paths();
    /*!
     * Setter for paths.
     */
    void setScrollBarWidth(int width);
    /*!
     * Getter for paths.
     */
    int scrollBarWidth();
};

#endif // CONFIGLIBRARY_HPP
