#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QApplication>
#include <QMutex>
#include <QObject>
#include <QSet>
#include <QStringList>

#include "audio.hpp"
#include "audioloader.hpp"
#include "cachebuilder.hpp"
#include "threadpool.hpp"
#include "types.hpp"

#define eggLibrary (Library::instance())

class Library : public QObject
{
    Q_OBJECT

public:
    Library(QObject *parent = nullptr);
    Library(bool sorted, QObject *parent = nullptr);
    ~Library();

    static Library * instance();

    void setSorted(bool sorted);
    bool isSorted() const;
    Audios audios() const;

    void load(const StringList &paths);

public slots:
    void insert(Audio *audio);

signals:
    void loaded();
    void inserted(Audio *, int);

private slots:
    void onAudioLoaderFinished();

private:
    int lowerBound(Audio *audio);
    void insertBinary(Audio *audio);
    void append(Audio *audio);

    StringList uniqueFiles(const StringList &paths);

    bool m_sorted;
    Audios m_audios;
    AudioLoader *pm_audioLoader;
    CacheBuilder *pm_cacheBuilder;
    QMutex m_mutex;
    QSet<QString> m_paths;

    static Library *_instance;
};

#endif // LIBRARY_HPP
