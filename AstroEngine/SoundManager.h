#pragma once
#include <unordered_map>
#include "SFML/Audio.hpp"
#include "AudioManager.h"
#include "SoundProps.h"

enum class StateType;

struct SoundInfo
{
	SoundInfo(const std::string& name)
		: m_name(name), m_manualPaused(false) {}

	std::string m_name;
	bool m_manualPaused;
};

using SoundID = int;

using SoundProperties = std::unordered_map<std::string, SoundProps>;
using SoundContainer = std::unordered_map<SoundID,
	std::pair<SoundInfo, sf::Sound*>>;
using Sounds = std::unordered_map<StateType, SoundContainer>;
using RecycledSounds = std::vector<std::pair<std::pair<
	SoundID, std::string>, sf::Sound*>>;
using MusicContainer = std::unordered_map<StateType,
	std::pair<SoundInfo, sf::Music*>>;

class SoundManager
{
public:
	SoundManager(AudioManager* audioMgr);
	~SoundManager();

	void ChangeState(const StateType& state);
	void RemoveState(const StateType& state);

	void Update(float dt);

	SoundID Play(const std::string& sound,
		const sf::Vector3f& position,
		bool loop = false,
		bool relative = false);
	bool Play(const SoundID& id);
	bool Stop(const SoundID& id);
	bool Pause(const SoundID& id);

	bool PlayMusic(const std::string& musicID,
		float volume = 100.f,
		bool loop = false);
	bool PlayMusic(const StateType& state);
	bool StopMusic(const StateType& state);
	bool PauseMusic(const StateType& state);

	bool SetPosition(const SoundID& id, const sf::Vector3f& pos);
	bool IsPlaying(const SoundID& id);
	SoundProps* GetSoundProperties(const std::string& soundName);

	static const int Max_Sounds = 150;
	static const int Sound_Cache = 75;

private:
	bool loadProperties(const std::string& name);
	void pauseAll(const StateType& state);
	void unpauseAll(const StateType& state);

	sf::Sound* createSound(SoundID& id, const std::string& audioName);
	void setUpSound(sf::Sound* sound,
		const SoundProps* props,
		bool loop = false,
		bool relative = false);
	void recycleSound(const SoundID& id, sf::Sound* sound,
		const std::string& name);

	void cleanup();

	Sounds m_audio;
	MusicContainer m_music;
	RecycledSounds m_recycled;
	SoundProperties m_properties;
	StateType m_currentState;

	SoundID m_lastID;
	unsigned int m_numSounds;
	float m_elapsed;

	AudioManager* m_audioManager;
};

