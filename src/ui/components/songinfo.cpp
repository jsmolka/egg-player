#include "songinfo.hpp"

/*
 * Constructor.
 *
 * :param audio: audio
 * :param parent: parent, default nullptr
 */
SongInfo::SongInfo(Audio *audio, QWidget *parent) :
    QWidget(parent)
{
    pm_audio = audio;
    m_even = false;
}

/*
 * Destructor.
 */
SongInfo::~SongInfo()
{

}

/*
 * Setter for even property.
 *
 * :param even: even
 */
void SongInfo::setEven(bool even)
{
    m_even = even;
}

/*
 * Getter for even property.
 *
 * :return: even
 */
bool SongInfo::isEven() const
{
    return m_even;
}

/*
 * Initialize function. Loops over all created
 * labels and shows them with stretch value.
 *
 * :param stretches: list of stretches
 */
void SongInfo::init(const QVector<int> &stretches)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    for (int i = 0; i < m_labels.size(); i++)
        layout->addWidget(m_labels[i], stretches[i]);
    setLayout(layout);
}

/*
 * Show track.
 *
 *:param horizontal: horizontal alignment
 */
void SongInfo::showTrack(Qt::Alignment horizontal)
{
    if (pm_audio->track() != 0)
        createLabel(QString::number(pm_audio->track()), horizontal);
    else
        createLabel();
}

/*
 * Show title.
 *
 * :param horizontal: horizontal alignment
 */
void SongInfo::showTitle(Qt::Alignment horizontal)
{
    createLabel(pm_audio->title(), horizontal);
}

/*
 * Show artist.
 *
 * :param horizontal: horizontal alignment
 */
void SongInfo::showArtist(Qt::Alignment horizontal)
{
    createLabel(pm_audio->artist(), horizontal);
}

/*
 * Show album.
 *
 * :param horizontal: horizontal alignment
 */
void SongInfo::showAlbum(Qt::Alignment horizontal)
{
    createLabel(pm_audio->album(), horizontal);
}

/*
 * Show year.
 *
 * :param horizontal: horizontal alignment
 */
void SongInfo::showYear(Qt::Alignment horizontal)
{
    if (pm_audio->year() != 0)
        createLabel(QString::number(pm_audio->year()), horizontal);
    else
        createLabel();
}

/*
 * Show genre.
 *
 * :param horizontal: horizontal alignment
 */
void SongInfo::showGenre(Qt::Alignment horizontal)
{
    createLabel(pm_audio->genre(), horizontal);
}

/*
 * Show length.
 *
 * :param horizontal: horizontal alignment
 */
void SongInfo::showLength(Qt::Alignment horizontal)
{
    createLabel(Utils::timeString(pm_audio->length()), horizontal);
}

/*
 * Paint event for custom css.
 */
void SongInfo::paintEvent(QPaintEvent *)
{
    QStyleOption option;
    option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

/*
 * Creates label.
 *
 * :param text: text, default empty
 * :param align: horizontal alignment, default left
 */
void SongInfo::createLabel(const QString &text, Qt::Alignment horizontal)
{
    QLabel *label = new QLabel(text, this);
    label->setAlignment(horizontal | Qt::AlignVCenter);
    m_labels << label;
}
