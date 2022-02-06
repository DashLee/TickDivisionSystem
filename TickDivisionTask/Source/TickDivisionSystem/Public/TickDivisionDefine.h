#pragma once

#define PURE =0

enum class ETickDivisionTaskStatus
{
	None = 0,

	Tasking,
	Waiting,
	Succeed,
	Failed,
	
	Max
};

class FTickDivisionTaskStatus
{
public:
	FTickDivisionTaskStatus(const ETickDivisionTaskStatus InStatus)
		: m_Status(InStatus)
	{
		
	}

	bool IsWaiting() const { return m_Status == ETickDivisionTaskStatus::Waiting; }
	bool IsEndTask() const { return m_Status == ETickDivisionTaskStatus::Succeed || m_Status == ETickDivisionTaskStatus::Failed; }

	operator ETickDivisionTaskStatus() const
	{
		return m_Status;
	}

private:
	const ETickDivisionTaskStatus m_Status;
};

class ITickDivisionTask;
DECLARE_DELEGATE_TwoParams(FTickDivisionSystemDelegate, ETickDivisionTaskStatus, TSharedPtr<ITickDivisionTask>)
