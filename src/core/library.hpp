#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QObject>

#include "core/audio.hpp"
#include "core/audios.hpp"
#include "core/globals.hpp"
#include "core/filesystem/filesystem.hpp"
#include "threading/audioupdater.hpp"
#include "threading/audioloader.hpp"
#include "threading/coverloader.hpp"
#include "threading/initialloader.hpp"

#define eLibrary (Library::instance())

#define egg_library eLibrary

class Library : public QObject
{
    Q_OBJECT

public:
    explicit Library(QObject *parent = nullptr);

    static Library *instance();

    Audios *audios();
    Audios *audios() const;

    FileSystem &fileSystem();
    FileSystem &fileSystem() const;

    void initialLoad(const QStrings &paths);
    void loadFiles(const QStrings &files);

public slots:
    void insert(Audio *audio);

signals:
    void inserted(Audio *audio, int index);

private slots:
    void onInitialLoaderFinished();
    void onAudioUpdaterUpdated(Audio *audio);

    void onFileSystemRenamed(Audio *audio, const QString &to);
    void onFileSystemRemoved(Audio *audio);

private:
    int lowerBound(Audio *audio);

    Audios m_audios;
    FileSystem m_fileSystem;
    InitialLoader m_initialLoader;
    CoverLoader m_coverLoader;
    AudioUpdater m_audioUpdater;
    AudioLoader m_audioLoader;
};

#endif // LIBRARY_HPP
