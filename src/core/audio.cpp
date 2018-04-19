#include "audio.hpp"

using namespace TagLib;

/*
 * Constructor.
 *
 * :param path: path of audio
 */
Audio::Audio(const QString &path)
{
    m_path = path;
    m_valid = readTags();

    if (m_valid)
    {
        // Use filename as title if tag is empty
        if (m_title.isEmpty())
            m_title = FileUtil::fileName(m_path);
    }
    else
    {
        Logger::log("Audio: Cannot read tags '%1'", m_path);
    }
}

/*
 * Destructor.
 */
Audio::~Audio()
{

}

/*
 * Getter for valid.
 *
 * :return: audio is valid
 */
bool Audio::isValid() const
{
    return m_valid;
}

/*
 * Getter for path.
 *
 * :return: path of audio
 */
QString Audio::path() const
{
    return m_path;
}

/*
 * Getter for title.
 *
 * :return: audio title
 */
QString Audio::title() const
{
    return m_title;
}

/*
 * Getter for artist.
 *
 * :return: audio artist
 */
QString Audio::artist() const
{
    return m_artist;
}

/*
 * Getter for album.
 *
 * :return: audio album
 */
QString Audio::album() const
{
    return m_album;
}

/*
 * Getter for genre.
 *
 * :return: audio genre
 */
QString Audio::genre() const
{
    return m_genre;
}

/*
 * Getter for year.
 *
 * :return: audio release year
 */
int Audio::year() const
{
    return m_year;
}

/*
 * Getter for track.
 *
 * :return: audio track number
 */
int Audio::track() const
{
    return m_track;
}

/*
 * Getter for length.
 *
 * :return: audio length in seconds
 */
int Audio::length() const
{
    return m_length;
}

/*
 * Seconds without minutes.
 *
 * :return: seconds
 */
int Audio::seconds() const
{
    return m_length % 60;
}

/*
 * Minutes without seconds.
 *
 * :return: minutes
 */
int Audio::minutes() const
{
    return (m_length - seconds()) / 60;
}

/*
 * Returns audio cover.
 *
 * :param size: cover size (square)
 */
QPixmap Audio::cover(int size)
{
    return resizeCover(readCover(), size);
}

/*
 * Reads audio tags.
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
 * :param cover: cover to resize
 * :param size: size to resize
 * :return: resized cover
 */
QPixmap Audio::resizeCover(const QPixmap &cover, int size)
{
    return cover.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

/*
 * Reads cover of audio file. Returns
 * default cover if it cannot be read.
 *
 * :return: cover
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

                // Fill non square cover
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
        }
    }

    if (image.isNull())
    {
        image = QPixmap(IMG_DEFAULT_COVER);
        Logger::log("Audio: Cannot read cover '%1'", m_path);
    }
    return image;
}
