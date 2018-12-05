#ifndef TAG_HPP
#define TAG_HPP

#include <QString>

#include "core/macros.hpp"

class Tag
{
public:
    Tag();
    explicit Tag(const QString &file);

    EGG_C_PROP(QString, file, setFile, file)
    EGG_C_PROP(QString, title, setTitle, title)
    EGG_C_PROP(QString, artist, setArtist, artist)
    EGG_C_PROP(QString, album, setAlbum, album)
    EGG_C_PROP(QString, genre, setGenre, genre)
    EGG_P_PROP(int, year, setYear, year)
    EGG_P_PROP(int, track, setTrack, track)
    EGG_P_PROP(int, duration, setDuration, duration)

    bool read();
};

#endif // TAG_HPP
