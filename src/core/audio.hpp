#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <QPainter>
#include <QPixmap>
#include <QPixmapCache>
#include <QVector>

#include <taglib/attachedpictureframe.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>

#include "constants.hpp"
#include "logger.hpp"
#include "utils.hpp"

/*!
 * This class represents an audio object with all tag information.
 */
class Audio
{
public:
    /*!
     * Constructor.
     */
    Audio(const QString &path);
    /*!
     * Constructor used for cached audios.
     */
    Audio(const QString &path, const QString &title, const QString &artist, const QString &album,
          const QString &genre, int year, int track, int duration, int coverId, int size);
    /*!
     * Destructor.
     */
    ~Audio();
    /*!
     * Getter for valid property.
     */
    bool isValid() const;
    /*!
     * Getter for path property.
     */
    QString path() const;
    /*!
     * Getter for title property.
     */
    QString title() const;
    /*!
     * Getter for artist property.
     */
    QString artist() const;
    /*!
     * Getter for album property.
     */
    QString album() const;
    /*!
     * Getter for genre property.
     */
    QString genre() const;
    /*!
     * Getter for year property.
     */
    int year() const;
    /*!
     * Getter for track property.
     */
    int track() const;
    /*!
     * Getter for length property. Returns the nearest amount in seconds if seconds
     * is true. Otherwise the length in milliseconds will be returned.
     */
    int duration(bool seconds = true) const;
    /*!
     * Setter for cover id property.
     */
    void setCoverId(int coverId);
    /*!
     * Getter for cover id property.
     */
    int coverId() const;
    /*!
     * Getter for size property.
     */
    quint64 size() const;
    /*!
     * Getter for outdated property.
     */
    bool isOutdated() const;
    /*!
     * Returns the path as constant wide char pointer.
     */
    const wchar_t * pathWChar() const;
    /*!
     * Reads the cover and returns it.
     */
    QPixmap cover(int size = 200);

private:
    /*!
     * Reads the audio tags.
     */
    bool readTags();
    /*!
     * Converts a pixmap into a valid cover with a square layout.
     */
    QPixmap coverify(const QPixmap &cover);
    /*!
     * Reads the cover.
     */
    QPixmap readCover();
    /*!
     * Member variables.
     */
    bool m_valid;
    QString m_path;
    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_genre;
    int m_year;
    int m_track;
    int m_duration;
    int m_coverId;
    quint64 m_size;
    bool m_outdated;
};

typedef QVector<Audio *> Audios;

#endif // AUDIO_HPP
