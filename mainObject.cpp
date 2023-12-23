#include "mainObject.h"
#include "./steps/resource.h"

MainObject::MainObject() :
    m_timer(this)
{
    printf("start >>>\n");

    m_timer.setSingleShot(true);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(slt_timeout()));

    m_taskList.append(generateStepHandle1());
    connect(&*m_taskList.last(), SIGNAL(sig_startup(StepInterface*)), this, SLOT(slt_startup(StepInterface*)));    
    connect(&*m_taskList.last(), SIGNAL(sig_failed(StepInterface*)), this, SLOT(slt_failed(StepInterface*)));
    connect(&*m_taskList.last(), SIGNAL(sig_successful(StepInterface*)), this, SLOT(slt_successful(StepInterface*)));
    m_taskList[0]->exe();
}

StepPtr MainObject::generateStepHandle1()
{
    StepPtr stepHandle1(StepPtr(new StepHandle1()));
    stepHandle1->m_stepList.append(StepPtr(new StepTask(1)));//step 1, NEXT
    stepHandle1->m_stepList.append(StepPtr(new StepTask(2)));//step 2, NEXT
    stepHandle1->m_stepList.append(generateStepHandle2());//step 3, WAIT/sig
    stepHandle1->m_stepList.append(StepPtr(new StepTask(3)));//step 4, NEXT

    for (int i = 0; i < stepHandle1->m_stepList.count(); ++i) {
        connect(&*stepHandle1->m_stepList[i], SIGNAL(sig_startup(StepInterface*)), &*stepHandle1, SLOT(slt_startup(StepInterface*)));
        connect(&*stepHandle1->m_stepList[i], SIGNAL(sig_failed(StepInterface*)), &*stepHandle1, SLOT(slt_failed(StepInterface*)));
        connect(&*stepHandle1->m_stepList[i], SIGNAL(sig_successful(StepInterface*)), &*stepHandle1, SLOT(slt_successful(StepInterface*)));
    }
    return stepHandle1;
}

StepPtr MainObject::generateStepHandle2()
{
    StepPtr stepHandle2(StepPtr(new StepHandle2()));
    stepHandle2->m_stepList.append(StepPtr(new StepTask(4)));//step 1, NEXT
    stepHandle2->m_stepList.append(StepPtr(new StepTimer(3000)));//step 2, WAIT/sig
    stepHandle2->m_stepList.append(StepPtr(new StepCount(3)));//step 3, NEXT/END

    for (int i = 0; i < stepHandle2->m_stepList.count(); ++i) {
        connect(&*stepHandle2->m_stepList[i], SIGNAL(sig_startup(StepInterface*)), &*stepHandle2, SLOT(slt_startup(StepInterface*)));
        connect(&*stepHandle2->m_stepList[i], SIGNAL(sig_failed(StepInterface*)), &*stepHandle2, SLOT(slt_failed(StepInterface*)));
        connect(&*stepHandle2->m_stepList[i], SIGNAL(sig_successful(StepInterface*)), &*stepHandle2, SLOT(slt_successful(StepInterface*)));
    }
    return stepHandle2;
}

void MainObject::slt_timeout()
{
    printf("slt_timeout >>>\n");
    if (0 == m_taskList.count()) return;
    QByteArray ba;
    QDataStream ds(&ba, QIODevice::WriteOnly);
    QString str("parameters...");
    ds << str;
    m_taskList[0]->exe(ba);
}

void MainObject::slt_startup(StepInterface *p)
{
    printf("slt_startup <<<\n");
    m_timer.start(3000);
}

void MainObject::slt_failed(StepInterface *p)
{
    m_taskList.clear();
}

void MainObject::slt_successful(StepInterface *p)
{
    printf("slt_successful <<<\n");
    m_taskList.clear();
}
