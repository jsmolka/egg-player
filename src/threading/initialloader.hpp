#ifndef INITIALAUDIOLOADER_HPP
#define INITIALAUDIOLOADER_HPP

#include "audio.hpp"
#include "controller.hpp"
#include "types.hpp"

class InitialLoader : public Controller
{
    Q_OBJECT

public:
    explicit InitialLoader(QObject *parent = nullptr);
    explicit InitialLoader(const Files &files, QObject *parent = nullptr);

    void setFiles(const Files &files);
    Files files() const;

public slots:
    void start() override;

signals:
    void loaded(Audio *audio);

private:
    Files m_files;
};

#endif // INITIALAUDIOLOADER_HPP
