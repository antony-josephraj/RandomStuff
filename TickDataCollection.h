#pragma once
#include "IOptimizedCollection.h"
#include "OptimizedCollectionForPrint.h"
#include "OptimizedCollectionForProduct.h"

#include <string>
#include <memory>

class TickDataCollection
{
public:
	TickDataCollection(std::string strOptimizerType);
	~TickDataCollection() {}

	virtual void LoadTickData(std::string strSymbolFile);

	virtual void Print(uint64_t nStart, uint64_t nEnd, std::string strSymbol);

	virtual void Product(uint64_t nStart, uint64_t nEnd, std::string strSymbol, std::string strField1, std::string strField2);

private:
	//interface to the concrete optimized storages ..
	std::unique_ptr<IOptimizedCollection> uptrTickCollection;
};