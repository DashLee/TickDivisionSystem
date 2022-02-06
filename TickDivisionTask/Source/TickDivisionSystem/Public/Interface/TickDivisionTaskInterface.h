#pragma once

#include "TickDivisionDefine.h"

class TICKDIVISIONSYSTEM_API ITickDivisionTask
{
public:
	virtual ~ITickDivisionTask() = default;

	virtual void AddReferencedObjects(FReferenceCollector& OutCollector) {}

	virtual ETickDivisionTaskStatus Tick(float InTimeLimit) PURE;

	virtual void NextStep() PURE;
	virtual void Succeed() PURE;
	virtual void Failed() PURE;
};
