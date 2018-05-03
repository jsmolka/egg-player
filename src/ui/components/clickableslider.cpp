#include "clickableslider.hpp"

/*
 * Constructor. Sets slider style to make
 * the slider clickable.
 *
 * :param parent: parent, default nullptr
 */
ClickableSlider::ClickableSlider(QWidget *parent) :
    QSlider(parent)
{
    setOrientation(Qt::Horizontal);
    setStyle(new ClickableSliderStyle(style()));

    m_pressed = false;

    connect(this, SIGNAL(sliderPressed()), this, SLOT(onSliderPressed()));
    connect(this, SIGNAL(sliderReleased()), this, SLOT(onSliderReleased()));
}

/*
 * Destructor.
 */
ClickableSlider::~ClickableSlider()
{

}

/*
 * Getter for pressed property.
 *
 * :return: pressed
 */
bool ClickableSlider::isPressed() const
{
    return m_pressed;
}

/*
 * Slot for slider pressed.
 *
 * :emit sliderMoved: position
 */
void ClickableSlider::onSliderPressed()
{
    m_pressed = true;
    emit sliderMoved(value());
}

/*
 * Slot for slider released. It sets the pressed
 * property and emits the current value. It also
 * removes to focus to prevent accidently moving
 * the slider with key presses.
 *
 * :emit sliderValueChanged: value
 */
void ClickableSlider::onSliderReleased()
{
    m_pressed = false;
    emit sliderValueChanged(value());
}
