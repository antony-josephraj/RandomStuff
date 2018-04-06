#pragma once
#include "IOptimizedCollection.h"

#include <string>
#include <map>
#include <vector>
#include <unordered_map>


class OptimizedCollectionForProduct : public IOptimizedCollection
{
public:

	OptimizedCollectionForProduct();

	~OptimizedCollectionForProduct();

	virtual void LoadTickData(std::string strSymbolFile);

	virtual void Print(uint64_t nStart, uint64_t nEnd, std::string strSymbol);

	virtual void Product(uint64_t nStart, uint64_t nEnd, std::string strSymbol, std::string strField1, std::string strField2);

private:

	//             string => symbol;                  string => FieldNames    uint64_t => times     Float => Value
	std::unordered_map<std::string, std::unordered_map< std::string, std::map<uint64_t, float>>> mapTickCollection;
};