#ifndef CACHE_HPP
#define CACHE_HPP

#include <QBuffer>
#include <QHash>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QThread>

#include "audio.hpp"
#include "constants.hpp"
#include "logger.hpp"

/*!
 * This class represents an audio cache in form of an sqlite database.
 */
class Cache
{
public:
    /*!
     * Constructor.
     */
    Cache();
    /*!
     * Destructor.
     */
    ~Cache();
    /*!
     * Starts a transaction.
     */
    bool transaction();
    /*!
     * Commits the current transaction.
     */
    bool commit();
    /*!
     * Rolls the current transaction back.
     */
    bool rollback();
    /*!
     * Loads an audio object for a given path. A nullptr will be returned if the
     * audio cannot be loaded.
     */
    Audio * load(const QString &path);
    /*!
     * Inserts the tags of an audio object into the cache.
     */
    void insertTags(Audio *audio);
    /*!
     * Inserts the cover of an audio object into the cache. Returns the cover
     * id.
     */
    int insertCover(Audio *audio, int size = 200);
    /*!
     * Updates the tags of an audio object. Note that this function will reset
     * the cover id.
     */
    void updateTags(Audio *audio);
    /*!
     * Returns the cover id of an audio.
     */
    int coverId(Audio *audio);
    /*!
     * Loads the cover of an audio object from the cache. Uses a cached version
     * if the cover has already been loaded.
     */
    QPixmap cover(Audio *audio, int size = 200);

private:
    /*!
     * Gets the database name based on the current thread because every thread
     * needs a unique database connection.
     */
    QString dbName();
    /*!
     * Gets the cache database.
     */
    QSqlDatabase db();
    /*!
     * Creates the covers table if it does not exist already.
     */
    void createCovers();
    /*!
     * Creates the audios table if it does not exist already.
     */
    void createAudios();
    /*!
     * Inserts the a cover into the cache or returns its id if it exists
     * already. Returns -1 if the cover cannot be inserted or retrieved.
     */
    int getOrInsertCover(const QPixmap &cover);
    /*!
     * Inserts a cover in byte array form into the cache and returns its id.
     */
    int insertByteCover(const QByteArray &bytes);
    /*!
     * Retrieves the cover id for a given cover in byte array form. For
     * performance reasons it first tries to query the cover by byte array
     * size and then by blob comparison.
     */
    int coverId(const QByteArray &bytes);
    /*!
     * Gets the last (highest) cover id.
     */
    int lastCoverId();
    /*!
     * Queries a cover by size.
     */
    int queryCoverIdBySize(int size);
    /*!
     * Queries a cover by blob comparison.
     */
    int queryCoverIdByBlob(const QByteArray &bytes);
    /*!
     * Handles database errors.
     */
    void handleError();
    /*!
     * Gets the last used query by replacing all bounded values with the used
     * ones.
     */
    QString lastQuery();
    /*!
     * Converts a cover to a byte array.
     */
    QByteArray coverToBytes(const QPixmap &cover);
    /*!
     * Member variables.
     */
    QSqlDatabase m_db;
    QSqlQuery m_query;
    /*!
     * Static variables.
     */
    static QHash<int, QPixmap> _covers;
};

#endif // CACHE_HPP
