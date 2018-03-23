#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QListWidget>

#include "src/gui/layouts/borderlayout.hpp"
#include "src/core/audio.hpp"
#include "src/core/audiolist.hpp"
#include "src/core/library.hpp"
#include "src/core/player.hpp"
#include "src/utils/fileutil.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(500, 500);

    QLabel *center = new QLabel;
    center->setText("center");
    center->setStyleSheet("QLabel {background-color: green;}");

    QLabel *north = new QLabel;
    north->setText("north");
    north->setFixedHeight(50);
    north->setStyleSheet("QLabel {background-color: red;}");

    QLabel *east = new QLabel;
    east->setText("east");
    east->setFixedWidth(50);
    east->setStyleSheet("QLabel {background-color: cyan;}");

    QLabel *south = new QLabel;
    south->setText("south");
    south->setFixedHeight(50);
    south->setStyleSheet("QLabel {background-color: blue;}");

    QLabel *west = new QLabel;
    west->setText("west");
    west->setFixedWidth(50);
    west->setStyleSheet("QLabel {background-color: orange;}");

    BorderLayout *layout = new BorderLayout;    
    layout->addWidget(center, BorderLayout::Center);
    layout->addWidget(north, BorderLayout::North);
    layout->addWidget(west, BorderLayout::West);
    layout->addWidget(east, BorderLayout::East);
    layout->addWidget(south, BorderLayout::South);
    window.setLayout(layout);

    window.show();
    return app.exec();
}
