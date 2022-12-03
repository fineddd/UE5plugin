#include "SGTypes.h"


DEFINE_LOG_CATEGORY(SGLog);

int64_t SGToolFun::GetNowMilTimeStamp()
{
	return FDateTime::Now().ToUnixTimestamp() * 1000 + FDateTime::Now().GetMillisecond();
}