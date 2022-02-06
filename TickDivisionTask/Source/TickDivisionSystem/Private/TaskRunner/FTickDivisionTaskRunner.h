#pragma once

#include "TickDivisionDefine.h"

class ITickDivisionTask;

class FTickDivisionTaskRunner
{
public:
	FTickDivisionTaskRunner(float InLimitTime, TArray<TSharedPtr<ITickDivisionTask>>& InTaskContainer, FTickDivisionSystemDelegate& InDelegate);
	virtual ~FTickDivisionTaskRunner() = default;
	
	void Run();

protected:
	virtual bool IsRemainLimitTime() const;
	virtual bool IsOverLimitTime() const;
	
private:
	void RunTask(TSharedPtr<ITickDivisionTask> InTask);
	float GetLimitTime() const;
	void MinusLimitTime(float InMinusTime);
	void OnTaskEndEvent(TSharedPtr<ITickDivisionTask>, ETickDivisionTaskStatus InTaskStatus);
	
private:
	int32 m_Index;
	float m_LimitTime;
	TArray<TSharedPtr<ITickDivisionTask>>& m_TaskContainer;
	FTickDivisionSystemDelegate& m_Delegate;
};

class FTickDivisionTaskUnlimitRunner final : public FTickDivisionTaskRunner
{
public:
	FTickDivisionTaskUnlimitRunner(TArray<TSharedPtr<ITickDivisionTask>>& InTaskContainer, FTickDivisionSystemDelegate& InDelegate);
	
protected:
	virtual bool IsRemainLimitTime() const override;
	virtual bool IsOverLimitTime() const override;
};
