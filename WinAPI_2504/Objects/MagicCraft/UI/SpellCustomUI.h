#pragma once

class SpellCustomUI : public RectCollider {

public:
	SpellCustomUI();
	~SpellCustomUI();

	void InitSpellMarker();

	void InitSpellSlot();

	void InitSpellSampleSlot();

	void InitOption();

	void Update();
	void Render();

	void MarkerMovePosition(Button* marker, int index);

	void MarkerClick(int index);


private:
	Quad* backGround;
	Quad* pageLeft;
	Quad* pageRight;

	Quad* bookMarker;

	OptionButton* slot;
	OptionButton* slot2;

	Option* optionPiercing;
	Option* optionDuplication;
	Option* optionHoming;
	Option* optionReflect;
	Option* optionUpScale;

	int selectedIndex = 0;

	const int OPTION_SLOT_ROW = 5;
	const int OPTION_SLOT_COL = 4;
	const int OPTION_SLOT_PADDING = 5;

	const int SAMPLE_SLOT_SIZE = 5;

	const int OPTIONS_SIZE = 5;
	const int SPELL_MARKERS_SIZE = 10;

	const float MARKER_HOVER_TIME = 0.1f;

	vector<OptionButton*> slots;
	Transform* spellSlotsTransform;

	vector<OptionButton*> sampleSlots;
	Transform* spellSampleSlotsTransform;

	Transform* spellMarkersTransform;


	vector<Button*> spellMarkers;
	vector<float> hoverTimers;

	CircleUI* elementUI;
	CircleUI* shapeUI;


};