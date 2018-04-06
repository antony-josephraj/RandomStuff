#include "OptimizedCollectionForPrint.h"
#include <iostream>
#include <fstream>
#include <iomanip>

#include "CSVRow.h"

OptimizedCollectionForPrint::OptimizedCollectionForPrint()
{
}

OptimizedCollectionForPrint::~OptimizedCollectionForPrint()
{
}

void OptimizedCollectionForPrint::LoadTickData(std::string strSymbolFile)
{
	std::ifstream ifsTickerFile(strSymbolFile.c_str());	
	if (!ifsTickerFile.is_open())
	{
		std::cout << "Cannot Open file [" << strSymbolFile << "]" << std::endl;
		return;
	}

	CSVRow aRow;

	uint64_t ulTickTime = 0;
	std::string strSymbol;
	size_t szRemFields = 0;

	while (ifsTickerFile >> aRow)
	{
		ulTickTime = std::strtoull(aRow[0].c_str(), 0, 10); //column 0 is time
		strSymbol = aRow[1]; // column 1 is Symbol

		szRemFields = aRow.size(); //excluding the first two fields in the row ..
		std::vector<FieldInfo> vecFieldInfo;
		for (int i = 2; i < szRemFields; ++i)
		{
			FieldInfo aFieldInfo;
			aFieldInfo.strFieldName = aRow[i]; 
			aFieldInfo.fValue = std::strtof(aRow[++i].c_str(),0);
			vecFieldInfo.push_back(aFieldInfo);
		}

		auto iter = mapTickCollection.find(strSymbol);
		if (iter != mapTickCollection.end())
		{ //already exists
			iter->second[ulTickTime] = std::move(vecFieldInfo);
		}
		else
		{ //new symbol
			mapTickCollection[strSymbol][ulTickTime] = std::move(vecFieldInfo);
		}		
	}
}

void OptimizedCollectionForPrint::Print(uint64_t nStart, uint64_t nEnd, std::string strSymbol)
{
	auto iter = mapTickCollection.find(strSymbol);
	if (iter != mapTickCollection.end())
	{ 
		for (auto const& kv : iter->second)
		{
			if (kv.first >= nStart && kv.first <= nEnd)
			{
				for (auto const& FieldInfo : kv.second)
				{
					std::cout << FieldInfo.strFieldName << ":" << FieldInfo.fValue << " ";
				}
				std::cout << std::endl;
			}
		}
	}
}


void OptimizedCollectionForPrint::Product(uint64_t nStart, uint64_t nEnd, std::string strSymbol, std::string strField1, std::string strField2)
{
	float fVal1 = 0.0f;
	float fVal2 = 0.0f;
	float fSumVal = 0.0f;

	auto iter = mapTickCollection.find(strSymbol);
	if (iter != mapTickCollection.end())
	{
		for (auto const& kv : iter->second)
		{
			fVal1 = fVal2 = 0.0f;
			if (kv.first >= nStart && kv.first <= nEnd)
			{
				for (auto const& FieldInfo : kv.second)
				{
					if (FieldInfo.strFieldName == strField1)
					{
						fVal1 = FieldInfo.fValue;
					}
					else if (FieldInfo.strFieldName == strField2)
					{
						fVal2 = FieldInfo.fValue;
					}
					if (fVal1 && fVal2)
					{
						break;
					}
				}
				if (fVal1 && fVal2)
				{
					fSumVal += (fVal1 * fVal2);
				}
			}
		}
		if (fSumVal)
		{
			std::cout << std::setprecision(6) << fSumVal << std::endl;
		}
	}
}
