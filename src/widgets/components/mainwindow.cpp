#include "mainwindow.hpp"

#include <QSettings>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

}

void MainWindow::showSavedState()
{
    QSettings settings;

    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    move(settings.value("pos", pos()).toPoint());
    m_size = settings.value("size", size()).toSize();
    resize(m_size);

    if (settings.value("maximized", isMaximized()).toBool())
        showMaximized();
    else
        show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveState();

    QWidget::closeEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_size = event->oldSize();
    QWidget::resizeEvent(event);
}

void MainWindow::saveState()
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("pos", pos());
    settings.setValue("size", isMaximized() ? m_size : size());
    settings.setValue("maximized", isMaximized());
}
