#ifndef IMERROR_H
#define IMERROR_H

#include <QString>
#include <qmqtt_client.h>
#include <QJsonParseError>

namespace im {
/*
 * 本类用于返回im连接过程中的错误
 */
class ImError
{
public:
    //需要传入clienterror枚举量
    ImError(QMQTT::ClientError error);
    //需要传入parse error枚举量
    ImError(QJsonParseError& error);
    //获取错误字符串信息
    QString toString() const;
    //获取错误类型
    QMQTT::ClientError getQMqttError() const;
    QJsonParseError::ParseError getJsonError() const;
private:
    QString error_str;
    QMQTT::ClientError QMQTTerror;
    QJsonParseError::ParseError JSONerror;
};
}

#endif // IMERROR_H
