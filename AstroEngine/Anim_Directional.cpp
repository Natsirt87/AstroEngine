#include "Anim_Directional.h"
#include "SpriteSheet.h"

void Anim_Directional::frameStep()
{
	if (m_frameStart < m_frameEnd) { m_frameCurrent++; }
	else { m_frameCurrent--; }

	if ((m_frameStart < m_frameEnd && m_frameCurrent > m_frameEnd) ||
		(m_frameStart > m_frameEnd&& m_frameCurrent < m_frameEnd))
	{
		if (m_loop) { m_frameCurrent = m_frameStart; return; }
		m_frameCurrent = m_frameEnd;
		Pause();
	}
}

void Anim_Directional::cropSprite()
{
	sf::IntRect rect(
		m_spriteSheet->GetSpriteSize().x * m_frameCurrent,
		m_spriteSheet->GetSpriteSize().y *
		(m_frameRow + (short)m_spriteSheet->GetDirection()),
		m_spriteSheet->GetSpriteSize().x,
		m_spriteSheet->GetSpriteSize().y);
	m_spriteSheet->CropSprite(rect);
		
}

void Anim_Directional::readIn(std::stringstream& stream)
{
	stream >> m_frameStart >> m_frameEnd >> m_frameRow
		>> m_frameTime >> m_frameActionStart >> m_frameActionEnd;
}
