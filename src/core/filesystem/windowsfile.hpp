#ifndef FS_WINDOWSFILE_HPP
#define FS_WINDOWSFILE_HPP

#include <Windows.h>

#include <QString>

namespace fs
{

class WindowsFile
{
public:
    explicit WindowsFile(const QString &file);
    ~WindowsFile();

    QString file() const;
    HANDLE handle() const;

    DWORD fileIndexLow() const;
    DWORD fileIndexHigh() const;
    DWORD volume() const;

    bool isHandleValid() const;

    bool readFileInfo();

private:
    void createHandle();
    void closeHandle();

    QString m_file;
    HANDLE m_handle;
    DWORD m_fileIndexLow;
    DWORD m_fileIndexHigh;
    DWORD m_volume;
};

}

#endif // FS_WINDOWSFILE_HPP
