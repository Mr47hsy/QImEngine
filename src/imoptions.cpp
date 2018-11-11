#include "imoptions.h"

im::ImOptions::ImOptions()
{
}

im::ImOptions &im::ImOptions::setMQTTVersion(QMQTT::MQTTVersion version)
{
    this->version = version;
    return *this;
}

im::ImOptions &im::ImOptions::setKeepAlive(unsigned short time)
{
    this->keepAliveTime = time;
    return *this;
}

im::ImOptions &im::ImOptions::setAutoReconnect(bool isReconnect)
{
    this->isReconnect = isReconnect;
    return *this;
}

im::ImOptions &im::ImOptions::setReconnectIntervalTime(unsigned short time)
{
    this->reconnectIntervalTime = time;
    return *this;
}

im::ImOptions &im::ImOptions::setOffLineContext(const QString &msg)
{
    this->offLineContext = msg;
    return *this;
}

im::ImOptions &im::ImOptions::setUseSSL(bool isSSL)
{
    this->isSSL = isSSL;
    return *this;
}

im::ImOptions &im::ImOptions::setSSLConfig(const QSslConfiguration& sslConfig)
{
    this->mysslConfig = sslConfig;
    return *this;
}

void im::ImOptions::endOptions()
{
}

QMQTT::MQTTVersion im::ImOptions::getMQTTVersion() const
{
    return version;
}

unsigned short im::ImOptions::getKeepAliveTime() const
{
    return keepAliveTime;
}

bool im::ImOptions::autoReconnect() const
{
    return isReconnect;
}

unsigned short im::ImOptions::getReconnectIntervalTime() const
{
    return reconnectIntervalTime;
}

QString im::ImOptions::getOffLineContext() const
{
    return offLineContext;
}

bool im::ImOptions::useSSL() const
{
    return isSSL;
}

QSslConfiguration im::ImOptions::getSSLConfig() const
{
    return mysslConfig;
}
