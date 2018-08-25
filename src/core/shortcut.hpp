#ifndef SHORTCUT_HPP
#define SHORTCUT_HPP

#include <Windows.h>

#include <QAbstractEventDispatcher>
#include <QAbstractNativeEventFilter>
#include <QAtomicInt>
#include <QHash>
#include <QObject>

class Shortcut : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    Shortcut(const QString &shortcut, bool repeat, QObject *parent = nullptr);
    ~Shortcut() override;

    int id() const;
    bool isRepeat() const;
    bool isRegistered() const;
    QString shortcut() const;

signals:
    void pressed();

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;

private:
    void activate();

    QStringList prepareShortcut();
    UINT parseModifier(const QStringList &sequence);
    UINT parseVirtualKey(const QStringList &sequence);

    bool registerShortcut(UINT modifier, UINT vk);
    bool unregisterShortcut();

    int m_id;
    bool m_repeat;
    bool m_registered;
    QString m_shortcut;

    static QAtomicInt s_id;
    static const QHash<QString, UINT> s_keys;
    static const QHash<QString, UINT> s_modifiers;
};

#endif // SHORTCUT_HPP
