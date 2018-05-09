#ifndef MUSICLIBRARY_HPP
#define MUSICLIBRARY_HPP

#include <QListWidget>
#include <QScrollBar>

#include "constants.hpp"
#include "config.hpp"
#include "library.hpp"
#include "songinfo.hpp"
#include "utils.hpp"

class MusicLibrary : public QListWidget
{
    Q_OBJECT

public:
    MusicLibrary(QWidget *parent = nullptr);
    ~MusicLibrary();

    void loadLibrary(Library *library);

private:
    QString loadStyleSheet();
};

#endif // MUSICLIBRARY_HPP
