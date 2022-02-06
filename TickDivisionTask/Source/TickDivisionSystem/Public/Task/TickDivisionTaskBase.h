#pragma once
#include "Interface/TickDivisionTaskInterface.h"

class TICKDIVISIONSYSTEM_API FTickDivisionTaskBase : public ITickDivisionTask
{
public:
	FTickDivisionTaskBase();
	
protected:
	// Begin ITickDivisionTask Interface
	virtual void Succeed() override;
	virtual void Failed() override;
	// ~~End ITickDivisionTask Interface

private:
	ETickDivisionTaskStatus m_Status;
};
