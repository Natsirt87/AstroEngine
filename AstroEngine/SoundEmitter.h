#pragma once
#include "BaseComponent.h"
#include "SoundManager.h"

class SoundEmitter : public BaseComponent
{
public:
	SoundEmitter(Entity* owner, SoundManager* soundMgr);
	~SoundEmitter();

	void Update();

	int Play(const std::string& sound,
		const sf::Vector2f& position,
		bool loop = false,
		bool attached = false,
		bool relative = false);
	bool Play(const int& id);
	bool Stop(const int& id);
	bool Pause(const int& id);

	bool SetPosition(const int& id, const sf::Vector3f& pos);
	bool IsPlaying(const int& id);
	SoundProps* GetSoundProperties(const std::string& soundName);

private:
	SoundManager* m_soundMgr;
	std::vector<int> m_attachedSounds;
};

