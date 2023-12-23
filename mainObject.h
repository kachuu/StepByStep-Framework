#pragma once

#include <QObject>
#include <QTimer>
#include "./framework/stepInterface.hpp"

class MainObject : public QObject
{
    Q_OBJECT
public:
    MainObject();
    ~MainObject() {}
    StepPtr generateStepHandle1();
    StepPtr generateStepHandle2();

public slots:
    void slt_timeout();
    void slt_startup(StepInterface *p);
    void slt_failed(StepInterface *p);
    void slt_successful(StepInterface *p);

public:
    StepList m_taskList;
    QTimer m_timer;
};
