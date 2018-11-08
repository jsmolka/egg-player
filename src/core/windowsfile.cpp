#include "windowsfile.hpp"

#include "core/logger.hpp"
#include "core/utils.hpp"

WindowsFile::WindowsFile(const QString &file)
    : m_file(file)
    , m_handle(INVALID_HANDLE_VALUE)
    , m_fileIndexLow(0)
    , m_fileIndexHigh(0)
    , m_volume(0)

{
    createHandle();
}

WindowsFile::~WindowsFile()
{
    closeHandle();
}

QString WindowsFile::file() const
{
    return m_file;
}

HANDLE WindowsFile::handle() const
{
    return m_handle;
}

DWORD WindowsFile::fileIndexLow() const
{
    return m_fileIndexLow;
}

DWORD WindowsFile::fileIndexHigh() const
{
    return m_fileIndexHigh;
}

DWORD WindowsFile::volume() const
{
    return m_volume;
}

bool WindowsFile::isHandleValid() const
{
    return m_handle != INVALID_HANDLE_VALUE;
}

bool WindowsFile::readFileInfo()
{
    BY_HANDLE_FILE_INFORMATION info;
    if (!GetFileInformationByHandle(m_handle, &info))
    {
        EGG_LOG("Cannot read file information %1", m_file);
        return false;
    }

    m_fileIndexLow = info.nFileIndexLow;
    m_fileIndexHigh = info.nFileIndexHigh;
    m_volume = info.dwVolumeSerialNumber;

    return true;
}

void WindowsFile::createHandle()
{
    m_handle = CreateFileW(
        Util::toWString(m_file),
        0,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (!isHandleValid())
        EGG_LOG("Cannot create file handle %1", m_file);
}

void WindowsFile::closeHandle()
{
    if (!CloseHandle(m_handle))
        EGG_LOG("Cannot close file handle %1", m_file);
}
