

#include "TGCO.h"
#include <cstdlib>
#include "Utils.h"

TArray<int32> Utils::InitWhithoutDuplication(int32 iSize)
{
	TArray<int32> Result = TArray<int32>();
	for (int i = 0; i < iSize; ++i)
	{
		Result.Add(i);
	}
	return Result;
}

void Utils::Blend(TArray<int32> Array)
{
	int nbDigged = 0;
	int temp = 0;

	for (int i = 0; i < Array.Num(); ++i)
	{
		nbDigged = static_cast<int>((rand() / static_cast<float>(RAND_MAX)) * Array.Num());
		// Exchange case
		temp = Array[i];
		Array[i] = Array[nbDigged];
		Array[nbDigged] = temp;
	}
}
