#ifndef __GAME_H_
#define __GAME_H_

#include <vector>

enum Direction {
    no,
    so,
    ea,
    we,
    ne,
    nw,
    se,
    sw
};

class Player;
class Cell;
class Item;
class Cell;
class Enemy;

class Game {
    Player *p;
    std::vector<std::vector<Cell *>> floor;

    int level;
    std::vector<Item *> items;
    std::vector<Enemy *> enemies;
    TextDisplay *td;
    bool merchantHostile;
public:
    Game();
    void generateFloor(Player *p);
    void printGame();
    bool isValidCell(Direction dir);
};

#endif

// consider generateEnemy(char type) and generateItem(char type)

// have private field called BarrierSuitFloor, number from 1-5.
// -> when curLevel == BarrierSuitFloor, when generatingItems, generate barrier suit + protect it with a dragon (and so, decrement enemies)

// Game also has a private field, stairsVisible. Upon floor generation, this is reset to false. Upon acquiring compass, this is set to true.

// Game::Game(race, isTesting, floorPlanSrc)
// -> assign values, set initial floor level to 1
// -> call generateFloor()

// Game::generateFloor():
// -> open filestream with floorPlanSrc
// -> getUpper + lowerBound (calculation with curFloorLevel)
// -> if isTesting:
    // -> loop through 25 lines (specified through bounds):
        // -> set up vector<Cell*> curRow
        // -> save each line to string curLine
        // -> open iss to read one char at a time in a loop:
            // -> depending on char, generate specific entity (enemy/item)
            // -> if char == '@', create a player owned by game.
            // -> construct Cell, pass in entity pointer (if it has an entity)
            // -> push cell into curRow vector
        // -> push curRow into floor vector
// -> else:
    // -> loop through 25 times (specfied through bounds):
        // -> set up vector<Cell*> curRow
        // -> save each line to string curLine
        // -> open iss to read one char at a time in a loop:
            // -> generate cell. (no entity, entity will always be null)
    // -> assign chambers
    // -> spawn player (either randomly, or wherever it previously was)
    // -> spawn stairs (ensure it is in a different chamber)
    // -> spawn potions
    // -> spawn gold
    // -> check for any dragon hoards. for each dragon hoard, spawn dragon + decrement enemies needed to spawn
    // -> spawn remaining enemies
    // -> randomly choose one enemy to hold the compass

    
