#ifndef FILEUTIL_HPP
#define FILEUTIL_HPP

#include <QDirIterator>
#include <QTextStream>

#include "types.hpp"

/*!
 * This namespace contains functions used for file related operations.
 */
namespace FileUtil
{
    /*!
     * Checks if a file exists.
     */
    extern bool exists(const QString &file);
    /*!
     * Returns the file name.
     */
    extern QString fileName(const QString &file);
    /*!
     * Returns the file size.
     */
    extern quint64 size(const QString &file);
    /*!
     * Reads the file content. Returns an empty string if the file cannot be
     * read.
     */
    extern QString read(const QString &file);
    /*!
     * Globs files with a certain suffix recursively.
     */
    extern StringList glob(const QString &path, const QString &suffix);
}

#endif // FILEUTIL_HPP
