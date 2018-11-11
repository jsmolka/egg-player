#ifndef CFG_APPOBJECT_HPP
#define CFG_APPOBJECT_HPP

#include "core/config/jsonobject.hpp"

namespace cfg
{

namespace app
{

class MinimalSizeObject : public JsonObject
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

class AppObject : public JsonObject
{
public:
    void loadObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    const app::MinimalSizeObject &minimalSize() const;

    app::MinimalSizeObject &minimalSize();

    void setFontSize(double size);
    double fontSize() const;

    void setLog(bool log);
    bool log() const;

private:
    app::MinimalSizeObject m_minimalSize;
};

}

#endif // CFG_APPOBJECT_HPP
