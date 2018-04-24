#include "audio.hpp"

/*
 * Use TagLib namespace for whole class.
 */
using namespace TagLib;

/*
 * Constructor. Creates an audio object
 * and tries to read tags.
 * If the title tag is empty it will be
 * set to the file name of the read file.
 *
 * :param path: audio path
 */
Audio::Audio(const QString &path)
{
    m_path = path;
    m_valid = readTags();

    if (!m_valid)
    {
        Logger::log("Audio: Cannot read tags '%1'", m_path);
        return;
    }

    if (m_title.isEmpty())
        m_title = Utils::fileName(m_path);
}

/*
 * Destructor.
 */
Audio::~Audio()
{

}

/*
 * Getter for valid property.
 *
 * :return: valid
 */
bool Audio::isValid() const
{
    return m_valid;
}

/*
 * Getter for path property.
 *
 * :return: path
 */
QString Audio::path() const
{
    return m_path;
}

/*
 * Getter for title property.
 *
 * :return: title
 */
QString Audio::title() const
{
    return m_title;
}

/*
 * Getter for artist property.
 *
 * :return: artist
 */
QString Audio::artist() const
{
    return m_artist;
}

/*
 * Getter for album property.
 *
 * :return: album
 */
QString Audio::album() const
{
    return m_album;
}

/*
 * Getter for genre property.
 *
 * :return: genre
 */
QString Audio::genre() const
{
    return m_genre;
}

/*
 * Getter for year property.
 *
 * :return: year
 */
int Audio::year() const
{
    return m_year;
}

/*
 * Getter for track property.
 *
 * :return: track
 */
int Audio::track() const
{
    return m_track;
}

/*
 * Getter for length property.
 *
 * :return: length in seconds
 */
int Audio::length() const
{
    return m_length;
}

/*
 * Returns audio cover.
 *
 * :param size: cover size
 */
QPixmap Audio::cover(int size)
{
    return resize(readCover(), size);
}

/*
 * Reads audio tags. If either the
 * tags or the audio properties cannot
 * be read the function returns false.
 *
 * :return: success
 */
bool Audio::readTags()
{
    FileRef fileRef(m_path.toLatin1().data());

    if (fileRef.isNull()
            || !fileRef.tag()
            || !fileRef.audioProperties())
        return false;

    Tag *tag = fileRef.tag();
    AudioProperties *audioProp = fileRef.audioProperties();

    m_title = QString(tag->title().toCString());
    m_artist = QString(tag->artist().toCString());
    m_album = QString(tag->album().toCString());
    m_genre = QString(tag->genre().toCString());
    m_year = tag->year();
    m_track = tag->track();
    m_length = audioProp->length();

    return true;
}

/*
 * Resizes cover.
 *
 * :param cover: cover
 * :param size: size
 * :return: resized cover
 */
QPixmap Audio::resize(const QPixmap &cover, int size)
{
    return cover.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

/*
 * Reads cover of audio file. If the cover
 * is not a square it will be drawn onto a
 * transparent square.
 * Returns default cover if it cannot be read.
 *
 * :return: cover or default
 */
QPixmap Audio::readCover()
{
    MPEG::File file(m_path.toLatin1().data());
    ID3v2::Tag *tag = file.ID3v2Tag();
    QPixmap image;

    if (tag)
    {
        ID3v2::FrameListMap frameMap = tag->frameListMap();
        if (frameMap.contains("APIC"))
        {
            ID3v2::FrameList frameList = frameMap["APIC"];
            if (!frameList.isEmpty())
            {
                ID3v2::AttachedPictureFrame *frame = static_cast<ID3v2::AttachedPictureFrame *>(frameList.front());
                image.loadFromData((const uchar *) frame->picture().data(), frame->picture().size());
            }
        }
    }

    if (!image.isNull())
    {
        if (image.height() != image.width())
        {
            int size = std::max(image.height(), image.width());
            QPixmap background(size, size);
            background.fill(Qt::transparent);

            QPainter painter(&background);
            int x = (size - image.height()) / 2;
            int y = (size - image.width()) / 2;
            painter.drawPixmap(x, y, image);
            image = background;
        }
    }
    else
    {
        image = QPixmap(IMG_DEFAULT_COVER);
        Logger::log("Audio: Cannot read cover '%1'", m_path);
    }

    return image;
}
