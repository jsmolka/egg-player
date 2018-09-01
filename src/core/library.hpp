#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QObject>

#include "audio.hpp"
#include "audios.hpp"
#include "audioupdater.hpp"
#include "audioloader.hpp"
#include "coverloader.hpp"
#include "filesystem.hpp"
#include "initialloader.hpp"
#include "types.hpp"

#define eLibrary (Library::instance())

class Library : public QObject
{
    Q_OBJECT

public:
    explicit Library(QObject *parent = nullptr);
    explicit Library(bool sorted, QObject *parent = nullptr);

    static Library *instance();

    void setSorted(bool sorted);
    bool isSorted() const;

    Audios *audios();

    void initialLoad(const Paths &paths);

public slots:
    void insert(Audio *audio);

signals:
    void inserted(Audio *audio, int index);

private slots:
    void onAudioLoaderFinished();

    void onFileSystemRenamed(Audio *audio, const File &to);
    void onFileSystemRemoved(Audio *audio);

private:
    int lowerBound(Audio *audio);

    bool m_sorted;
    Audios m_audios;
    FileSystem m_fileSystem;
    InitialLoader m_initialLoader;
    CoverLoader m_coverLoader;
    AudioUpdater m_audioUpdater;
    AudioLoader m_audioLoader;
};

#endif // LIBRARY_HPP
