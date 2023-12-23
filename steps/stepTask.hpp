#pragma once

#include "../framework/stepInterface.hpp"

class StepTask : public StepInterface
{
    Q_OBJECT
public:
    StepTask(int id) : m_id(id) {}

    RESULT exe() {
        if (4 == m_id) printf("      StepTask id = %d\n", m_id);
        else printf("    StepTask id = %d\n", m_id);
        return NEXT;
    }

public:
    int m_id;
};
