#include "uniquefileinfo.hpp"

#include <Windows.h>

UniqueFileInfo::UniqueFileInfo()
    : m_index(0)
    , m_volume(0)
{

}

UniqueFileInfo::UniqueFileInfo(const QString &file)
    : UniqueFileInfo()
{
    readInfo(file);
}

quint64 UniqueFileInfo::index() const
{
    return m_index;
}

quint64 UniqueFileInfo::volume() const
{
    return m_volume;
}

void UniqueFileInfo::readInfo(const QString &file)
{
    HANDLE handle = CreateFileW(
        Util::toWString(file),
        0,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (handle == INVALID_HANDLE_VALUE)
    {
        LOG("Cannot get file handle %1", file);
        return;
    }

    BY_HANDLE_FILE_INFORMATION info;
    if (!GetFileInformationByHandle(handle, &info))
    {
        LOG("Cannot get file information %1", file);
        return;
    }

    m_index = info.nFileIndexHigh;
    m_index <<= 32;
    m_index += info.nFileIndexLow;
    m_volume = info.dwVolumeSerialNumber;

    if (!CloseHandle(handle))
        LOG("Cannot close file handle %1", file);
}
