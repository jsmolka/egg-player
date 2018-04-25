#include "musicbar.hpp"

/*
 * Constructor.
 *
 * :param parent: parent pointer
 */
MusicBar::MusicBar(QWidget *parent) : QWidget(parent)
{
    pm_player = new Player(this);
    pm_player->setVolume(Config::PVolume());

    setupUi();

    connect(pm_nextButton, SIGNAL(pressed()), pm_player, SLOT(next()));
    connect(pm_backButton, SIGNAL(pressed()), pm_player, SLOT(back()));
    connect(pm_shuffleButton, SIGNAL(locked(bool)), this, SLOT(onShuffleButtonLocked(bool)));
    connect(pm_loopButton, SIGNAL(locked(bool)), this, SLOT(onLoopButtonLocked(bool)));
    connect(pm_playButton, SIGNAL(pressed()), this, SLOT(onPlayButtonPressed()));

    connect(pm_lengthSlider, SIGNAL(sliderMoved(int)), this, SLOT(onLengthSliderMoved(int)));
    connect(pm_lengthSlider, SIGNAL(positionChanged(int)), this, SLOT(onLengthSliderPositionChanged(int)));

    connect(pm_player, SIGNAL(audioChanged(Audio *)), this, SLOT(onPlayerAudioChanged(Audio *)));
    connect(pm_player, SIGNAL(stateChanged(Player::State)), this, SLOT(onPlayerStateChanged(Player::State)));
    connect(pm_player, SIGNAL(positionChanged(int)), this, SLOT(onPlayerPositionChanged(int)));
}

/*
 * Destructor.
 */
MusicBar::~MusicBar()
{

}

/*
 * Getter for player property.
 *
 * :return: player pointer
 */
Player * MusicBar::player()
{
    return pm_player;
}

/*
 * Getter for cover label.
 *
 * :return: cover label pointer
 */
QLabel * MusicBar::coverLabel()
{
    return pm_coverLabel;
}

/*
 * Getter for track label property.
 *
 * :return: track label pointer
 */
QLabel * MusicBar::trackLabel()
{
    return pm_trackLabel;
}

/*
 * Getter for time label property.
 *
 * :return: time label pointer
 */
QLabel * MusicBar::currentTimeLabel()
{
    return pm_currentTimeLabel;
}

/*
 * Getter for time label property.
 *
 * :return: time label pointer
 */
QLabel * MusicBar::totalTimeLabel()
{
    return pm_totalTimeLabel;
}

/*
 * Getter for length slider property.
 *
 * :return: length slider pointer
 */
LengthSlider * MusicBar::lengthSlider()
{
    return pm_lengthSlider;
}

/*
 * Getter for play button property.
 *
 * :return: play button pointer
 */
IconButton * MusicBar::playButton()
{
    return pm_playButton;
}

/*
 * Getter for next button property.
 *
 * :return: next button pointer
 */
IconButton * MusicBar::nextButton()
{
    return pm_nextButton;
}

/*
 * Getter for back button property.
 *
 * :return: back button pointer
 */
IconButton * MusicBar::backButton()
{
    return pm_backButton;
}

/*
 * Getter for shuffle button property.
 *
 * :return: shuffle button pointer
 */
IconButton * MusicBar::shuffleButton()
{
    return pm_shuffleButton;
}

/*
 * Getter for loop button property.
 *
 * :return: loop button pointer
 */
IconButton * MusicBar::loopButton()
{
    return pm_loopButton;
}

/*
 * Getter for volume button property.
 *
 * :return: volume button pointer
 */
IconButton * MusicBar::volumeButton()
{
    return pm_volumeButton;
}

/*
 * Paint event for custom css.
 */
