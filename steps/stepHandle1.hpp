#pragma once

#include "../framework/stepInterface.hpp"
#include <QIODevice>

class StepHandle1 : public StepInterface
{
    Q_OBJECT
public:
    RESULT exe() {//starting point of step
        printf("  StepHandle1\n");
        return loop();
    }

    RESULT exe(QByteArray &byteArray) {//triggering point of step
        QDataStream ds(&byteArray, QIODevice::ReadOnly);
        QString str;
        ds >> str;
        printf("  StepHandle1:%s\n", str.toStdString().c_str());
        return m_stepList[++m_stepIndex]->exe(byteArray);//step 3 return WAIT, same this function return
    }

    RESULT loop() {
        while (m_stepIndex < m_stepList.count()) {
            RESULT res = m_stepList[m_stepIndex]->exe();
            if (NEXT == res && 1 == m_stepIndex) {//step 2 return NEXT
                emit sig_startup(this);return WAIT;//send notifications to outside, similar to callback
            } else
            if (WAIT == res) return WAIT;//step 3 (stepHandle2) return WAIT, waiting for event to return
            m_stepIndex += 1;//sequentially execute next step
        }
        emit sig_successful(this);return WAIT;//all steps have been completed, send notification outside
    }

public slots:
    void slt_successful(StepInterface *p) {//step 3 (stepHandle2) triggers sig_successful  
        m_stepIndex += 1;
        loop();
    }
};
