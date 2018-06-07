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
 * This class represents a cache in form of an sqlite database.
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
     * Loads an audio object for a given path. If the audio cannot be loaded a
     * nullptr will be returned.
     */
    Audio * load(const QString &path);
    /*!
     * Inserts the tags of an audio object into the cache.
     */
    bool insertAudio(Audio *audio);
    /*!
     * Inserts the cover of an audio object into the cache.
     */
    bool insertCover(Audio *audio, int size = 200);
    /*!
     * Checks if the cache contains an audio object.
     */
    bool contains(Audio *audio);
    /*!
     * Loads the cover of an audio object from the cache.
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
     * length and then by blob comparison.
     */
    int coverId(const QByteArray &bytes);
    /*!
     * Gets the last (highest) cover id.
     */
    int lastCoverId();
    /*!
     * Queries a cover by length.
     */
    int queryCoverIdByLength(int length);
    /*!
     * Queries a cover by blob comparison.
     */
    int queryCoverIdByBlob(const QByteArray &bytes);
    /*!
     * Handles database errors.
     */
    void handleError(const QSqlQuery &query);
    /*!
     * Gets the last used query by replacing all bounded values with the used
     * ones.
     */
    QString lastQuery(const QSqlQuery &query);
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
