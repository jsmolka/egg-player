#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QObject>
#include <QStringList>

#include "audio.hpp"
#include "audios.hpp"
#include "cachebuilder.hpp"
#include "audioloader.hpp"

class Library : public QObject
{
    Q_OBJECT

public:
    Library(QObject *parent = nullptr);
    ~Library();

    Audios audios() const;
    QStringList paths() const;

    void sortByTitle();

    void load(const QStringList &paths);
    void load(const QString &path);

    Audios search(const QString &string, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    Audio * audioAt(int index);

public slots:
    void insert(Audio *audio);

signals:
    void loaded();

private slots:
    void onLibraryBuilderFinished();

private:
    Audios m_audios;
    QStringList m_paths;
    CacheBuilder *pm_cacheBuilder;
    AudioLoader *pm_libraryBuilder;
};

#endif // LIBRARY_HPP
