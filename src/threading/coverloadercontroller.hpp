#ifndef COVERLOADERCONTROLLER_HPP
#define COVERLOADERCONTROLLER_HPP

#include "abstractcontroller.hpp"
#include "audio.hpp"
#include "audios.hpp"
#include "cache.hpp"
#include "coverloaderworker.hpp"

class CoverLoaderController : public AbstractController
{
    Q_OBJECT

public:
    CoverLoaderController(QObject *parent = nullptr);
    CoverLoaderController(AudioVector audios, QObject *parent = nullptr);
    ~CoverLoaderController();

    void setAudios(const AudioVector &audios);
    AudioVector audios() const;

public slots:
    void start() override;

private:
    AudioVector m_audios;
};

#endif // COVERLOADERCONTROLLER_HPP
