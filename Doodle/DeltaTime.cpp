#include "DeltaTime.h"

unsigned int DeltaTime::_deltaTick = 0;
unsigned int DeltaTime::_previousTick = 0;

void DeltaTime::Init(unsigned int currentTick)
{
	_previousTick = currentTick;
}
void DeltaTime::Update(unsigned int currentTick)
{
	_deltaTick = currentTick - _previousTick;
	_previousTick = currentTick;
}
 float DeltaTime::Get()
{
	return (float)_deltaTick / 1000;
}