#pragma once

#include "ISettings.h"
#include "SettingsValue.h"

namespace Set
{
	class Settings : public ISettings
	{
		map <string, SettingsValue> list;

		bool isValidId(string str);

		string cutString(string str);

		bool checkValueType(string str, DataType type);

	public:

		virtual bool LoadFromFile(const string& name);

		virtual bool SaveToFile(const string& name);

		virtual ISettingsValue& Get(const string& paramName);

		virtual int GetInteger(const string& paramName);

		virtual double GetFloat(const string& paramName);

		virtual bool GetBoolean(const string& paramName);

		virtual string GetString(const string& paramName);

		virtual void SetValue(const string& paramName, ISettingsValue& value);

		virtual void SetValue(const string& paramName, int value);

		virtual void SetValue(const string& paramName, double value);

		virtual void SetValue(const string& paramName, bool value);

		virtual void SetValue(const string& paramName, const char* value);

		virtual void SetInteger(const string& paramName, int value);

		virtual void SetFloat(const string& paramName, double value);

		virtual void SetBoolean(const string& paramName, bool value);

		virtual void SetString(const string& paramName, const string& value);

	};
}