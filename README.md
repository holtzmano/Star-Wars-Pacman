.  The game is built of mazes.  Coins are spread around the maze that the player needs to pick up to beat the game.  There are enemies who will try a catch the player before it collects all the coins.  There are three types of enemies: smart, stupid and patrol.  The stupid enemy moves in a random way, patrol from left to right and the smart works by a certain algorithm to find the player as quick as it can.  There are also several different types of bonuses to collect that will give the player a variety of power ups such as point bonus, one extra life, one extra enemy and a bonus that will add time to the time left in the game.  The game is over when the player completes all the levels or loses all its lives.  The game runs on real time meaning that the player and enemies move at the same time. 
Design:  
The game is built of many objects, each item in the game has an object for itself.  The controller object will run the flow of the game.  The board object will deal with anything involving the objects on the board his notable members are the data structures of all the moving objects and non-moving objects.  
The controller also has a member from Class Menu, oversees loading all the menus that there are (main menu, after winning, after losing).
Speeds: We made the smart enemy slightly slower than the player because he doesn’t need time to press keys or think where to go, so he gets places faster. If he was the same speed or faster he catches up with the player extremely fast because of the user’s change of direction.
The patrol and stupid enemy are slightly faster than the player to make them harder to pass
Files:
Header files:
BaseEnemy.h, Board.h, Bonus.h, Coin.h, Controller.h, EnemyBonus.h, GameObj.h, Ladder.h, Level.h, Level.h, LifeBonus.h, Macros.h, Menu.h, MovingObj.h, Music.h, PatrolEnemy.h, Player.h, PointBonus.h, Rail.h, SmartEnemy.h, StaticObj.h, StupidEnemy.h, Textures.h, TimeBonus.h, Wall.h.
Cpp Files:
BaseEnemy.cpp, Board.cpp, Bonus.cpp, Coin.cpp, Controller.cpp, EnemyBonus.cpp, GameObj.cpp, Ladder.cpp, Level.cpp, Level.cpp, LifeBonus.cpp, Macros.cpp, Main.cpp, Menu.cpp, MovingObj.cpp, Music.cpp, PatrolEnemy.cpp, Player.cpp, PointBonus.cpp, Rail.cpp, SmartEnemy.cpp, StaticObj.cpp, StupidEnemy.cpp, Textures.cpp, TimeBonus.cpp, Wall.cpp.
Data Structures:
1.	2D vector of unique pointers of Static Objects (associated with Board).
2.	Vector of unique pointers of Moving Objects (associated with Board).
3.	Vector of strings to hold the raw character level (associated with Level).
4.	Vector of textures to hold all the textures we load (associated with Textures).
Board.txt Format
All levels can be placed in the same text file. The line above each level board includes the number of rows then cols then the time allocated for the level (-1 if no time). After each level there is a newline(including the last).
Notable Algorithms:
The SmartEnemy algorithm scans 3 directions depending on the location of the player. If the player is above checks if there is a way up from the left and the right and saves the point at the end of each way up.  If he can move up (on a ladder) will save the location at the end of the ladder or until he’s on the same level as the player. (in some cases a forth move option is checked to help overcome obstacles, these cases are when there is no way to move left or right). After finding the coordinates checks which coordinate is closest to the player therefore signaling that this direction does help the enemy move towards the player. Then moves in the found direction.
Bugs: 
-The player sometimes has trouble getting into tight spots.
-moving between ladders and rails can sometimes be jumpy. 
Miscellaneous:  
The project is compatible with levels of different sizes although we recommend using the sizes: Width: between 30 to 40.  Height: between 20 to 30.  All constant sizes are dependent on the width and height of the window.  To change the size of the window, go to the file Macros.h and change the const WIN_WIDTH and WIN_HEIGHT.
Changes and corrections since the presentation: 
I added the option to only begin once space is pressed as suggested, and improved movement through cracks. Also, due to the comments about not using double dispatch, we tried and even redid the entire project but we didn’t have enough time to deal with movement bugs particularly of the smart enemy, so we chose to submit this version. Enjoy 😊

