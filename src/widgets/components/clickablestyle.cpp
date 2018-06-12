#include "clickablestyle.hpp"

/*
 * Calculate style hint.
 *
 * :param hint: hint
 * :param option: option
 * :param widget: widget
 * :param returnData: return data
 * :return: style hint
 */
int ClickableStyle::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    if (hint == QStyle::SH_Slider_AbsoluteSetButtons)
        return Qt::LeftButton;

    if (hint == QStyle::SH_ScrollBar_LeftClickAbsolutePosition)
        return Qt::LeftButton;

    return QProxyStyle::styleHint(hint, option, widget, returnData);
}
