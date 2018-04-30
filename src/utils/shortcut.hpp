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
    Shortcut(QObject *parent = nullptr);
    Shortcut(const QString &shortcut, QObject *parent = nullptr);
    Shortcut(const QString &shortcut, bool hold, QObject *parent = nullptr);
    ~Shortcut();

    int id() const;
    bool isRegistered() const;

signals:
    void pressed();

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;

private:
    struct Combination
    {
        Combination(UINT vk, UINT modifier)
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

    Combination parseShortcut(const QString &shortcut, bool hold);
    bool registerShortcut(Combination combination);
    bool unregisterShortcut();

    static int m_count;
    static const QHash<QString, int> m_map;

    int m_id;
    bool m_registered;
};

#endif // SHORTCUT_HPP
