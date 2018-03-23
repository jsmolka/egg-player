#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>

#include "src/core/library.hpp"
#include "src/gui/songlist.hpp"
#include "src/gui/layouts/borderlayout.hpp"

class MainWindow : public QWidget
{
public:
    MainWindow();

private:
    void setupUi();

    void createSongList();

    Library m_library;
    SongList *m_songList;
};

#endif // MAINWINDOW_HPP
