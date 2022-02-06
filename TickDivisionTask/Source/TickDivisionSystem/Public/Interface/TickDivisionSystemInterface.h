#pragma once

#include "TickDivisionDefine.h"

class ITickDivisionTask;

class TICKDIVISIONSYSTEM_API ITickDivisionSystem
{
public:
	virtual ~ITickDivisionSystem() = default;
	static TSharedPtr<ITickDivisionSystem> Create();

	virtual void SetDelegate(FTickDivisionSystemDelegate InDelegate) PURE;
	virtual void DeleteDelegate() PURE;
	virtual void Shutdown() PURE;

	virtual void AddReferencedObjects(FReferenceCollector& Collector) PURE;
	virtual void Tick(float InTimeLimit) PURE;

	virtual void AddTask(TSharedPtr<ITickDivisionTask> InTask) PURE;
	virtual bool RemoveTask(TSharedPtr<ITickDivisionTask> InTask) PURE;
	virtual void Flush() PURE;
	virtual void ClearTask() PURE;
	
	virtual void ExecuteBound(const ETickDivisionTaskStatus& InType, TSharedPtr<ITickDivisionTask> InTask) PURE;
};
