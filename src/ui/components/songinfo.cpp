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
}

/*
 * Destructor.
 */
SongInfo::~SongInfo()
{

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
 */
void SongInfo::showTrack()
{
    if (pm_audio->track() != 0)
        createLabel(QString::number(pm_audio->track()));
    else
        createLabel();
}

/*
 * Show title.
 */
void SongInfo::showTitle()
{
    createLabel(pm_audio->title());
}

/*
 * Show artist.
 */
void SongInfo::showArtist()
{
    createLabel(pm_audio->artist());
}

/*
 * Show album.
 */
void SongInfo::showAlbum()
{
    createLabel(pm_audio->album());
}

/*
 * Show year.
 */
void SongInfo::showYear()
{
    if (pm_audio->year() != 0)
        createLabel(QString::number(pm_audio->year()));
    else
        createLabel();
}

/*
 * Show genre.
 */
void SongInfo::showGenre()
{
    createLabel(pm_audio->genre());
}

/*
 * Show length.
 */
void SongInfo::showLength()
{
    createLabel(Utils::timeString(pm_audio->length()), Qt::AlignRight);
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
void SongInfo::createLabel(const QString &text, Qt::Alignment align)
{
    QLabel *label = new QLabel(text, this);
    label->setAlignment(align | Qt::AlignVCenter);
    m_labels << label;
}
