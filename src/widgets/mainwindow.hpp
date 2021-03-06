#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QSize>
#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void showSavedState();

protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void saveState();

    QSize m_size;
};

#endif // MAINWINDOW_HPP
