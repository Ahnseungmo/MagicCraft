#include "Framework.h"

string Utility::ToString(wstring str)
{
	string result;
	result.assign(str.begin(), str.end());

	return result;
}

wstring Utility::ToWString(string str)
{
	wstring result;
	result.assign(str.begin(), str.end());

	return result;
}

vector<string> Utility::SplitString(string origin, string tok)
{
	vector<string> result;
	size_t pos = 0;
	string token;

	while ((pos = origin.find(tok)) != string::npos)
	{
		token = origin.substr(0, pos);
		result.push_back(token);
		origin.erase(0, pos + tok.length());
	}

	result.push_back(origin);

    return result;
}
