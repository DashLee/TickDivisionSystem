#include "TickDivisionSystem.h"

#include "Interface/TickDivisionTaskInterface.h"
#include "TaskRunner/FTickDivisionTaskRunner.h"

TSharedPtr<ITickDivisionSystem> ITickDivisionSystem::Create()
{
	return MakeShareable(new FTickDivisionSystem);
}

void FTickDivisionSystem::SetDelegate(FTickDivisionSystemDelegate InDelegate)
{
	m_Delegate = InDelegate;
}

void FTickDivisionSystem::DeleteDelegate()
{
	m_Delegate.Unbind();
}

void FTickDivisionSystem::Shutdown()
{
	// to do release process
	DeleteDelegate();
	m_TaskContainer.Reset();
}

void FTickDivisionSystem::AddReferencedObjects(FReferenceCollector& Collector)
{
	for(TSharedPtr<ITickDivisionTask> Task : m_TaskContainer)
		Task->AddReferencedObjects(Collector);
}

void FTickDivisionSystem::Tick(float InTimeLimit)
{
	FTickDivisionTaskRunner(InTimeLimit, m_TaskContainer, m_Delegate).Run();
}

void FTickDivisionSystem::AddTask(TSharedPtr<ITickDivisionTask> InTask)
{
	check (InTask.IsValid() == true);
	check (m_TaskContainer.Contains(InTask) == false);

	m_TaskContainer.AddUnique(InTask);
}

bool FTickDivisionSystem::RemoveTask(TSharedPtr<ITickDivisionTask> InTask)
{
	return m_TaskContainer.RemoveSingle(InTask) > 0 ? true : false;
}

void FTickDivisionSystem::Flush()
{
	FTickDivisionTaskUnlimitRunner(m_TaskContainer, m_Delegate).Run();
}

void FTickDivisionSystem::ClearTask()
{
	if(m_TaskContainer.Num() > 0)
		m_TaskContainer.Reset();
}

void FTickDivisionSystem::ExecuteBound(const ETickDivisionTaskStatus& InType, TSharedPtr<ITickDivisionTask> InTask)
{
	m_Delegate.ExecuteIfBound(InType, InTask);
}
