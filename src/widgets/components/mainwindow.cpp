#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

}

MainWindow::~MainWindow()
{

}

void MainWindow::showSavedPosition()
{
    QSettings settings;
    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    move(settings.value("pos", pos()).toPoint());
    resize(settings.value("size", size()).toSize());
    if (settings.value("maximized", isMaximized()).toBool())
        showMaximized();
    else
        show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    savePosition();

    QWidget::closeEvent(event);
}

void MainWindow::savePosition()
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("maximized", isMaximized());
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}
