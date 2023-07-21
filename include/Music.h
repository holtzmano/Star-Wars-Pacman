#pragma once
#include <string>
#include <SFML/Audio.hpp>
//-----------------------------------------------------------------------------


class Music
{
public:
	enum class Sound
	{
		menu,
		coinEat,
		enemyAte,
		game,
		addScore,
		addLife,
		addEnemy,
		addTime,
		wonGame,
		lostGame,
		buzzer
	};

	static Music& instance();
	void playEnemy();
	void playCoin();
	void playMenu();
	void playGame();
	void stopMenu();
	void stopGame();
	void playScoreBonus();
	void playEnemyBonus();
	void playLifeBonus();
	void playTimeBonus();
	void playWonGame();
	void stopWonGame();
	void playLostGame();
	void stopLostGame();
	void playBuzzer();

private:
	Music(); 
	void loadSound(const std::string);
	const sf::SoundBuffer& getSound(const Sound) const;
	void setSounds();
	std::vector<sf::SoundBuffer> m_soundBuff;
	std::vector <sf::Sound> m_sounds;
	void loadSounds();
};