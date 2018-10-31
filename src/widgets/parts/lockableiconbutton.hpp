#ifndef LOCKABLEICONBUTTON_HPP
#define LOCKABLEICONBUTTON_HPP

#include "widgets/parts/iconbutton.hpp"

class LockableIconButton : public IconButton
{
    Q_OBJECT

    Q_PROPERTY(bool locked READ isLocked WRITE setLocked)

public:
    explicit LockableIconButton(QWidget *parent = nullptr);

    void setLocked(bool locked);
    bool isLocked() const;

signals:
    void locked(bool locked);

private slots:
    void onClicked();

private:
    bool m_locked;
};

#endif // LOCKABLEICONBUTTON_HPP
