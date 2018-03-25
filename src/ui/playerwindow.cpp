#include "playerwindow.hpp"

PlayerWindow::PlayerWindow() : QWidget()
{
    pm_player = new Player;

    setupUi();
}

Player * PlayerWindow::player()
{
    return pm_player;
}

QLabel * PlayerWindow::coverLabel()
{
    return pm_coverLabel;
}

QLabel * PlayerWindow::trackLabel()
{
    return pm_trackLabel;
}

IconButton * PlayerWindow::playButton()
{
    return pm_playButton;
}

IconButton * PlayerWindow::nextButton()
{
    return pm_backButton;
}

IconButton * PlayerWindow::backButton()
{
    return pm_nextButton;
}

IconButton * PlayerWindow::shuffleButton()
{
    return pm_shuffleButton;
}

IconButton * PlayerWindow::replayButton()
{
    return pm_replayButton;
}

IconButton * PlayerWindow::volumeButton()
{
    return pm_volumeButton;
}

void PlayerWindow::paintEvent(QPaintEvent *event)
{
  QStyleOption option;
  option.initFrom(this);
  QPainter painter(this);
  style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void PlayerWindow::setupUi()
{
    QSize size(40, 40);
    setFixedHeight(67);
    setStyleSheet(FileUtil::read(CSS_PLAYERWINDOW));

    QGridLayout *layout = new QGridLayout;

    pm_coverLabel = new QLabel("lul", this);
    pm_coverLabel->setPixmap(defaultCover());
    //pm_cover->setFixedSize(QSize(50, 50));
    layout->addWidget(pm_coverLabel, 0, 0);

    QList<IconButton *> buttons;

    pm_backButton = new IconButton(false, this);
    pm_backButton->init(ICO_REWIND, size);
    buttons << pm_backButton;

    pm_playButton = new IconButton(true, this);
    pm_playButton->init(ICO_PLAY, ICO_PAUSE, size);
    buttons << pm_playButton;

    pm_nextButton = new IconButton(false, this);
    pm_nextButton->init(ICO_FORWARD, size);
    buttons << pm_nextButton;

    pm_shuffleButton = new IconButton(false, this);
    pm_shuffleButton->setLockable(true);
    pm_shuffleButton->init(ICO_SHUFFLE, size);
    buttons << pm_shuffleButton;

    pm_replayButton = new IconButton(false, this);
    pm_replayButton->setLockable(true);
    pm_replayButton->init(ICO_REPLAY, size);
    buttons << pm_replayButton;

    pm_volumeButton = new IconButton(false, this);
    pm_volumeButton->init(ICO_VOLUME, ICO_MUTE, size);
    buttons << pm_volumeButton;

    QString css = FileUtil::read(CSS_ICONBUTTON);
    int column = 1;
    for (IconButton *button : buttons)
    {
        button->setStyleSheet(css);
        layout->addWidget(button, 0, column);
        column++;
    }
    setLayout(layout);
}

QPixmap PlayerWindow::defaultCover()
{
    QImage image(IMG_DEFAULT_COVER);
    image = image.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    return QPixmap::fromImage(image);
}
