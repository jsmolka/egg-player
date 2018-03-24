#include "mainwindow.hpp"

MainWindow::MainWindow() : QWidget()
{
    m_library = Library("C:/Users/Julian/Music/Linkin Park");

    setupUi();
}

void MainWindow::setupUi()
{
    createSongList();

    QLabel *south = new QLabel;
    south->setFixedHeight(65);
    south->setStyleSheet("QLabel {background-color: #006666;}");

    QLabel *west = new QLabel;
    west->setFixedWidth(315);
    west->setStyleSheet("QLabel {background-color: #666666;}");

    BorderLayout *layout = new BorderLayout(0);
    layout->addWidget(pm_songList, BorderLayout::Center);
    layout->addWidget(west, BorderLayout::West);
    layout->addWidget(south, BorderLayout::South);
    setLayout(layout);
}

void MainWindow::createSongList()
{
    pm_songList = new SongList(&m_library);
}
