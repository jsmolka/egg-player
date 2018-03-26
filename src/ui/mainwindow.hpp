#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>

#include "src/core/library.hpp"
#include "src/ui/musicwindow.hpp"
#include "src/ui/playerwindow.hpp"
#include "src/ui/layouts/borderlayout.hpp"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void play();
    void start(const QModelIndex &index);
    void next();
    void back();
    void loop();

private:
    void setupUi();
    void updateTrackInfo(int index);

    void createMusicWindow();
    void createPlayerWindow();

    Library m_library;
    MusicWindow *pm_musicWindow;
    PlayerWindow *pm_playerWindow;
};

#endif // MAINWINDOW_HPP
