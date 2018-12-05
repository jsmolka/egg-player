#include "eggwidget.hpp"

#include <QDir>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfo>

#include "core/config.hpp"
#include "core/constants.hpp"
#include "core/library.hpp"
#include "core/player.hpp"
#include "core/utils.hpp"
#include "threading/threadpool.hpp"
#include "widgets/borderlayout.hpp"

EggWidget::EggWidget(QWidget *parent)
    : MainWindow(parent)
    , m_bar(this)
    , m_library(this)
    , m_shortcuts(this)
{
    init();

    connect(&m_library, &AudiosWidget::doubleClicked, this, &EggWidget::onLibraryDoubleClicked);

    m_library.setAudios(&egg_library.audios());

    egg_library.init(cfg_library.paths());
}

void EggWidget::closeEvent(QCloseEvent *event)
{
    egg_pool.interruptThreads();

    cfg_player.setVolume(egg_player.volume());
    cfg_player.setLoop(egg_player.playlist().isLoop());
    cfg_player.setShuffle(egg_player.playlist().isShuffle());

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

    FileSystem &fileSystem = egg_library.fileSystem();

    QStrings files;
    for (const QUrl &url : event->mimeData()->urls())
    {
        const QString file = url.toLocalFile();
        const QFileInfo info(file);

        if (info.isFile())
        {
            if (fileSystem.containsFile(file) && !fileSystem.isIgnored(file))
                continue;

            fileSystem.addFile(file);
            files << file;
        }
        else if (info.isDir())
        {
            if (fileSystem.containsDir(file))
                continue;

            fileSystem.addPath(file);
            files << fileSystem.globDirFiles(file, FileSystem::GlobPolicy::Recursive);
        }
    }
    egg_library.load(files);
}

void EggWidget::onLibraryDoubleClicked(const QModelIndex &index) const
{
    audios::CurrentState *state = egg_library.audios().currentState();

    egg_player.playlist().loadFromState(state, index.row());
    egg_player.play();
}

void EggWidget::init()
{
    setAcceptDrops(true);
    setMinimumHeight(cfg_app.minimalSize().height());
    setMinimumWidth(cfg_app.minimalSize().width());

    initUi();
    initStyle();
}

void EggWidget::initUi()
{
    BorderLayout *layout = new BorderLayout(0, this);
    layout->addWidget(&m_library, BorderLayout::Center);
    layout->addWidget(&m_bar, BorderLayout::South);
    setLayout(layout);
}

void EggWidget::initStyle()
{
    setStyleSheet(FileUtil::read(constants::css::Egg));
}
