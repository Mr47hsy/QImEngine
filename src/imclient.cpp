#include "imclient.h"
#include <QHostAddress>

im::ImClient::ImClient(const QString &id, const QString& address,
                       unsigned short port, const ImOptions& options)
{
    if(options.useSSL() == true){
        this->client = new QMQTT::Client(address, port, options.getSSLConfig());
    }else{
        QHostAddress host(address);
        this->client = new QMQTT::Client(host, port);
    }
    this->client->setClientId(id);

    this->client->setVersion(options.getMQTTVersion());
    this->client->setKeepAlive(options.getKeepAliveTime());
    this->client->setAutoReconnect(options.autoReconnect());
    this->client->setAutoReconnectInterval(options.getReconnectIntervalTime());
    this->client->setWillMessage(options.getOffLineContext().toUtf8());

    this->client->setCleanSession(false);
    this->client->setWillTopic("USR/" + id + im::SPEC);
    this->client->setWillRetain(false);
    this->client->setWillQos(im::QOS);
}

im::ImClient::ImClient(const QString &id, const QString &username,
                       const QByteArray &password, const QString &address,
                       unsigned short port, const im::ImOptions &options)
{
    ImClient(id, address, port, options);
    this->client->setUsername(username);
    this->client->setPassword(password);
}

im::ImClient::~ImClient()
{
    delete client;
}

QMQTT::Client *im::ImClient::getQMqttClient() const
{
    return client;
}

bool im::ImClient::connectionState() const
{
    return this->client->isConnectedToHost();
}

QString im::ImClient::id() const
{
    return this->client->clientId();
}

void im::ImClient::addTarget(const im::TopicType type, const QString &targetId)
{
    ImMessage msg(type, targetId);
    if(type == im::USR){
        this->client->subscribe(msg.specbuild(), im::QOS);
    }else if(type == im::GRO){
        this->client->subscribe(msg.build(), im::QOS);
    }
}

void im::ImClient::deleTarget(const im::TopicType type, const QString &targetId)
{
    ImMessage msg(type, targetId);
    if(type == im::USR){
        this->client->unsubscribe(msg.specbuild());
    }else if(type == im::GRO){
        this->client->unsubscribe(msg.build());
    }
}

void im::ImClient::send(ImMessage &msg)
{
    this->client->publish(msg.toQMqtt());
}

void im::ImClient::disConnect()
{
    this->client->disconnectFromHost();
}
