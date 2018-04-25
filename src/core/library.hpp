#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QObject>
#include <QStringList>

#include "audio.hpp"
#include "audiolist.hpp"
#include "cache.hpp"
#include "cachebuilder.hpp"
#include "logger.hpp"
#include "utils.hpp"

class Library
{
public:
    Library(const QString &path);
    ~Library();

    AudioList audioList() const;
    bool isEmpty() const;

    void sortByTitle();

    AudioList search(const QString &string, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    Audio * audioAt(int index);

private:
    void loadFiles(const QString &path);

    AudioList m_audioList;
};

#endif // LIBRARY_HPP
