#ifndef MUSICLIBRARY_HPP
#define MUSICLIBRARY_HPP

#include <QListWidget>
#include <QScrollBar>

#include "constants.hpp"
#include "config.hpp"
#include "library.hpp"
#include "songinfo.hpp"
#include "utils.hpp"

/*
 * The MusicLibrary class is responsible for
 * displaying the library.
 */
class MusicLibrary : public QListWidget
{
    Q_OBJECT

public:
    MusicLibrary(Library *library, QWidget *parent = nullptr);
    ~MusicLibrary();

private:
    void setupUi();

    Library *pm_library;
};

#endif // MUSICLIBRARY_HPP
