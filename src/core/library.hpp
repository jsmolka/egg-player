#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QString>
#include <QStringList>

#include <src/core/audio.hpp>
#include <src/core/audiolist.hpp>
#include <src/utils/fileutil.hpp>

class Library
{
public:
    Library();
    Library(const QString &path);
    Library(QStringList paths);

    AudioList audioList() const;
    bool isEmpty() const;

    AudioList getByTitle(const QString &title, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    AudioList getByArtist(const QString &artist, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    AudioList getByAlbum(const QString &album, Qt::CaseSensitivity cs = Qt::CaseInsensitive);

    AudioList searchByTitle(const QString &title, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    AudioList searchByArtist(const QString &artist, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    AudioList searchByAlbum(const QString &album, Qt::CaseSensitivity cs = Qt::CaseInsensitive);

    void sortByTitle(bool reverse = false);
    void sortByArtist(bool reverse = false);
    void sortByAlbum(bool reverse = false);

    Audio * at(quint32 idx);

signals:
    void libraryUpdated();

private:
    void loadFiles(const QString &path);

    AudioList m_audioList;
};

#endif // LIBRARY_HPP
