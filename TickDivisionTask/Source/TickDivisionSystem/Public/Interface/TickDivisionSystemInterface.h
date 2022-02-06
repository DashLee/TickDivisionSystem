#pragma once

#include "TickDivisionDefine.h"

class ITickDivisionSystem
{
public:
	virtual ~ITickDivisionSystem() = default;
	static TSharedPtr<ITickDivisionSystem> Create();

	virtual void SetDelegate(FTickDivisionSystemDelegate InDelegate) PURE;
	virtual void DeleteDelegate() PURE;
	virtual void Shutdown() PURE;
};
