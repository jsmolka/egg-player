#ifndef COVERLOADER_HPP
#define COVERLOADER_HPP

#include "core/audio.hpp"
#include "core/globals.hpp"
#include "threading/core/controller.hpp"

class CoverLoader : public Controller
{
    Q_OBJECT

public:
    explicit CoverLoader(QObject *parent = nullptr);
    explicit CoverLoader(Audio::vector audios, QObject *parent = nullptr);

    EGG_CPROP(Audio::vector, audios, setAudios, audios)

public slots:
    void start() override;
};

#endif // COVERLOADER_HPP
