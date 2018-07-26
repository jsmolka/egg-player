#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QApplication>
#include <QObject>
#include <QSet>

#include "audio.hpp"
#include "audioloadercontroller.hpp"
#include "coverloadercontroller.hpp"
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
    CoverLoaderController * coverLoader();
    AudioLoaderController * audioLoader();

    void load(const Files &paths);

public slots:
    void insert(Audio *audio);

signals:
    void inserted(Audio *audio, int index);

private slots:
    void onAudioLoaderFinished();

private:
    int lowerBound(Audio *audio);
    int insertBinary(Audio *audio);
    int append(Audio *audio);

    Files uniqueFiles(const Files &paths);

    bool m_sorted;
    Audios m_audios;
    AudioLoaderController m_audioLoader;
    CoverLoaderController m_coverLoader;
    Files m_paths;

    static Library *_instance;
};

#endif // LIBRARY_HPP
