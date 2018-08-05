#ifndef COVERLOADERCONTROLLER_HPP
#define COVERLOADERCONTROLLER_HPP

#include "abstractcontroller.hpp"
#include "audio.hpp"
#include "cache.hpp"
#include "coverloaderworker.hpp"

class CoverLoaderController : public AbstractController
{
    Q_OBJECT

public:
    CoverLoaderController(QObject *parent = nullptr);
    CoverLoaderController(Audios audios, QObject *parent = nullptr);
    ~CoverLoaderController();

    void setAudios(const Audios &audios);
    Audios audios() const;

public slots:
    void start() override;

private:
    Audios m_audios;
};

#endif // COVERLOADERCONTROLLER_HPP