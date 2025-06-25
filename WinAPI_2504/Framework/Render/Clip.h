#pragma once

class Clip
{
private:
    const float FPS = 10.0f;

public:
    Clip(vector<Frame*> frames, bool isLoop = true, float speed = 1.0f);
    ~Clip();

    void Update();
    void Render();

    void Play();
    void Stop() { isPlay = false; }

    void SetShader(wstring shaderFile);    
	void SetEvent(Event event, int frameNum = -1);

    Frame* GetCurFrame() { return frames[curFrameNum]; }

    void DeleteFreames();

private:
    vector<Frame*> frames;

    UINT curFrameNum = 0;

    float frameTime = 0.0f;
    float intervalTime = 0.0f;
    float speed;

    bool isLoop;
    bool isPlay = true;
    bool endEvent = false;

	unordered_map<int, Event> events;
};