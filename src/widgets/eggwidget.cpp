#include "eggwidget.hpp"

EggWidget::EggWidget(QWidget *parent)
    : MainWindow(parent)
    , m_library(this)
    , m_bar(this)
{
    setup();
    setupUi();

    connect(eLibrary, &Library::inserted, &m_library, &LibraryWidget::insert);
    connect(&m_library, &LibraryWidget::doubleClicked, this, &EggWidget::onLibraryDoubleClicked);

    eLibrary->load(cfgLibrary->paths());
}

EggWidget::~EggWidget()
{

}

void EggWidget::closeEvent(QCloseEvent *event)
{
    AudioLoaderController *audioLoader = eLibrary->audioLoader();
    CoverLoaderController *coverLoader = eLibrary->coverLoader();

    audioLoader->stopWorkerThreads();
    coverLoader->stopWorkerThreads();

    QWidget::closeEvent(event);
}

void EggWidget::onLibraryDoubleClicked(const QModelIndex &index)
{
    ePlayer->loadPlaylist(eLibrary->audios(), index.row());
    ePlayer->play();
}

void EggWidget::setup()
{
    setStyleSheet(FileUtil::Css::egg());
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
    m_library.addColumn(LibraryWidget::Length, Qt::AlignRight, false);

    BorderLayout *layout = new BorderLayout(0, this);
    layout->addWidget(&m_library, BorderLayout::Center);
    layout->addWidget(label, BorderLayout::West);
    layout->addWidget(&m_bar, BorderLayout::South);
    setLayout(layout);
}
