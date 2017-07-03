#include "IniAnalyzer.h"

CIniAnalyzer::CIniAnalyzer() : m_separator("="), m_note("#")
{
}

CIniAnalyzer::~CIniAnalyzer()
{
}

bool CIniAnalyzer::split_string(const std::string &str, const std::string &flag, std::string &left, std::string &right)
{
	if (str.empty() || flag.empty())
	{
		return false;
	}

	try
	{
		std::string::size_type pos = str.find(flag);
		if (pos == std::string::npos)
		{
			return false;
		}

		left.assign(str.begin(),str.begin() + pos);
		right.assign(str.begin() + pos + flag.size(),str.end()); //分隔串不要，所以+m_strSplit.size()
	}
	catch (...)
	{
		return false;
	}


	return true;
}

bool CIniAnalyzer::extract_string_left(const std::string &str, const std::string &flag, std::string &value)
{
	if (str.empty() || flag.empty())
	{
		return false;
	}

	try
	{
		std::string::size_type pos = str.find(flag);
		if (pos == std::string::npos)
		{
			return false;
		}

		value.assign(str.begin(),str.begin() + pos);
	}
	catch (...)
	{
		return false;
	}


	return true;
}

bool CIniAnalyzer::extract_string_right(const std::string &str, const std::string &flag, std::string &value)
{
	if (str.empty() || flag.empty())
	{
		return false;
	}

	try
	{
		std::string::size_type pos = str.find(flag);
		if (pos == std::string::npos)
		{
			return false;
		}

		value.assign(str.begin() + pos + flag.size(),str.end());
	}
	catch (...)
	{
		return false;
	}


	return true;
}

bool CIniAnalyzer::extract_string_mid(const std::string &str, const std::string &left_flag, const std::string &right_flag, std::string &value)
{
	if (str.empty() || left_flag.empty() || right_flag.empty())
	{
		return false;
	}

	try
	{
		std::string::size_type pos_left = str.find(left_flag);
		if (pos_left == std::string::npos)
		{
			return false;
		}

		std::string::size_type pos_right = str.find(right_flag);
		if (pos_right == std::string::npos)
		{
			return false;
		}

		value.assign(str.begin() + pos_left + 1,str.begin() + pos_right);
	}
	catch (...)
	{
		return false;
	}


	return true;
}

void CIniAnalyzer::analysis_file(const std::string &filename)
{
	m_map_data.clear();

	std::ifstream infile(filename.c_str());
	if (!infile)
	{
		return;
	}

	std::string line;
	std::string key;
	std::string value;

	while (std::getline(infile,line))
	{
		//对于注释行返回false
		if (line.compare(0,m_note.size(),m_note) == 0)
		{
			continue;
		}

		if (split_string(line,m_separator,key,value))
		{
			m_map_data.insert(std::make_pair(key,value));
		}
	}

	infile.close();

	return;
}

const std::string CIniAnalyzer::find_value(const std::string &key)
{
	std::map<std::string,std::string>::iterator itr = m_map_data.find(key);
	if (itr != m_map_data.end())
	{
		return itr->second;
	}
	else
	{
		return "";
	}
}