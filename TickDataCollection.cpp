#include "TickDataCollection.h"


TickDataCollection::TickDataCollection(std::string strOptimizerType)
{
	if (strOptimizerType == "OptimizePrint")
	{
		uptrTickCollection = std::unique_ptr<OptimizedCollectionForPrint>(new OptimizedCollectionForPrint());
	}
	else if (strOptimizerType == "OptimizeProduct")
	{
		uptrTickCollection = std::unique_ptr<OptimizedCollectionForProduct>(new OptimizedCollectionForProduct());
	}
}

void TickDataCollection::LoadTickData(std::string strSymbolFile)
{
	uptrTickCollection->LoadTickData(strSymbolFile);
}

void TickDataCollection::Print(uint64_t nStart, uint64_t nEnd, std::string strSymbol)
{
	uptrTickCollection->Print(nStart, nEnd, strSymbol);
}

void TickDataCollection::Product(uint64_t nStart, uint64_t nEnd, std::string strSymbol, std::string strField1, std::string strField2)
{
	uptrTickCollection->Product(nStart, nEnd, strSymbol, strField1, strField2);
}
