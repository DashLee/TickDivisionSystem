#pragma once

#include "Interface/TickDivisionSystemInterface.h"

class FTickDivisionSystem : public ITickDivisionSystem
{
protected:
	// Begin ITickDivisionSystem Interface
	virtual void SetDelegate(FTickDivisionSystemDelegate InDelegate) override;
	virtual void DeleteDelegate() override;
	virtual void Shutdown() override;
	// ~~End ITickDivisionSystem Interface

private:
	FTickDivisionSystemDelegate m_Delegate;
};
