#include "librarywidget.hpp"

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
