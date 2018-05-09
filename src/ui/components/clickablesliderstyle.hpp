#ifndef CLICKABLESLIDERSTYLE_HPP
#define CLICKABLESLIDERSTYLE_HPP

#include <QProxyStyle>

class ClickableSliderStyle : public QProxyStyle
{
public:
    using QProxyStyle::QProxyStyle;

    int styleHint(QStyle::StyleHint hint, const QStyleOption* option = nullptr, const QWidget* widget = nullptr, QStyleHintReturn* returnData = nullptr) const
    {
        if (hint == QStyle::SH_Slider_AbsoluteSetButtons)
            return Qt::LeftButton;

        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};

#endif // CLICKABLESLIDERSTYLE_HPP
