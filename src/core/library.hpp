#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QStringList>

#include "src/core/audio.hpp"
#include "src/core/audiolist.hpp"
#include "src/core/cache.hpp"
#include "src/utils/fileutil.hpp"

class Library
{
public:
    Library();
    Library(const QString &path);
    Library(const QStringList &paths);
    ~Library();

    AudioList audioList() const;
    bool isEmpty() const;

    AudioList getByTitle(const QString &title, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    AudioList getByArtist(const QString &artist, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    AudioList getByAlbum(const QString &album, Qt::CaseSensitivity cs = Qt::CaseInsensitive);

    AudioList searchByTitle(const QString &title, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    AudioList searchByArtist(const QString &artist, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    AudioList searchByAlbum(const QString &album, Qt::CaseSensitivity cs = Qt::CaseInsensitive);

    void sortByTitle();
    void sortByArtist();
    void sortByAlbum();

    Audio * at(int idx);

signals:
    void libraryUpdated();

private:
    void loadFiles(const QString &path);

    AudioList m_audioList;

};

#endif // LIBRARY_HPP
