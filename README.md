​	QImEngine是基于QMQTT库快速构建im客户端的QT库，**仅可build by GUN/g++，如果采用MingGW or MSVC build 可能会失败**。

    [了解QMQTT]: https://github.com/emqtt/qmqtt



## 使用

------

首先请导入生成的QImEngine.a静态库

在生成的QTpro文件中加入**QT += network**

Quick start :

```c++
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //Quick start
    //传入客户端id
    im::QIMengine engine("myClient");
    //连接
    im::ImClient* client_ptr = engine.loginBroker("127.0.0.1",1883);
    //发送
    im::ImMessage msg(im::USR,"otherClient",true//可见消息
                                       ,im::STR//字符串消息
                                       ,client_ptr->id(),"hello world");
    client_ptr->send(msg);
    //结束
    engine.clear();
    return a.exec();
}
```

No ssl example:

```c++
Test::Test(const QString& id, QObject *parent) : QObject(parent)
{
    im::QIMengine::startOptions()
            .setOffLineContext("logout")
            .setAutoReconnect(true)
            .setReconnectIntervalTime(10)
            .endOptions();
    engine_ptr = new im::QIMengine(id);
    connect(engine_ptr,SIGNAL(success()),this,SLOT(OnSuccess()));
    connect(engine_ptr,SIGNAL(error(im::ImError)),this,SLOT(OnError(im::ImError)));
    connect(engine_ptr,SIGNAL(delivered(im::ImMessage,unsigned short)),
            this,SLOT(OnDelivered(im::ImMessage)));
    connect(engine_ptr,SIGNAL(received(im::ImMessage)),this,SLOT(OnReceived(im::ImMessage)));
    engine_ptr->loginBroker("127.0.0.1",1883);
}

void Test::OnSuccess()
{
    qDebug() << "login";
    im::ImClient* client_ptr = engine_ptr->getClient();
    im::ImMessage msg(im::USR,"otherClient",true,im::STR,client_ptr->id(),"hello world");
    client_ptr->send(msg);
}

void Test::OnError(const im::ImError &error)
{
    qDebug() << "error:" << error.toString();
}

void Test::OnDelivered(const im::ImMessage &msg)
{
    qDebug() << "msg:" << msg.getContext();
}

void Test::OnReceived(const im::ImMessage &msg)
{
    qDebug() << "id" << msg.getSendId() << "context:" << msg.getContext();
}
```

​	

Ssl example:

```c++
Test::Test(const QString& id, QObject *parent) : QObject(parent)
{
    //ssl配置
    QSslSocket ssl_socket;
    ssl_socket.setPrivateKey("/home/MqttSSL/AliMqtt/client.key");
    ssl_socket.setLocalCertificate("/home/MqttSSL/AliMqtt/client.crt");
    QSslConfiguration ssl_config;
    ssl_config.setCaCertificates(QSslCertificate::fromPath("/home/MqttSSL/AliMqtt/ca.crt"));
    ssl_config.setPrivateKey(ssl_socket.privateKey());
    ssl_config.setLocalCertificate(ssl_socket.localCertificate());

    im::QIMengine::startOptions()
            .setOffLineContext("logout")
            .setAutoReconnect(true)
            .setReconnectIntervalTime(10)
            //使用ssl
            .setUseSSL(true)
            //载入配置
            .setSSLConfig(ssl_config)
            .endOptions();
    engine_ptr = new im::QIMengine(id);
    connect(engine_ptr,SIGNAL(success()),this,SLOT(OnSuccess()));
    connect(engine_ptr,SIGNAL(error(im::ImError)),this,SLOT(OnError(im::ImError)));
    connect(engine_ptr,SIGNAL(delivered(im::ImMessage,unsigned short)),
            this,SLOT(OnDelivered(im::ImMessage)));
    connect(engine_ptr,SIGNAL(received(im::ImMessage)),this,SLOT(OnReceived(im::ImMessage)));
    //载入用户名和密码
    engine_ptr->loginBroker("127.0.0.1",1883,"你的用户名",QString("你的密码").toUtf8());
}

void Test::OnSuccess()
{
    qDebug() << "login";
    im::ImClient* client_ptr = engine_ptr->getClient();
    im::ImMessage msg(im::USR,"otherClient",true,im::STR,client_ptr->id(),"hello world");
    client_ptr->send(msg);
}

void Test::OnError(const im::ImError &error)
{
    qDebug() << "error:" << error.toString();
}

void Test::OnDelivered(const im::ImMessage &msg)
{
    qDebug() << "msg:" << msg.getContext();
}

void Test::OnReceived(const im::ImMessage &msg)
{
    qDebug() << "id" << msg.getSendId() << "context:" << msg.getContext();
}
```



Options:

```c++
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
```



## Signals

------

```c++
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
```

