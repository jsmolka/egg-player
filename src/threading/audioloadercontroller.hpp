#ifndef AUDIOLOADERCONTROLLER_HPP
#define AUDIOLOADERCONTROLLER_HPP

#include "abstractcontroller.hpp"
#include "audioloaderworker.hpp"
#include "audio.hpp"
#include "types.hpp"
#include "util.hpp"

class AudioLoaderController : public AbstractController
{
    Q_OBJECT

public:
    AudioLoaderController(QObject *parent = nullptr);
    AudioLoaderController(const Files &files, QObject *parent = nullptr);
    ~AudioLoaderController();

    void setFiles(const Files &files);
    Files files() const;

public slots:
    void start() override;

signals:
    void loaded(Audio *audio);

private:
    Files m_files;
};

#endif // AUDIOLOADERCONTROLLER_HPP
