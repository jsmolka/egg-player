#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QObject>
#include <QStringList>

#include "audio.hpp"
#include "audios.hpp"
#include "cache.hpp"
#include "cachebuilder.hpp"
#include "logger.hpp"
#include "utils.hpp"

class Library
{
public:
    Library(const QString &path);
    ~Library();

    Audios audios() const;
    bool isEmpty() const;

    void sortByTitle();

    Audios search(const QString &string, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    Audio * audioAt(int index);

private:
    void loadFiles(const QString &path);

    Audios m_audios;
};

#endif // LIBRARY_HPP
