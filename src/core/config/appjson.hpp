#ifndef CFG_APPJSON_HPP
#define CFG_APPJSON_HPP

#include "core/config/jsonobject.hpp"

namespace cfg
{

class MinimalSizeJson : public JsonObject
{
public:
    void loadFromObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    void setHeight(int height);
    int height() const;

    void setWidth(int width);
    int width() const;
};

class AppJson : public JsonObject
{
public:
    void loadFromObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    const MinimalSizeJson &minimalSize() const;
    MinimalSizeJson &minimalSize();

    void setFontSize(double size);
    double fontSize() const;

private:    
    MinimalSizeJson m_minimalSize;
};

}

#endif // CFG_APPJSON_HPP
