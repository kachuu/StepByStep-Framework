#pragma once

#include <QSharedPointer>
#include <QList>
#include <QObject>
#include <QByteArray>

class StepInterface;
typedef QSharedPointer<StepInterface> StepPtr;
typedef QList<StepPtr> StepList;

class StepInterface : public QObject
{
    Q_OBJECT
public:
    typedef enum {
        NEXT = 1,
        WAIT = 0,
        END  = -1,
    } RESULT;//step result, different values can represent different states

    StepInterface() : m_stepIndex(0) {}
    virtual ~StepInterface() {}
    virtual RESULT exe() {return WAIT;}
    virtual RESULT exe(QByteArray &byteArray) {return WAIT;}

signals:
    void sig_startup(StepInterface *p);
    void sig_failed(StepInterface *p);
    void sig_successful(StepInterface *p);

public slots:
    virtual void slt_startup(StepInterface *p) {}
    virtual void slt_failed(StepInterface *p) {}
    virtual void slt_successful(StepInterface *p) {}

public:
    StepList m_stepList;//list of steps
    int m_stepIndex;//e.g. step to take now
};
