#include "eggwidget.hpp"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfo>

#include "core/library.hpp"
#include "core/logger.hpp"
#include "core/player.hpp"
#include "core/utils.hpp"
#include "core/config/config.hpp"
#include "threading/core/threadpool.hpp"
#include "widgets/parts/borderlayout.hpp"

EggWidget::EggWidget(QWidget *parent)
    : MainWindow(parent)
    , m_bar(this)
    , m_library(this)
{
    init();

    connect(&m_library, &AudiosWidget::doubleClicked, this, &EggWidget::onLibraryDoubleClicked);

    m_library.setAudios(&egg_library.audios());

    egg_library.initialLoad(cfg_library.paths());
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

    const QStrings files = processDropEvent(event->mimeData());
    egg_library.loadFiles(files);
}

void EggWidget::onLibraryDoubleClicked(const QModelIndex &index)
{
    Audios *state = egg_library.audios().currentState();

    egg_player.createPlaylist(state, index.row());
    egg_player.play();
}

QStrings EggWidget::processDropEvent(const QMimeData *data)
{
    QStrings files;
    for (const QUrl &url : data->urls())
    {
        const QString file = url.toLocalFile();
        const QFileInfo info(file);

        if (info.isFile())
            processDropEventFile(files, file);
        else if (info.isDir())
            processDropEventDir(files, file);
    }
    return files;
}

void EggWidget::processDropEventFile(QStrings &files, const QString &file)
{
    if (file.endsWith(".mp3", Qt::CaseInsensitive))
        files << file;
}

void EggWidget::processDropEventDir(QStrings &files, const QString &path)
{
    FileSystem &fileSystem = egg_library.fileSystem();
    fileSystem.addPath(path);

    Directory *dir = fileSystem.dirs().value(path, nullptr);
    if (!dir)
    {
        EGG_LOG("Failed retrieving directory %1", path);
        return;
    }
    files << dir->globAudios();
}

void EggWidget::init()
{
    setAcceptDrops(true);
    setMinimumHeight(cfgApp.minimalSize().height());
    setMinimumWidth(cfgApp.minimalSize().width());

    initUi();
    initStyle();
}

void EggWidget::initUi()
{
    QLabel *label = new QLabel(this);
    label->setFixedWidth(250);
    label->setStyleSheet("QLabel {background-color: #666666;}");

    BorderLayout *layout = new BorderLayout(0, this);
    layout->addWidget(&m_library, BorderLayout::Center);
    layout->addWidget(label, BorderLayout::West);
    layout->addWidget(&m_bar, BorderLayout::South);
    setLayout(layout);
}

void EggWidget::initStyle()
{
    setStyleSheet(FileUtil::read(constants::css::egg));
}
