#include "mainwindow.hpp"

MainWindow::MainWindow() : QWidget()
{
    m_library = Library("C:/Users/Julian/Music/Tiny Moving Parts");

    setupUi();
}

void MainWindow::setupUi()
{
    createSongList();

    QLabel *south = new QLabel;
    south->setText("south");
    south->setFixedHeight(75);
    south->setStyleSheet("QLabel {background-color: blue;}");

    QLabel *west = new QLabel;
    west->setText("west");
    west->setFixedWidth(350);
    west->setStyleSheet("QLabel {background-color: orange;}");

    BorderLayout *layout = new BorderLayout(0);
    layout->addWidget(m_songList, BorderLayout::Center);
    layout->addWidget(west, BorderLayout::West);
    layout->addWidget(south, BorderLayout::South);
    setLayout(layout);
}

void MainWindow::createSongList()
{
    m_songList = new SongList(&m_library);
}
