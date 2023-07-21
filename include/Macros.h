#pragma once

const auto LIVES = 3;
const auto LEVELUP = 50;
const auto WALL = '#';
const auto PLAYER = '@';
const auto PLAYERONLADDER = 'S';
const auto ENEMY = '%';
const auto RAIL = '-';
const auto LADDER = 'H';
const auto COIN = '*';
const auto EMPTY = ' ';
const auto BONUS = '+';
const auto COINPTS = 2;
const auto DEAD = 0;
const auto LEFT = -1;
const auto RIGHT = 1;
const auto MENU_TEXT_SIZE = 60;
const auto VOL = 30;
const auto WIN_WIDTH = 1600;
const auto WIN_HEIGHT = 900;
const auto INFO_MENU_HEIGHT = 60;
const auto LEVEL_TEXT_X_POS = WIN_WIDTH/32;
const auto SCORE_TEXT_X_POS = WIN_WIDTH/5.33;
const auto LIVES_TEXT_X_POS = WIN_WIDTH/2.66;
const auto TIME_TEXT_X_POS = WIN_WIDTH/1.882;
const auto SPACE_TO_START= WIN_WIDTH / 1.391;
const auto INFO_MENU_TEXT_SIZE = 30;
const auto INFO_MENU_TEXTS_Y_POS = WIN_HEIGHT - (INFO_MENU_HEIGHT / 2) - (INFO_MENU_TEXT_SIZE / 2);
const auto ENTER_WIDTH = WIN_WIDTH / 2.75;
const auto ENTER_HEIGHT = WIN_HEIGHT / 5;
const auto ENTER_HEIGHT2 = WIN_HEIGHT / 2.1;
const auto EXIT_WIDTH = WIN_WIDTH / 2.35;
const auto EXIT_HEIGHT = WIN_HEIGHT / 1.13;
const auto MAIN_MSG_WIDTH = WIN_WIDTH * 0.01 - 6;
const auto MAIN_MSG_WIDTH2 = WIN_WIDTH / 3;
const auto MAIN_MSG_HEIGHT = WIN_HEIGHT / 15;
const auto MAIN_MSG_HEIGHT2 = WIN_HEIGHT / 12;
const auto MAIN_MSG_HEIGHT3 = WIN_HEIGHT / 10;
const auto SPRITE_SIZE = 64;
const auto AUDIOS = 11;





enum Direction {
	right, left, down, up, stop
};



enum SurroundingChars {
	leftBCorner,
	rightBCorner,
	topCorner,
	inFront,
	atFeetNew,
	atFeet,
	bottom,
	above
};

enum CollectedObjs {
	coin, addEnemy, addTime, addLife
};