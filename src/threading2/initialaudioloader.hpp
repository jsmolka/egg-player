#ifndef INITIALAUDIOLOADER_HPP
#define INITIALAUDIOLOADER_HPP

#include "audio.hpp"
#include "controller.hpp"
#include "types.hpp"

class InitialAudioLoader : public Controller
{
    Q_OBJECT

public:
    explicit InitialAudioLoader(QObject *parent = nullptr);
    explicit InitialAudioLoader(const Files &files, QObject *parent = nullptr);

    void setFiles(const Files &files);
    Files files() const;

public slots:
    void start();

signals:
    void loaded(Audio *audio);

private:
    Files m_files;
};

#endif // INITIALAUDIOLOADER_HPP
