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
    return pm_nextButton;
}

IconButton * PlayerWindow::backButton()
{
    return pm_backButton;
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
    setStyleSheet(CSS_PLAYERWINDOW);

    QGridLayout *layout = new QGridLayout;
    layout->setSpacing(15);

    pm_coverLabel = new QLabel(this);
    pm_coverLabel->setPixmap(defaultCover());
    pm_coverLabel->setFixedSize(QSize(50, 50));
    layout->addWidget(pm_coverLabel, 0, 0);

    pm_trackLabel = new QLabel(this);
    pm_trackLabel->setStyleSheet("color: white");
    pm_trackLabel->setFixedSize(QSize(240, 50));
    layout->addWidget(pm_trackLabel, 0, 1);

    QLabel *label = new QLabel(this);
    layout->addWidget(label, 0, 2);

    QList<IconButton *> buttons;

    pm_backButton = new IconButton(this);
    pm_backButton->init(QIcon(ICO_REWIND), size);
    buttons << pm_backButton;

    pm_playButton = new IconButton(this);
    pm_playButton->init(QIcon(ICO_PLAY), QIcon(ICO_PAUSE), size);
    buttons << pm_playButton;

    pm_nextButton = new IconButton(this);
    pm_nextButton->init(QIcon(ICO_FORWARD), size);
    buttons << pm_nextButton;

    pm_shuffleButton = new IconButton(this);
    pm_shuffleButton->setLockable(true);
    pm_shuffleButton->init(QIcon(ICO_SHUFFLE), size);
    buttons << pm_shuffleButton;

    pm_replayButton = new IconButton(this);
    pm_replayButton->setLockable(true);
    pm_replayButton->init(QIcon(ICO_REPLAY), size);
    buttons << pm_replayButton;

    pm_volumeButton = new IconButton(this);
    pm_volumeButton->init(QIcon(ICO_VOLUME), QIcon(ICO_MUTE), size);
    buttons << pm_volumeButton;

    int column = 3;
    for (IconButton *button : buttons)
    {
        button->setStyleSheet(CSS_ICONBUTTON);
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
