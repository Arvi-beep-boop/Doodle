#pragma once
class DeltaTime
{
	static unsigned int _previousTick;
	static unsigned int _deltaTick;
	

public: 
	static void Init(unsigned int currentTick);
	static void Update(unsigned int currentTick);
	static float Get();
};

