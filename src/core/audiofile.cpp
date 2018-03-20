#include "audiofile.hpp"

using namespace TagLib;

AudioFile::AudioFile(QString path)
{
    m_path = path;
    m_isValid = readTags();
}

bool AudioFile::isValid() const
{
    return m_isValid;
}

QString AudioFile::path() const
{
    return m_path;
}

QString AudioFile::title() const
{
    return m_title;
}

QString AudioFile::artist() const
{
    return m_artist;
}

QString AudioFile::album() const
{
    return m_album;
}

QString AudioFile::genre() const
{
    return m_genre;
}

quint32 AudioFile::year() const
{
    return m_year;
}

quint32 AudioFile::track() const
{
    return m_track;
}

quint32 AudioFile::length() const
{
    return m_length;
}

quint32 AudioFile::seconds() const
{
    return m_length % 60;
}

quint32 AudioFile::minutes() const
{
    return (m_length - seconds()) / 60;
}

QUrl AudioFile::url() const
{
    return QUrl::fromLocalFile(m_path);
}

QImage AudioFile::cover()
{
    return resizeCover(getCover());
}

bool AudioFile::readTags()
{
    FileRef fileRef(m_path.toLatin1().data());

    if (fileRef.isNull() || !fileRef.tag() || !fileRef.audioProperties())
        return false;

    Tag *tag = fileRef.tag();
    AudioProperties *audio = fileRef.audioProperties();

    m_title = QString(tag->title().toCString());
    m_artist = QString(tag->artist().toCString());
    m_album = QString(tag->album().toCString());
    m_genre = QString(tag->genre().toCString());
    m_year = tag->year();
    m_track = tag->track();
    m_length = audio->length();

    return true;
}

QImage AudioFile::resizeCover(QImage image)
{
    return image.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QImage AudioFile::getCover()
{
    QImage image = readCover();
    if (!image.isNull())
        return image;

    image = loadCoverFromFile();
    if (!image.isNull())
        return image;

    return QImage(IMG_DEFAULT_COVER);
}

QImage AudioFile::readCover()
{
    MPEG::File file(m_path.toLatin1().data());
    ID3v2::Tag *tag = file.ID3v2Tag();
    QImage image;

    if (tag)
    {
        ID3v2::FrameList frameList = tag->frameListMap()["APIC"];
        if (!frameList.isEmpty())
        {
            ID3v2::AttachedPictureFrame *frame = static_cast<ID3v2::AttachedPictureFrame *>(frameList.front());
            image.loadFromData((const uchar *) frame->picture().data(), frame->picture().size());
        }
    }
    return image;
}

QImage AudioFile::loadCoverFromFile()
{
    QStringList covers;
    QDir dir = FileUtil::dir(m_path);

    for (QString cover : covers)
    {
        QString path = FileUtil::join(dir, cover);

        if (FileUtil::exists(path))
            return QImage(path);
    }
    return QImage();
}
