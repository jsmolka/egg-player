#include "uniquefileinfo.hpp"

#include <Windows.h>

#include "core/logger.hpp"
#include "core/utils.hpp"

UniqueFileInfo::UniqueFileInfo()
    : m_index(0)
    , m_volume(0)
{

}

UniqueFileInfo::UniqueFileInfo(const QString &file)
    : UniqueFileInfo()
{
    readInfo(file);

    if (!isValid())
        EGG_LOG("Invalid unique file info %1", file);
}

bool UniqueFileInfo::isValid() const
{
    return m_index != 0 && m_volume != 0;
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
        EGG_LOG("Cannot get file handle %1", file);
        return;
    }

    BY_HANDLE_FILE_INFORMATION info;
    if (GetFileInformationByHandle(handle, &info))
    {
        m_index = info.nFileIndexHigh;
        m_index <<= 32;
        m_index += info.nFileIndexLow;
        m_volume = info.dwVolumeSerialNumber;
    }
    else
    {
        EGG_LOG("Cannot get file information %1", file);
    }
    if (!CloseHandle(handle))
        EGG_LOG("Cannot close file handle %1", file);
}
