#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QObject>

#include "core/audio.hpp"
#include "core/audios.hpp"
#include "core/filesystem.hpp"
#include "core/singleton.hpp"
#include "threading/audioupdater.hpp"
#include "threading/audioloader.hpp"
#include "threading/coverloader.hpp"
#include "threading/initialloader.hpp"

#define egg_library (Library::instance())

class Library : public QObject, public Singleton<Library>
{
    Q_OBJECT

public:
    explicit Library(QObject *parent = nullptr);

    const Audios &audios() const;
    const FileSystem &fileSystem() const;

    Audios &audios();
    FileSystem &fileSystem();

    void initialLoad(const QStrings &paths);
    void loadFiles(const QStrings &files);

public slots:
    void insert(Audio *audio);

signals:
    void inserted(Audio *audio, int index);

private slots:
    void onInitialLoaderFinished();
    void onAudioUpdaterUpdated(Audio *audio);

    void onFileSystemRenamed(Audio *audio, const QString &file);
    void onFileSystemRemoved(Audio *audio);

private:
    Audios m_audios;
    FileSystem m_fileSystem;
    InitialLoader m_initialLoader;
    CoverLoader m_coverLoader;
    AudioUpdater m_audioUpdater;
    AudioLoader m_audioLoader;
};

#endif // LIBRARY_HPP
