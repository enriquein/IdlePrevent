#pragma once
#include "wakemethod.h"

class MouseAndPowerEventWakeMethod : public WakeMethod
{
public:
    MouseAndPowerEventWakeMethod(void);
    ~MouseAndPowerEventWakeMethod(void);
    virtual void Wake();
};
