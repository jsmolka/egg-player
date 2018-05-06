#ifndef EGGPLAYER_HPP
#define EGGPLAYER_HPP

#include <QSettings>
#include <QWidget>

#include "borderlayout.hpp"
#include "cachebuilder.hpp"
#include "library.hpp"
#include "librarybuilder.hpp"
#include "musiclibrary.hpp"
#include "musicbar.hpp"

class EggPlayer : public QWidget
{
    Q_OBJECT

public:
    EggPlayer(QWidget *parent = nullptr);
    ~EggPlayer();

    void showSavedPosition();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void onMusicLibraryDoubleClicked(const QModelIndex &index);
    void onLibraryLoaded();

private:
    void setupUi();
    void savePosition();

    Library *pm_library;
    MusicLibrary *pm_musicLibrary;
    MusicBar *pm_musicBar;
};

#endif // EGGPLAYER_HPP
