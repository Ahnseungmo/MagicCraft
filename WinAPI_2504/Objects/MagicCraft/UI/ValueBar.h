#pragma once

class ValueBar : public Quad{
public:
	ValueBar(wstring str);
	~ValueBar();

	void Render();

	void SetValue(float data) { this->data = data; }
	float GetValue() { return data; }

private:
	float data = 0;
	FloatValueBuffer *valueBuffer;
};