void MusicBar::paintEvent(QPaintEvent *)
{
    QStyleOption option;
    option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

/*
 * Slot for play button pressed. Starts or
 * pauses player.
 */
void MusicBar::onPlayButtonPressed()
{
    if (pm_player->index() != -1)
    {
        if (pm_playButton->selectedIcon() == 0)
            pm_player->play();
        else
            pm_player->pause();
    }
}

/*
 * Slot for audio changed. Sets up cover,
 * track label, time labels and length slider.
 *
 * :param audio: audio pointer
 */
void MusicBar::onPlayerAudioChanged(Audio *audio)
{
    QPixmap cover = Cache().cover(audio->path(), Config::BCoverSize());

    pm_coverLabel->setPixmap(cover);
    pm_trackLabel->setText(QString("%1\n%2").arg(audio->title(), audio->artist()));

    pm_currentTimeLabel->setText(Utils::timeString(0));
    pm_totalTimeLabel->setText(Utils::timeString(audio->length()));

    pm_lengthSlider->setRange(0, audio->length());
    pm_lengthSlider->setEnabled(true);

    setColor(Utils::backgroundColor(cover));
}

/*
 * Slot for player state changed. Sets corresponding
 * icon of play button.
 *
 * :param state: current player state
 */
void MusicBar::onPlayerStateChanged(Player::State state)
{
    pm_playButton->setSelectedIcon(state == Player::State::Playing ? 1 : 0);
}

/*
 * Slot for player position changed. Sets
 * slider position if it is not pressed.
 *
 * :param position: current position in seconds
 */
void MusicBar::onPlayerPositionChanged(int position)
{
    if (!pm_lengthSlider->isPressed())
    {
        pm_currentTimeLabel->setText(Utils::timeString(position));
        pm_lengthSlider->setValue(position);
    }
}

/*
 * Slot for player volume change. Saves
 * the saved volume in config for later use.
 *
 * :param volume: volume
 */
void MusicBar::onPlayerVolumeChanged(int volume)
{
    Config::PVolume(volume);
}

/*
 * Slot for shuffle button locked. Applies change
 * to player and saves it in the config.
 */
void MusicBar::onShuffleButtonLocked(bool locked)
{
    pm_player->setShuffled(locked);
    Config::PShuffle(locked);
}

/*
 * Slot for loop button locked. Applies change
 * to player and saves it in the config.
 */
void MusicBar::onLoopButtonLocked(bool locked)
{
    pm_player->setLoop(locked);
    Config::PLoop(locked);
}

/*
 * Slot for slider moved. Set the value
 * of current time label to reflect change.
 *
 * :param position: position in seconds
 */
void MusicBar::onLengthSliderMoved(int position)
{
    pm_currentTimeLabel->setText(Utils::timeString(position));
}

/*
 * Slot for slider position changed. Updates the current
 * time and player position accordingly.
 *
 * :param position: position in seconds
 */
void MusicBar::onLengthSliderPositionChanged(int position)
{
    pm_currentTimeLabel->setText(Utils::timeString(position));
    pm_player->setPosition(position);
}

/*
 * Sets up user interface.
 */
void MusicBar::setupUi()
{
    QGridLayout *layout = new QGridLayout(this);
    layout->setSpacing(Config::BSpacing());
    layout->setContentsMargins(layout->spacing(), 0, layout->spacing(), 0);

    setFixedHeight(Config::BHeight());
    setStyleSheet(Utils::read(CSS_MUSICBAR));
    setAutoFillBackground(true);
    setColor(Utils::backgroundColor(Utils::defaultCover(Config::BCoverSize())));
    setLayout(layout);

    pm_coverLabel = new QLabel(this);
    pm_coverLabel->setPixmap(Utils::defaultCover(Config::BCoverSize()));
    pm_coverLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    layout->addWidget(pm_coverLabel, 0, 0);

    pm_trackLabel = new QLabel(this);
    pm_trackLabel->setFixedWidth(Config::BTrackWidth());
    layout->addWidget(pm_trackLabel, 0, 1);

    pm_currentTimeLabel = new QLabel(this);
    pm_currentTimeLabel->setFixedWidth(Config::BTimeWidth());
    pm_currentTimeLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    pm_currentTimeLabel->setAlignment(Qt::AlignRight);
    layout->addWidget(pm_currentTimeLabel, 0, 2);

    pm_lengthSlider = new LengthSlider(this);
    pm_lengthSlider->setEnabled(false);
    pm_lengthSlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    layout->addWidget(pm_lengthSlider, 0, 3);

    pm_totalTimeLabel = new QLabel(this);
    pm_totalTimeLabel->setFixedWidth(Config::BTimeWidth());
    pm_totalTimeLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    layout->addWidget(pm_totalTimeLabel, 0, 4);

    QList<IconButton *> buttons;

    pm_backButton = new IconButton(this);
    pm_backButton->init({QIcon(ICO_BACK)}, Config::BIconSize());
    buttons << pm_backButton;

    pm_playButton = new IconButton(this);
    pm_playButton->init({QIcon(ICO_PLAY), QIcon(ICO_PAUSE)}, Config::BIconSize());
    buttons << pm_playButton;

    pm_nextButton = new IconButton(this);
    pm_nextButton->init({QIcon(ICO_NEXT)}, Config::BIconSize());
    buttons << pm_nextButton;

    pm_shuffleButton = new IconButton(this);
    pm_shuffleButton->init({QIcon(ICO_SHUFFLE)}, Config::BIconSize(), true);
    pm_shuffleButton->setLocked(Config::PShuffle());
    buttons << pm_shuffleButton;

    pm_loopButton = new IconButton(this);
    pm_loopButton->init({QIcon(ICO_REPLAY)}, Config::BIconSize(), true);
    pm_loopButton->setLocked(Config::PLoop());
    buttons << pm_loopButton;

    pm_volumeButton = new IconButton(this);
    pm_volumeButton->init({QIcon(ICO_VOLUME), QIcon(ICO_MUTE)}, Config::BIconSize());
    buttons << pm_volumeButton;

    int column = 5;
    for (IconButton *button : buttons)
    {
        layout->addWidget(button, 0, column);
        column++;
    }
}

/*
 * Sets music bar color.
 *
 * :param color: color
 */
void MusicBar::setColor(const QColor &color)
{
    QPalette palette;
    palette.setColor(QPalette::Background, color);
    setPalette(palette);
}
