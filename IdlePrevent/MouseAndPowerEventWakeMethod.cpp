#include "StdAfx.h"
#include "MouseAndPowerEventWakeMethod.h"

MouseAndPowerEventWakeMethod::MouseAndPowerEventWakeMethod(void) {}

MouseAndPowerEventWakeMethod::~MouseAndPowerEventWakeMethod(void) {}

void MouseAndPowerEventWakeMethod::Wake()
{
	INPUT mouseInput[1];
	mouseInput[0].mi.dx = 0;
	mouseInput[0].mi.dy = 0;
	mouseInput[0].mi.mouseData = 0;
	mouseInput[0].mi.dwFlags = MOUSEEVENTF_MOVE;
	mouseInput[0].mi.time = 0;
	mouseInput[0].mi.dwExtraInfo = NULL;
	SendInput(1, mouseInput, sizeof(mouseInput));
	SetThreadExecutionState(ES_DISPLAY_REQUIRED);
}