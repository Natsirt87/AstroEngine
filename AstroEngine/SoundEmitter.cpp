#include "SoundEmitter.h"

SoundEmitter::SoundEmitter(Entity* owner, SoundManager* soundMgr)
	: BaseComponent(owner), m_soundMgr(soundMgr) {}

SoundEmitter::~SoundEmitter() {}

void SoundEmitter::Update()
{
	if (m_attachedSounds.empty()) { return; }

	sf::Vector2f ownerPos = GetOwner()->GetPosition();
	sf::Vector3f soundPos = sf::Vector3f(ownerPos.x, 0.f, ownerPos.y);

	for (int i = 0; i < m_attachedSounds.size(); i++)
	{
		m_soundMgr->SetPosition(m_attachedSounds[i], soundPos);
	}
}

int SoundEmitter::Play(const std::string& sound, const sf::Vector2f& position, bool loop, bool attached, bool relative)
{ 
	sf::Vector3f soundPos = sf::Vector3f(position.x, 0.f, position.y);
	int id = m_soundMgr->Play(sound, soundPos, loop, relative); 
	if (attached)
	{
		m_attachedSounds.push_back(id);
	}
	return id;
}

bool SoundEmitter::Play(const int& id) { return m_soundMgr->Play(id); }
bool SoundEmitter::Stop(const int& id) { return m_soundMgr->Stop(id); }
bool SoundEmitter::Pause(const int& id) { return m_soundMgr->Pause(id); }

bool SoundEmitter::SetPosition(const int& id, const sf::Vector3f& pos)
{ return m_soundMgr->SetPosition(id, pos); }

bool SoundEmitter::IsPlaying(const int& id) 
{ return m_soundMgr->IsPlaying(id); }

SoundProps* SoundEmitter::GetSoundProperties(const std::string& soundName)
{ return m_soundMgr->GetSoundProperties(soundName); }
