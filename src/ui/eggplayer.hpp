#ifndef EGGPLAYER_HPP
#define EGGPLAYER_HPP

#include <QWidget>

#include "borderlayout.hpp"
#include "library.hpp"
#include "musiclibrary.hpp"
#include "musicbar.hpp"

class EggPlayer : public QWidget
{
    Q_OBJECT

public:
    EggPlayer();
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
