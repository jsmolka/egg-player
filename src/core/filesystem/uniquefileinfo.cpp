#include "uniquefileinfo.hpp"

#include "core/filesystem/windowsfile.hpp"

fs::UniqueFileInfo::UniqueFileInfo()
    : m_index(0)
    , m_volume(0)
{

}

fs::UniqueFileInfo::UniqueFileInfo(const QString &file)
    : UniqueFileInfo()
{
    m_file = file;

    readFileInfo();
}

QString fs::UniqueFileInfo::file() const
{
    return m_file;
}

quint64 fs::UniqueFileInfo::index() const
{
    return m_index;
}

quint64 fs::UniqueFileInfo::volume() const
{
    return m_volume;
}

bool fs::UniqueFileInfo::isValid() const
{
    return m_index != 0 && m_volume != 0;
}

void fs::UniqueFileInfo::readFileInfo()
{
    WindowsFile file(m_file);

    if (!file.readFileInfo())
        return;

    m_index = file.fileIndexHigh();
    m_index <<= 32;
    m_index += file.fileIndexLow();
    m_volume = file.volume();
}
