#include "immessage.h"
#include "imoptions.h"
#include <QJsonObject>
#include <QJsonDocument>

im::ImMessage::ImTopic::ImTopic()
{
}

im::ImMessage::ImTopic::ImTopic(const im::TopicType type, const QString &targetId)
{
    this->type = type;
    this->targetId = targetId;
}

void im::ImMessage::ImTopic::setTopicType(const im::TopicType type)
{
    this->type = type;
}

void im::ImMessage::ImTopic::setTargetId(const QString &targetId)
{
    this->targetId = targetId;
}

im::TopicType im::ImMessage::ImTopic::getTopicType() const
{
    return type;
}

QString im::ImMessage::ImTopic::getTargetId() const
{
    return targetId;
}

im::ImMessage::ImMessage(const im::TopicType type, const QString &targetId)
:QObject(nullptr)
{
    topic.setTopicType(type);
    topic.setTargetId(targetId);
}

im::ImMessage::ImMessage(const im::TopicType type1, const QString &targetId,
                         bool visible, const im::ContextType type2,
                         const QString &sendId, const QString &context)
:QObject(nullptr)
{
    topic.setTopicType(type1);
    topic.setTargetId(targetId);
    this->visible = visible;
    this->type = type2;
    this->sendId = sendId;
    this->context = context;
}

im::ImMessage::ImMessage(const im::ImMessage &msg)
: QObject(nullptr)
{
    this->msgid = msg.msgid;
    this->visible = msg.visible;
    this->type = msg.type;
    this->sendId = msg.sendId;
    this->context = msg.context;
    this->topic = msg.topic;
}

unsigned short im::ImMessage::getMsgId() const
{
    return msgid;
}

bool im::ImMessage::isVisible() const
{
    return visible;
}

im::ContextType im::ImMessage::getContextType() const
{
    return type;
}

QString im::ImMessage::getSendId() const
{
    return sendId;
}

QString im::ImMessage::getContext() const
{
    return context;
}

void im::ImMessage::setMsgId(unsigned short msgid)
{
    this->msgid = msgid;
}

void im::ImMessage::setVisible(bool visible)
{
    this->visible = visible;
}

void im::ImMessage::setContextType(const im::ContextType type)
{
    this->type = type;
}

void im::ImMessage::setContextType(const int type)
{
    switch(type){
    case im::IMG :{
        this->type = im::IMG;
        break;
    }
    case im::STR :{
        this->type = im::STR;
    }
    }
}

void im::ImMessage::setSendId(const QString &sendId)
{
    this->sendId = sendId;
}

void im::ImMessage::setContext(const QString &context)
{
    this->context = context;
}

QString im::ImMessage::build()
{
    QString topic_str;

    switch(topic.getTopicType()){
    case im::SYS :{
        topic_str = "SYS/";
        break;
    }
    case im::USR :{
        topic_str = "USR/";
        break;
    }
    case im::GRO :{
        topic_str = "GRO/";
        break;
    }
    }

    topic_str += topic.getTargetId();
    return topic_str;
}

QString im::ImMessage::specbuild()
{
    QString topic_str = this->build();

    topic_str += im::SPEC;
    return topic_str;
}

QMQTT::Message im::ImMessage::toQMqtt()
{
    QMQTT::Message msg;
    msg.setId(this->getMsgId());
    msg.setQos(im::QOS);
    msg.setDup(false);
    msg.setRetain(false);
    msg.setTopic(this->build());
    msg.setPayload(this->make());
    return msg;
}

void im::ImMessage::toIm(const QMQTT::Message &message)
{
    TopicType type;
    QString targetId;
    ImMessage::fix(type,targetId,message.topic());
    topic.setTopicType(type);
    topic.setTargetId(targetId);

    this->setMsgId(message.id());
    this->form(message.payload());
}

void im::ImMessage::fix(im::TopicType &type, QString &targetId, const QString &topic)
{
    QStringList sections = topic.split('/');
    QString type_str = sections.at(0).trimmed();
    if(type_str == "SYS"){
        type = im::SYS;
        targetId = "0";
        return;
    }else if(type_str == "USR"){
        type = im::USR;
        targetId = sections.at(1).trimmed();
        return;
    }else if(type_str == "GRO"){
        type = im::GRO;
        targetId = sections.at(1).trimmed();
    }
}

void im::ImMessage::form(const QByteArray &payload)
{
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(payload, &jsonError);
    if(jsonError.error == QJsonParseError::NoError){
        QString str(document.toJson());
        if(document.isObject()){
            QJsonObject object = document.object();
            this->setVisible(object.value("isVisible").toBool(true));
            this->setContextType(object.value("Context").toInt(1));
            this->setSendId(object.value("SendId").toString("0"));
            this->setContext(object.value("Context").toString(""));
        }else{
            ImError imerror(jsonError);
            qDebug() << "error";
            emit this->error(imerror);
        }
    }
}

QByteArray im::ImMessage::make()
{
    QJsonObject json;
    json.insert("IsVisible", this->isVisible());
    json.insert("ContextType", this->getContextType());
    json.insert("SendId", this->getSendId());
    json.insert("Context", this->getContext());

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.
            toJson(QJsonDocument::Compact);

    return byteArray;
}
