#ifndef INITIALAUDIOLOADER_HPP
#define INITIALAUDIOLOADER_HPP

#include "core/audio.hpp"
#include "core/globals.hpp"
#include "threading/core/controller.hpp"

class InitialLoader : public Controller
{
    Q_OBJECT

public:
    explicit InitialLoader(QObject *parent = nullptr);
    explicit InitialLoader(const QStrings &files, QObject *parent = nullptr);

    void setFiles(const QStrings &files);
    QStrings files() const;

public slots:
    void start() override;

signals:
    void loaded(Audio *audio);

private:
    QStrings m_files;
};

#endif // INITIALAUDIOLOADER_HPP
