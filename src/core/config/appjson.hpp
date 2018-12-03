#ifndef CFG_APPJSON_HPP
#define CFG_APPJSON_HPP

#include "core/config/jsonobject.hpp"

namespace cfg
{

namespace app
{

class MinimalSizeJson : public JsonObject
{
public:
    void loadObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    void setHeight(int height);
    int height() const;

    void setWidth(int width);
    int width() const;
};

}

class AppJson : public JsonObject
{
public:
    void loadObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    const app::MinimalSizeJson &minimalSize() const;

    app::MinimalSizeJson &minimalSize();

    void setFontSize(double size);
    double fontSize() const;

private:
    app::MinimalSizeJson m_minimalSize;
};

}

#endif // CFG_APPJSON_HPP
