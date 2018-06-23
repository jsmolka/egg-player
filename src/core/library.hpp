#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QApplication>
#include <QObject>
#include <QSet>
#include <QStringList>

#include "audio.hpp"
#include "audioloader.hpp"
#include "cachebuilder.hpp"
#include "threadpool.hpp"

#define eLibrary (Library::instance())

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

    void load(const QVector<QString> &paths);

public slots:
    void insert(Audio *audio);

signals:
    void loaded();
    void inserted(Audio *audio, int index);

private slots:
    void onAudioLoaderFinished();

private:
    int lowerBound(Audio *audio);
    void insertBinary(Audio *audio);
    void append(Audio *audio);

    QVector<QString> uniqueFiles(const QVector<QString> &paths);

    bool m_sorted;
    Audios m_audios;
    AudioLoader *pm_audioLoader;
    CacheBuilder *pm_cacheBuilder;
    QSet<QString> m_paths;

    static Library *_instance;
};

#endif // LIBRARY_HPP
