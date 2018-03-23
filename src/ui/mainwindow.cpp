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
    south->setText("south");
    south->setFixedHeight(75);
    south->setStyleSheet("QLabel {background-color: #006666;}");

    QLabel *west = new QLabel;
    west->setText("west");
    west->setFixedWidth(350);
    west->setStyleSheet("QLabel {background-color: #666666;}");

    BorderLayout *layout = new BorderLayout(1);
    layout->addWidget(pm_songList, BorderLayout::Center);
    layout->addWidget(west, BorderLayout::West);
    layout->addWidget(south, BorderLayout::South);
    setLayout(layout);
}

void MainWindow::createSongList()
{
    pm_songList = new SongList(&m_library);
}
