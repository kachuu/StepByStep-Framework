#pragma once

#include "../framework/stepInterface.hpp"
#include <QDataStream>
#include <QIODevice>

class StepHandle2 : public StepInterface
{
    Q_OBJECT
public:
    RESULT exe(QByteArray &byteArray) {
        QDataStream ds(&byteArray, QIODevice::ReadOnly);
        QString str;
        ds >> str;
        printf("    StepHandle2:%s\n", str.toStdString().c_str());
        return loop();
    }

    RESULT loop() {
        while (m_stepIndex < m_stepList.count()) {
            RESULT res = m_stepList[m_stepIndex]->exe();
            if (NEXT == res && 0 == m_stepIndex) {//step 1 return NEXT
                m_stepIndex += 1;continue;//sequentially execute next step
            } else
            if (NEXT == res && 2 == m_stepIndex) {//step 3 (stepCount) return NEXT
                m_stepIndex = 0;continue;//counter for (stepCount) has not been reset to zero, re-run step list
            } else
            if (END == res) {//step 3 (stepCount) return END
                emit sig_successful(this);break;//send notifications to outside, similar to callback
            } else break;//stepTimer return WAIT, no need to proceed to next step
        } return WAIT;
    }

public slots:
    void slt_successful(StepInterface *p) {//stepTimer triggers timeout event
        m_stepIndex += 1;//prepare to execute next step
        loop();
    }
};
