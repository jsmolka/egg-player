#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QSettings>
#include <QWidget>

class MainWindow : public QWidget
{
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showSavedPosition();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void savePosition();
};

#endif // MAINWINDOW_HPP
