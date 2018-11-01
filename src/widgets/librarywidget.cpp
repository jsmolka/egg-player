#include "librarywidget.hpp"

#include <ShellScalingApi.h>

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
    static const float factor = static_cast<float>(GetScaleFactorForDevice(DEVICE_PRIMARY)) / 100.0f;

    const bool hideAlbum = width < 675 * factor;
    const bool hideGenre = width < 875 * factor;
    const bool hideYear = width < 975 * factor;

    setColumnHidden(2, hideAlbum);
    setColumnHidden(3, hideYear);
    setColumnHidden(4, hideGenre);
}
