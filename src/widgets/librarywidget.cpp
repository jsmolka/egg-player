#include "librarywidget.hpp"

#include <ShellScalingApi.h>

LibraryWidget::LibraryWidget(QWidget *parent)
    : AudiosWidget(parent)
{
    addColumn(AudiosWidget::Title);
    addColumn(AudiosWidget::Artist);
    addColumn(AudiosWidget::Album);
    addColumn(AudiosWidget::Year, Qt::AlignLeft, false);
    addColumn(AudiosWidget::Genre);
    addColumn(AudiosWidget::Duration, Qt::AlignRight, false);
}

void LibraryWidget::resizeEvent(QResizeEvent *event)
{
    adjustToWidth(event->size().width());

    AudiosWidget::resizeEvent(event);
}

void LibraryWidget::adjustToWidth(int width)
{
    const static float factor = static_cast<float>(GetScaleFactorForDevice(DEVICE_PRIMARY)) / 100.0f;

    const bool hideAlbum = width < 675 * factor;
    const bool hideGenre = width < 925 * factor;
    const bool hideYear = width < 1025 * factor;

    setColumnHidden(2, hideAlbum);
    setColumnHidden(3, hideYear);
    setColumnHidden(4, hideGenre);
}
