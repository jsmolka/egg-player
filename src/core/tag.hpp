#ifndef TAG_HPP
#define TAG_HPP

#include <QString>

#include "core/macros.hpp"

class Tag
{
public:
    Tag();
    explicit Tag(const QString &file);

    EGG_CPROP(QString, file, setFile, file)
    EGG_CPROP(QString, title, setTitle, title)
    EGG_CPROP(QString, artist, setArtist, artist)
    EGG_CPROP(QString, album, setAlbum, album)
    EGG_CPROP(QString, genre, setGenre, genre)
    EGG_PPROP(int, year, setYear, year)
    EGG_PPROP(int, track, setTrack, track)
    EGG_PPROP(int, duration, setDuration, duration)

    bool read();
};

#endif // TAG_HPP
