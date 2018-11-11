#ifndef IMOPTIONS_H
#define IMOPTIONS_H

#include <QSslConfiguration>
#include <immessage.h>
#include <qmqtt.h>

namespace im{
//全局QOS
const unsigned char QOS=2;
//特殊topic后缀
const QString SPEC="/INFO";

/*
 *本类用于载入im客户端全局连接选项
 */
class ImOptions
{
public:
    ImOptions();
    //设置mqtt版本
    ImOptions& setMQTTVersion(QMQTT::MQTTVersion version);
    //设置心跳检测
    ImOptions& setKeepAlive(unsigned short time);
    //设置重连
    ImOptions& setAutoReconnect(bool isReconnect);
    //设置重连间隔
    ImOptions& setReconnectIntervalTime(unsigned short time);
    //设置断线消息
    ImOptions& setOffLineContext(const QString& msg);
    //设置是否采用SSL
    ImOptions& setUseSSL(bool isSSL);
    //载入SSL配置
    ImOptions& setSSLConfig(const QSslConfiguration& sslConfig);
    //载入配置
    void endOptions();

    QMQTT::MQTTVersion getMQTTVersion() const;
    unsigned short getKeepAliveTime() const;
    bool autoReconnect() const;
    unsigned short getReconnectIntervalTime() const;
    QString getOffLineContext() const;
    bool useSSL() const;
    QSslConfiguration getSSLConfig() const;
private:
    //使用Mqtt版本
    //默认为V3_1_1
    QMQTT::MQTTVersion version=QMQTT::V3_1_1;
    //心跳检测时间
    //默认20s
    unsigned short keepAliveTime=10;
    //是否自动重连
    //默认为否
    bool isReconnect=false;
    //自动连接间隔
    //默认为10s
    unsigned short reconnectIntervalTime=10;
    //断线消息
    //默认为""
    QString offLineContext="";
    //是否采用SSL连接
    //默认为否
    bool isSSL=false;
    //SSL连接配置
    QSslConfiguration mysslConfig;
};
}


#endif // IMOPTIONS_H
