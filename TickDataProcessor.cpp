// TickDataProcessor.cpp : Defines the entry point for the console application.
//

#include "TickDataProcessor.h"
#include "TickDataCollection.h"

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

int main(int argc, const char* argv[])
{
	std::string strOptimizerType = ParseOptions(argc, argv);

	//Collection object that inturn holds the reference to the data collections ..
	TickDataCollection objTickCollection(strOptimizerType);
	
	std::string strUserCommand;
	std::string strToken;
	std::vector<std::string> vecTokens;

	std::cout << "Press \"Ctrl + c\" to exit ... " << std::endl;
	while (1)
	{
		strUserCommand = "";
		std::getline(std::cin, strUserCommand);
		std::istringstream iss(strUserCommand);
		
		vecTokens.clear();
		while (std::getline(iss, strToken, ' '))
		{
			vecTokens.push_back(strToken);
		}

		if (vecTokens[0] == "tickerfile")
		{			
			objTickCollection.LoadTickData(vecTokens[1]);
		}
		else if (vecTokens[0] == "print")
		{
			objTickCollection.Print(std::strtoull(vecTokens[1].c_str(), 0 ,10), std::strtoull(vecTokens[2].c_str(), 0, 10), vecTokens[3]);
		}
		else if (vecTokens[0] == "product")
		{
			objTickCollection.Product(std::strtoull(vecTokens[1].c_str(), 0, 10), std::strtoull(vecTokens[2].c_str(), 0, 10), vecTokens[3], vecTokens[4], vecTokens[5]);
		}		
	}
	
    return 0;
}
