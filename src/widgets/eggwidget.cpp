#include "eggwidget.hpp"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfo>

#include "core/library.hpp"
#include "core/player.hpp"
#include "core/filesystem/directory.hpp"
#include "threading/core/threadpool.hpp"
#include "widgets/parts/borderlayout.hpp"

EggWidget::EggWidget(QWidget *parent)
    : MainWindow(parent)
    , m_bar(new BarWidget(this))
    , m_library(new LibraryWidget(this))
{
    setup();

    connect(m_library, &AudiosWidget::doubleClicked, this, &EggWidget::onLibraryDoubleClicked);

    m_library->setAudios(egg_library->audios());
    egg_library->initialLoad(cfg_library.paths());
}

void EggWidget::closeEvent(QCloseEvent *event)
{
    egg_pool.interruptThreads();

    MainWindow::closeEvent(event);
}

void EggWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void EggWidget::dropEvent(QDropEvent *event)
{
    if (!event->mimeData()->hasUrls())
        return;

    const QStrings files = processDropEvent(event->mimeData());
    egg_library->loadFiles(files);
}

void EggWidget::onLibraryDoubleClicked(const QModelIndex &index)
{
    egg_player->createPlaylist(egg_library->audios()->currentState(), index.row());
    egg_player->play();
}

QStrings EggWidget::processDropEvent(const QMimeData *data)
{
    QStrings files;
    for (const QUrl &url : data->urls())
    {
        const QString path = url.toLocalFile();
        if (QFileInfo(path).isDir())
        {
            egg_library->fileSystem().addPath(path);
            Directory *dir = egg_library->fileSystem().dirs().value(path);
            files << dir->globAudios();
        }
        else
        {
            if (path.endsWith(QLatin1String(".mp3"), Qt::CaseInsensitive))
            {
                egg_library->fileSystem().watcher().addPath(path);
                files << path;
            }
        }
    }
    return files;
}

void EggWidget::setup()
{
    setAcceptDrops(true);
    setMinimumHeight(cfgApp.minimalSize().height());
    setMinimumWidth(cfgApp.minimalSize().width());

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
    layout->addWidget(m_library, BorderLayout::Center);
    layout->addWidget(label, BorderLayout::West);
    layout->addWidget(m_bar, BorderLayout::South);
    setLayout(layout);
}
