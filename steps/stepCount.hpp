#pragma once

#include "../framework/stepInterface.hpp"

class StepCount : public StepInterface
{
    Q_OBJECT
public:
    StepCount(int count) : m_count(count) {}

    RESULT exe() {
        printf("      StepCount\n");
        if (0 < --m_count) return NEXT; 
        return END;
    }

public:
    int m_count;
};
