#ifndef IMCLIENT_H
#define IMCLIENT_H

#include <qmqtt_client.h>
#include <imerror.h>
#include <immessage.h>
#include <imoptions.h>

namespace im{
/*
 * 本类为im客户端
 * 用于执行客户端相应操作
 */
class ImClient
{
public:
    ImClient(const QString& id, const QString& address,
             unsigned short port, const ImOptions& options);
    ImClient(const QString& id, const QString& username,
             const QByteArray& password, const QString& address,
             unsigned short port, const ImOptions& options);
    virtual ~ImClient();
    //获取Qmqtt客户端指针
    QMQTT::Client* getQMqttClient() const;
    //获取连接状态
    bool connectionState() const;
    //获取客户端id
    QString id() const;
    //添加目标类型的目标id
    void addTarget(const TopicType type, const QString& targetId);
    //删除目标类型的目标id
    void deleTarget(const TopicType type, const QString& targetId);
    //发送消息
    void send(ImMessage &msg);
    //取消连接
    void disConnect();
private:
    //QMqtt客户端
    //用于执行客户端操作
    QMQTT::Client* client;
};
}

#endif // IMCLIENT_H
