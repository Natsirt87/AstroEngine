#pragma once
#include <iostream>

struct SoundProps
{
	SoundProps(const std::string& name)
		: m_audioName(name), m_volume(100), m_pitch(1.f),
		m_minDistance(10.f), m_attenuation(10.f) {}

	std::string m_audioName;
	float m_volume;
	float m_pitch;
	float m_minDistance;
	float m_attenuation;
};

