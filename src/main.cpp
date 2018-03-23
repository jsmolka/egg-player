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

    BorderLayout *layout = new BorderLayout;
    layout->addWidget(new QLabel("lul"), BorderLayout::Center);
    layout->addWidget(new QLabel("lul"), BorderLayout::North);
    layout->addWidget(new QLabel("lul"), BorderLayout::West);
    layout->addWidget(new QLabel("lul"), BorderLayout::East);
    layout->addWidget(new QLabel("lul"), BorderLayout::South);
    window.setLayout(layout);

    window.show();
    return app.exec();
}
