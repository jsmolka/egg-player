#ifndef EGGPLAYER_HPP
#define EGGPLAYER_HPP

#include "src/core/library.hpp"
#include "src/ui/musiclibrary.hpp"
#include "src/ui/musicbar.hpp"
#include "src/ui/layouts/borderlayout.hpp"

class EggPlayer : public QWidget
{
    Q_OBJECT

public:
    EggPlayer(QWidget *parent = 0);
    ~EggPlayer();

private slots:
    void onLibraryDoubleClicked(const QModelIndex &index);

private:
    void setupUi();

    void createMusicLibrary();
    void createMusicBar();

    Library m_library;
    MusicLibrary *pm_musicLibrary;
    MusicBar *pm_musicBar;
};

#endif // EGGPLAYER_HPP
