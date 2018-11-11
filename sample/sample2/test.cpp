#include "test.h"

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
