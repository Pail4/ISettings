
#include "pch.h"
#include "SettingsValue.h"
#include "Settings.h"

namespace Set
{
	bool SettingsValue::isString(string str) //���� ���� ���-��, ����� ���� !� ��� ����� �����!
	{
		return true; //���� �� ���� ������ ���������, ��� ��� ��, ��� ������ ����(�� ������, �� ����������,
					//�� ����� � �� ������������) ����� �������
	}

	bool SettingsValue::isDigit(char chr)
	{
		return (chr >= '0' && chr <= '9');
	}

	bool SettingsValue::isInteger(string str) // ���� ���� ������ �����
	{
		stringstream s(str);
		char chr;
		if (str[0] == '-')
			s.get(chr);
		while (s.get(chr))
		{
			if (!isDigit(chr))
				return false;
		}
		return true;
	}

	bool SettingsValue::isFloat(string str) // ���� ��� ����� � ���� 1 ����� (������, ����� - ".51" ���� �������� = 0.51 - ��� ����)
	{
		stringstream s(str);
		char chr;
		bool flag = false;

		if (str[0] == '-')
			s.get(chr);
		while (s.get(chr))
		{
			if (!isDigit(chr) && (chr != '.' || flag))
				return false;
			else if (chr == '.')
				flag = true;
		}
		return true;
	}


	void SettingsValue::SetValue(const string& value)
	{
		if (value.empty())
			SetValue(dtUnknown, value);

		else if (value == "true" || value == "false")
			SetValue(dtBoolean, value);

		else if (isInteger(value))
			SetValue(dtInteger, value);

		else if (isFloat(value))
			SetValue(dtFloat, value);

		else if (isString(value))
			SetValue(dtString, value);

		else
			SetValue(dtUnknown, value);
	}

	void SettingsValue::SetValue(DataType type, const string& value)
	{
		this->value = value;
		this->type = type;
	}

	string SettingsValue::AsString()
	{
		switch (GetType())
		{
		case 2:
			if (AsBoolean())
				return "true";
			return "false";
		default:
			return value;
		}
	}

	int SettingsValue::AsInteger()
	{
		stringstream valueStream(value);
		int result = 0;
		valueStream >> result;
		return result;
	}

	double SettingsValue::AsDouble()
	{
		stringstream valueStream(value);
		double result = 0;
		valueStream >> result;
		return result;
	}

	bool SettingsValue::AsBoolean()
	{
		if (value == "false" || value == "0" || value.empty())
			return false;
		return true;
	}

	DataType SettingsValue::GetType()
	{
		return type;
	}

	//SettingsValue::~ISettingsValue() {};

}