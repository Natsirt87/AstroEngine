#include "SoundManager.h"

SoundManager::SoundManager(AudioManager* audioMgr)
	: m_lastID(0), m_audioManager(audioMgr),
	m_elapsed(0.f), m_numSounds(0) {}

SoundManager::~SoundManager() { cleanup(); }

void SoundManager::ChangeState(const StateType& state)
{
	pauseAll(m_currentState);
	unpauseAll(state);
	m_currentState = state;

	if (m_music.find(m_currentState) != m_music.end()) { return; }
	SoundInfo info("");
	sf::Music* music = nullptr;
	m_music.emplace(m_currentState, std::make_pair(info, music));
}

void SoundManager::RemoveState(const StateType& state)
{
	auto& StateSounds = m_audio.find(state)->second;
	for (auto& itr : StateSounds)
	{
		recycleSound(itr.first, itr.second.second,
			itr.second.first.m_name);
	}
	m_audio.erase(state);
	auto music = m_music.find(state);
	if (music == m_music.end()) { return; }
	if (music->second.second)
	{
		delete music->second.second;
		m_numSounds--;
	}
	m_music.erase(state);
}

void SoundManager::Update(float dt)
{
	m_elapsed += dt;

	if (m_elapsed < 0.33f) { return; }
	//Run every 1/3 of a second
	m_elapsed = 0;
	auto& container = m_audio[m_currentState];

	for (auto itr = container.begin(); itr != container.end();)
	{
		if (!itr->second.second->getStatus())
		{
			recycleSound(itr->first, itr->second.second,
				itr->second.first.m_name);
			itr = container.erase(itr); //Remove sound
			continue;
		}
		itr++;
	}

	auto music = m_music.find(m_currentState);
	if (music == m_music.end()) { return; }
	if (!music->second.second) { return; }
	if (music->second.second->getStatus()) { return; }
	delete music->second.second;
	music->second.second = nullptr;
	m_numSounds--;
}

SoundID SoundManager::Play(const std::string& sound, 
	const sf::Vector3f& position, bool loop, bool relative)
{
	SoundProps* props = GetSoundProperties(sound);
	if (!props) { return -1; }
	SoundID id;
	sf::Sound* newSound = createSound(id, props->m_audioName);
	if (!newSound) { return -1; }
	//Sound has been created successfully
	setUpSound(newSound, props, loop, relative);
	newSound->setPosition(position);
	SoundInfo info(props->m_audioName);
	m_audio[m_currentState].emplace(id, std::make_pair(info, newSound));
	newSound->play();
	return id;
}

bool SoundManager::Play(const SoundID& id)
{
	auto& container = m_audio[m_currentState];
	auto sound = container.find(id);
	if (sound == container.end()) { return false; }
	sound->second.second->play();
	sound->second.first.m_manualPaused = false;
	return true;
}

bool SoundManager::Stop(const SoundID& id)
{
	auto& container = m_audio[m_currentState];
	auto sound = container.find(id);
	if (sound == container.end()) { return false; }
	sound->second.second->stop();
	sound->second.first.m_manualPaused = true;
	return true;
}

bool SoundManager::Pause(const SoundID& id)
{
	auto& container = m_audio[m_currentState];
	auto sound = container.find(id);
	if (sound == container.end()) { return false; }
	sound->second.second->pause();
	sound->second.first.m_manualPaused = true;
	return true;
}

bool SoundManager::PlayMusic(const std::string& musicID, float volume, bool loop)
{
	auto s = m_music.find(m_currentState);
	if (s == m_music.end()) { return false; }
	std::string path = m_audioManager->GetPath(musicID);
	if (path == "") { return false; }

	if (!s->second.second)
	{
		s->second.second = new sf::Music();
		m_numSounds++;
	}

	sf::Music* music = s->second.second;
	if (!music->openFromFile(path))
	{
		delete music;
		m_numSounds--;
		s->second.second = nullptr;
		std::cerr << "[SoundManager] Failed to load music from file: "
			<< musicID << std::endl;
		return false;
	}

	music->setLoop(loop);
	music->setVolume(volume);
	music->setRelativeToListener(true); //Always relative
	music->play();
	s->second.first.m_name = musicID;
	return true;
}

bool SoundManager::PlayMusic(const StateType& state)
{
	auto music = m_music.find(m_currentState);
	if (music == m_music.end()) { return false; }
	if (!music->second.second) { return false; }
	music->second.second->play();
	music->second.first.m_manualPaused = false;
	return true;
}

bool SoundManager::StopMusic(const StateType& state)
{
	auto music = m_music.find(m_currentState);
	if (music == m_music.end()) { return false; }
	if (!music->second.second) { return false; }
	music->second.second->stop();
	delete music->second.second;
	music->second.second = nullptr;
	m_numSounds--;
	return true;
}

bool SoundManager::PauseMusic(const StateType& state)
{
	auto music = m_music.find(m_currentState);
	if (music == m_music.end()) { return false; }
	if (!music->second.second) { return false; }
	music->second.second->pause();
	music->second.first.m_manualPaused = true;
	return true;
}

bool SoundManager::SetPosition(const SoundID& id, const sf::Vector3f& pos)
{
	auto& container = m_audio[m_currentState];
	auto sound = container.find(id);
	if (sound == container.end()) { return false; }
	sound->second.second->setPosition(pos);
	return true;
}

