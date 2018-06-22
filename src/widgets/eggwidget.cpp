#include "eggwidget.hpp"

EggWidget::EggWidget(QWidget *parent)
    : QWidget(parent)
    , m_libraryWidget(this)
    , m_barWidget(this)
{
    setup();
    setupUi();

    connect(eLibrary, SIGNAL(inserted(Audio *, int)), &m_libraryWidget, SLOT(insert(Audio *, int)));

    connect(&m_libraryWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onMusicLibraryDoubleClicked(QModelIndex)));

    eLibrary->load(cfgLibrary->paths());
}

EggWidget::~EggWidget()
{

}

void EggWidget::showSavedPosition()
{
    QSettings settings;
    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    move(settings.value("pos", pos()).toPoint());
    resize(settings.value("size", size()).toSize());

    if (settings.value("maximized", isMaximized()).toBool())
        showMaximized();
    else
        show();
}

void EggWidget::closeEvent(QCloseEvent *event)
{
    savePosition();
    QWidget::closeEvent(event);
}

void EggWidget::onMusicLibraryDoubleClicked(const QModelIndex &index)
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
    QLabel *west = new QLabel(this);
    west->setFixedWidth(315);
    west->setStyleSheet("QLabel {background-color: #666666;}");

    m_libraryWidget.addColumn(LibraryWidget::Title);
    m_libraryWidget.addColumn(LibraryWidget::Artist);
    m_libraryWidget.addColumn(LibraryWidget::Album);
    m_libraryWidget.addColumn(LibraryWidget::Year, Qt::AlignLeft, false);
    m_libraryWidget.addColumn(LibraryWidget::Genre);
    m_libraryWidget.addColumn(LibraryWidget::Length, Qt::AlignRight, false);

    BorderLayout *layout = new BorderLayout(0, this);
    layout->addWidget(&m_libraryWidget, BorderLayout::Center);
    layout->addWidget(west, BorderLayout::West);
    layout->addWidget(&m_barWidget, BorderLayout::South);
    setLayout(layout);
}

void EggWidget::savePosition()
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("maximized", isMaximized());
    if (!isMaximized())
    {
        settings.setValue("pos", pos());
        settings.setValue("size", size());
    }
}
