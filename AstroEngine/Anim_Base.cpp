#include "Anim_Base.h"
#include "SpriteSheet.h"

Anim_Base::Anim_Base() : m_frameCurrent(0), m_frameStart(0), m_frameEnd(0),
	m_frameRow(0), m_frameTime(0.f), m_elapsedTime(0.f), m_frameActionStart(-1),
	m_frameActionEnd(-1), m_loop(false), m_playing(false) {}

Anim_Base::~Anim_Base() {}

void Anim_Base::SetFrame(Frame frame)
{
	if ((frame >= m_frameStart && frame <= m_frameEnd) ||
		(frame >= m_frameEnd && frame <= m_frameStart))
	{
		m_frameCurrent = frame;
	}
}

bool Anim_Base::IsInAction()
{
	if (m_frameActionStart == -1 || m_frameActionEnd == -1) { return true; }
	return (m_frameCurrent >= m_frameActionStart && m_frameCurrent <= m_frameActionEnd);
}

void Anim_Base::Reset()
{
	m_frameCurrent = m_frameStart;
	m_elapsedTime = 0.0f;
	cropSprite();
}

void Anim_Base::Update(const float& dt)
{
	if (!m_playing) { return; }
	m_elapsedTime += dt;
	m_animTime += dt;
	if (m_elapsedTime < m_frameTime) { return; }
	frameStep();
	cropSprite();
	m_elapsedTime = 0;
	if (m_animTime < m_frameTime * (m_frameEnd - m_frameStart + 1)) { return; }
	m_animTime = 0;
	if (m_nextAnim != "")
	{
		m_spriteSheet->SetAnimation(m_nextAnim, true, m_nextLooping);
	}
}

void Anim_Base::SetSpriteSheet(SpriteSheet* sheet) { m_spriteSheet = sheet; }
void Anim_Base::SetStartFrame(Frame frame) { m_frameStart = frame; }
void Anim_Base::SetEndFrame(Frame frame) { m_frameEnd = frame; }
void Anim_Base::SetFrameRow(Frame row) { m_frameRow = row; }
void Anim_Base::SetActionStart(Frame frame) { m_frameActionStart = frame; }
void Anim_Base::SetActionEnd(Frame frame) { m_frameActionEnd = frame; }
void Anim_Base::SetFrameTime(float time) { m_frameTime = time; }
void Anim_Base::SetLooping(bool loop) { m_loop = loop; }
void Anim_Base::SetNextLooping(bool loop) { m_nextLooping = loop; }
void Anim_Base::SetNextAnim(const std::string& anim) { m_nextAnim = anim; }
void Anim_Base::SetName(const std::string& name) { m_name = name; }

SpriteSheet* Anim_Base::GetSpriteSheet() { return m_spriteSheet; }
Frame Anim_Base::GetFrame() { return m_frameCurrent; }
Frame Anim_Base::GetStartFrame() { return m_frameStart; }
Frame Anim_Base::GetEndFrame() { return m_frameEnd; }
Frame Anim_Base::GetFrameRow() { return m_frameRow; }
int Anim_Base::GetActionStart() { return m_frameActionStart; }
int Anim_Base::GetActionEnd() { return m_frameActionEnd; }
float Anim_Base::GetFrameTime() { return m_frameTime; }
float Anim_Base::GetElapsedTime() { return m_elapsedTime; }
std::string Anim_Base::GetName() { return m_name; }
bool Anim_Base::IsLooping() { return m_loop; }
bool Anim_Base::IsPlaying() { return m_playing; }

void Anim_Base::Play() { m_playing = true; }
void Anim_Base::Pause() { m_playing = false; }
void Anim_Base::Stop() { m_playing = false; Reset(); }