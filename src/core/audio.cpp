#include "audio.hpp"

/*
 * Use TagLib namespace for whole class.
 */
using namespace TagLib;

/*
 * Constructor. Creates an audio object and tries
 * to read its tags. If the title tag is empty it
 * will be set to the file name of the read file.
 *
 * :param path: audio path
 */
Audio::Audio(const QString &path)
{
    m_path = path;
    m_valid = readTags();

    if (!m_valid)
    {
        Logger::log("Audio: Cannot read tags '%1'", {m_path});
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
 * Returns the path in wide char form. Needs to
 * be used for taglib and BASS.
 *
 * :return: path
 */
const wchar_t * Audio::pathWChar() const
{
    return reinterpret_cast<const wchar_t*>(m_path.constData());
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
 * Reads audio tags. If either the tags or the
 * audio properties cannot be read the function
 * returns false. If the file has a tag it will
 * be read.
 *
 * :return: success
 */
bool Audio::readTags()
{
    FileRef fileRef(pathWChar());

    if (fileRef.isNull() || !fileRef.audioProperties())
        return false;

    AudioProperties *audioProp = fileRef.audioProperties();
    m_length = audioProp->length();

    if (fileRef.tag())
    {
        Tag *tag = fileRef.tag();
        m_title = TStringToQString(tag->title());
        m_artist = TStringToQString(tag->artist());
        m_album = TStringToQString(tag->album());
        m_genre = TStringToQString(tag->genre());
        m_year = tag->year();
        m_track = tag->track();
    }
    return true;
}

/*
 * Reads cover of audio file. Because covers
 * should always be squares the read cover
 * will be drawn onto a transparent square
 * if it is not square.
 *
 * :return: cover
 */
QPixmap Audio::readCover()
{
    MPEG::File file(pathWChar());
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
            int x = (size - image.width()) / 2;
            int y = (size - image.height()) / 2;
            painter.drawPixmap(x, y, image);
            image = background;
        }
    }
    else
    {
        image = Utils::defaultCover();
        Logger::log("Audio: Cannot read cover '%1'", {m_path});
    }
    return image;
}
