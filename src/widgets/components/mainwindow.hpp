#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>

class MainWindow : public QWidget
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void showSavedPosition();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void savePosition();
};

#endif // MAINWINDOW_HPP
