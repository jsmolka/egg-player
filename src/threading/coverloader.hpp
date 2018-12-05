#ifndef COVERLOADER_HPP
#define COVERLOADER_HPP

#include <QVector>

#include "core/audio.hpp"
#include "core/macros.hpp"
#include "threading/controller.hpp"

class CoverLoader : public Controller
{
    Q_OBJECT

public:
    using Controller::Controller;

    EGG_C_PROP(QVector<Audio>, audios, setAudios, audios)

public slots:
    void start() override;
};

#endif // COVERLOADER_HPP
