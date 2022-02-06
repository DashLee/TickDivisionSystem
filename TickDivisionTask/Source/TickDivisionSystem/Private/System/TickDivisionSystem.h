#pragma once

#include "Interface/TickDivisionSystemInterface.h"

class FTickDivisionSystem : public ITickDivisionSystem
{
protected:
	// Begin ITickDivisionSystem Interface
	virtual void SetDelegate(FTickDivisionSystemDelegate InDelegate) override;
	virtual void DeleteDelegate() override;
	virtual void Shutdown() override;

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual void Tick(float InTimeLimit) override;

	virtual void AddTask(TSharedPtr<ITickDivisionTask> InTask) override;
	virtual bool RemoveTask(TSharedPtr<ITickDivisionTask> InTask) override;
	virtual void Flush() override;
	virtual void ClearTask() override;
	
	virtual void ExecuteBound(const ETickDivisionTaskStatus& InType, TSharedPtr<ITickDivisionTask> InTask) override;
	// ~~End ITickDivisionSystem Interface

private:
	FTickDivisionSystemDelegate m_Delegate;
	TArray<TSharedPtr<ITickDivisionTask>> m_TaskContainer;
};
