#include "CSVRow.h"

//A global extractor to push a row\line from the file to the CSVRow object.
std::istream& operator>>(std::istream& inStream, CSVRow& data)
{
	data.readNextRow(inStream);
	return inStream;
}