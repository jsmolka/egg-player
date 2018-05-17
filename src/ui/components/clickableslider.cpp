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
    setStyle(new ClickableStyle(style()));

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
 * Pressed event. Makes clicking the slider a
 * move.
 *
 * :emit sliderMoved: position
 */
void ClickableSlider::onSliderPressed()
{
    m_pressed = true;
    emit sliderMoved(value());
}

/*
 * Released event. It sets the pressed property
 * and emits the current value. It also removes
 * to focus to prevent accidently moving the
 * slider with key presses.
 *
 * :emit sliderValueChanged: value
 */
void ClickableSlider::onSliderReleased()
{
    m_pressed = false;
    emit sliderValueChanged(value());
}
