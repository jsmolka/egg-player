#include "musicbar.hpp"

/*
 * Constructor.
 *
 * :param parent: parent pointer
 */
MusicBar::MusicBar(QWidget *parent) :
    QWidget(parent)
{
    pm_player = new Player(this);
    pm_player->setVolume(Config::Player::volume());
    pm_player->setShuffle(Config::Player::shuffle());
    pm_player->setLoop(Config::Player::loop());

    pm_scPlayPause = new Shortcut(Config::Shortcut::playPause(), false, this);
    pm_scNext = new Shortcut(Config::Shortcut::next(), false, this);
    pm_scPrevious = new Shortcut(Config::Shortcut::previous(), false, this);
    pm_scVolumeUp = new Shortcut(Config::Shortcut::volumeUp(), true, this);
    pm_scVolumeDown = new Shortcut(Config::Shortcut::volumeDown(), true, this);

    setupUi();

    connect(pm_nextButton, SIGNAL(pressed()), pm_player, SLOT(next()));
    connect(pm_previousButton, SIGNAL(pressed()), pm_player, SLOT(previous()));
    connect(pm_shuffleButton, SIGNAL(locked(bool)), this, SLOT(onShuffleButtonLocked(bool)));
    connect(pm_loopButton, SIGNAL(locked(bool)), this, SLOT(onLoopButtonLocked(bool)));
    connect(pm_playButton, SIGNAL(pressed()), this, SLOT(onPlayButtonPressed()));

    connect(pm_lengthSlider, SIGNAL(sliderMoved(int)), this, SLOT(onLengthSliderMoved(int)));
    connect(pm_lengthSlider, SIGNAL(positionChanged(int)), this, SLOT(onLengthSliderPositionChanged(int)));

    connect(pm_player, SIGNAL(audioChanged(Audio *)), this, SLOT(onPlayerAudioChanged(Audio *)));
    connect(pm_player, SIGNAL(stateChanged(Player::State)), this, SLOT(onPlayerStateChanged(Player::State)));
    connect(pm_player, SIGNAL(positionChanged(int)), this, SLOT(onPlayerPositionChanged(int)));
    connect(pm_player, SIGNAL(volumeChanged(int)), this, SLOT(onPlayerVolumeChanged(int)));

    connect(pm_scPlayPause, SIGNAL(pressed()), this, SLOT(onShortcutPlayPausePressed()));
    connect(pm_scNext, SIGNAL(pressed()), pm_player, SLOT(next()));
    connect(pm_scPrevious, SIGNAL(pressed()), pm_player, SLOT(previous()));
    connect(pm_scVolumeUp, SIGNAL(pressed()), this, SLOT(onShortcutVolumeUpPressed()));
    connect(pm_scVolumeDown, SIGNAL(pressed()), this, SLOT(onShortcutVolumeDownPressed()));
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
IconButton * MusicBar::previousButton()
{
    return pm_previousButton;
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
    if (pm_playButton->selectedIcon() == 0)
        pm_player->play();
    else
        pm_player->pause();
}

/*
 * Slot for audio changed. Sets up cover, track label,
 * time labels and length slider.
 *
 * :param audio: audio pointer
 */
void MusicBar::onPlayerAudioChanged(Audio *audio)
{
    QPixmap cover = Cache().cover(audio->path(), Config::Bar::coverSize());

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
 * Slot for player position changed. Sets slider
 * position if it is not pressed.
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
 * Slot for player volume change. Saves the changed
 * volume in config and adjusts the volume icon.
 *
 * :param volume: volume
 */
void MusicBar::onPlayerVolumeChanged(int volume)
{
    Config::Player::setVolume(volume);
    setVolumeIcon();
}

/*
 * Slot for shuffle button locked. Applies change
 * to player and saves it in the config.
 */
void MusicBar::onShuffleButtonLocked(bool locked)
{
    pm_player->setShuffle(locked);
    Config::Player::setShuffle(locked);
}

/*
 * Slot for loop button locked. Applies change
 * to player and saves it in the config.
 */
void MusicBar::onLoopButtonLocked(bool locked)
{
    pm_player->setLoop(locked);
    Config::Player::setShuffle(locked);
}

/*
 * Slot for slider moved. Set the value of the
 * current time label to reflect the change.
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
 * Slot for shortcut play pause pressed. Plays or pauses
 * the player depending on the current state.
 */
void MusicBar::onShortcutPlayPausePressed()
{
    pm_player->isPlaying() ? pm_player->pause() : pm_player->play();
}

/*
 * Slot for shotcut volume up pressed. Increases the
 * player volume.
 */
void MusicBar::onShortcutVolumeUpPressed()
{
    pm_player->setVolume(pm_player->volume() + 1);
}

/*
 * Slot for shortcut volume down pressed. Decreases
 * the player volume.
 */
void MusicBar::onShortcutVolumeDownPressed()
{
    pm_player->setVolume(pm_player->volume() - 1);
}

/*
 * Sets up user interface.
 */
void MusicBar::setupUi()
{
    QGridLayout *layout = new QGridLayout(this);
    layout->setSpacing(Config::Bar::spacing());
    layout->setContentsMargins(layout->spacing(), 0, layout->spacing(), 0);

    setFixedHeight(Config::Bar::height());
    setStyleSheet(Utils::read(CSS_MUSICBAR));
    setAutoFillBackground(true);
    setColor(Utils::backgroundColor(Utils::defaultCover(Config::Bar::coverSize())));
    setLayout(layout);

    pm_coverLabel = new QLabel(this);
    pm_coverLabel->setPixmap(Utils::defaultCover(Config::Bar::coverSize()));
    pm_coverLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    layout->addWidget(pm_coverLabel, 0, 0);

    pm_trackLabel = new QLabel(this);
    pm_trackLabel->setFixedWidth(Config::Bar::trackWidth());
    layout->addWidget(pm_trackLabel, 0, 1);

    pm_currentTimeLabel = new QLabel(this);
    pm_currentTimeLabel->setFixedWidth(Config::Bar::timeWidth());
    pm_currentTimeLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    pm_currentTimeLabel->setAlignment(Qt::AlignRight);
    layout->addWidget(pm_currentTimeLabel, 0, 2);

    pm_lengthSlider = new LengthSlider(this);
    pm_lengthSlider->setEnabled(false);
    pm_lengthSlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    layout->addWidget(pm_lengthSlider, 0, 3);

    pm_totalTimeLabel = new QLabel(this);
    pm_totalTimeLabel->setFixedWidth(Config::Bar::timeWidth());
    pm_totalTimeLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    layout->addWidget(pm_totalTimeLabel, 0, 4);

    QList<IconButton *> buttons;

    pm_previousButton = new IconButton(this);
    pm_previousButton->init({QIcon(ICO_PREVIOUS)}, Config::Bar::iconSize());
    buttons << pm_previousButton;

    pm_playButton = new IconButton(this);
    pm_playButton->init({QIcon(ICO_PLAY), QIcon(ICO_PAUSE)}, Config::Bar::iconSize());
    buttons << pm_playButton;

    pm_nextButton = new IconButton(this);
    pm_nextButton->init({QIcon(ICO_NEXT)}, Config::Bar::iconSize());
    buttons << pm_nextButton;

    pm_shuffleButton = new IconButton(this);
    pm_shuffleButton->init({QIcon(ICO_SHUFFLE)}, Config::Bar::iconSize(), true);
    pm_shuffleButton->setLocked(Config::Player::shuffle());
    buttons << pm_shuffleButton;

    pm_loopButton = new IconButton(this);
    pm_loopButton->init({QIcon(ICO_LOOP)}, Config::Bar::iconSize(), true);
    pm_loopButton->setLocked(Config::Player::loop());
    buttons << pm_loopButton;

    pm_volumeButton = new IconButton(this);
    pm_volumeButton->init({QIcon(ICO_VOLUME_FULL),
                           QIcon(ICO_VOLUME_MEDIUM),
                           QIcon(ICO_VOLUME_LOW),
                           QIcon(ICO_VOLUME_MUTE)}, Config::Bar::iconSize());
    setVolumeIcon();
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

/*
 * Sets volume icon according to player volume.
 */
void MusicBar::setVolumeIcon()
{
    int volume = pm_player->volume();

    if (volume > 66)
        pm_volumeButton->setSelectedIcon(0);
    else if (volume > 33)
        pm_volumeButton->setSelectedIcon(1);
    else if (volume > 0)
        pm_volumeButton->setSelectedIcon(2);
    else
        pm_volumeButton->setSelectedIcon(3);
}
