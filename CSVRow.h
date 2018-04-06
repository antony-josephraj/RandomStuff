#pragma once
#pragma warning (disable:4251)

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>


//Helper class to parse the csv data ...
class CSVRow
{
public:
	std::string const& operator[](std::size_t index) const
	{
		return m_vecData[index];
	}

	std::size_t size() const
	{
		return m_vecData.size();
	}

	void readNextRow(std::istream& str)
	{
		std::string         line;
		std::getline(str, line);

		std::stringstream   lineStream(line);
		std::string         aColumn;

		m_vecData.clear();

		while (std::getline(lineStream, aColumn, ','))
		{
			m_vecData.push_back(aColumn);
		}
	}

private:
	std::vector<std::string>    m_vecData;
};

std::istream& operator>>(std::istream& inStream, CSVRow& data);