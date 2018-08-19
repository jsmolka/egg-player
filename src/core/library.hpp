#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QObject>

#include "audio.hpp"
#include "audios.hpp"
#include "audioloadercontroller.hpp"
#include "audioupdatercontroller.hpp"
#include "coverloadercontroller.hpp"
#include "filesystem.hpp"
#include "types.hpp"

#define eLibrary (Library::instance())

class Library : public QObject
{
    Q_OBJECT

public:
    explicit Library(QObject *parent = nullptr);
    explicit Library(bool sorted, QObject *parent = nullptr);
    ~Library();

    static Library *instance();

    void setSorted(bool sorted);
    bool isSorted() const;

    Audios *audios();

    AudioLoaderController &audioLoader();
    AudioUpdaterController &audioUpdater();
    CoverLoaderController &coverLoader();

    void load(const Paths &paths);

public slots:
    void insert(Audio *audio);

signals:
    void inserted(Audio *audio, int index);

private slots:
    void onAudioLoaderFinished();

    void onFileSystemModified(Audio *audio);
    void onFileSystemRenamed(Audio *audio, const File &to);
    void onFileSystemAdded(const File &file);
    void onFileSystemRemoved(Audio *audio);

private:
    int lowerBound(Audio *audio);

    bool m_sorted;
    Audios m_audios;
    FileSystem m_fileSystem;
    AudioLoaderController m_audioLoader;
    AudioUpdaterController m_audioUpdater;
    CoverLoaderController m_coverLoader;
};

#endif // LIBRARY_HPP
