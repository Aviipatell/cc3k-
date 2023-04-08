#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>

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
class TestDisplay;

// see if we can use this anywhere as a single source of truth
enum PlayerRaces {
    Human=0,
    Dwarf,
    Elf,
    Orc,
    BonusRace1,
    BonusRace2
};

class Game {
    Player* p;
    std::vector<std::vector<Cell*>> floor;
    std::vector<Enemy*> enemies;
    std::vector<Item*> items;
    std::string gameAction;

    // will get incremented everytime generateNewFloor is ran?
    int currentFloor = 0;
    int barrierSuitFloor;
    bool isStairsVisible = false;
    bool isMerchantHostile = false;
    bool isOver = false;

    bool isTesting;
    std::string floorPlanSrc;
    bool DLC;

    std::default_random_engine& rng;

    TestDisplay* td;

    public:

        Game(int raceSelect, bool DLCSelect, bool isTesting, std::string floorPlanSrc, std::default_random_engine& rng);
        void generateNewFloor();
        Player* generatePlayer(int raceSelect);
        Enemy* generateEnemy(char type = 0);
        Item* generateItem(char type = 0);

        void removeFloorEntities();
        void assignChambers(Cell* c, std::vector<int>& chambers);
        // void mergeChambers(std::vector<std::vector<Position>>& chambers);
        int getUnsetChamber(std::vector<int>& chambers);
        void loadFloorFromFile();
        std::vector<Cell*> getEmptyCellsFromChamber(std::vector<Cell*> cells, int chamber);


        void attack(char dir1, char dir2);
        void usePotion(char dir1, char dir2);
        void movePlayer(char dir1, char dir2);
        void moveEnemies();
        bool isFinished();

        void print();
};

#endif

// ***** FIELDS ******

// consider generateEnemy(char type) and generateItem(char type)

// have private field called BarrierSuitFloor, number from 1-5.
// -> when curLevel == BarrierSuitFloor, when generatingItems, generate barrier suit + protect it with a dragon (and so, decrement enemies)

// Game also has a private field, stairsVisible. Upon floor generation, this is reset to false. Upon acquiring compass, this is set to true.

// have a private field that stores the games current action/state.

// have a private isOver boolean field that keeps track whether or not the game is over (ie: player has died or player has finished all 5 levels).

// ***** METHODS ****

// Game::Game(race, isTesting, floorPlanSrc)
// -> assign values, set initial floor level to 1
// -> use race to init player
// -> call generateFloor()

// Game::generateNewFloor():
// -> if currentLevel > 5, call a function that prints cleared dungeon graphic + final player stats + final player score (and then possibly a leaderboard or something). set Game::isOver = true. then, break out of this function and let control flow resume back to controller which will call Game::isFinished() which will be true because currentLevel > 5, and thus will prompt user whether they want to quit or restart.
// -> if enemies != null, destroy all enemies.
// -> if items != null, destroy all items.
// -> stairsVisible to false.
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
// -> close filestream with floorPlanSrc?

// Game::attack(dir1, dir2):
// -> get player's position, and the intended square to attack. Call Cell::getType() which should be of type Enemy in this case (modify FloorType enum).
// -> if Cell::getType() != Enemy:
    // -> attack pretty much fails, rest of the game characters get updated. quirky msg added to Game's action field and then exit function
    // -> else, run p.attackEnemy(Cell::getEntity()? or cast that to an Enemy?) and print out information regarding the attack. run p.attackEnemy and then Game::moveEnemies(), and then set the informative action message, followed by exiting to then inevitably be printed.

// Game::usePotion(dir1, dir2):
// -> get player's position, and the intended square to use potion.
// -> if Cell::getType() != Potion:
    // -> use potion pretty much fails, rest of the game characters are updated. quirky msg added to Game's action field and then exit function
    // -> p = new StatusEffect{p}, where StatusEffect is replaced by the specific type of statusEffect inflicted to given player.
    // -> check if Player::isDead, since there is a chance they drank a poison potion which took their HP down to 0. If so, call the function that brings a 'You died.' graphic, + final player stats + message. Then, set Game::isOver to true, which will then be detected via Game::isFinished() method in controller.
    // -> then, run Game::moveEnemies(), and then set the informative action message, followed by exiting to then inevitably printing out the board again

// Game::move(dir1, dir2):
// -> check if Cell::getType = a valid cell to move into (ie: not occupied by an enemy, wall, or item)
    // -> if not valid, run Game::moveEnemies() and print quirky informative msg, ie: you ran into a wall
    // -> else:
        // -> check if Cell::getType == stairCase. if so, move player in specified direction. Then, run generateNewFloor() + set informative action statement.
        // -> otherwise, move player in the specified direction. Then, check neighbours to see if there are any items surrounding you, ie: potion, enemy, etc. If so, add that to informative action msg. Then, run moveEnemies() and add to the informative action msg if necessary.
        // handle known potion logic in Move, since when use any potion P, it will always state potion name

// Game::moveEnemies():
// -> recurse through grid from top left to bottom right. everytime you encounter an enemy:
    // -> check if Enemy is dragon. if so, check if the item it is protected has player as neighbour. if so, attack said player. else, do not move dragon. move on to process next enemy
    // -> if enemy not dragon, check if there is a player in the vicinity.
        // -> if player is neighbour, attack player. add on to the informative message. if Player::isDead, call a function that brings a 'You died' graphic + final player stats (no final player score is generated in this case. they just lose according to program specifications). then, set Game::isOver to true, which will then be detected via Game::isFinished() method in controller
        // -> if no player is neighbour, randomly choose a valid direction it can move to.
    // then, set hasMoved = true and continue to process our next enemy.
    // -> once all enemies have been 'moved', recurse through enemies vector and set hasBeenMoved to false so that they can all be moved during our next turn.

// Game::getIsOver():
// -> returns Game::isOver boolean value

// NOTE: every time a cell is set to have a different value or something, run notifyObservers() to inform the observing textdisplay to also update its grid for that specific cell.
// -> OR, drop TextDisplay all together and just overload the Game output operator to properly print the floor with player stats + action

// SIDE NOTE: think we should definitely set up inventory system, which we will use to store up to 3 potions and 2 weapons (apart from simply punching/kicking enemies.) ie: a weapon can be equipped, unequipped, dropped and picked up (but once you drop a weapon, it's gone.) Potions can also be stored, dropped, and used. Potions stored in your inventory are carried with you throughout subsequent floors/levels.
