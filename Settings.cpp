// ISettings.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"

#include "Settings.h"
#include "SettingsValue.h"

namespace Set
{
	bool Settings::isValidId(string str)
	{
		stringstream ss(str);
		char chr;
		if (str[0] >= '0' && str[0] <= '9')
			return false;
		while (ss.get(chr))
		{
			if (!(chr == '_' || chr >= 'a' && chr <= 'z' || chr >= 'A' && chr <= 'Z' || chr >= '0' && chr <= '9'))
			{
				return false;
			}
		}
		return true;
	}

	string Settings::cutString(string str)
	{
		return str.substr(1, str.size() - 2);
	}

	bool Settings::checkValueType(string str, DataType type)
	{
		SettingsValue test;
		test.SetValue(str);
		return (test.GetType() == type);
	}

	bool Settings::LoadFromFile(const string& name)
	{
		ifstream file(name);
		if (!file)
			return false;
		string line = "";
		while (getline(file, line))
		{
			stringstream ss(line);
			string paramName, sum, value;
			ss >> paramName >> sum >> value;

			if (sum != "=" || !isValidId(paramName))
				continue;
			if (value[0] == '\"')
			{
				while (value[(value.size() - 1)] != '\"')
				{
					string buf;
					ss >> buf;
					value += " " + buf;
				}
				value = cutString(value);
			}
			else if (checkValueType(value, dtString))
				continue;

			list[paramName].SetValue(value);
		}
		return true;
	}

	bool Settings::SaveToFile(const string& name)
	{
		ofstream file(name);
		if (list.empty())
			return true;

		if (file)
		{
			for (auto item : list)
			{
				file << item.first << " = ";
				if (item.second.GetType() == 3)
					file << "\"" + item.second.AsString() + "\"" << "\n";
				else
					file << item.second.AsString() << "\n";
			}

			file.close();
			return true;
		}
		return false;
	}

	ISettingsValue& Settings::Get(const string& paramName)
	{
		return list[paramName];
	}

	int Settings::GetInteger(const string& paramName)
	{
		return list[paramName].AsInteger();
	}

	double Settings::GetFloat(const string& paramName)
	{
		return list[paramName].AsDouble();
	}

	bool Settings::GetBoolean(const string& paramName)
	{
		return list[paramName].AsBoolean();
	}

	string Settings::GetString(const string& paramName)
	{
		return list[paramName].AsString();
	}

	void Settings::SetValue(const string& paramName, ISettingsValue& value)
	{
		if (!isValidId(paramName))
			throw invalid_argument("invalid parametr name");
		list[paramName].SetValue(value.AsString());
	}

	void Settings::SetValue(const string& paramName, int value)
	{
		if (!isValidId(paramName))
			throw invalid_argument("invalid parametr name");
		ostringstream oss;
		oss << value;
		list[paramName].SetValue(dtInteger, oss.str());
	}

	void Settings::SetValue(const string& paramName, double value)
	{
		if (!isValidId(paramName))
			throw invalid_argument("invalid parametr name");
		ostringstream oss;
		oss << value;
		list[paramName].SetValue(dtFloat, oss.str());
	}

	void Settings::SetValue(const string& paramName, bool value)
	{
		if (!isValidId(paramName))
			throw invalid_argument("invalid parametr name");
		ostringstream oss;
		oss << value;
		list[paramName].SetValue(dtBoolean, oss.str());
	}

	void Settings::SetValue(const string& paramName, const char* value)
	{
		if (!isValidId(paramName))
			throw invalid_argument("invalid parametr name");
		ostringstream oss;
		oss << value;
		list[paramName].SetValue(dtString, oss.str());
	}

	void Settings::SetInteger(const string& paramName, int value)
	{
		SetValue(paramName, value);
	}

	void Settings::SetFloat(const string& paramName, double value)
	{
		SetValue(paramName, value);
	}

	void Settings::SetBoolean(const string& paramName, bool value)
	{
		SetValue(paramName, value);
	}

	void Settings::SetString(const string& paramName, const string& value)
	{
		if (!isValidId(paramName))
			throw invalid_argument("invalid parametr name");
		ostringstream oss;
		oss << value;
		list[paramName].SetValue(dtString, oss.str());
	}

};
