#include "musicbar.hpp"

/*
 * Constructor. Creates all necessary objects and
 * connections.
 *
 * :param parent: parent, default nullptr
 */
MusicBar::MusicBar(QWidget *parent) :
    QWidget(parent),
    m_player(this),
    m_coverLabel(this),
    m_trackLabel(this),
    m_currentTimeLabel(this),
    m_totalTimeLabel(this),
    m_playPauseButton(this),
    m_nextButton(this),
    m_previousButton(this),
    m_shuffleButton(this),
    m_loopButton(this),
    m_volumeButton(this),
    m_lengthSlider(this),
    m_volumeSlider(this),
    m_scPlayPause(Config::Shortcut::playPause(), false, this),
    m_scNext(Config::Shortcut::next(), false, this),
    m_scPrevious(Config::Shortcut::previous(), false, this),
    m_scVolumeUp(Config::Shortcut::volumeUp(), true, this),
    m_scVolumeDown(Config::Shortcut::volumeDown(), true, this)
{
    m_player.setVolume(Config::Player::volume());
    m_player.setShuffle(Config::Player::shuffle());
    m_player.setLoop(Config::Player::loop());

    setup();
    setupUi();

    connect(&m_player, SIGNAL(audioChanged(Audio *)), this, SLOT(onPlayerAudioChanged(Audio *)));
    connect(&m_player, SIGNAL(stateChanged(Player::State)), this, SLOT(onPlayerStateChanged(Player::State)));
    connect(&m_player, SIGNAL(positionChanged(int)), this, SLOT(onPlayerPositionChanged(int)));
    connect(&m_player, SIGNAL(volumeChanged(int)), this, SLOT(onPlayerVolumeChanged(int)));

    connect(&m_nextButton, SIGNAL(pressed()), &m_player, SLOT(next()));
    connect(&m_playPauseButton, SIGNAL(pressed()), this, SLOT(onPlayPauseButtonPressed()));
    connect(&m_previousButton, SIGNAL(pressed()), &m_player, SLOT(previous()));
    connect(&m_shuffleButton, SIGNAL(locked(bool)), this, SLOT(onShuffleButtonLocked(bool)));
    connect(&m_loopButton, SIGNAL(locked(bool)), this, SLOT(onLoopButtonLocked(bool)));
    connect(&m_volumeButton, SIGNAL(pressed()), this, SLOT(onVolumeButtonPressed()));

    connect(&m_lengthSlider, SIGNAL(sliderMoved(int)), this, SLOT(onLengthSliderMoved(int)));
    connect(&m_lengthSlider, SIGNAL(sliderValueChanged(int)), this, SLOT(onLengthSliderValueChanged(int)));
    connect(&m_volumeSlider, SIGNAL(sliderMoved(int)), this, SLOT(onVolumeSliderMoved(int)));
    connect(&m_volumeSlider, SIGNAL(sliderValueChanged(int)), SLOT(onVolumeSliderValueChanged(int)));

    connect(&m_scPlayPause, SIGNAL(pressed()), this, SLOT(onShortcutPlayPausePressed()));
    connect(&m_scNext, SIGNAL(pressed()), &m_player, SLOT(next()));
    connect(&m_scPrevious, SIGNAL(pressed()), &m_player, SLOT(previous()));
    connect(&m_scVolumeUp, SIGNAL(pressed()), this, SLOT(onShortcutVolumeUpPressed()));
    connect(&m_scVolumeDown, SIGNAL(pressed()), this, SLOT(onShortcutVolumeDownPressed()));
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
    return &m_player;
}

/*
 * Getter for cover label.
 *
 * :return: cover label
 */
QLabel * MusicBar::coverLabel()
{
    return &m_coverLabel;
}

/*
 * Getter for track label property.
 *
 * :return: track label
 */
QLabel * MusicBar::trackLabel()
{
    return &m_trackLabel;
}

/*
 * Getter for time label property.
 *
 * :return: time label
 */
