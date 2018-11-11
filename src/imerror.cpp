#include "imerror.h"

im::ImError::ImError(QMQTT::ClientError error)
{
    this->QMQTTerror = error;
    switch(error){
    case QMQTT::UnknownError: {
        this->error_str = QString("UnknownError");
        break;
    }
    case QMQTT::SocketConnectionRefusedError: {
        this->error_str = QString("SocketConnectionRefusedError");
        break;
    }
    case QMQTT::SocketRemoteHostClosedError: {
        this->error_str = QString("SocketRemoteHostClosedError");
        break;
    }
    case QMQTT::MqttBadUserNameOrPasswordError: {
        this->error_str = QString("MqttBadUserNameOrPasswordError");
        break;
    }
    case QMQTT::MqttIdentifierRejectedError: {
        this->error_str = QString("MqttIdentifierRejectedError");
        break;
    }
    case QMQTT::MqttNoPingResponse: {
        this->error_str = QString("MqttNoPingResponse");
        break;
    }
    case QMQTT::MqttNotAuthorizedError: {
        this->error_str = QString("MqttNotAuthorizedError");
        break;
    }
    case QMQTT::MqttServerUnavailableError: {
        this->error_str = QString("MqttServerUnavailableError");
        break;
    }
    case QMQTT::MqttUnacceptableProtocolVersionError: {
        this->error_str = QString("MqttUnacceptableProtocolVersionError");
        break;
    }
    case QMQTT::SocketAccessError: {
        this->error_str = QString("SocketAccessError");
        break;
    }
    case QMQTT::SocketAddressInUseError: {
        this->error_str = QString("SocketAddressInUseError");
        break;
    }
    case QMQTT::SocketAddressNotAvailableError: {
        this->error_str = QString("SocketAddressNotAvailableError");
        break;
    }
    case QMQTT::SocketDatagramTooLargeError: {
        this->error_str = QString("SocketDatagramTooLargeError:");
        break;
    }
    case QMQTT::SocketHostNotFoundError: {
        this->error_str = QString("SocketHostNotFoundError");
        break;
    }
    case QMQTT::SocketNetworkError: {
        this->error_str = QString("SocketNetworkError");
        break;
    }
    case QMQTT::SocketOperationError: {
        this->error_str = QString("SocketOperationError");
        break;
    }
    case QMQTT::SocketProxyAuthenticationRequiredError: {
        this->error_str = QString("SocketProxyAuthenticationRequiredError");
        break;
    }
    case QMQTT::SocketProxyConnectionClosedError: {
        this->error_str = QString("SocketProxyConnectionClosedError");
        break;
    }
    case QMQTT::SocketProxyConnectionRefusedError: {
        this->error_str = QString("SocketProxyConnectionRefusedError");
        break;
    }
    case QMQTT::SocketProxyConnectionTimeoutError: {
        this->error_str = QString("SocketProxyConnectionTimeoutError");
        break;
    }
    case QMQTT::SocketProxyNotFoundError: {
        this->error_str = QString("SocketProxyNotFoundError");
        break;
    }
    case QMQTT::SocketProxyProtocolError: {
        this->error_str = QString("SocketProxyProtocolError");
        break;
    }
    case QMQTT::SocketResourceError: {
        this->error_str = QString("SocketResourceError");
        break;
    }
    case QMQTT::SocketSslHandshakeFailedError: {
        this->error_str = QString("SocketSslHandshakeFailedError");
        break;
    }
    case QMQTT::SocketSslInternalError: {
        this->error_str = QString("SocketSslInternalError");
        break;
    }
    case QMQTT::SocketSslInvalidUserDataError: {
        this->error_str = QString("SocketSslInvalidUserDataError");
        break;
    }
    case QMQTT::SocketTemporaryError: {
        this->error_str = QString("SocketTemporaryError");
        break;
    }
    case QMQTT::SocketTimeoutError: {
        this->error_str = QString("SocketTimeoutError");
        break;
    }
    case QMQTT::SocketUnfinishedSocketOperationError: {
        this->error_str = QString("SocketUnfinishedSocketOperationError");
        break;
    }
    case QMQTT::SocketUnsupportedSocketOperationError: {
        this->error_str = QString("SocketUnsupportedSocketOperationError");
        break;
    }
    }
}

im::ImError::ImError(QJsonParseError &error)
{
    this->JSONerror = error.error;
    this->error_str = error.errorString();
}

QString im::ImError::toString() const
{
    return error_str;
}

QMQTT::ClientError im::ImError::getQMqttError() const
{
    return QMQTTerror;
}

QJsonParseError::ParseError im::ImError::getJsonError() const
{
    return JSONerror;
}
