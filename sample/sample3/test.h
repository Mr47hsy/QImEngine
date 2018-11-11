#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <qimengine.h>
#include <QSslSocket>

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(const QString& id,QObject *parent = nullptr);
    im::QIMengine* engine_ptr;
signals:

public slots:
    void OnSuccess();
    void OnError(const im::ImError& error);
    void OnDelivered(const im::ImMessage& msg);
    void OnReceived(const im::ImMessage& msg);
};

#endif // TEST_H
