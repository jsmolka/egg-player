#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <algorithm>

#include <QList>
#include <QString>
#include <QStringList>

#include <src/core/audiofile.hpp>
#include <src/utils/fileutil.hpp>

class Library
{
public:
    Library(const QString &path);
    Library(QStringList pathList);

    QList<AudioFile> library() const;
    bool isEmpty() const;

    QList<AudioFile> getByTitle(const QString &title, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    QList<AudioFile> getByArtist(const QString &artist, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    QList<AudioFile> getByAlbum(const QString &album, Qt::CaseSensitivity cs = Qt::CaseInsensitive);

    QList<AudioFile> searchByTitle(const QString &title, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    QList<AudioFile> searchByArtist(const QString &artist, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    QList<AudioFile> searchByAlbum(const QString &album, Qt::CaseSensitivity cs = Qt::CaseInsensitive);

    void sortByTitle();
    void sortByArtist();
    void sortByAlbum();

    AudioFile at(quint32 idx) const;

signals:
    void libraryUpdated();

private:
    void loadFiles(const QString &path);

    QList<AudioFile> m_library;
};

#endif // LIBRARY_HPP
