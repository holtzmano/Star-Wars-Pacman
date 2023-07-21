#include <Music.h>
#include <Macros.h>
//-----------------------------------------------------------------------------

Music::Music()
{
	loadSounds();
	setSounds();
}
//-----------------------------------------------------------------------------
Music& Music::instance()
{
	static Music instance;
	return instance;
}
//-----------------------------------------------------------------------------
void Music::playEnemy() 
{
	m_sounds[(int)Sound::enemyAte].play();
}
//-----------------------------------------------------------------------------
void Music::playCoin() 
{
	m_sounds[(int)Sound::coinEat].play();
}
//-----------------------------------------------------------------------------
void Music::playMenu() 
{
	m_sounds[(int)Sound::menu].play();
}
//-----------------------------------------------------------------------------
void Music::playGame() 
{
	m_sounds[(int)Sound::game].play();
}
//-----------------------------------------------------------------------------
void Music::stopMenu() 
{
	m_sounds[(int)Sound::menu].stop();
}
//-----------------------------------------------------------------------------
void Music::stopGame() 
{
	m_sounds[(int)Sound::game].stop();
}
//-----------------------------------------------------------------------------
void Music::playScoreBonus() 
{
	m_sounds[(int)Sound::addScore].play();
}
//-----------------------------------------------------------------------------

void Music::playEnemyBonus() 
{
	m_sounds[(int)Sound::addEnemy].play();
}
//-----------------------------------------------------------------------------

void Music::playLifeBonus() 
{
	m_sounds[(int)Sound::addLife].play();
}
//-----------------------------------------------------------------------------

void Music::playTimeBonus() 
{
	m_sounds[(int)Sound::addTime].play();
}
//-----------------------------------------------------------------------------

void Music::playWonGame() 
{
	m_sounds[(int)Sound::wonGame].play();
}
//-----------------------------------------------------------------------------
void Music::stopWonGame() 
{
	m_sounds[(int)Sound::wonGame].stop();
}
//-----------------------------------------------------------------------------
void Music::playLostGame() 
{
	m_sounds[(int)Sound::lostGame].play();
}
//-----------------------------------------------------------------------------
void Music::stopLostGame()
{
	m_sounds[(int)Sound::lostGame].stop();
}
//-----------------------------------------------------------------------------
void Music::playBuzzer()
{
	m_sounds[(int)Sound::buzzer].play();
}
//-----------------------------------------------------------------------------
const sf::SoundBuffer& Music::getSound(const Sound name)  const
{
	return m_soundBuff[(int)name];
}
//-----------------------------------------------------------------------------
void Music::loadSounds() 
{
	loadSound("MenuOpening.wav");
	loadSound("GetCoin.wav");
	loadSound("EnemyEat.wav");
	loadSound("JediTheme.wav");
	loadSound("yodaForceWithyou.wav");
	loadSound("TheForceIswithYouYoungSkywalker.wav");
	loadSound("Newenemyarrives.wav");
	loadSound("ImpressiveDarth.wav");
	loadSound("WinningSong.wav");
	loadSound("LostGame.wav");
	loadSound("Buzzer!.wav");
}
//-----------------------------------------------------------------------------

void Music::loadSound(const std::string path)
{
	sf::SoundBuffer temp;
	temp.loadFromFile(path);
	m_soundBuff.push_back(temp);
}
//-----------------------------------------------------------------------------
void Music::setSounds()
{
	for(int i = 0; i < AUDIOS; i++)
	{
		m_sounds.push_back(sf::Sound(getSound(Sound(i))));
		m_sounds[i].setVolume(VOL); 
	}
}
