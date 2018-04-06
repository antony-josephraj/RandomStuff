#include "OptimizedCollectionForProduct.h"
#include <iostream>
#include <fstream>
#include <iomanip>

#include "CSVRow.h"

OptimizedCollectionForProduct::OptimizedCollectionForProduct()
{
}

OptimizedCollectionForProduct::~OptimizedCollectionForProduct()
{
}

void OptimizedCollectionForProduct::LoadTickData(std::string strSymbolFile)
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
		ulTickTime = std::strtoull(aRow[0].c_str(), 0, 10); //time
		strSymbol = aRow[1]; //symbol

		szRemFields = aRow.size(); 
				
		auto iter = mapTickCollection.find(strSymbol);
		if (iter != mapTickCollection.end()) //duplicating the for loop logic because it's better than doing this check for every field ..
		{ //already exists
			for (int i = 2; i < szRemFields; ++i) //excluding the first two fields in the row ..
			{
				std::pair<uint64_t, float> FieldInfoPair(ulTickTime, std::strtof(aRow[i + 1].c_str(), 0));
				iter->second[aRow[i++]].insert(std::pair<uint64_t, float>(FieldInfoPair));
			}
		}
		else
		{ //new symbol
			for (int i = 2; i < szRemFields; ++i)
			{
				std::pair<uint64_t, float> FieldInfoPair (ulTickTime, std::strtof(aRow[i+1].c_str(), 0));
				mapTickCollection[strSymbol][aRow[i++]].insert(std::pair<uint64_t, float>(FieldInfoPair));
			}
		}
	}
}

void OptimizedCollectionForProduct::Print(uint64_t nStart, uint64_t nEnd, std::string strSymbol)
{
	auto iter = mapTickCollection.find(strSymbol);
	if (iter != mapTickCollection.end())
	{	
		std::unordered_map<std::string, std::map<uint64_t, float>>::iterator iterFields = iter->second.begin();
		while (iterFields != iter->second.end())
		{
			for (auto FieldInfo : iterFields->second)
			{
				if (FieldInfo.first >= nStart && FieldInfo.first <= nEnd)
				{
					//the print on the product optimized storage is a little goofy .. prints everything, but not in order
					std::cout << iterFields->first << ":" << FieldInfo.second << " "; 
				}
			}
			++iterFields;
		}
		std::cout << std::endl;
	}
}

void OptimizedCollectionForProduct::Product(uint64_t nStart, uint64_t nEnd, std::string strSymbol, std::string strField1, std::string strField2)
{
	float fVal1 = 0.0f;
	float fVal2 = 0.0f;
	float fSumVal = 0.0f;

	auto iter = mapTickCollection.find(strSymbol);
	if (iter != mapTickCollection.end())
	{
		std::unordered_map<std::string, std::map<uint64_t, float>>::iterator iterField1 = iter->second.find(strField1);
		std::unordered_map<std::string, std::map<uint64_t, float>>::iterator iterField2 = iter->second.find(strField2);
		
		if (iterField1 != iter->second.end())
		{
			for (auto FieldInfo : iterField1->second)
			{
				fVal1 = fVal2 = 0.0f;
				if (FieldInfo.first >= nStart && FieldInfo.first <= nEnd)
				{
					fVal1 = FieldInfo.second;

					//see if there is a corresponding tick for field2 ..
					if (iterField2 != iter->second.end())
					{
						std::map<uint64_t, float>::iterator iterField = iterField2->second.find(FieldInfo.first);
						if (iterField != iterField2->second.end())
						{//found a tick with the same timestamp
							fVal2 = iterField->second;
						}						
					}
					if (fVal1 && fVal2)
					{
						fSumVal += (fVal1 * fVal2);
					}
				}
			}
		}
		if (fSumVal)
		{
			std::cout << std::setprecision(6) << fSumVal << std::endl;
		}
	}
}
