#include "eggwidget.hpp"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfo>
#include <QMimeData>

#include "borderlayout.hpp"
#include "config.hpp"
#include "constants.hpp"
#include "directory.hpp"
#include "fileutil.hpp"
#include "library.hpp"
#include "player.hpp"
#include "threadpool.hpp"

EggWidget::EggWidget(QWidget *parent)
    : MainWindow(parent)
    , m_bar(this)
    , m_library(this)
{
    setup();
    setupUi();

    connect(&m_library, &LibraryWidget::doubleClicked, this, &EggWidget::onLibraryDoubleClicked);

    m_library.setAudios(eLibrary->audios());
    eLibrary->initialLoad(cfgLibrary.paths());
}

void EggWidget::closeEvent(QCloseEvent *event)
{
    ThreadPool::instance()->interruptThreads();

    MainWindow::closeEvent(event);
}

void EggWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void EggWidget::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    Files files;
    if (mimeData->hasUrls())
    {
        for (const QUrl &url : mimeData->urls())
        {
            const Path path = url.toLocalFile();
            if (QFileInfo(path).isDir())
            {
                Directory dir(path);
                dir.parse();
                files << dir.globAudios();
            }
            else
            {
                files << url.toLocalFile();
            }
        }
    }
    eLibrary->tryLoadFiles(files);
}

void EggWidget::onLibraryDoubleClicked(const QModelIndex &index)
{
    ePlayer->createPlaylist(eLibrary->audios(), index.row());
    ePlayer->play();
}

void EggWidget::setup()
{
    setAcceptDrops(true);

    setupCss();
}

void EggWidget::setupCss()
{
    setStyleSheet(FileUtil::read(CSS_EGG));
}

void EggWidget::setupUi()
{
    QLabel *label = new QLabel(this);
    label->setFixedWidth(315);
    label->setStyleSheet("QLabel {background-color: #666666;}");

    m_library.addColumn(LibraryWidget::Title);
    m_library.addColumn(LibraryWidget::Artist);
    m_library.addColumn(LibraryWidget::Album);
    m_library.addColumn(LibraryWidget::Year, Qt::AlignLeft, false);
    m_library.addColumn(LibraryWidget::Genre);
    m_library.addColumn(LibraryWidget::Duration, Qt::AlignRight, false);

    BorderLayout *layout = new BorderLayout(0, this);
    layout->addWidget(&m_library, BorderLayout::Center);
    layout->addWidget(label, BorderLayout::West);
    layout->addWidget(&m_bar, BorderLayout::South);
    setLayout(layout);
}
