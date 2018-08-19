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
    explicit AudioLoaderController(const Paths &paths, QObject *parent = nullptr);
    ~AudioLoaderController();

    void setPaths(const Paths &paths);
    Paths paths() const;

public slots:
    void start() override;

signals:
    void loaded(Audio *audio);

private:
    Paths m_paths;
};

#endif // AUDIOLOADERCONTROLLER_HPP
