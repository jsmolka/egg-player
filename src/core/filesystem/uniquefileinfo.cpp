#include "uniquefileinfo.hpp"

#include "core/filesystem/windowsfile.hpp"

UniqueFileInfo::UniqueFileInfo()
    : m_index(0)
    , m_volume(0)
{

}

UniqueFileInfo::UniqueFileInfo(const QString &file)
    : UniqueFileInfo()
{
    m_file = file;

    readFileInfo();
}

QString UniqueFileInfo::file() const
{
    return m_file;
}

quint64 UniqueFileInfo::index() const
{
    return m_index;
}

quint64 UniqueFileInfo::volume() const
{
    return m_volume;
}

bool UniqueFileInfo::isValid() const
{
    return m_index != 0 && m_volume != 0;
}

void UniqueFileInfo::readFileInfo()
{
    WindowsFile wFile(m_file);

    if (!wFile.readFileInfo())
        return;

    m_index = wFile.fileIndexHigh();
    m_index <<= 32;
    m_index += wFile.fileIndexLow();
    m_volume = wFile.volume();
}
