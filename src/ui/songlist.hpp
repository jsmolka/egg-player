#ifndef SONGLIST_HPP
#define SONGLIST_HPP

#include <QLabel>
#include <QList>
#include <QListWidget>

#include "src/constants/path.hpp"
#include "src/core/library.hpp"
#include "src/ui/components/songinfo.hpp"
#include "src/utils/fileutil.hpp"

class SongList : public QListWidget
{
public:
    SongList(Library *library);

private:
    void setupUi();

    Library *pm_library;
};

#endif // SONGLIST_HPP