QLabel * MusicBar::currentTimeLabel()
{
    return &m_currentTimeLabel;
}

/*
 * Getter for time label property.
 *
 * :return: time label
 */
QLabel * MusicBar::totalTimeLabel()
{
    return &m_totalTimeLabel;
}

/*
 * Getter for play pause button property.
 *
 * :return: play pause button
 */
IconButton * MusicBar::playPauseButton()
{
    return &m_playPauseButton;
}

/*
 * Getter for next button property.
 *
 * :return: next button
 */
IconButton * MusicBar::nextButton()
{
    return &m_nextButton;
}

/*
 * Getter for back button property.
 *
 * :return: back button
 */
IconButton * MusicBar::previousButton()
{
    return &m_previousButton;
}

/*
 * Getter for shuffle button property.
 *
 * :return: shuffle button
 */
IconButton * MusicBar::shuffleButton()
{
    return &m_shuffleButton;
}

/*
 * Getter for loop button property.
 *
 * :return: loop button
 */
IconButton * MusicBar::loopButton()
{
    return &m_loopButton;
}

/*
 * Getter for volume button property.
 *
 * :return: volume button
 */
IconButton * MusicBar::volumeButton()
{
    return &m_volumeButton;
}

/*
 * Getter for length slider property.
 *
 * :return: length slider
 */
ClickableSlider * MusicBar::lengthSlider()
{
    return &m_lengthSlider;
}

/*
 * Getter for volume slider property.
 *
 * :return: volume slider
 */
ClickableSlider * MusicBar::volumeSlider()
{
    return &m_volumeSlider;
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

    m_coverLabel.setPixmap(cover);
    m_trackLabel.setText(QString("%1\n%2").arg(audio->title(), audio->artist()));

    m_currentTimeLabel.setText(Utils::timeString(0));
    m_totalTimeLabel.setText(Utils::timeString(audio->length()));

    m_lengthSlider.setRange(0, audio->length());
    m_lengthSlider.setEnabled(true);

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
    m_playPauseButton.setSelectedIcon(state == Player::State::Playing ? 1 : 0);
}

/*
 * Player position changed event. Sets slider
 * position if it is not pressed.
 *
 * :param position: position in seconds
 */
