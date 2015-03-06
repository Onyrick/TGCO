

#include "TGCO.h"
#include <ctime>
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

TArray<int32> Utils::CreateRandomArrayOfSolution(int32 iSize)
{
	TArray<int32> Result = TArray<int32>();
	srand(time(NULL));
	bool bAlreadyExist;
	bool bRetry = true;
	int iRandomNumber;

	for (int i = 0; i < iSize; ++i)
	{
		while (bRetry)
		{
			bAlreadyExist = false;
			iRandomNumber = rand() % (iSize+1);
			for (int j = 0; j < Result.Num(); ++j)
			{
				if (Result[j] == iRandomNumber)
				{
					bAlreadyExist = true;
				}
			}
			if (bAlreadyExist)
			{
				bRetry = true;
			}
			else
			{
				bRetry = false;
			}
		}
		Result.Add(iRandomNumber);
		bRetry = true;
	}
	return Result;
}
