#include "TickDivisionTaskBase.h"

FTickDivisionTaskBase::FTickDivisionTaskBase()
	: m_Status(ETickDivisionTaskStatus::Tasking)
{
}

void FTickDivisionTaskBase::Succeed()
{
	m_Status = ETickDivisionTaskStatus::Succeed;
}

void FTickDivisionTaskBase::Failed()
{
	m_Status = ETickDivisionTaskStatus::Failed;
}
