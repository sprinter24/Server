#pragma once
#include <string>




class Parser
{

	public:
	enum commandType { insert_W, remowe_W, select_W, reselect_W, print_W, error_W };
	commandType CommandDefine(std::string line) 
	{
		if (line.size() < 5)
		{
			return error_W;
		}

		if (line[0] == 'p' && line[1] == 'r' && line[2] == 'i' && line[3] == 'n' && line[4] == 't')
		{
			return print_W;
		}
		if (line.size()< 6)
		{
			return error_W;
		}

		if (line[0] == 'i' && line[1] == 'n' && line[2] == 's' && line[3] == 'e' && line[4] == 'r' && line[5] == 't')
		{
			return insert_W;
		}
		if(line[0] == 'r' && line[1] == 'e' && line[2] == 'm' && line[3] == 'o' && line[4] == 'v' && line[5] == 'e')
		{
			return remowe_W;
		}
		if (line[0] == 's' && line[1] == 'e' && line[2] == 'l' && line[3] == 'e' && line[4] == 'c' && line[5] == 't')
		{
			return select_W;
		}

		if (line.size() < 8)
		{
			return error_W;
		}

		if(line[0] == 'r' && line[1] == 'e' && line[2] == 's' && line[3] == 'e' && line[4] == 'l' && line[5] == 'e' && line[6] == 'c' && line[7] == 't')
		{
			return reselect_W;
		}

		return error_W;
	}


};

