#ifndef CLICKABLESTYLE_HPP
#define CLICKABLESTYLE_HPP

#include <QProxyStyle>

class ClickableStyle : public QProxyStyle
{
public:
    int styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const;
};

#endif // CLICKABLESTYLE_HPP