void MusicBar::onPlayerPositionChanged(int position)
{
    if (!m_lengthSlider.isPressed())
    {
        m_currentTimeLabel.setText(Utils::timeString(position));
        m_lengthSlider.setValue(position);
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
    if (m_playPauseButton.selectedIcon() == 0)
        m_player.play();
    else
        m_player.pause();
}

/*
 * Shuffle button locked event. Applies change to
 * player and saves it in the config.
 *
 * :param locked: locked
 */
void MusicBar::onShuffleButtonLocked(bool locked)
{
    m_player.setShuffle(locked);
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
    m_player.setLoop(locked);
    Config::Player::setLoop(locked);
}

/*
 * Volume button pressed event. Shows or hides
 * the volume slider depeding its current state.
 */
void MusicBar::onVolumeButtonPressed()
{
    if (m_volumeSlider.isVisible())
    {
        m_volumeSlider.setVisible(false);
        showButtons();
    }
    else
    {
        hideButtons();
        m_volumeSlider.setVisible(true);
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
    m_currentTimeLabel.setText(Utils::timeString(value));
}

/*
 * Length slider value changed event. Updates the
 * current time and player position accordingly.
 *
 * :param value: position in seconds
 */
void MusicBar::onLengthSliderValueChanged(int value)
{
    m_currentTimeLabel.setText(Utils::timeString(value));
    m_player.setPosition(value);
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
    if (m_player.isPlaying())
        m_player.pause();
    else
        m_player.play();
}

/*
 * Volume up shortcut pressed event. Increases
 * the player volume.
 */
void MusicBar::onShortcutVolumeUpPressed()
{
    changeVolume(m_player.volume(), 1);
}

/*
 * Volume down shortcut pressed event. Decreases
 * the player volume.
 */
void MusicBar::onShortcutVolumeDownPressed()
{
    changeVolume(m_player.volume(), -1);
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
    m_coverLabel.setPixmap(Utils::defaultCover(Config::Bar::coverSize()));
    m_coverLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    m_trackLabel.setFixedWidth(Config::Bar::trackWidth());
    m_trackLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

/*
 * Creates the length slider user inferface part.
 */
void MusicBar::createLengthSlider()
{
    m_currentTimeLabel.setFixedWidth(Config::Bar::timeWidth());
    m_currentTimeLabel.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    m_currentTimeLabel.setAlignment(Qt::AlignRight | Qt::AlignHCenter);

    m_lengthSlider.setEnabled(false);
    m_lengthSlider.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_totalTimeLabel.setFixedWidth(Config::Bar::timeWidth());
    m_totalTimeLabel.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
}

/*
 * Creates the buttons user interface part.
 */
void MusicBar::createButtons()
{
    m_playPauseButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_playPauseButton.init({ICO_PLAY, ICO_PAUSE}, Config::Bar::iconSize());

    m_previousButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_previousButton.init({ICO_PREVIOUS}, Config::Bar::iconSize());

    m_nextButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_nextButton.init({ICO_NEXT}, Config::Bar::iconSize());

    m_shuffleButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_shuffleButton.init({ICO_SHUFFLE}, Config::Bar::iconSize(), true);
    m_shuffleButton.setLocked(Config::Player::shuffle());

    m_loopButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_loopButton.init({ICO_LOOP}, Config::Bar::iconSize(), true);
    m_loopButton.setLocked(Config::Player::loop());

    m_volumeButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_volumeButton.init({ICO_VOLUME_FULL,
                           ICO_VOLUME_MEDIUM,
                           ICO_VOLUME_LOW,
                           ICO_VOLUME_MUTE}, Config::Bar::iconSize());
    setVolumeIcon(Config::Player::volume());

    m_volumeSlider.setVisible(false);
    m_volumeSlider.setRange(0, 100);
    m_volumeSlider.setValue(Config::Player::volume());
    m_volumeSlider.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    m_volumeSlider.setFixedWidth(5 * Config::Bar::iconSize() + 4 * Config::Bar::spacing());
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
    layout->addWidget(&m_coverLabel, 0, 0);
    layout->addWidget(&m_trackLabel, 0, 1);
    layout->addWidget(&m_currentTimeLabel, 0, 2);
    layout->addWidget(&m_lengthSlider, 0, 3);
    layout->addWidget(&m_totalTimeLabel, 0, 4);
    layout->addWidget(&m_previousButton, 0, 5);
    layout->addWidget(&m_volumeSlider, 0, 5, 1, 5, Qt::AlignRight);
    layout->addWidget(&m_playPauseButton, 0, 6);
    layout->addWidget(&m_nextButton, 0, 7);
    layout->addWidget(&m_shuffleButton, 0, 8);
    layout->addWidget(&m_loopButton, 0, 9);
    layout->addWidget(&m_volumeButton, 0, 10);
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
    m_previousButton.setVisible(visible);
    m_playPauseButton.setVisible(visible);
    m_nextButton.setVisible(visible);
    m_shuffleButton.setVisible(visible);
    m_loopButton.setVisible(visible);
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
        m_volumeButton.setSelectedIcon(0);
    else if (volume > 33)
        m_volumeButton.setSelectedIcon(1);
    else if (volume > 0)
        m_volumeButton.setSelectedIcon(2);
    else
        m_volumeButton.setSelectedIcon(3);
}

/*
 * Sets player volume.
 *
 * :param volume: volume
 */
void MusicBar::setVolumePlayer(int volume)
{
    m_player.setVolume(volume);
}

/*
 * Sets volume slider position.
 *
 * :param volume: volume
 */
void MusicBar::setVolumeSlider(int volume)
{
    m_volumeSlider.setValue(volume);
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
