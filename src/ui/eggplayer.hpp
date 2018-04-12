#ifndef EGGPLAYER_HPP
#define EGGPLAYER_HPP

#include <QSettings>
#include <QWidget>

#include "borderlayout.hpp"
#include "config.hpp"
#include "library.hpp"
#include "musiclibrary.hpp"
#include "musicbar.hpp"

class EggPlayer : public QWidget
{
    Q_OBJECT

public:
    EggPlayer();
    ~EggPlayer();

    void showSavedPosition();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void onLibraryDoubleClicked(const QModelIndex &index);

private:
    void setupUi();
    void savePosition();

    Library *pm_library;
    MusicLibrary *pm_musicLibrary;
    MusicBar *pm_musicBar;
};

#endif // EGGPLAYER_HPP
