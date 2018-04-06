#pragma once
#include <string>

class IOptimizedCollection
{
public:

	IOptimizedCollection() {}

	virtual ~IOptimizedCollection() {}

	virtual void LoadTickData(std::string strSymbolFile) = 0;

	virtual void Print(uint64_t nStart, uint64_t nEnd, std::string strSymbol) = 0;

	virtual void Product(uint64_t nStart, uint64_t nEnd, std::string strSymbol, std::string strField1, std::string strField2) = 0;
};