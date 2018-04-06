#pragma once
#include <string>

std::string ParseOptions(int argc, const char* argv[])
{
	std::string strOption;

	for (int i = 0; i < argc; ++i)
	{
		if (argv[i][0] == '-')
		{
			strOption.assign(&argv[i][1]);
			break;
		}
	}

	return strOption;
}