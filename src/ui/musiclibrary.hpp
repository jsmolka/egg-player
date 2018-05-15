#ifndef MUSICLIBRARY_HPP
#define MUSICLIBRARY_HPP

#include <QHeaderView>
#include <QScrollBar>
#include <QTableWidget>

#include "constants.hpp"
#include "config.hpp"
#include "library.hpp"
#include "rowhoverdelegate.hpp"
#include "songinfo.hpp"
#include "utils.hpp"

class MusicLibrary : public QTableWidget
{
    Q_OBJECT

public:
    MusicLibrary(QWidget *parent = nullptr);
    ~MusicLibrary();

    void loadAudios(Audios audios);
    void loadLibrary(Library *library);

private:
    QString loadStyleSheet();
};

#endif // MUSICLIBRARY_HPP
