#ifndef EGGPLAYER_HPP
#define EGGPLAYER_HPP

#include <QWidget>

#include "src/core/cache.hpp"
#include "src/core/library.hpp"
#include "src/ui/musiclibrary.hpp"
#include "src/ui/musicbar.hpp"
#include "src/ui/layouts/borderlayout.hpp"

class EggPlayer : public QWidget
{
    Q_OBJECT

public:
    EggPlayer();

public slots:
    void play();
    void start(const QModelIndex &index);
    void next();
    void back();
    void loop();
    void change();
    void shuffle();

private:
    void setupUi();
    void updateTrackInfo();

    void createMusicLibrary();
    void createMusicBar();

    Cache m_cache;
    Library m_library;
    MusicLibrary *pm_musicLibrary;
    MusicBar *pm_musicBar;
};

#endif // EGGPLAYER_HPP