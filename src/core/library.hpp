#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QApplication>
#include <QObject>
#include <QSet>

#include "audio.hpp"
#include "audioloaderthread.hpp"
#include "coverloaderthread.hpp"
#include "threadpool.hpp"
#include "types.hpp"

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
    void insert(Audio *audio, bool doEmit = true);
    void insert(Audios audios);

signals:
    void loaded();
    void inserted(Audio *audio, int index);
    void inserted(Audios audios, Indices indices);

private slots:
    void onAudioLoaderFinished();

private:
    int lowerBound(Audio *audio);
    int insertBinary(Audio *audio);
    int append(Audio *audio);

    void fillBuffer(Audio *audio, int index);
    void emitBuffer();

    Files uniqueFiles(const Files &paths);

    bool m_sorted;
    Audios m_audios;
    AudioLoaderThread *pm_audioLoader;
    CoverLoaderThread *pm_coverLoader;
    Files m_paths;

    Audios m_bufferAudios;
    Indices m_bufferIndices;

    static Library *_instance;
};

#endif // LIBRARY_HPP
