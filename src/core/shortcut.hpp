#ifndef SHORTCUT_HPP
#define SHORTCUT_HPP

#include <Windows.h>

#include <QApplication>
#include <QAbstractEventDispatcher>
#include <QAbstractNativeEventFilter>
#include <QHash>
#include <QObject>

#include "logger.hpp"

class Shortcut : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    Shortcut(const QString &shortcut, bool repeat, QObject *parent = nullptr);
    ~Shortcut();

    int id() const;
    int vk() const;
    int modifier() const;

    bool isRepeat() const;
    bool isRegistered() const;
    QString shortcut() const;

signals:
    void pressed();

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;

private:
    bool parseShortcut();
    bool registerShortcut();
    bool unregisterShortcut();

    int m_id;
    int m_vk;
    int m_modifier;
    bool m_repeat;
    bool m_registered;
    QString m_shortcut;

    static int _id;
    static const QHash<QString, int> s_keys;
    static const QHash<QString, int> s_modifiers;
};

#endif // SHORTCUT_HPP
