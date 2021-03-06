#ifndef AUDIOSWIDGET_HPP
#define AUDIOSWIDGET_HPP

#include <QVector>

#include "core/audio.hpp"
#include "core/audiofinder.hpp"
#include "core/audios.hpp"
#include "widgets/tablewidget.hpp"

class AudiosWidget : public TableWidget
{
    Q_OBJECT

public:
    enum AudioInfo {Title, Artist, Album, Track, Year, Genre, Duration};
    enum ColumnSizePolicy {Expand, Shrink};

    explicit AudiosWidget(QWidget *parent = nullptr);
    explicit AudiosWidget(Audios *audios, QWidget *parent = nullptr);

    void setAudios(Audios *audios);
    Audios *audios() const;

    void addColumn(AudioInfo info, Qt::Alignment align = Qt::AlignLeft, ColumnSizePolicy policy = Expand);

    void keyboardSearch(const QString &search) override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onAudiosInserted(int row);
    void onAudiosRemoved(int row);
    void onAudiosUpdated(int row);

private:
    struct Column
    {
        AudioInfo info;
        Qt::Alignment align;
    };
    static QString audioInfo(const Audio &audio, AudioInfo info);

    void insert(int row, const Audio &audio);

    void init();
    void initStyle();

    Audios *m_audios;
    AudioFinder m_finder;
    QVector<Column> m_columns;
};

#endif // AUDIOSWIDGET_HPP
