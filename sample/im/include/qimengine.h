#ifndef QIMENGINE_H
#define QIMENGINE_H

#include <QObject>
#include <qmqtt.h>
#include <imclient.h>
#include <imoptions.h>
#include <QString>
#include <imerror.h>

namespace im{
    /*
     * 本类为im客户端构建入口以及载入相关设置
     */
    class QIMengine : public QObject
    {
        Q_OBJECT
    public:
        //构造方法
        //需传入客户端id
        QIMengine(const QString& id);
        //连接服务器
        //需要传入服务器地址
        //需要传入连接端口
        ImClient* loginBroker(const QString& address, unsigned short port);
        //需要额外传入登陆名和登陆密码
        ImClient* loginBroker(const QString& address, unsigned short port,
                              const QString& username, const QByteArray& password);
        //修改连接配置
        static ImOptions& startOptions();
        //获取客户端指针
        //如果未进行loginBroker则返回nullptr;
        ImClient* getClient();
        //清除客户端client_ptr
        void clear();
    signals:
        //连接到Broker成功时发出信号
        void success();
        //取消连接成功时发出信号
        void disconnected();
        //发生错误时发出信号
        //error为发生错误的枚举量
        void error(const im::ImError& error);
        //发送信息成功时发出信号
        //msg为发送的信息
        //msgId为发送信息的id
        void delivered(const im::ImMessage& msg, unsigned short id = 0);
        //收到消息时发出信号
        //msg为收到的消息
        void received(const im::ImMessage& msg);
        //添加成功时发出信号
        //type为添加的Topic类型
        //targetId为添加的目标id
        void add(const im::TopicType type, const QString& targetId);
        //删除成功时发出信号
        //type为删除的Topic类型
        //targetId为删除的目标id
        void dele(const im::TopicType type, const QString& targetId);
        //心跳响应时发送信号
        void pingresp();
    private slots:
        void OnSuccess();
        void onDisconnected();
        void onError(const QMQTT::ClientError error);
        void onSubscribed(const QString& topic);
        void onUnsubscribed(const QString& topic);
        void onPublished(const QMQTT::Message& message, unsigned short msgid = 0);
        void onReceived(const QMQTT::Message& message);
    private:
        //全局连接配置
        static ImOptions options;
        //指向客户端指针
        ImClient* client_ptr;
        //连接服务器地址
        QString address;
        //连接端口
        unsigned short port;
        //客户端id
        QString id;
    };
}


#endif // QIMENGINE_H
