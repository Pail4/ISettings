#pragma once

#include <string>
#include <fstream>
#include <map>
#include <sstream>


using namespace std;

namespace Set
{

	class SettingsValue : public ISettingsValue
	{
		string value = "";

		DataType type = dtUnknown;

		bool isString(string str);

		bool isDigit(char chr);

		bool isInteger(string str);

		bool isFloat(string str);

	public:

		virtual void SetValue(const string& value);

		virtual void SetValue(DataType type, const string& value);

		virtual string AsString();

		virtual int AsInteger();

		virtual double AsDouble();

		virtual bool AsBoolean();

		virtual DataType GetType();

		//virtual ~ISettingsValue();
	};
}