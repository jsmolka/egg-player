#include "audio.hpp"

using namespace TagLib;

Audio::Audio(QString path)
{
    m_path = path;
    m_isValid = readTags();
    if (m_isValid)
        m_url = QUrl::fromLocalFile(path);
}

bool Audio::isValid() const
{
    return m_isValid;
}

QString Audio::path() const
{
    return m_path;
}

QUrl Audio::url() const
{
    return m_url;
}

QString Audio::title() const
{
    return m_title;
}

QString Audio::artist() const
{
    return m_artist;
}

QString Audio::album() const
{
    return m_album;
}

QString Audio::genre() const
{
    return m_genre;
}

quint32 Audio::year() const
{
    return m_year;
}

quint32 Audio::track() const
{
    return m_track;
}

quint32 Audio::length() const
{
    return m_length;
}

quint32 Audio::seconds() const
{
    return m_length % 60;
}

quint32 Audio::minutes() const
{
    return (m_length - seconds()) / 60;
}

QImage Audio::cover()
{
    return resizeCover(getCover());
}

bool Audio::readTags()
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

QImage Audio::resizeCover(QImage image)
{
    return image.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QImage Audio::getCover()
{
    QImage image = readCover();
    if (!image.isNull())
        return image;

    image = loadCoverFromFile();
    if (!image.isNull())
        return image;

    return QImage(IMG_DEFAULT_COVER);
}

QImage Audio::readCover()
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

QImage Audio::loadCoverFromFile()
{
    QStringList covers;
    covers << "cover.jpg" << "cover.jpeg" << "cover.png";

    QDir dir = FileUtil::dir(m_path);

    for (QString cover : covers)
    {
        QString path = FileUtil::join(dir, cover);

        if (FileUtil::exists(path))
            return QImage(path);
    }
    return QImage();
}
