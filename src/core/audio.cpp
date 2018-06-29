#include "audio.hpp"

using namespace TagLib;

Audio::Audio(const QString &path)
    : m_valid(true)
    , m_path(path)
    , m_coverId(-1)
    , m_outdated(false)
    , m_size(FileUtil::size(path))
{
    if (!readTags())
    {
        m_valid = false;

        if (!FileUtil::exists(path))
            log("Audio: File does not exist %1", {m_path});
        else
            log("Audio: Cannot read tags %1", {m_path});
    }
}

Audio::Audio(const QString &path, const QString &title, const QString &artist,
             const QString &album, const QString &genre, int year, int track,
             int length, int coverId, int size)
    : m_valid(true)
    , m_path(path)
    , m_title(title)
    , m_artist(artist)
    , m_album(album)
    , m_genre(genre)
    , m_year(year)
    , m_track(track)
    , m_duration(length)
    , m_coverId(coverId)
    , m_size(size)
{
    m_outdated = size != FileUtil::size(path);
}

Audio::~Audio()
{

}

bool Audio::isValid() const
{
    return m_valid;
}

QString Audio::path() const
{
    return m_path;
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

int Audio::year() const
{
    return m_year;
}

int Audio::track() const
{
    return m_track;
}

int Audio::duration(bool seconds) const
{
    if (seconds)
        return static_cast<int>(round(static_cast<float>(m_duration) / 1000.0));
    else
        return m_duration;
}

void Audio::setCoverId(int id)
{
    m_coverId = id;
}

int Audio::coverId() const
{
    return m_coverId;
}

quint64 Audio::size() const
{
    return m_size;
}

bool Audio::isOutdated() const
{
    return m_outdated;
}

const wchar_t * Audio::pathWChar() const
{
    return reinterpret_cast<const wchar_t *>(m_path.constData());
}

QPixmap Audio::cover(int size)
{
    QPixmap cover = readCover();
    if (cover.isNull())
    {
        cover = Util::cover();
        log("Audio: Cannot read cover %1", {m_path});
    }
    return Util::resize(cover, size);
}

bool Audio::readTags()
{
    FileRef fileRef(pathWChar());

    if (fileRef.isNull() || !fileRef.audioProperties())
        return false;

    m_duration = fileRef.audioProperties()->lengthInMilliseconds();

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

        if (m_title.isEmpty())
            m_title = FileUtil::fileName(m_path);
    }
    return true;
}

QPixmap Audio::coverify(const QPixmap &cover)
{
    int height = cover.height();
    int width = cover.width();

    if (height != width)
    {
        int size = std::max(height, width);
        QPixmap square(size, size);
        square.fill(Qt::transparent);

        QPainter painter(&square);
        int x = (size - width) / 2;
        int y = (size - height) / 2;
        painter.drawPixmap(x, y, cover);
        return square;
    }
    return cover;
}

QPixmap Audio::readCover()
{
    MPEG::File file(pathWChar());
    QPixmap cover;

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
                cover.loadFromData((const uchar *) frame->picture().data(), frame->picture().size());
                cover = coverify(cover);
            }
        }
    }
    return cover;
}
