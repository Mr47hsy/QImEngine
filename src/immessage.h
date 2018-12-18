#ifndef IMMESSAGE_H
#define IMMESSAGE_H

#include <QObject>
#include <QString>
#include <qmqtt_message.h>
#include <imerror.h>

namespace im {

enum TopicType {
    //系统topic
    SYS=0,
    //个人topic
    USR,
    //群体topic
    GRO
};

enum ContextType {
    //图片
    IMG=0,
    //音频
    VOI,
    //字符串
    STR
};

/*
 * 本类用于构建消息体，以及解析收到的消息
 */
class ImMessage : public QObject
{
    Q_OBJECT
    /*
     * 本类用于构建发送的目标
     */
    private: class ImTopic
    {
    public:
        ImTopic();
        ImTopic(const TopicType type, const QString& targetId);
        //设置目标类型
        void setTopicType(const TopicType type);
        //设置目标id
        void setTargetId(const QString& targetId);
        //获取目标类型
        TopicType getTopicType() const;
        //获取目标id
        QString getTargetId() const;
    private:
        //目标类型
        TopicType type;
        //目标id
        QString targetId="0";
    };

public:
    /*
     * 需要传入目标的topic类型
     * 需要传入目标id
     */
    ImMessage(const TopicType type, const QString& targetId);
    /*
     * 需要传入目标topic类型
     * 需要传入目标id
     * 需要设定是否为可视消息,默认为true
     * 需要传入发送消息类型
     * 需要传入发送者id
     * 需要传入发送内容
     */
    ImMessage(const TopicType type1, const QString& targetId,
              bool visible, const ContextType type2,
              const QString& sendId, const QString& context, const QString& sendTime);
    ImMessage(const ImMessage& msg);
    //获取消息id
    unsigned short getMsgId() const;
    //获取可视设置
    bool isVisible() const;
    //获取发送信息类型
    ContextType getContextType() const;
    //获取发送者id
    QString getSendId() const;
    //获取发送内容
    QString getContext() const;
    //获取发送时间
    QString getSendTime() const;
    //设置消息id
    void setMsgId(unsigned short msgid);
    //设置可视设置
    void setVisible(bool visible);
    //设置发送信息类型
    void setContextType(const ContextType type);
    void setContextType(const int type);
    //设置发送者id
    void setSendId(const QString& sendId);
    //设置发送内容
    void setContext(const QString& context);
    //设置发送时间
    void setSendTime(const QString& sendTime);
    //生成topic
    QString build();
    //生成特殊topic
    QString  specbuild();
    //生成QMqtt Message
    QMQTT::Message toQMqtt();
    //生成ImMessage
    void toIm(const QMQTT::Message& message);
    //解析topic
    static void fix(TopicType& type, QString& targetId, const QString& topic);
signals:
    //发生错误时发送该信号
    //错误一般源于json的解析或生成过程
    void error(const im::ImError& error);
private slots:
    //解析json
    void form(const QByteArray& payload);
    //生成json
    QByteArray make();
private:
    //消息id
    //默认为0
    unsigned short msgid=0;
    //消息是否可显
    bool visible=true;
    //发送信息类型
    ContextType type;
    //发送者id
    QString sendId;
    //发送内容
    QString context;
    //发送时间
    QString sendTime;
    //topic
    ImTopic topic;
};
}


#endif // IMMESSAGE_H
