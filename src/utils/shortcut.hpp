#ifndef SHORTCUT_HPP
#define SHORTCUT_HPP

#include <Windows.h>

#include <QAbstractEventDispatcher>
#include <QAbstractNativeEventFilter>
#include <QHash>
#include <QObject>
#include <QStringList>

#include "logger.hpp"

class Shortcut : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    Shortcut(const QString &shortcut, bool repeat, QObject *parent = nullptr);
    ~Shortcut();

    int id() const;
    bool isRegistered() const;
    QString shortcut() const;

signals:
    void pressed();

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;

private:
    struct Combination
    {
        Combination(UINT vk = 0, UINT modifier = 0)
        {
            this->vk = vk;
            this->modifier = modifier;
        }

        bool isValid()
        {
            return vk != 0;
        }

        UINT vk;
        UINT modifier;
    };

    Combination parseShortcut(const QString &shortcut);
    bool registerShortcut(const QString &shortcut, bool repeat);
    bool unregisterShortcut();

    int m_id;
    bool m_registered;
    QString m_shortcut;

    static int _count;
    static const QHash<QString, int> _map;
};

#endif // SHORTCUT_HPP
