#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QStringList>

#include "audio.hpp"
#include "audiolist.hpp"
#include "cache.hpp"
#include "fileutil.hpp"
#include "logger.hpp"

class Library
{
public:
    Library(const QString &path);
    ~Library();

    AudioList audioList() const;
    bool isEmpty() const;

    AudioList search(const QString &string, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    void sortByTitle();
    Audio * audioAt(int index);

private:
    void loadFiles(const QString &path);

    AudioList m_audioList;
};

#endif // LIBRARY_HPP
