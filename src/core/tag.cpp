#include "tag.hpp"

#include <QFileInfo>

#include <taglib/attachedpictureframe.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>

#include "logger.hpp"
#include "utils.hpp"

Tag::Tag(QObject *parent)
    : Tag(QString(), parent)
{

}

Tag::Tag(const File &file, QObject *parent)
    : QObject(parent)
    , m_file(file)
    , m_year(0)
    , m_track(0)
    , m_duration(0)
{

}

bool Tag::read()
{
    const TagLib::MPEG::File file(toWString(m_file));

    if (!file.isValid() || !file.audioProperties())
    {
        LOG(QFileInfo::exists(m_file)
            ? "Cannot read tags %1"
            : "File does not exist %1", m_file);
        return false;
    }

    m_duration = file.audioProperties()->lengthInSeconds();

    if (file.tag())
    {
        TagLib::Tag *tag = file.tag();
        m_title = toQString(tag->title());
        m_artist = toQString(tag->artist());
        m_album = toQString(tag->album());
        m_genre = toQString(tag->genre());
        m_year = static_cast<int>(tag->year());
        m_track = static_cast<int>(tag->track());
    }

    if (m_title.isEmpty())
        m_title = QFileInfo(m_file).baseName();

    return true;
}

QPixmap Tag::readCover()
{
    QPixmap cover;
    TagLib::MPEG::File file(toWString(m_file));
    if (file.hasID3v2Tag())
    {
        const TagLib::ID3v2::Tag *tag = file.ID3v2Tag();
        const TagLib::ID3v2::FrameList frameList = tag->frameList("APIC");
        if (!frameList.isEmpty())
        {
            const TagLib::ID3v2::AttachedPictureFrame *frame = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());
            cover.loadFromData(reinterpret_cast<const uchar *>(frame->picture().data()), frame->picture().size());
        }
    }

    if (cover.isNull())
        LOG("Cannot read cover %1", m_file);

    return cover;
}

void Tag::setFile(const File &file)
{
    m_file = file;
}

File Tag::file() const
{
    return m_file;
}

void Tag::setTitle(const QString &title)
{
    m_title = title;

    emit updated();
}

QString Tag::title() const
{
    return m_title;
}

void Tag::setArtist(const QString &artist)
{
    m_artist = artist;

    emit updated();
}

QString Tag::artist() const
{
    return m_artist;
}

void Tag::setAlbum(const QString &album)
{
    m_album = album;

    emit updated();
}

QString Tag::album() const
{
    return m_album;
}

void Tag::setGenre(const QString &genre)
{
    m_genre = genre;

    emit updated();
}

QString Tag::genre() const
{
    return m_genre;
}

void Tag::setYear(int year)
{
    m_year = year;

    emit updated();
}

int Tag::year() const
{
    return m_year;
}

void Tag::setTrack(int track)
{
    m_track = track;

    emit updated();
}

int Tag::track() const
{
    return m_track;
}

void Tag::setDuration(int duration)
{
    m_duration = duration;

    emit updated();
}

int Tag::duration() const
{
    return m_duration;
}