bool SoundManager::IsPlaying(const SoundID& id)
{
	auto& container = m_audio[m_currentState];
	auto sound = container.find(id);
	return (sound != container.end() ?
		sound->second.second->getStatus() : false);
}

SoundProps* SoundManager::GetSoundProperties(const std::string& soundName)
{
	auto properties = m_properties.find(soundName);
	if (properties == m_properties.end())
	{
		if (!loadProperties(soundName)) { return nullptr; }
		properties = m_properties.find(soundName);
	}
	return &properties->second;
}

bool SoundManager::loadProperties(const std::string& name)
{
	std::ifstream file;
	file.open("Data/Sounds/" + name + ".sound");
	if (!file.is_open())
	{
		std::cerr << "[SoundManager] Failed to load sound: " << name << std::endl;
		return false;
	}
	SoundProps props("");
	std::string line;

	while (std::getline(file, line))
	{
		if (line[0] == '|') { continue; }
		std::stringstream keystream(line);
		std::string type;
		keystream >> type;
		if (type == "Audio")
		{
			keystream >> props.m_audioName;
		}
		else if (type == "Volume")
		{
			keystream >> props.m_volume;
		}
		else if (type == "Pitch")
		{
			keystream >> props.m_pitch;
		}
		else if (type == "Distance")
		{
			keystream >> props.m_minDistance;
		}
		else if (type == "Attenuation")
		{
			keystream >> props.m_attenuation;
		}
	}

	file.close();
	if (props.m_audioName == "") { return false; }
	m_properties.emplace(name, props);
	return true;
}

void SoundManager::pauseAll(const StateType& state)
{
	auto& container = m_audio[state];
	for (auto itr = container.begin(); itr != container.end();)
	{
		if (!itr->second.second->getStatus())
		{
			recycleSound(itr->first, itr->second.second,
				itr->second.first.m_name);
			itr = container.erase(itr);
			continue;
		}
		itr->second.second->pause();
		itr++;
	}
	auto music = m_music.find(state);
	if (music == m_music.end()) { return; }
	if (!music->second.second) { return; }
	music->second.second->pause();
}

void SoundManager::unpauseAll(const StateType& state)
{
	auto& container = m_audio[state];
	for (auto& itr : container)
	{
		if (itr.second.first.m_manualPaused) { continue; }
		itr.second.second->play();
	}

	auto music = m_music.find(state);
	if (music == m_music.end()) { return; }
	if (!music->second.second || music->second.first.m_manualPaused)
	{
		return;
	}
	music->second.second->play();
}

sf::Sound* SoundManager::createSound(SoundID& id, const std::string& audioName)
{
	sf::Sound* sound = nullptr;
	if (!m_recycled.empty() && (m_numSounds >= Max_Sounds ||
		m_recycled.size() >= Sound_Cache))
	{
		auto itr = m_recycled.begin();
		while (itr != m_recycled.end())
		{
			if (itr->first.second == audioName) { break; }
			itr++;
		}

		if (itr == m_recycled.end()) //Sound with same name hasn't been found
		{
			auto element = m_recycled.begin();
			id = element->first.first;
			m_audioManager->ReleaseResource(element->first.second);
			m_audioManager->RequireResource(audioName);
			sound = element->second;
			sound->setBuffer(*m_audioManager->GetResource(audioName));
			m_recycled.erase(element);
		}
		else
		{
			id = itr->first.first;
			sound = itr->second;
			m_recycled.erase(itr);
		}
		return sound;
	}

	if (m_numSounds < Max_Sounds)
	{
		if (m_audioManager->RequireResource(audioName))
		{
			sound = new sf::Sound();
			id = m_lastID;
			m_lastID++;
			m_numSounds++;
			sound->setBuffer(*m_audioManager->GetResource(audioName));
			return sound;
		}
	}
	std::cerr << "[SoundManager] Failed to create sound." << std::endl;
	return nullptr;
}

void SoundManager::setUpSound(sf::Sound* sound, const SoundProps* props, bool loop, bool relative)
{
	sound->setVolume(props->m_volume);
	sound->setPitch(props->m_pitch);
	sound->setMinDistance(props->m_minDistance);
	sound->setAttenuation(props->m_attenuation);
	sound->setLoop(loop);
	sound->setRelativeToListener(relative);
}

void SoundManager::recycleSound(const SoundID& id, sf::Sound* sound, const std::string& name)
{
	m_recycled.emplace_back(std::make_pair(id, name), sound);
}

void SoundManager::cleanup()
{
	for (auto& state : m_audio)
	{
		for (auto& sound : state.second)
		{
			m_audioManager->ReleaseResource(sound.second.first.m_name);
			delete sound.second.second;
		}
	}
	m_audio.clear();
	for (auto& recycled : m_recycled)
	{
		m_audioManager->ReleaseResource(recycled.first.second);
		delete recycled.second;
	}
	m_recycled.clear();
	for (auto& music : m_music)
	{
		if (music.second.second)
		{
			delete music.second.second;
		}
	}
	m_music.clear();

	m_properties.clear();
	m_numSounds = 0;
	m_lastID = 0;
}
