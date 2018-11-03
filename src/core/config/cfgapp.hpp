#ifndef CFGAPP_HPP
#define CFGAPP_HPP

#include "core/config/cfgappminimalsize.hpp"
#include "core/config/cfgbase.hpp"

namespace cfg
{
class App : public Base
{
public:
    void loadObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    app::MinimalSize &minimalSize();

    void setFontSize(double size);
    double fontSize() const;

    void setLog(bool log);
    bool log() const;

private:
    app::MinimalSize m_minimalSize;
};
}

#endif // CFGAPP_HPP
