#include "qimengine.h"

im::ImOptions im::QIMengine::options;

im::QIMengine::QIMengine(const QString &id) :QObject(nullptr)
{
    this->id = id;
}

im::ImClient *im::QIMengine::loginBroker(const QString &address, unsigned short port)
{
    this->address = address;
    this->port = port;
    this->client_ptr = new ImClient(this->id, address, port, options);

    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(connected()), this, SLOT(OnSuccess()));
    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(error(QMQTT::ClientError)), this, SLOT(onError(QMQTT::ClientError)));
    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(subscribed(QString,quint8)), this, SLOT(onSubscribed(QString)));
    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(unsubscribed(QString)), this, SLOT(onUnsubscribed(QString)));
    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(published(QMQTT::Message,quint16)),
            this, SLOT(onPublished(QMQTT::Message,unsigned short)));
    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(received(QMQTT::Message)), this, SLOT(onReceived(QMQTT::Message)));
    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(pingresp()), this, SIGNAL(pingresp()));

    this->client_ptr->getQMqttClient()->connectToHost();
    return this->client_ptr;
}

im::ImClient *im::QIMengine::loginBroker(const QString &address, unsigned short port,
                                         const QString &username, const QByteArray &password)
{
    this->address = address;
    this->port = port;
    this->client_ptr = new ImClient(this->id, username, password, address, port, options);

    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(connected()), this, SLOT(OnLogSuccess()));
    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(error(QMQTT::ClientError)), this, SLOT(onError(QMQTT::ClientError)));
    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(subscribed(QString,quint8)), this, SLOT(onSubscribed(QString)));
    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(unsubscribed(QString)), this, SLOT(onUnsubscribed(QString)));
    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(published(QMQTT::Message,quint16)),
            this, SLOT(onPublished(QMQTT::Message,unsigned short)));
    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(received(QMQTT::Message)), this, SLOT(onReceived(QMQTT::Message)));
    connect(this->client_ptr->getQMqttClient(),
            SIGNAL(pingresp()), this, SIGNAL(pingresp()));

    this->client_ptr->getQMqttClient()->connectToHost();
    return this->client_ptr;
}

im::ImOptions &im::QIMengine::startOptions()
{
    return options;
}

im::ImClient *im::QIMengine::getClient()
{
    if(client_ptr == nullptr){
        return nullptr;
    }
    return client_ptr;
}

void im::QIMengine::clear()
{
    delete client_ptr;
}

void im::QIMengine::OnSuccess()
{
    client_ptr->getQMqttClient()->subscribe("SYS/#", im::QOS);
    QString topic = "USR/" + this->id;
    client_ptr->getQMqttClient()->subscribe(topic, im::QOS);

    emit success();
}

void im::QIMengine::onDisconnected()
{
    emit disconnected();
}

void im::QIMengine::onError(const QMQTT::ClientError error)
{
    ImError imerror(error);
    emit this->error(imerror);
}

void im::QIMengine::onSubscribed(const QString &topic)
{
    TopicType type;
    QString targetId;

    ImMessage::fix(type, targetId, topic);

    emit add(type, targetId);
}

void im::QIMengine::onUnsubscribed(const QString &topic)
{
    TopicType type;
    QString targetId;

    ImMessage::fix(type, targetId, topic);

    emit dele(type, targetId);
}

void im::QIMengine::onPublished(const QMQTT::Message &message, unsigned short msgid)
{
    TopicType type;
    QString targetId;
    QString topic = message.topic();

    ImMessage::fix(type, targetId, topic);

    ImMessage msg(type, targetId);
    msg.toIm(message);

    emit delivered(msg, msgid);
}

void im::QIMengine::onReceived(const QMQTT::Message &message)
{
    TopicType type;
    QString targetId;
    QString topic = message.topic();

    ImMessage::fix(type, targetId, topic);

    ImMessage msg(type, targetId);
    msg.toIm(message);
    //避免接受自己所发消息
    if(this->id == msg.getSendId()){
        return;
    }

    emit received(msg);
}
