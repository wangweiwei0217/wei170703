#ifndef		__INI_READER_H_2015_08_24__
#define		__INI_READER_H_2015_08_24__

#include <string>
#include <map>
#include <fstream>


class CIniAnalyzer
{
public:
	CIniAnalyzer();
	~CIniAnalyzer();

public:
	static bool split_string(const std::string &str, const std::string &flag, std::string &left, std::string &right);
	static bool extract_string_left(const std::string &str, const std::string &flag, std::string &value);
	static bool extract_string_right(const std::string &str, const std::string &flag, std::string &value);
	static bool extract_string_mid(const std::string &str, const std::string &left_flag, const std::string &right_flag, std::string &value);

public:
	void analysis_file(const std::string &filename);

	const std::string find_value(const std::string &key);

	inline bool set_separator(const std::string &separator)
	{
		if (separator.empty())
		{
			return false;
		}
		else
		{
			m_separator = separator;
			return true;
		}
	}

	inline void set_note(const std::string &note)
	{
		m_note = note;
	}

	inline const std::map<std::string, std::string>& get_all_data() const
	{
		return m_map_data;
	}

private:
	std::map<std::string, std::string> m_map_data;
	std::string m_separator; //·Ö¸ô·û
	std::string m_note; //×¢ÊÍ·û
};




#endif