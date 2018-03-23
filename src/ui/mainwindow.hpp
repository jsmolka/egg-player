#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>

#include "src/core/library.hpp"
#include "src/ui/songlist.hpp"
#include "src/ui/layouts/borderlayout.hpp"

class MainWindow : public QWidget
{
public:
    MainWindow();

private:
    void setupUi();

    void createSongList();

    Library m_library;
    SongList *pm_songList;
};

#endif // MAINWINDOW_HPP
