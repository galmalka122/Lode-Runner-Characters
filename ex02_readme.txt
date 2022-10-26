ex: 
	ex2

names:
	 gal meir malka-201647211 and yaniv sonino-207205683

description:
	 the program gets a map file and build the lode runner game by the file.

design:
	Board- reads the map and responsable for setting the player's and enemies first locations, and print the board for each move.

	Player-responsable to get a key and move the player on board, and keep the current life remaining and holds the shape of the player.

	Enemy-responsable to get the player's location after the player's turn, and than finds the best way to make the player lose.

	GameController-responsable to keep all objects connecting with each other and keep the game running, checks the game data and 
		            decides which move is valid , and updates the score , current level , and the maximum score available.
	
files added:
	Board.txt-a text file contains all the maps.

main structures:
                     Location-which is an array of 2 integer variables representing each object's location on the board.
	enemyArmy-Vector of Enemy objects, holds all enemies in the game
	level-vector of strings, holds the map of each level.
	
worth mentioned algorithems:
	gravityPlayer-check if the player needs to fall and updates the location until he gets to the closest floor.
	gravityEnemy-the same as player just inside a loop for each enemy.
	moveEnemy-decides the best way for the enemy to get to the player and make him lose.
	
known bugs:
	

notes:
	the movement on the ropes is from beneath it and not on the same row of the rope (like the original game).
	the player can jump to the side while climbing ladders and.
