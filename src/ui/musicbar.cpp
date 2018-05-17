#include "musicbar.hpp"

/*
 * Constructor. Creates all necessary objects and
 * connections.
 *
 * :param parent: parent, default nullptr
 */
MusicBar::MusicBar(QWidget *parent) :
    QWidget(parent),
    pm_player(new Player(this)),
    pm_coverLabel(new QLabel(this)),
    pm_trackLabel(new QLabel(this)),
    pm_currentTimeLabel(new QLabel(this)),
    pm_totalTimeLabel(new QLabel(this)),
    pm_playPauseButton(new IconButton(this)),
    pm_nextButton(new IconButton(this)),
    pm_previousButton(new IconButton(this)),
    pm_shuffleButton(new IconButton(this)),
    pm_loopButton(new IconButton(this)),
    pm_volumeButton(new IconButton(this)),
    pm_lengthSlider(new ClickableSlider(this)),
    pm_volumeSlider(new ClickableSlider(this)),
    pm_scPlayPause(new Shortcut(Config::Shortcut::playPause(), false, this)),
    pm_scNext(new Shortcut(Config::Shortcut::next(), false, this)),
    pm_scPrevious(new Shortcut(Config::Shortcut::previous(), false, this)),
    pm_scVolumeUp(new Shortcut(Config::Shortcut::volumeUp(), true, this)),
    pm_scVolumeDown(new Shortcut(Config::Shortcut::volumeDown(), true, this))
{
    pm_player->setVolume(Config::Player::volume());
    pm_player->setShuffle(Config::Player::shuffle());
    pm_player->setLoop(Config::Player::loop());

    setup();
    setupUi();

    connect(pm_player, SIGNAL(audioChanged(Audio *)), this, SLOT(onPlayerAudioChanged(Audio *)));
    connect(pm_player, SIGNAL(stateChanged(Player::State)), this, SLOT(onPlayerStateChanged(Player::State)));
    connect(pm_player, SIGNAL(positionChanged(int)), this, SLOT(onPlayerPositionChanged(int)));
    connect(pm_player, SIGNAL(volumeChanged(int)), this, SLOT(onPlayerVolumeChanged(int)));

    connect(pm_nextButton, SIGNAL(pressed()), pm_player, SLOT(next()));
    connect(pm_playPauseButton, SIGNAL(pressed()), this, SLOT(onPlayPauseButtonPressed()));
    connect(pm_previousButton, SIGNAL(pressed()), pm_player, SLOT(previous()));
    connect(pm_shuffleButton, SIGNAL(locked(bool)), this, SLOT(onShuffleButtonLocked(bool)));
    connect(pm_loopButton, SIGNAL(locked(bool)), this, SLOT(onLoopButtonLocked(bool)));
    connect(pm_volumeButton, SIGNAL(pressed()), this, SLOT(onVolumeButtonPressed()));

    connect(pm_lengthSlider, SIGNAL(sliderMoved(int)), this, SLOT(onLengthSliderMoved(int)));
    connect(pm_lengthSlider, SIGNAL(sliderValueChanged(int)), this, SLOT(onLengthSliderValueChanged(int)));
    connect(pm_volumeSlider, SIGNAL(sliderMoved(int)), this, SLOT(onVolumeSliderMoved(int)));
    connect(pm_volumeSlider, SIGNAL(sliderValueChanged(int)), SLOT(onVolumeSliderValueChanged(int)));

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
 * :return: player
 */
Player * MusicBar::player()
{
    return pm_player;
}

/*
 * Getter for cover label.
 *
 * :return: cover label
 */
QLabel * MusicBar::coverLabel()
{
    return pm_coverLabel;
}

/*
 * Getter for track label property.
 *
 * :return: track label
 */
QLabel * MusicBar::trackLabel()
{
    return pm_trackLabel;
}

/*
 * Getter for time label property.
 *
 * :return: time label
 */
QLabel * MusicBar::currentTimeLabel()
{
    return pm_currentTimeLabel;
}

/*
 * Getter for time label property.
 *
 * :return: time label
 */
QLabel * MusicBar::totalTimeLabel()
{
    return pm_totalTimeLabel;
}

/*
 * Getter for play pause button property.
 *
 * :return: play pause button
 */
IconButton * MusicBar::playPauseButton()
{
    return pm_playPauseButton;
}

/*
 * Getter for next button property.
 *
 * :return: next button
 */
IconButton * MusicBar::nextButton()
{
    return pm_nextButton;
}

/*
 * Getter for back button property.
 *
 * :return: back button
 */
IconButton * MusicBar::previousButton()
{
    return pm_previousButton;
}

/*
 * Getter for shuffle button property.
 *
 * :return: shuffle button
 */
IconButton * MusicBar::shuffleButton()
{
    return pm_shuffleButton;
}

/*
 * Getter for loop button property.
 *
 * :return: loop button
 */
IconButton * MusicBar::loopButton()
{
    return pm_loopButton;
}

/*
 * Getter for volume button property.
 *
 * :return: volume button
 */
IconButton * MusicBar::volumeButton()
{
    return pm_volumeButton;
}

/*
 * Getter for length slider property.
 *
 * :return: length slider
 */
ClickableSlider * MusicBar::lengthSlider()
{
    return pm_lengthSlider;
}

/*
 * Getter for volume slider property.
 *
 * :return: volume slider
 */
ClickableSlider * MusicBar::volumeSlider()
{
    return pm_volumeSlider;
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
 * Player audio changed event. Sets up cover,
 * track label, time labels and length slider.
 *
 * :param audio: audio
 */
void MusicBar::onPlayerAudioChanged(Audio *audio)
{
    QPixmap cover = Cache().cover(audio, Config::Bar::coverSize());

    pm_coverLabel->setPixmap(cover);
    pm_trackLabel->setText(QString("%1\n%2").arg(audio->title(), audio->artist()));

    pm_currentTimeLabel->setText(Utils::timeString(0));
    pm_totalTimeLabel->setText(Utils::timeString(audio->length()));

    pm_lengthSlider->setRange(0, audio->length());
    pm_lengthSlider->setEnabled(true);

    setColor(Utils::backgroundColor(cover));
}

/*
 * Player state changed event. Sets the
 * corresponding icon of play button.
 *
 * :param state: player state
 */
void MusicBar::onPlayerStateChanged(Player::State state)
{
    pm_playPauseButton->setSelectedIcon(state == Player::State::Playing ? 1 : 0);
}

/*
 * Player position changed event. Sets slider
 * position if it is not pressed.
 *
 * :param position: position in seconds
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
 * Player volume changed event. Just set the
 * volume button icon because other volume events
 * are done seperately.
 */
void MusicBar::onPlayerVolumeChanged(int volume)
{
    setVolumeIcon(volume);
}

/*
 * Play pause button pressed event. Starts or
 * pauses the player depeding on the button icon.
 */
void MusicBar::onPlayPauseButtonPressed()
{
    if (pm_playPauseButton->selectedIcon() == 0)
        pm_player->play();
    else
        pm_player->pause();
}

/*
 * Shuffle button locked event. Applies change to
 * player and saves it in the config.
 *
 * :param locked: locked
 */
void MusicBar::onShuffleButtonLocked(bool locked)
{
    pm_player->setShuffle(locked);
    Config::Player::setShuffle(locked);
}

/*
 * Loop button locked event. Applies change to
 * player and saves it in the config.
 *
 * :param locked: locked
 */
void MusicBar::onLoopButtonLocked(bool locked)
{
    pm_player->setLoop(locked);
    Config::Player::setLoop(locked);
}

/*
 * Volume button pressed event. Shows or hides
 * the volume slider depeding its current state.
 */
void MusicBar::onVolumeButtonPressed()
{
    if (pm_volumeSlider->isVisible())
    {
        pm_volumeSlider->setVisible(false);
        showButtons();
    }
    else
    {
        hideButtons();
        pm_volumeSlider->setVisible(true);
    }
}

/*
 * Length slider moved event. Set the value of
 * the current time label to reflect the change.
 *
 * :param value: position in seconds
 */
void MusicBar::onLengthSliderMoved(int value)
{
    pm_currentTimeLabel->setText(Utils::timeString(value));
}

/*
 * Length slider value changed event. Updates the
 * current time and player position accordingly.
 *
 * :param value: position in seconds
 */
void MusicBar::onLengthSliderValueChanged(int value)
{
    pm_currentTimeLabel->setText(Utils::timeString(value));
    pm_player->setPosition(value);
}

/*
 * Volume slider moved event. Sets the player
 * volume accordingly. Does not change the config
 * because of performance reason.
 *
 * :param value: value
 */
void MusicBar::onVolumeSliderMoved(int value)
{
    setVolumePlayer(value);
}

/*
 * Volume slider value changed event. Changes the
 * player volume and config value accordingly.
 *
 * :param value: value
 */
void MusicBar::onVolumeSliderValueChanged(int value)
{
    setVolumeConfig(value);
    setVolumePlayer(value);
}

/*
 * Play pause shortcut pressed event. Plays or
 * pauses the player depending on the current
 * state.
 */
void MusicBar::onShortcutPlayPausePressed()
{
    if (pm_player->isPlaying())
        pm_player->pause();
    else
        pm_player->play();
}

/*
 * Volume up shortcut pressed event. Increases
 * the player volume.
 */
void MusicBar::onShortcutVolumeUpPressed()
{
    changeVolume(pm_player->volume(), 1);
}

/*
 * Volume down shortcut pressed event. Decreases
 * the player volume.
 */
void MusicBar::onShortcutVolumeDownPressed()
{
    changeVolume(pm_player->volume(), -1);
}

/*
 * Loads style sheet and replaces placeholders.
 *
 * :return: style sheet
 */
QString MusicBar::loadStyleSheet()
{
    return Utils::read(CSS_MUSICBAR)
            .replace(
                "groove-height",
                QString::number(Config::Bar::grooveHeight()))
            .replace(
                "handle-size-half",
                QString::number(Config::Bar::handleSize() / 2))
            .replace(
                "handle-size",
                QString::number(Config::Bar::handleSize()))
            .replace(
                "icon-size-half",
                QString::number(Config::Bar::iconSize() / 2));
}

/*
 * Sets up widget.
 */
void MusicBar::setup()
{
    setAutoFillBackground(true);
    setFixedHeight(Config::Bar::height());
    setStyleSheet(loadStyleSheet());
    setColor(Utils::backgroundColor(Utils::defaultCover()));
}

/*
 * Sets up user interface.
 */
void MusicBar::setupUi()
{
    createAudioInfo();
    createLengthSlider();
    createButtons();
    createLayout();
}

/*
 * Creates the audio info user inferface part.
 */
void MusicBar::createAudioInfo()
{
    pm_coverLabel->setPixmap(Utils::defaultCover(Config::Bar::coverSize()));
    pm_coverLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    pm_trackLabel->setFixedWidth(Config::Bar::trackWidth());
    pm_trackLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

/*
 * Creates the length slider user inferface part.
 */
void MusicBar::createLengthSlider()
{
    pm_currentTimeLabel->setFixedWidth(Config::Bar::timeWidth());
    pm_currentTimeLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    pm_currentTimeLabel->setAlignment(Qt::AlignRight | Qt::AlignHCenter);

    pm_lengthSlider->setEnabled(false);
    pm_lengthSlider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    pm_totalTimeLabel->setFixedWidth(Config::Bar::timeWidth());
    pm_totalTimeLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
}

/*
 * Creates the buttons user interface part.
 */
void MusicBar::createButtons()
{
    pm_previousButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pm_previousButton->init({ICO_PREVIOUS}, Config::Bar::iconSize());

    pm_playPauseButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pm_playPauseButton->init({ICO_PLAY, ICO_PAUSE}, Config::Bar::iconSize());


    pm_nextButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pm_nextButton->init({ICO_NEXT}, Config::Bar::iconSize());

    pm_shuffleButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pm_shuffleButton->init({ICO_SHUFFLE}, Config::Bar::iconSize(), true);
    pm_shuffleButton->setLocked(Config::Player::shuffle());

    pm_loopButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pm_loopButton->init({ICO_LOOP}, Config::Bar::iconSize(), true);
    pm_loopButton->setLocked(Config::Player::loop());

    pm_volumeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pm_volumeButton->init({ICO_VOLUME_FULL,
                           ICO_VOLUME_MEDIUM,
                           ICO_VOLUME_LOW,
                           ICO_VOLUME_MUTE}, Config::Bar::iconSize());
    setVolumeIcon(Config::Player::volume());

    pm_volumeSlider->setVisible(false);
    pm_volumeSlider->setRange(0, 100);
    pm_volumeSlider->setValue(Config::Player::volume());
    pm_volumeSlider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    pm_volumeSlider->setFixedWidth(5 * Config::Bar::iconSize() + 4 * Config::Bar::spacing());
}

/*
 * Places all items in the layout.
 */
void MusicBar::createLayout()
{
    QGridLayout *layout = new QGridLayout(this);
    layout->setHorizontalSpacing(Config::Bar::spacing());
    layout->setContentsMargins(Config::Bar::margin(),
                               Config::Bar::margin(),
                               Config::Bar::margin(),
                               Config::Bar::margin());
    layout->addWidget(pm_coverLabel, 0, 0);
    layout->addWidget(pm_trackLabel, 0, 1);
    layout->addWidget(pm_currentTimeLabel, 0, 2);
    layout->addWidget(pm_lengthSlider, 0, 3);
    layout->addWidget(pm_totalTimeLabel, 0, 4);
    layout->addWidget(pm_previousButton, 0, 5);
    layout->addWidget(pm_volumeSlider, 0, 5, 1, 5, Qt::AlignRight);
    layout->addWidget(pm_playPauseButton, 0, 6);
    layout->addWidget(pm_nextButton, 0, 7);
    layout->addWidget(pm_shuffleButton, 0, 8);
    layout->addWidget(pm_loopButton, 0, 9);
    layout->addWidget(pm_volumeButton, 0, 10);
    setLayout(layout);
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
 * Sets visibility for all buttons.
 *
 * :param visible: visible
 */
void MusicBar::setButtonVisibility(bool visible)
{
    pm_previousButton->setVisible(visible);
    pm_playPauseButton->setVisible(visible);
    pm_nextButton->setVisible(visible);
    pm_shuffleButton->setVisible(visible);
    pm_loopButton->setVisible(visible);
}

/*
 * Hides all buttons.
 */
void MusicBar::hideButtons()
{
    setButtonVisibility(false);
}

/*
 * Shows all buttons.
 */
void MusicBar::showButtons()
{
    setButtonVisibility(true);
}

/*
 * Sets player volume in config.
 *
 * :param volume: volume
 */
void MusicBar::setVolumeConfig(int volume)
{
    Config::Player::setVolume(volume);
}

/*
 * Sets volume icon according to volume.
 *
 * :param volume: volume
 */
void MusicBar::setVolumeIcon(int volume)
{
    if (volume > 66)
        pm_volumeButton->setSelectedIcon(0);
    else if (volume > 33)
        pm_volumeButton->setSelectedIcon(1);
    else if (volume > 0)
        pm_volumeButton->setSelectedIcon(2);
    else
        pm_volumeButton->setSelectedIcon(3);
}

/*
 * Sets player volume.
 *
 * :param volume: volume
 */
void MusicBar::setVolumePlayer(int volume)
{
    pm_player->setVolume(volume);
}

/*
 * Sets volume slider position.
 *
 * :param volume: volume
 */
void MusicBar::setVolumeSlider(int volume)
{
    pm_volumeSlider->setValue(volume);
}

/*
 * Changes volume by a step.
 *
 * :param volume: volume
 * :param step: step
 */
void MusicBar::changeVolume(int volume, int step)
{
    volume = volume + step;
    if (volume < 0 || volume > 100)
        return;

    setVolumeConfig(volume);
    setVolumePlayer(volume);
    setVolumeSlider(volume);
}
