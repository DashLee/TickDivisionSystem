#pragma once

#define PURE =0

enum class ETickDivisionTaskStatus
{
	None = 0,

	Continue,
	Waiting,
	Succeed,
	Failed,
	
	Max
};

DECLARE_DELEGATE(FTickDivisionSystemDelegate)
