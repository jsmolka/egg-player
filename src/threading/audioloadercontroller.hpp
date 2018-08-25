#ifndef AUDIOLOADERCONTROLLER_HPP
#define AUDIOLOADERCONTROLLER_HPP

#include "abstractcontroller.hpp"
#include "audio.hpp"
#include "types.hpp"

class AudioLoaderController : public AbstractController
{
    Q_OBJECT

public:
    explicit AudioLoaderController(QObject *parent = nullptr);
    explicit AudioLoaderController(const Files &files, QObject *parent = nullptr);

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
