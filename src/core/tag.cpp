#include "tag.hpp"

#include <QFileInfo>

#include <taglib/fileref.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>

#include "core/logger.hpp"
#include "core/utils.hpp"

Tag::Tag()
    : Tag(QString())
{

}

Tag::Tag(const QString &file)
    : m_file(file)
    , m_year(0)
    , m_track(0)
    , m_duration(0)
{

}

bool Tag::read()
{
    const TagLib::MPEG::File file(Util::toWString(m_file));
    if (!file.isValid() || !file.audioProperties())
    {
        egg_log() << "Invalid file" << m_file;
        return false;
    }

    if (file.tag())
    {
        TagLib::Tag *tag = file.tag();
        m_title = Util::toQString(tag->title());
        m_artist = Util::toQString(tag->artist());
        m_album = Util::toQString(tag->album());
        m_genre = Util::toQString(tag->genre());
        m_year = static_cast<int>(tag->year());
        m_track = static_cast<int>(tag->track());
    }
    m_duration = file.audioProperties()->lengthInSeconds();

    if (m_title.isEmpty())
        m_title = QFileInfo(m_file).baseName();

    return true;
}
