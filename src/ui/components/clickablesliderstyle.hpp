#ifndef CLICKABLESLIDERSTYLE_HPP
#define CLICKABLESLIDERSTYLE_HPP

#include <QProxyStyle>

class ClickableSliderStyle : public QProxyStyle
{
public:
    using QProxyStyle::QProxyStyle;

    int styleHint(QStyle::StyleHint hint, const QStyleOption* option, const QWidget* widget, QStyleHintReturn* returnData) const;
};

#endif // CLICKABLESLIDERSTYLE_HPP
