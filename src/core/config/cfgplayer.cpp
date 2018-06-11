#include "cfgplayer.hpp"

CfgPlayer::CfgPlayer()
{

}

CfgPlayer::CfgPlayer(QJsonObject object)
    : CfgAbstract(object)
{

}

void CfgPlayer::setDefaults()
{
    setDefault("loop", false);
    setDefault("shuffle", false);
    setDefault("volume", 25);
}

void CfgPlayer::setLoop(bool loop)
{
    m_object.insert("loop", loop);
}

bool CfgPlayer::loop()
{
    return m_object.value("loop").toBool();
}

void CfgPlayer::setShuffle(bool shuffle)
{
    m_object.insert("shuffle", shuffle);
}

bool CfgPlayer::shuffle()
{
    return m_object.value("shuffle").toBool();
}

void CfgPlayer::setVolume(int volume)
{
    m_object.insert("volume", volume);
}

int CfgPlayer::volume()
{
    return m_object.value("volume").toInt();
}
