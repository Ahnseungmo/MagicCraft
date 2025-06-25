#include "Framework.h"


DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}


void DataManager::LoadData(const string& fileName)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		MessageBox(nullptr, L"Failed to open file", L"Error", MB_OK);
		return;
	}

	string line;

	bool isFirstLine = true;

	while (getline(file, line))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> data = Utility::SplitString(line, ",");

		ItemData itemData;
		itemData.key = stoi(data[0]);
		itemData.name = data[1];
		itemData.explane = data[2];
		itemData.price = stoi(data[3]);
		itemData.value = stoi(data[4]);
		itemData.type = (ItemData::Type)stoi(data[5]);

		itemDatas[itemData.key] = itemData;
	}
	file.close();
}

vector<string> DataManager::GetSubdirectories(const string& path) {
	vector<string> directories;
	string searchPath = path + "/*";

	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				strcmp(findData.cFileName, ".") != 0 &&
				strcmp(findData.cFileName, "..") != 0) {
				directories.push_back(findData.cFileName);
			}
		} while (FindNextFileA(hFind, &findData));
		FindClose(hFind);
	}

	return directories;
}
vector<string> GetFilesWithExtension(const string& folderPath, const string& extension) {
	std::vector<std::string> matchedFiles;
	std::string searchPath = folderPath + "/*";

	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				std::string fileName = findData.cFileName;

				size_t pos = fileName.rfind('.');
				if (pos != string::npos) {
					std::string fileExt = fileName.substr(pos);
					if (_stricmp(fileExt.c_str(), extension.c_str()) == 0) {
						matchedFiles.push_back(fileName);
					}
				}
			}
		} while (FindNextFileA(hFind, &findData));
		FindClose(hFind);
	}

	return matchedFiles;
}
void DataManager::LoadFrames(string path)
{
	vector<string> shapes;
	vector<string> elements;

	shapes = GetSubdirectories(path);

	for (int i = 0; i < shapes.size();i++) {
		elements = GetSubdirectories(path + "/" + shapes.at(i));
//		spellFrames.insert(make_pair(shapes.at(i), nullptr));
		for (int j = 0; j < elements.size();j++) {

			string filePath = path + "/" + shapes.at(i) + "/" + elements.at(j);
			vector<string> fileNames;
			fileNames = GetFilesWithExtension(filePath,".xml");
			
			for (int k = 0; k < fileNames.size();k++) {

				tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
				document->LoadFile((filePath + "/" + fileNames.at(k)).c_str());

				tinyxml2::XMLElement* atlas = document->FirstChildElement();
				string textureFile = filePath + "/" + atlas->Attribute("imagePath");

				vector<Frame*> frames;
				tinyxml2::XMLElement* sprite = atlas->FirstChildElement();

				while (sprite != nullptr)
				{
					float x, y, w, h;
					x = sprite->FloatAttribute("x");
					y = sprite->FloatAttribute("y");
					w = sprite->FloatAttribute("w");
					h = sprite->FloatAttribute("h");

					wstring file = Utility::ToWString(textureFile);
					frames.push_back(new Frame(file, x, y, w, h));

					sprite = sprite->NextSiblingElement();
				}
				Shape shapeEnum = SpellManager::StringToShape.at(shapes[i]);
				Element elementEnum = SpellManager::StringToElement.at(elements[j]);
				spellFrames[shapeEnum][elementEnum].push_back(frames);
				delete document;
			}
		}
	}
}