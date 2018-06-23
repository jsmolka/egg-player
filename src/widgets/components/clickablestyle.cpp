#include "clickablestyle.hpp"

int ClickableStyle::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    if (hint == QStyle::SH_Slider_AbsoluteSetButtons
            || hint == QStyle::SH_ScrollBar_LeftClickAbsolutePosition)
        return Qt::LeftButton;

    return QProxyStyle::styleHint(hint, option, widget, returnData);
}
