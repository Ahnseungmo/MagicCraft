#include "Framework.h"


TextBox::TextBox()
{
	static int ID_COUNT = 0;
	id = ID_COUNT++;
}

TextBox::~TextBox()
{

}

void TextBox::Update()
{

		
}

void TextBox::Render()
{
	string name = "textBox_" + to_string(id);
	ImVec2 pos;
	if (parent) {
		Vector2 parentPos = parent->GetGlobalPosition();
		pos = ImVec2(localPos.x + parentPos.x, localPos.y + parentPos.y);
	}
	else pos = ImVec2(localPos.x, localPos.y);
	pos.y = SCREEN_HEIGHT - pos.y;

	if(font) ImGui::PushFont(font);
	ImGuiWindowFlags flag =
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove | 
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoMouseInputs 
		|
		ImGuiWindowFlags_NoBackground
		;


 //	ImGui::BeginPopupContextWindow(name.c_str(), flag);
	ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
	ImGui::SetNextWindowSize(textSize);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	
	ImVec2 textBoxPos;
	switch (align)
	{
	case TextBox::Center:
		textBoxPos = ImVec2(pos.x - (textSize.x * 0.5), pos.y - (textSize.y * 0.5));
		break;
	case TextBox::Left:
		textBoxPos = ImVec2(pos.x, pos.y - (textSize.y * 0.5));
		break;
	case TextBox::Right:
		textBoxPos = ImVec2(pos.x - (textSize.x), pos.y - (textSize.y * 0.5));
		break;
	default:
		textBoxPos = pos;
		break;
	}

	ImGui::SetNextWindowPos(textBoxPos);

	ImGui::Begin(name.c_str(),0,flag);
//	ImGui::PushItemWidth()
//	ImGui::Text(text.c_str());
//	ImGui::Spacing
	ImGui::TextColored(color,text.c_str());
//	ImGui::SetWindowSize()
//	ImGui::AlignTextToFramePadding();
	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::PopFont();
}
