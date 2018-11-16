#ifndef AUDIOLOADER_HPP
#define AUDIOLOADER_HPP

#include "core/audio.hpp"
#include "core/macros.hpp"
#include "core/types.hpp"
#include "threading/controller.hpp"

class AudioLoader : public Controller
{
    Q_OBJECT

public:
    using Controller::Controller;

    EGG_CPROP(QStrings, files, setFiles, files)

public slots:
    void start() override;

signals:
    void loaded(Audio *audio);
};

#endif // AUDIOLOADER_HPP
