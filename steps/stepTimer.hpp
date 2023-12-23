#pragma once

#include "../framework/stepInterface.hpp"
#include <QTimer>

class StepTimer : public StepInterface
{
    Q_OBJECT
public:
    StepTimer(int ms) : m_ms(ms), m_timer(this) {
        m_timer.setSingleShot(true);
        connect(&m_timer, SIGNAL(timeout()), this, SLOT(slt_timeout()));
    }

    RESULT exe() {
        m_timer.start(m_ms);return WAIT;
    }

public slots:
    void slt_timeout() {
        printf("      StepTimer\n");
        emit sig_successful(this);
    }

public:
    int m_ms;
    QTimer m_timer;
};
