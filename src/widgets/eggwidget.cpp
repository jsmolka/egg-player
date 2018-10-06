#include "eggwidget.hpp"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfo>

#include "borderlayout.hpp"
#include "config.hpp"
#include "constants.hpp"
#include "directory.hpp"
#include "library.hpp"
#include "player.hpp"
#include "threadpool.hpp"
#include "utils.hpp"

EggWidget::EggWidget(QWidget *parent)
    : MainWindow(parent)
    , m_bar(this)
    , m_library(this)
{
    setup();

    connect(&m_library, &AudiosWidget::doubleClicked, this, &EggWidget::onLibraryDoubleClicked);

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
    if (event->mimeData()->hasUrls())
        processDropEvent(event->mimeData());
}

void EggWidget::onLibraryDoubleClicked(const QModelIndex &index)
{
    ePlayer->createPlaylist(eLibrary->audios()->currentState(), index.row());
    ePlayer->play();
}

void EggWidget::processDropEvent(const QMimeData *data)
{
    Files files;
    for (const QUrl &url : data->urls())
    {
        const Path path = url.toLocalFile();
        if (QFileInfo(path).isDir())
        {
            eLibrary->fileSystem().addPath(path);
            files << eLibrary->fileSystem().dirs().value(path)->globAudios();
        }
        else
        {
            if (path.endsWith(QLatin1String(".mp3"), Qt::CaseInsensitive))
            {
                eLibrary->fileSystem().watcher().addPath(path);
                files << path;
            }
        }
    }
    eLibrary->loadFiles(files);
}

void EggWidget::setup()
{
    setAcceptDrops(true);
    setMinimumHeight(cfgApp.minimalHeight());
    setMinimumWidth(cfgApp.minimalWidth());

    setupCss();
    setupUi();
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

    BorderLayout *layout = new BorderLayout(0, this);
    layout->addWidget(&m_library, BorderLayout::Center);
    layout->addWidget(label, BorderLayout::West);
    layout->addWidget(&m_bar, BorderLayout::South);
    setLayout(layout);
}
