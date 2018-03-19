#include "audiofile.hpp"

using namespace TagLib;

AudioFile::AudioFile(QString path, bool autoLoadCover)
{
    m_path = path;
    m_ref = FileRef(path.toLatin1().data());

    if (!m_ref.isNull())
        m_isValid = readTags() && readAudio();
    else
        m_isValid = false;

    if (autoLoadCover)
        m_cover = getCover();
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

quint32 AudioFile::bitrate() const
{
    return m_bitrate;
}

quint32 AudioFile::seconds() const
{
    return m_length % 60;
}

quint32 AudioFile::minutes() const
{
    return (m_length - seconds()) / 60;
}

void AudioFile::setCover(QImage cover)
{
    m_cover = cover;
}

QImage AudioFile::cover() const
{
    return m_cover;
}

void AudioFile::setCoverPtr(QImage *coverPtr)
{
    m_coverPtr = coverPtr;
}

QImage * AudioFile::coverPtr() const
{
    return m_coverPtr;
}

bool AudioFile::readTags()
{
    if (!m_ref.tag())
        return false;

    Tag *tag = m_ref.tag();

    m_title = QString(tag->title().toCString());
    m_artist = QString(tag->artist().toCString());
    m_album = QString(tag->album().toCString());
    m_genre = QString(tag->genre().toCString());
    m_year = tag->year();
    m_track = tag->track();

    return true;
}

bool AudioFile::readAudio()
{
    if (!m_ref.audioProperties())
        return false;

    AudioProperties *audio = m_ref.audioProperties();

    m_length = audio->length();
    m_bitrate = audio->bitrate();

    return true;
}

QImage AudioFile::getCover()
{
    QImage image = loadCoverFromFile();
    if (!image.isNull())
        return image;

    image = readCover();
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
            ID3v2::FrameList::ConstIterator it = frameList.begin();
            for (; it != frameList.end(); it++)
            {
                ID3v2::AttachedPictureFrame *frame = static_cast<ID3v2::AttachedPictureFrame *>(*it);
                if (frame->type() == ID3v2::AttachedPictureFrame::FrontCover)
                {
                    image.loadFromData((const uchar *) frame->picture().data(), frame->picture().size());
                    return image;
                }
            }
        }
    }
    return image;
}

QImage AudioFile::loadCoverFromFile()
{
    QStringList covers;
    covers << "cover.jpg" << "cover.jpeg" << "cover.png";

    QDir dir = FileUtil::dir(m_path);

    for (QString cover : covers)
    {
        QString path = FileUtil::join(dir, cover);

        if (FileUtil::exists(path))
        {
            return QImage(path);
        }
    }
    return QImage();
}
