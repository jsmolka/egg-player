#include "audio.hpp"

/*
 * Use TagLib namespace for whole class.
 */
using namespace TagLib;

/*
 * Constructor. Creates an audio object and tries to read its tags. If the title
 * tag is empty it will be set to the file name of the read file.
 *
 * :param path: audio path
 */
Audio::Audio(const QString &path) :
    m_path(path)
{
    m_valid = readTags();
    if (!m_valid)
    {
        Logger::log("Audio: Cannot read tags %1", {m_path});
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
 * Getter for length property. Returns the* length either in seconds or in
 * milliseconds. The length in seconds will be ceiled to prevent playing the
 * next audio while the current one has not finished yet.
 *
 * :param seconds: use seconds, default true
 * :return: length
 */
int Audio::length(bool seconds) const
{
    if (seconds)
        return qCeil(static_cast<float>(m_length) / 1000.0);
    else
        return m_length;
}

/*
 * Returns the path in wide char form. Needs to be used for TagLib and BASS.
 * Reinterpret cast only works in Windows.
 *
 * :return: path
 */
const wchar_t * Audio::pathWChar() const
{
    return reinterpret_cast<const wchar_t *>(m_path.constData());
}

/*
 * Returns audio cover.
 *
 * :param size: cover size, default 200
 */
QPixmap Audio::cover(int size)
{
    return Utils::resize(readCover(), size);
}

/*
 * Reads audio tags. If either the tags or the audio properties cannot be read
 * the function returns false. If the file has a tag it will be read.
 *
 * :return: success
 */
bool Audio::readTags()
{
    FileRef fileRef(pathWChar());

    if (fileRef.isNull() || !fileRef.audioProperties())
        return false;

    m_length = fileRef.audioProperties()->lengthInMilliseconds();

    if (fileRef.tag())
    {
        Tag *tag = fileRef.tag();
        String title = tag->title();
        String artist = tag->artist();
        String album = tag->album();
        String genre = tag->genre();

        m_title = QString::fromWCharArray(title.toCWString(), title.size());
        m_artist = QString::fromWCharArray(artist.toCWString(), artist.size());
        m_album = QString::fromWCharArray(album.toCWString(), album.size());
        m_genre = QString::fromWCharArray(genre.toCWString(), genre.size());
        m_year = tag->year();
        m_track = tag->track();
    }
    return true;
}

/*
 * Reads cover of audio file. Because covers should always be squares, the read
 * cover will be drawn onto a transparent square if it is not square.
 *
 * :return: cover
 */
QPixmap Audio::readCover()
{
    MPEG::File file(pathWChar());
    QPixmap image;

    if (file.hasID3v2Tag())
    {
        ID3v2::Tag *tag = file.ID3v2Tag();
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
            int x = (size - image.width()) / 2;
            int y = (size - image.height()) / 2;
            painter.drawPixmap(x, y, image);
            image = background;
        }
    }
    else
    {
        image = Utils::defaultCover();
        Logger::log("Audio: Cannot read cover %1", {m_path});
    }
    return image;
}
