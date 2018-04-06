#pragma once
#include "IOptimizedCollection.h"

#include <string>
#include <map>
#include <vector>
#include <unordered_map>

struct FieldInfo
{
	std::string strFieldName;
	float fValue;
};

class OptimizedCollectionForPrint : public IOptimizedCollection
{
public:

	OptimizedCollectionForPrint();

	~OptimizedCollectionForPrint();

	virtual void LoadTickData(std::string strSymbolFile);

	virtual void Print(uint64_t nStart, uint64_t nEnd, std::string strSymbol);

	virtual void Product(uint64_t nStart, uint64_t nEnd, std::string strSymbol, std::string strField1, std::string strField2);

private:

	//             string => symbol;          uint64_t => times       FieldInfo => struct
	std::unordered_map<std::string, std::map< uint64_t, std::vector<FieldInfo>>> mapTickCollection;
};