#include "TickDivisionSystem.h"

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
	SetDelegate(nullptr);
}

void FTickDivisionSystem::Shutdown()
{
	// to do release process
	DeleteDelegate();
}
