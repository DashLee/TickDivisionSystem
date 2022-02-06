#include "FTickDivisionTaskRunner.h"

#include "TickDivisionDefine.h"
#include "Interface/TickDivisionTaskInterface.h"

FTickDivisionTaskRunner::FTickDivisionTaskRunner(float InLimitTime, TArray<TSharedPtr<ITickDivisionTask>>& InTaskContainer, FTickDivisionSystemDelegate& InDelegate)
	: m_Index(0)
	, m_LimitTime(InLimitTime)
	, m_TaskContainer(InTaskContainer)
	, m_Delegate(InDelegate)
{
}

void FTickDivisionTaskRunner::Run()
{
	int32 LocalLoopCount = m_TaskContainer.Num();
	for(m_Index = 0 ; m_Index < LocalLoopCount ; ++m_Index)
	{
		TSharedPtr<ITickDivisionTask> LocalTask = m_TaskContainer[m_Index]; 
		RunTask(LocalTask);

		if(IsOverLimitTime())
			break;
	}
}

bool FTickDivisionTaskRunner::IsRemainLimitTime() const
{
	return m_LimitTime > 0.0f;
}

bool FTickDivisionTaskRunner::IsOverLimitTime() const
{
	return m_LimitTime <= 0.0f;
}

void FTickDivisionTaskRunner::RunTask(TSharedPtr<ITickDivisionTask> InTask)
{
	if(false == InTask.IsValid())
		return;

	do
	{
		double LocalTaskStartTime = FPlatformTime::Seconds();

		FTickDivisionTaskStatus LocalResultStatus = InTask->Tick(GetLimitTime());

		const double LocalTaskEllapsedTime = FPlatformTime::Seconds() - LocalTaskStartTime;
		MinusLimitTime(static_cast<float>(LocalTaskEllapsedTime));
		
		if(LocalResultStatus.IsWaiting())
			break;
		
		if(LocalResultStatus.IsEndTask())
		{
			OnTaskEndEvent(InTask, LocalResultStatus);
			break;
		}
		
	}while(IsRemainLimitTime());
}

float FTickDivisionTaskRunner::GetLimitTime() const
{
	return m_LimitTime;
}

void FTickDivisionTaskRunner::MinusLimitTime(float InMinusTime)
{
	m_LimitTime -= InMinusTime;
}

void FTickDivisionTaskRunner::OnTaskEndEvent(TSharedPtr<ITickDivisionTask> InTask, ETickDivisionTaskStatus InTaskStatus)
{
	m_Delegate.ExecuteIfBound(InTaskStatus, InTask);
	m_TaskContainer.RemoveSingle(InTask);
	--m_Index;
}

FTickDivisionTaskUnlimitRunner::FTickDivisionTaskUnlimitRunner(TArray<TSharedPtr<ITickDivisionTask>>& InTaskContainer, FTickDivisionSystemDelegate& InDelegate)
	: FTickDivisionTaskRunner(0.0f, InTaskContainer, InDelegate)
{
}

bool FTickDivisionTaskUnlimitRunner::IsRemainLimitTime() const
{
	return true;
}

bool FTickDivisionTaskUnlimitRunner::IsOverLimitTime() const
{
	return false;
}
