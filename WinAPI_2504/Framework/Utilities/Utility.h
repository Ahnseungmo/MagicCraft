#pragma once

class Utility
{
public:
	static string ToString(wstring str);
	static wstring ToWString(string str);

	static vector<string> SplitString(string origin, string tok);
};