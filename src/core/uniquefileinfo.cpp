#include "uniquefileinfo.hpp"

#include "logger.hpp"

UniqueFileInfo::UniqueFileInfo()
    : m_low(0)
    , m_high(0)
    , m_volume(0)
{

}

UniqueFileInfo::UniqueFileInfo(const File &file)
    : UniqueFileInfo()
{
    readInfo(file);
}

void UniqueFileInfo::setLow(DWORD low)
{
    m_low = low;
}

DWORD UniqueFileInfo::low() const
{
    return m_low;
}

void UniqueFileInfo::setHigh(DWORD high)
{
    m_high = high;
}

DWORD UniqueFileInfo::high() const
{
    return m_high;
}

void UniqueFileInfo::setVolume(DWORD volume)
{
    m_volume = volume;
}

DWORD UniqueFileInfo::volume() const
{
    return m_volume;
}

void UniqueFileInfo::readInfo(const File &file)
{
    HANDLE handle = CreateFileW(
        reinterpret_cast<const wchar_t *>(file.constData()),
        GENERIC_READ,
        FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (handle == INVALID_HANDLE_VALUE)
    {
        LOG("Cannot open file %1", file);
        return;
    }

    BY_HANDLE_FILE_INFORMATION info;
    if (!GetFileInformationByHandle(handle, &info))
    {
        LOG("Cannot get file information %1", file);
        return;
    }

    m_volume = info.dwVolumeSerialNumber;
    m_low = info.nFileIndexLow;
    m_high = info.nFileIndexHigh;

    if (!CloseHandle(handle))
        LOG("Cannot close handle %1", file);
}
