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
#include "threading/audioloader.hpp"

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

    void init(const QStrings &paths);

public slots:
    void insert(const Audio &audio);

    void load(const QStrings &files);

signals:
    void inserted(Audio audio, int index);

private slots:
    void onAudioLoaderFinished();
    void onAudioUpdaterUpdated(Audio audio);

    void onFileSystemRenamed(Audio audio, const QString &name);
    void onFileSystemRemoved(Audio audio);

private:
    Audios m_audios;
    FileSystem m_fileSystem;
    AudioLoader m_audioLoader;
    CoverLoader m_coverLoader;
    AudioUpdater m_audioUpdater;
};

#endif // LIBRARY_HPP
