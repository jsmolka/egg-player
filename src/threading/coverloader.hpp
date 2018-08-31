#ifndef COVERLOADER_HPP
#define COVERLOADER_HPP

#include "audio.hpp"
#include "controller.hpp"

class CoverLoader : public Controller
{
    Q_OBJECT

public:
    explicit CoverLoader(QObject *parent = nullptr);
    explicit CoverLoader(Audio::vector audios, QObject *parent = nullptr);

    void setAudios(const Audio::vector &audios);
    Audio::vector audios() const;

public slots:
    void start() override;

private:
    Audio::vector m_audios;
};

#endif // COVERLOADER_HPP
