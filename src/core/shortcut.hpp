#ifndef SHORTCUT_HPP
#define SHORTCUT_HPP

#include <Windows.h>

#include <QAbstractNativeEventFilter>
#include <QHash>
#include <QObject>

class Shortcut : public QObject, private QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    enum RepeatPolicy {Repeat, NoRepeat};

    Shortcut(const QString &shortcut, RepeatPolicy repeat, QObject *parent = nullptr);
    ~Shortcut() override;

    QString shortcut() const;
    bool isRegistered() const;

signals:
    void activated();

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;

private:
    using KeyHash = QHash<QString, UINT>;

    static QStringList createSequence(const QString &shortcut);
    static UINT parseSequence(const QStringList &sequence, const KeyHash &keys);

    void parseShortcut(const QString &shortcut, RepeatPolicy repeat);

    void registerShortcut();
    void unregisterShortcut();

    static int s_id;
    static const KeyHash s_keys;
    static const KeyHash s_modifiers;

    int m_id;
    QString m_shortcut;
    UINT m_modifier;
    UINT m_vk;
    bool m_registered;
};

#endif // SHORTCUT_HPP
