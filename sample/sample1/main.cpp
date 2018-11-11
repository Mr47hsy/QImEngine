#include <QCoreApplication>
#include "qimengine.h"

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
