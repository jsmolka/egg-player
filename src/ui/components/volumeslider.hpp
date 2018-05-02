#ifndef VOLUMESLIDER_HPP
#define VOLUMESLIDER_HPP

#include <QCursor>
#include <QGridLayout>
#include <QSlider>
#include <QWidget>

#include "config.hpp"
#include "player.hpp"

class EggPlayer;

class VolumeSlider : public QWidget
{
public:
    VolumeSlider(QWidget *parent = nullptr);

public slots:
    void pop();
    void unpop();

private:
    QSlider *pm_slider;
};

#endif // VOLUMESLIDER_HPP
