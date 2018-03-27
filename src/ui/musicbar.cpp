#include "musicbar.hpp"

MusicBar::MusicBar() : QWidget()
{
    pm_player = new Player;

    setupUi();
}

Player * MusicBar::player()
{
    return pm_player;
}

QLabel * MusicBar::coverLabel()
{
    return pm_coverLabel;
}

QLabel * MusicBar::trackLabel()
{
    return pm_trackLabel;
}

IconButton * MusicBar::playButton()
{
    return pm_playButton;
}

IconButton * MusicBar::nextButton()
{
    return pm_nextButton;
}

IconButton * MusicBar::backButton()
{
    return pm_backButton;
}

IconButton * MusicBar::shuffleButton()
{
    return pm_shuffleButton;
}

IconButton * MusicBar::loopButton()
{
    return pm_loopButton;
}

IconButton * MusicBar::volumeButton()
{
    return pm_volumeButton;
}

void MusicBar::paintEvent(QPaintEvent *event)
{
  QStyleOption option;
  option.initFrom(this);
  QPainter painter(this);
  style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void MusicBar::setupUi()
{
    setFixedHeight(67);
    setStyleSheet(CSS_MUSICBAR);

    QGridLayout *layout = new QGridLayout;
    layout->setSpacing(15);

    pm_coverLabel = new QLabel(this);
    pm_coverLabel->setPixmap(defaultCover());
    pm_coverLabel->setFixedSize(QSize(50, 50));
    layout->addWidget(pm_coverLabel, 0, 0);

    pm_trackLabel = new QLabel(this);
    pm_trackLabel->setStyleSheet(CSS_TRACKLABEL);
    pm_trackLabel->setFixedSize(QSize(240, 50));
    layout->addWidget(pm_trackLabel, 0, 1);

    QLabel *label = new QLabel(this);
    layout->addWidget(label, 0, 2);

    QList<IconButton *> buttons;
    QSize size(40, 40);

    pm_backButton = new IconButton(this);
    pm_backButton->init(QIcon(ICO_BACK), size);
    buttons << pm_backButton;

    pm_playButton = new IconButton(this);
    pm_playButton->init(QIcon(ICO_PLAY), QIcon(ICO_PAUSE), size);
    buttons << pm_playButton;

    pm_nextButton = new IconButton(this);
    pm_nextButton->init(QIcon(ICO_NEXT), size);
    buttons << pm_nextButton;

    pm_shuffleButton = new IconButton(this);
    pm_shuffleButton->setLockable(true);
    pm_shuffleButton->init(QIcon(ICO_SHUFFLE), size);
    buttons << pm_shuffleButton;

    pm_loopButton = new IconButton(this);
    pm_loopButton->setLockable(true);
    pm_loopButton->init(QIcon(ICO_REPLAY), size);
    buttons << pm_loopButton;

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

QPixmap MusicBar::defaultCover()
{
    QPixmap image(IMG_DEFAULT_COVER);
    return image.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
