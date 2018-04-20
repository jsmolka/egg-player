#include "lengthslider.hpp"

/*
 * Constructor.
 *
 * :param parent: parent widget
 */
LengthSlider::LengthSlider(QWidget *parent) : QSlider(parent)
{
    setOrientation(Qt::Horizontal);
    setStyle(new LengthSliderStyle(style()));

    m_pressed = false;
    m_value = 0;

    connect(this, SIGNAL(sliderPressed()), this, SLOT(onSliderPressed()));
    connect(this, SIGNAL(sliderReleased()), this, SLOT(onSliderReleased()));
    connect(this, SIGNAL(sliderMoved(int)), this, SLOT(onSliderMoved(int)));
}

/*
 * Destructor.
 */
LengthSlider::~LengthSlider()
{

}

/*
 * Getter for pressed property.
 *
 * :return: is pressed
 */
bool LengthSlider::isPressed() const
{
    return m_pressed;
}

/*
 * Slot for slider pressed.
 */
void LengthSlider::onSliderPressed()
{
    m_pressed = true;
    m_value = value();
}

/*
 * Slot for slider released.
 *
 * :emit positionChanged: last value
 */
void LengthSlider::onSliderReleased()
{
    m_pressed = false;
    emit positionChanged(m_value);
}

/*
 * SLot for slider moved.
 *
 * :param value: current position
 */
void LengthSlider::onSliderMoved(int value)
{
    m_value = value;
}
