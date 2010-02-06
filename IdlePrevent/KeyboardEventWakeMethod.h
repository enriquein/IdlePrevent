#pragma once
#include "wakemethod.h"

class KeyboardEventWakeMethod : public WakeMethod
{
public:
    KeyboardEventWakeMethod(void);
    ~KeyboardEventWakeMethod(void);
    virtual void Wake();
};
