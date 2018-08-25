#ifndef COVERLOADERCONTROLLER_HPP
#define COVERLOADERCONTROLLER_HPP

#include "abstractcontroller.hpp"
#include "audio.hpp"

class CoverLoaderController : public AbstractController
{
    Q_OBJECT

public:
    explicit CoverLoaderController(QObject *parent = nullptr);
    explicit CoverLoaderController(Audio::vector audios, QObject *parent = nullptr);

    void setAudios(const Audio::vector &audios);
    Audio::vector audios() const;

public slots:
    void start() override;

private:
    Audio::vector m_audios;
};

#endif // COVERLOADERCONTROLLER_HPP
