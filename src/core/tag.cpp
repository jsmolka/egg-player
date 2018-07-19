#include "tag.hpp"

Tag::Tag(const wchar_t *file)
    : m_file(file)
{

}

Tag::~Tag()
{

}

bool Tag::isValid() const
{
    return m_file.isValid();
}

bool Tag::isAudioValid() const
{
    return static_cast<bool>(m_file.audioProperties());
}

bool Tag::isTagValid() const
{
    return static_cast<bool>(m_file.tag());
}

QString Tag::title() const
{
    return toQString(m_file.tag()->title());
}

QString Tag::artist() const
{
    return toQString(m_file.tag()->artist());
}

QString Tag::album() const
{
    return toQString(m_file.tag()->album());
}

QString Tag::genre() const
{
    return toQString(m_file.tag()->genre());
}

int Tag::year() const
{
    return m_file.tag()->year();
}

int Tag::track() const
{
    return m_file.tag()->track();
}

int Tag::duration() const
{
    return m_file.audioProperties()->length();
}

QPixmap Tag::cover(int size)
{
    QPixmap cover = readCover();
    if (cover.isNull())
    {
        cover = Util::cover();
        log("Tag: Cannot read cover %1", {toQString(m_file.name().toString())});
    }
    return Util::resize(cover, size);
}

QPixmap Tag::coverify(const QPixmap &cover)
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

QPixmap Tag::readCover()
{
    QPixmap cover;
    if (m_file.hasID3v2Tag())
    {
        TagLib::ID3v2::Tag *tag = m_file.ID3v2Tag();
        TagLib::ID3v2::FrameList frameList = tag->frameList("APIC");
        if (!frameList.isEmpty())
        {
            TagLib::ID3v2::AttachedPictureFrame *frame = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());
            cover.loadFromData((const uchar *)frame->picture().data(), frame->picture().size());
            cover = coverify(cover);
        }
    }
    return cover;
}

QString Tag::toQString(const TagLib::String &string) const
{
    return QString::fromWCharArray(string.toCWString(), string.size());
}
