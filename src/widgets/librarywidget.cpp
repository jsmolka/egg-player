#include "librarywidget.hpp"

#include <QResizeEvent>

#include "core/config/cfgbase.hpp"

LibraryWidget::LibraryWidget(QWidget *parent)
    : AudiosWidget(parent)
{
    addColumn(AudioInfo::Title);
    addColumn(AudioInfo::Artist);
    addColumn(AudioInfo::Album);
    addColumn(AudioInfo::Year, Qt::AlignLeft, ColumnSizePolicy::Shrink);
    addColumn(AudioInfo::Genre);
    addColumn(AudioInfo::Duration, Qt::AlignRight, ColumnSizePolicy::Shrink);
}

void LibraryWidget::resizeEvent(QResizeEvent *event)
{
    adjustToWidth(event->size().width());

    AudiosWidget::resizeEvent(event);
}

void LibraryWidget::adjustToWidth(int width)
{

    const bool hideAlbum = width < cfg::Base::scale(675);
    const bool hideGenre = width < cfg::Base::scale(875);
    const bool hideYear = width < cfg::Base::scale(975);

    setColumnHidden(2, hideAlbum);
    setColumnHidden(3, hideYear);
    setColumnHidden(4, hideGenre);
}
