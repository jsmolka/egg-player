#ifndef AUDIOSWIDGET_HPP
#define AUDIOSWIDGET_HPP

#include <QPair>
#include <QVector>

#include "core/audio.hpp"
#include "core/audios.hpp"
#include "core/globals.hpp"
#include "widgets/parts/tablewidget.hpp"

class AudiosWidget : public TableWidget
{
    Q_OBJECT

public:
    enum AudioInfo {Title, Artist, Album, Track, Year, Genre, Duration};
    enum SizePolicy {Expand, Shrink};

    explicit AudiosWidget(QWidget *parent = nullptr);
    explicit AudiosWidget(Audios *audios, QWidget *parent = nullptr);

    void setAudios(Audios *audios);
    Audios *audios() const;

    void addColumn(AudioInfo info, Qt::Alignment align = Qt::AlignLeft, SizePolicy policy = Expand);

private slots:
    void onAudiosUpdated(int row);
    void onAudiosInserted(int row);
    void onAudiosRemoved(int row);
    void onAudiosMoved(int from, int to);

private:
    using Column = QPair<AudioInfo, Qt::Alignment>;
    using Columns = QVector<Column>;

    static QString audioInfo(Audio *audio, AudioInfo info);
    void insert(Audio *audio, int row);

    void setup();
    void setupCss();

    Audios *m_audios;
    Columns m_columns;
};

#endif // AUDIOSWIDGET_HPP
