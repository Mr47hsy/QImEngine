#include "test.h"

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
