#ifndef EGGPLAYER_HPP
#define EGGPLAYER_HPP

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
    ~EggPlayer();

private slots:
    void onLibraryDoubleClicked(const QModelIndex &index);
    void onPlayButtonPressed();
    void onLoopButtonLocked(bool locked);
    void onShuffleButtonLocked(bool locked);
    void onAudioChanged(Audio *audio);
    void onStateChanged(bool playing);

private:
    void setupUi();
    void updateTrackInfo(Audio *audio);

    void createMusicLibrary();
    void createMusicBar();

    Cache m_cache;
    Library m_library;
    MusicLibrary *pm_musicLibrary;
    MusicBar *pm_musicBar;
};

#endif // EGGPLAYER_HPP
