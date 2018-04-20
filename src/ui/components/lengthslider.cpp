#include "lengthslider.hpp"

/*
 * Constructor. Sets slider style to
 * LengthSliderStyle to make the slider
 * clickable.
 *
 * :param parent: parent pointer
 */
LengthSlider::LengthSlider(QWidget *parent) : QSlider(parent)
{
    setOrientation(Qt::Horizontal);
    setStyle(new LengthSliderStyle(style()));

    m_pressed = false;

    connect(this, SIGNAL(sliderPressed()), this, SLOT(onSliderPressed()));
    connect(this, SIGNAL(sliderReleased()), this, SLOT(onSliderReleased()));
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
 * :return: pressed
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
}

/*
 * Slot for slider released. It sets the pressed
 * property and emits the current value.
 *
 * :emit positionChanged: value
 */
void LengthSlider::onSliderReleased()
{
    m_pressed = false;
    emit positionChanged(value());
}
