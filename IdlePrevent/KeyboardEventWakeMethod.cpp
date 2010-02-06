#include "StdAfx.h"
#include "KeyboardEventWakeMethod.h"
 
KeyboardEventWakeMethod::KeyboardEventWakeMethod(void) {}

KeyboardEventWakeMethod::~KeyboardEventWakeMethod(void) {}

void KeyboardEventWakeMethod::Wake()
{
    keybd_event(VK_RSHIFT,0xB6, KEYEVENTF_KEYUP,  0);
}