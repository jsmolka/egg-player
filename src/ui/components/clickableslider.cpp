#include "clickableslider.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
ClickableSlider::ClickableSlider(QWidget *parent) :
    QSlider(parent),
    m_pressed(false)
{
    setup();

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
 * Makes clicking the slider a move.
 *
 * :emit sliderMoved: position
 */
void ClickableSlider::onSliderPressed()
{
    m_pressed = true;
    emit sliderMoved(value());
}

/*
 * Sets the pressed property and emits the current value.
 *
 * :emit sliderValueChanged: value
 */
void ClickableSlider::onSliderReleased()
{
    m_pressed = false;
    emit sliderValueChanged(value());
}

/*
 * Sets up widget.
 */
void ClickableSlider::setup()
{
    setFocusPolicy(Qt::NoFocus);
    setOrientation(Qt::Horizontal);
    setStyle(new ClickableStyle(style()));
}
