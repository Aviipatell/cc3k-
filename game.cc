#include "game.h"
#include "cell.h"
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "statusEffect.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include "gold.h"
#include "compass.h"
#include "barrierSuit.h"
#include "dragon.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "werewolf.h"
#include "merchant.h"
#include "phoenix.h"
#include <sstream>
#include <random>

Game::Game(int raceSelect, std::string floorPlanSrc, GameMode mode, std::default_random_engine& rng) :
    floorPlanSrc{floorPlanSrc}, mode{mode}, rng{rng} {
        this->p = generatePlayer(raceSelect);
        if (mode == GameMode::Normal || mode == GameMode::DLC) {
            this->floorPlanSrc = "SampleFloorPlan.txt";
        }
        // Generate BS Floor
        std::uniform_int_distribution<unsigned> selectBSFloor(1, 5);
        this->barrierSuitFloor = selectBSFloor(rng);
        generateNewFloor();
}

std::vector<Cell*> Game::getEmptyCells() {
    std::vector<Cell*> cells;
    for (int row = 0; row < floor.size(); ++row) {
        for (int column = 0; column < floor[row].size(); ++column) {
            Cell* cell = floor[row][column];
            if (cell->getType() == FloorType::Tile && !(cell->getHasEntity())) {
                cells.push_back(cell);
            }
        }
    }
    return cells;
}

void Game::generateNewFloor(){
    ++currentFloor;
    if (currentFloor > 5) {
        std::cout << "You win." << std::endl;
        isOver = true;
        return;
    }

    removeFloorEntities();
    isStairsVisible = false;
    loadFloorFromFile();

    std::cout << "File loaded.." << std::endl;

    int index;
    Cell* randomCell;
    std::vector<Cell*> cells = getEmptyCells();

    std::cout << "generating entities.." << std::endl;
    std::cout << cells.size() << std::endl;

    // If not testing, generate all entities ourselves
    if (mode != GameMode::Testing) {

        // Player position
        randomCell = getRandomEmptyCellFromRandomChamber(cells);
        index = getIndexOfCell(randomCell, cells);
        p->setCell(randomCell);
        randomCell->setEntity(p);
        cells.erase(cells.begin() + index);

        std::cout << "Generated player" << std::endl;

        // Staircase position
        int playerChamber = p->getCell()->getChamber();
        randomCell = getRandomEmptyCellFromRandomChamber(cells, playerChamber);
        index = getIndexOfCell(randomCell, cells);
        randomCell->setIsStairCase(true);
        cells.erase(cells.begin() + index);

        std::cout << "Generated staircase" << std::endl;

        // Potion generation + position
        int potionSpawnCap = 10;
        for (int potionCount = 0; potionCount < potionSpawnCap; ++potionCount) {
            std::uniform_int_distribution<unsigned> selectPotionType(0, 5);
            int potionType = selectPotionType(rng);
            std::cout << "Potion type: " << potionType << std::endl;
            char entityType = potionType + '0';
            Entity* e = generateEntity(entityType);
            std::cout << "Items size: " << items.size() << std::endl;
            randomCell = getRandomEmptyCellFromRandomChamber(cells);
            index = getIndexOfCell(randomCell, cells);
            if (e)  {
                std::cout << "valid entity generated cell" << std::endl;
            }
            std::cout << "randomCellIndex: " << index << std::endl;
            e->setCell(randomCell);
            std::cout << "testetgsgesgsg" << std::endl;
            randomCell->setEntity(e);
            std::cout << "about to delete cell.." << std::endl;
            cells.erase(cells.begin() + index);
            std::cout << "deleted cell.." << std::endl;
        }

        std::cout << "Generated potions" << std::endl;

        // Gold generation + position
        int goldSpawnCap = 10;
        for (int goldCount = 0; goldCount < goldSpawnCap; ++goldCount) {
            std::uniform_int_distribution<unsigned> selectGoldType(1, 8);
            int goldType = selectGoldType(rng);
            char filteredType;
            if (goldType <= 5) {
                filteredType = '6';
            } else if (goldType <= 7) {
                filteredType = '7';
            } else {
                filteredType = '8';
            }
            Entity* e = generateEntity(filteredType);
            randomCell = getRandomEmptyCellFromRandomChamber(cells);
            index = getIndexOfCell(randomCell, cells);
            e->setCell(randomCell);
            randomCell->setEntity(e);
            cells.erase(cells.begin() + index);
        }

        std::cout << "Generated gold" << std::endl;

        // Barrier Suit generation + position
        if (currentFloor == barrierSuitFloor) {
            Entity* e = generateEntity('B');
            randomCell = getRandomEmptyCellFromRandomChamber(cells);
            index = getIndexOfCell(randomCell, cells);
            e->setCell(randomCell);
            randomCell->setEntity(e);
            cells.erase(cells.begin() + index);
        }

        // Guardian enemies generation + position
        int enemySpawnCap = 20;
        int enemyCount = 0;
        for (Item* i : items) {
            std::cout << enemyCount << std::endl;
            if (i->getNeedsProtection()) {
                char protectorType = i->getProtectorType();
                Entity* e = generateEntity(protectorType);
                if (e == nullptr) {
                    std::cout << "no entity" << std::endl;
                }
                Cell* itemCell = i->getCell();
                randomCell = getRandomValidNeighbour(itemCell);
                if (randomCell == nullptr) {
                    std::cout << "no randomCell" << std::endl;
                }
                index = getIndexOfCell(randomCell, cells);
                e->setCell(randomCell);
                randomCell->setEntity(e);
                cells.erase(cells.begin() + index);

                std::vector<Item*> guardingItems;
                for (Item* i2: items) {
                    if (i2->getNeedsProtection() && i2 != i && randomCell->isNeighbour(i2->getCell())) {
                        guardingItems.push_back(i2);
                    }
                }
                guardingItems.push_back(i);
                i->setIsProtected(true);
                Enemy* temp = dynamic_cast<Enemy*>(e);
                if (temp) temp->setGuardedItems(guardingItems);
                ++enemyCount;
            }
            if (enemyCount == enemySpawnCap) break;
        }

        std::cout << "guardian enemies spawned" << std::endl;

        for (; enemyCount < enemySpawnCap; ++enemyCount) {
            std::uniform_int_distribution<unsigned> selectEnemyType(1, 18);
            int enemyType = selectEnemyType(rng);
            char filteredType;
            if (enemyType < 5) {
                filteredType = 'W'; // 4/18 odds
            } else if (enemyType < 8) {
                filteredType = 'V'; // 3/18 odds
            } else if (enemyType < 13) {
                filteredType = 'N'; // 5/18 odds
            } else if (enemyType < 15) {
                filteredType = 'T'; // 2/18 odds
            } else if (enemyType < 17) {
                filteredType = 'X'; // 2/18 odds
            } else {
                filteredType = 'M'; // 2/18 odds
            }
            Entity* e = generateEntity(filteredType);
            randomCell = getRandomEmptyCellFromRandomChamber(cells);
            index = getIndexOfCell(randomCell, cells);
            e->setCell(randomCell);
            randomCell->setEntity(e);
            cells.erase(cells.begin() + index);
        }

        if (mode == GameMode::DLC) {
            // DLC ENEMY ITEM DROPS HERE
        }

    }

    std::cout << "Shit randomly generated properly.." << std::endl;

    int numEnemies = enemies.size();
    std::uniform_int_distribution<unsigned> selectCompassHolder(0, numEnemies-1);
    int compassIndex = selectCompassHolder(rng);
    enemies[compassIndex]->setHasItem(true);
    enemies[compassIndex]->setItemSymbol('C'); // TODO: needs functional delete enemies

    // TODO: set game action msg
    if (currentFloor == 1) {
        setGameMessage("Player has spawned.");
    }
}

std::vector<Cell*> Game::getEmptyCellsFromChamber(std::vector<Cell*> cells, int chamber) {
    std::vector<Cell*> emptyCells;
    for (int i = 0; i < cells.size(); ++i) {
        if (cells[i]->getChamber() == chamber && cells[i]->getType() == FloorType::Tile) {
            emptyCells.push_back(cells[i]);
        }
    }
    return emptyCells;
}

void Game::loadFloorFromFile() {
    int lowerBound = (currentFloor - 1) * 25;
    int upperBound = (currentFloor * 25) - 1;
    int lineCount = 0;

    std::cout << "Testing.." << std::endl;
    std::ifstream source{floorPlanSrc};

    std::cout << "Testing.." << std::endl;


    std::string currentLine;
    std::vector<int> assignedChambers;
    while (std::getline(source, currentLine)) {
        std::cout << currentLine << std::endl;
        if (lineCount < lowerBound) continue;
        if (lineCount > upperBound) break;

        // Parse characters in current line
        std::istringstream iss{currentLine};
        char currentChar;
        int row = lineCount - lowerBound;
        int column = 0;
        std::vector<Cell*> currentRow;
        floor.push_back(currentRow);
        while (iss >> std::noskipws >> currentChar) {


            std::cout << "Row: " << row << std::endl;
            std::cout << "Col: " << column << std::endl;

            Cell* c = new Cell{row, column, currentChar};
            std::cout << "Assigning chambers.." << std::endl;
            assignChambers(c, assignedChambers);
            std::cout << "assigned chambers.." << std::endl;
            floor[row].push_back(c);
            ++column;

            if (mode != GameMode::Testing) continue;

            if (!c->getHasEntity()) continue;

            if (currentChar == '@') {
                p->setCell(c);
                c->setEntity(p);
            } else {
                Entity* e = generateEntity(currentChar);
                e->setCell(c);
                c->setEntity(e);
            }
        }
        // add row of cells to the floor
        // floor.push_back(currentRow);
        ++lineCount;
    }

    for (int i = 0; i < floor.size(); ++i){
        for (int j = 0; j < floor[i].size(); ++j) {
            Cell* c = floor[i][j];
            std::cout << "Cell at " << i << "," << j << " is chamber:" << c->getChamber()  << std::endl;
        }
    }
    source.close();

    std::cout << "Testing.." << std::endl;
    std::cout << "Floor size: " << floor.size() << std::endl;

    // if (source.is_open()) {

    //     source.close();
    // } else {
    //     std::cout << "Unable to open file." << std::endl;
    // }

    // Set up Guardian enemies
    if (mode == GameMode::Testing) {
        for (Enemy* enemy : enemies) {
            if (enemy->getIsGuardian()) {
                std::vector<Item*> guardedItems;
                Cell* enemyCell = enemy->getCell();
                for (Item* i: items) {
                    if (i->getNeedsProtection() && enemyCell->isNeighbour(i->getCell())) {
                        guardedItems.push_back(i);
                        i->setIsProtected(true);
                    }
                }
                enemy->setGuardedItems(guardedItems);
            }
        }
    }
}

void Game::print() {

    std::cout << "---- printing game ----" << std::endl;

    int sizeHeight = this->floor.size();
    int sizeWidth = this->floor[0].size();
    // ANSI colour codes
    const std::string grey("\033[0;90m");
    const std::string brown("\033[0;33m");
    const std::string playerGreen("\e[1;92m");
    const std::string floorGreen("\e[0;32m");
    const std::string black("\033[0;30m");

    // original colour
    const std::string reset("\033[0m");

    for (int i = 0; i < sizeHeight; ++i) {
        for (int j = 0; j < sizeWidth; ++j) {
            char symbol = floor[i][j]->getSymbol();
            if (symbol == '.') std::cout << floorGreen;
            else if (symbol == ' ') std::cout << black;
            else if (symbol == '#') std::cout << grey;
            else if (symbol == '@') std::cout << playerGreen;
            else if (symbol == '|' || symbol == '-') std::cout << brown;
            std::cout << symbol << reset;
        }
        std::cout << std::endl;
    }
    std::cout << "Race: " << p->getRace() << " ";
    std::cout << "Gold: " << p->getPlayerGold() << " ";
    std::cout << "Floor: " << getCurrentFloor() << std::endl;
    std::cout << "HP: " << p->getHealth() << std::endl;
    std::cout << "Atk: " << p->getAttack() << std::endl;
    std::cout << "Def: " << p->getDefence() << std::endl;
    std::cout << "Action: " << getGameMessage() << std::endl;
}

Player* Game::generatePlayer(int playerType) {
    Player* p;
    if (playerType == 0) {
        p = new Human{};
    } else if (playerType == 1) {
        p = new Dwarf{};
    } else if (playerType == 2) {
        p = new Elf{};
    } else {
        p = new Orc{};
    }
    return p;
 }

void Game::clearPlayerStatus() {
    StatusEffect* curStatus = dynamic_cast<StatusEffect*>(p);
    while(curStatus != nullptr) {
        p = curStatus->getNext();
        StatusEffect* temp = dynamic_cast<StatusEffect*>(p);
        delete curStatus;
        curStatus = temp;
    }
}

Entity* Game::generateEntity(char entityType) {
    std::cout << "Generating entity.." << std::endl;
    std::cout << entityType << std::endl;
    Enemy* enemy = nullptr;
    Item* item = nullptr;
    switch(entityType) {
        case 'V':
            enemy = new Vampire{};
            enemies.push_back(enemy);
            break;
        case 'W':
            enemy = new Werewolf{};
            enemies.push_back(enemy);
            break;
        case 'T':
            enemy = new Troll{};
            enemies.push_back(enemy);
            break;
        case 'N':
            enemy = new Goblin{};
            enemies.push_back(enemy);
            break;
        case 'M':
            enemy = new Merchant{};
            enemy->setIsHostile(isMerchantHostile);
            enemy->setHasItem(true);
            enemy->setItemSymbol('8');
            enemies.push_back(enemy);
            break;
        case 'D':
            enemy = new Dragon{};
            enemy->setIsGuardian(true);
            enemies.push_back(enemy);
            break;
        case 'X':
            enemy = new Phoenix{};
            enemies.push_back(enemy);
            break;
        case 'C':
            item = new Compass{false};
            items.push_back(item);
            break;
        case 'B':
            item = new BarrierSuit{true};
            item->setProtectorType('D');
            items.push_back(item);
            break;
        case '0':
            item = new Potion{false, entityType};
            items.push_back(item);
            break;
        case '1':
            item = new Potion{false, entityType};
            items.push_back(item);
            break;
        case '2':
            std::cout << "Creating 2.." << std::endl;
            item = new Potion{false, entityType};
            items.push_back(item);
            break;
        case '3':
            item = new Potion{false, entityType};
            items.push_back(item);
            break;
        case '4':
            item = new Potion{false, entityType};
            items.push_back(item);
            break;
        case '5':
            item = new Potion{false, entityType};
            items.push_back(item);
            break;
        case '6':
            item = new Gold{false, entityType};
            items.push_back(item);
            break;
        case '7':
            item = new Gold{false, entityType};
            items.push_back(item);
            break;
        case '8':
            item = new Gold(false, entityType);
            items.push_back(item);
            break;
        case '9':
            item = new Gold(true, entityType);
            item->setProtectorType('D');
            items.push_back(item);
            break;
    }
    if (enemy != nullptr) {
        return enemy;
    } else {
        return item;
    }
}

void Game::removeFloorEntities() {
    for (int row = 0; row < floor.size(); ++row) {
        for (int column = 0; column < floor[row].size(); ++column) {
            delete floor[row][column];
        }
        floor[row].clear();
    }
    floor.clear();

    if (enemies.size() != 0) {
        for (int i = 0; i < enemies.size(); ++i) {
            delete enemies[i];
        }
    }
    enemies.clear();

    if (items.size() != 0) {
        for (int i = 0; i < enemies.size(); ++i) {
            delete items[i];
        }
    }
    items.clear();
}

Cell* Game::getRandomEmptyCellFromRandomChamber(std::vector<Cell*> cells, int restrictedChamber) {
    std::uniform_int_distribution<unsigned> selectChamber(1, 5);
    int chamber = selectChamber(rng);
    std::cout << chamber << std::endl;
    std::vector<Cell*> chamberCells = getEmptyCellsFromChamber(cells, chamber);
    for (auto& i : chamberCells) {
        std::cout << i->getPosition().row << " " << i->getPosition().column << std::endl;
        break;
    }
    while (chamberCells.size() == 0 || (restrictedChamber == chamber)) {
        chamber = selectChamber(rng);
        chamberCells = getEmptyCellsFromChamber(cells, chamber);
    }
    std::uniform_int_distribution<unsigned> selectCell(0, chamberCells.size() - 1);
    int cellIndex = selectCell(rng);
    return chamberCells[cellIndex];
}

int Game::getIndexOfCell(Cell* cell, std::vector<Cell*> cells) {
    for (int i = 0; i < cells.size(); ++i) {
        if (cell == cells[i]) return i;
    }
    return -1;
}

Cell* Game::getRandomValidNeighbour(Cell* cell) {
    std::vector<Cell*> validNeighbours;
    for (Cell* c : cell->getNeighbours()) {
        if (c->getType() == FloorType::Tile && !c->getHasEntity() && !c->getIsStairCase()) {
                validNeighbours.push_back(c);
        }
    }
    if (validNeighbours.size() == 0) return nullptr;
    std::uniform_int_distribution<unsigned> selectNeighbour(0, validNeighbours.size() - 1);
    int index = selectNeighbour(rng);
    return validNeighbours[index];
}

void Game::assignChambers(Cell* c, std::vector<int>& chambers) {
    std::cout << "In assigning chambers.." << std::endl;
    Position cPos = c->getPosition();
    int cRow = cPos.row;
    int cColumn = cPos.column;
    FloorType cType = c->getType();

    if (!(cRow >= 1 && cColumn >= 1)) return;
    if (cType != FloorType::Tile) return;

    std::cout << "Get chambers..." << std::endl;
    std::cout << cRow << std::endl;
    std::cout << cColumn << std::endl;

    std::cout << "Floor size: " << floor.size() << std::endl;

    int topChamber = floor[cRow-1][cColumn]->getChamber();
    int leftChamber = floor[cRow][cColumn-1]->getChamber();
    int currentChamber;

    std::cout << "Chambers retrieved.." << std::endl;

    if (topChamber != -1 && leftChamber != -1) {
        // top cell + left cell are valid cells with a chamber
        if (topChamber == leftChamber) {
            currentChamber = topChamber;
        } else {
            // conflicting chambers detected.
            // -> use topChamber as precedent,
            // -> get all existing cells in leftChamber, convert to topChamber
            for (int row = 0; row <= cRow; ++row) {
                for (int col = 0; col < floor[0].size(); ++col) {
                    if (row == cRow && col == cColumn) break;
                    if (floor[row][col]->getChamber() == leftChamber) {
                        floor[row][col]->setChamber(topChamber);
                    }
                }
            }
            // pop off leftChamber from chambers vector
            int leftChamberIndex;
            for (int i = 0; i < chambers.size(); ++i) {
                if (leftChamber == chambers[i]) leftChamberIndex = i;
            }
            chambers.erase(chambers.begin() + leftChamberIndex);
            currentChamber = topChamber;
        }

    } else if (topChamber != -1) {
        // only top cell is a valid cell with a chamber
        currentChamber = topChamber;
    } else if (leftChamber != -1) {
        // only left cell is a valid cell with a chamber
        currentChamber = leftChamber;
    } else {
        // neither top cell or left cell is a valid cell with a chamber
        currentChamber = getUnsetChamber(chambers);
        c->setChamber(currentChamber);
        chambers.push_back(currentChamber);
    }
    // set current chamber
    c->setChamber(currentChamber);
}

int Game::getUnsetChamber(std::vector<int>& chambers) {
    if (chambers.size() == 0) {
        return 1;
    }
    int chamberNum = 1;
    while (true) {
        bool chamberExists = false;
        for (int i = 0; i < chambers.size(); ++i) {
            if (chamberNum == chambers[i]) {
                chamberExists = true;
            }
        }
        if (!chamberExists) {
            return chamberNum;
        } else {
            ++chamberNum;
        }
    }
}

void Game::setGameMessage(std::string gameMessage) {
    this->gameMessage = gameMessage;
}

std::string Game::getGameMessage() const {
    return this->gameMessage;
}

std::string Game::getDirectionValue(Direction dir) {
    if (dir == Direction::NO) {
        return "North";
    } else if (dir == Direction::NE) {
        return "North East";
    } else if (dir == Direction::EA) {
        return "East";
    } else if (dir == Direction::SE) {
        return "South East";
    } else if (dir == Direction::SO) {
        return "South";
    } else if (dir == Direction::SW) {
        return "South West";
    } else if (dir == Direction::WE) {
        return "West";
    } else if (dir == Direction::NW) {
        return "North West";
    }
}

void Game::movePlayer(Direction dir){
    setGameMessage("");

    Cell* newCell = getCellAtDirection(dir);
    Cell* currentCell = p->getCell();
    std::ostringstream o;

    FloorType type = newCell->getType();
    std::string direction = getDirectionValue(dir);

    if (type == FloorType::Door || type == FloorType::Passage) {
        newCell->setEntity(p);
        currentCell->setEntity(nullptr);
        p->setCell(newCell);
    } else if (type == FloorType::Tile) {
        std::cout << "testicles" << std::endl;
        // check entity
        if (newCell->getIsStairCase()) {
            generateNewFloor();
            o << "PC moved " << direction << " and went down the staircase. PC is on level " << currentFloor<< ". ";
        } else if (currentCell->getHasEntity()) {
            // if staircase, move player to that position -> generateNewFloor (check random player)
            Entity* e = newCell->getEntity();
            if (e->getSymbol() == 'C') {
                Item* i = dynamic_cast<Item*>(e);
                i->useItem(p);
                deleteEntity(i);
                newCell->setEntity(p);
                currentCell->setEntity(nullptr);
                p->setCell(newCell);
            } else if (e->getSymbol() == 'G') {
                // process gold
                Item* i = dynamic_cast<Item*>(i);
                if (i->getIsProtected()) {
                    o << "Gold Hoard is still protected. Can't pick it up. ";
                } else {
                    i->useItem(p);
                    deleteEntity(i);
                    newCell->setEntity(p);
                    currentCell->setEntity(nullptr);
                    p->setCell(newCell);
                }
            } else if (e->getSymbol() == 'B') {
                // process BS
                Item* i = dynamic_cast<Item*>(e);
                if (i->getIsProtected()) {
                    o << "Barrier Suit is still protected. Can't pick it up. ";
                } else {
                    i->useItem(p);
                    deleteEntity(i);
                    o << "PC equipped barrier suit. ";
                    newCell->setEntity(p);
                    currentCell->setEntity(nullptr);
                    p->setCell(newCell);
                }
            } else if (e->getSymbol() == 'P') {
                // process potion
                o << "PC moved " << direction << " and ran into a potion. Unable to move into potion, try using it instead. ";
            }
        } else {
            // move
            newCell->setEntity(p);
            currentCell->setEntity(nullptr);
            p->setCell(newCell);
        }
    } else {
        int hitHeadDmg = 1;
        o << "PC tried moving " << direction << " and ran into a wall. PC lost " << hitHeadDmg << " HP. ";
    }

    // Look for nearby items
    o << scoutNeighboursForItems(newCell);
    setGameMessage(o.str());
    moveEnemies();
}

std::string Game::scoutNeighboursForItems(Cell* currentCell) {
    std::string surroundingItems;
    for (Cell* c : currentCell->getNeighbours()) {
        if (c->getHasEntity()) {
            Entity* e = c->getEntity();
            Item* i = dynamic_cast<Item*>(e);
            if (i != nullptr) {
                if (i->getSymbol() == 'C') {
                    surroundingItems+= "PC sees a Compass. ";
                } else if (i->getSymbol() == 'B') {
                    surroundingItems+= "PC sees a Barrier Suit. ";
                } else if (i->getSymbol() == 'G') {
                    surroundingItems+= "PC sees Gold. ";
                } else if (i->getSymbol() == 'P') {
                    Potion* p = dynamic_cast<Potion*>(i);
                    if (p != nullptr) {
                        if (isKnownPotion(p->getPotionType())) {
                            std::string name = "";
                            if (p->getPotionType() == PotionType::RHPotion) {
                                name="RH";
                            } else if (p->getPotionType() == PotionType::BAPotion) {
                                name="BA";
                            } else if (p->getPotionType() == PotionType::BDPotion) {
                                name="BD";
                            } else if (p->getPotionType() == PotionType::PHPotion) {
                                name="PH";
                            } else if (p->getPotionType() == PotionType::WAPotion) {
                                name="WA";
                            } else if (p->getPotionType() == PotionType::WDPotion) {
                                name="WD";
                            }
                            surroundingItems+= "PC sees a " + name + " Potion. ";
                        } else {
                            surroundingItems+= "PC sees an unknown Potion. ";
                        }
                    }
                }
            }
        }
    }
    return surroundingItems;
}

bool Game::isKnownPotion(PotionType potion) {
    bool isKnown = false;
    for (PotionType pt : knownPotions) {
        if (pt == potion) {
            return true;
        }
    }
    return false;
}

void Game::attack(Direction dir) {
    setGameMessage("");

    Cell* c = getCellAtDirection(dir);
    Enemy* enemy = dynamic_cast<Enemy*>(c->getEntity());
    std::ostringstream o;

    if (enemy != nullptr) {
        if (enemy->getSymbol() == 'M' && !isMerchantHostile) {
            isMerchantHostile = true;
            setMerchantsHostile();
        }
        std::string attackMessage = p->attack(enemy);

        if(enemy->getHealth() == 0){
            deleteEntity(enemy);
        }

        o << attackMessage << " ";
    } else {
        o << "PC is hallucinating, you WHIFFED!. ";
    }
    setGameMessage(o.str());
    moveEnemies();
}

void Game::setMerchantsHostile() {
    for (Enemy* e : enemies) {
        if (e->getSymbol() == 'M') {
            e->setIsHostile(true);
        }
    }
}

void Game::assignNeighbours() {
    int sizeHeight = this->floor.size();
    int sizeWidth = this->floor[0].size();

    for (int i = 0; i < sizeHeight; ++i) {
        for (int j = 0; j < sizeWidth; ++j) {
            std::vector<Cell*> cell_neighbours;

            // checking for valid neighbours and adding valid ones to the neighbours array
            if (i - 1 > 0) {
                cell_neighbours.push_back(this->floor[i-1][j]);
                if (j - 1 > 0) {
                    cell_neighbours.push_back(this->floor[i-1][j-1]);
                }
                if (j + 1 < sizeWidth) {
                    cell_neighbours.push_back(this->floor[i-1][j+1]);
                }
            }
            if (i + 1 < sizeHeight) {
                cell_neighbours.push_back(this->floor[i+1][j]);
                if (j - 1 > 0) {
                    cell_neighbours.push_back(this->floor[i+1][j-1]);
                }
                if (j + 1 < sizeWidth) {
                    cell_neighbours.push_back(this->floor[i+1][j+1]);
                }
            }
            if (j - 1 > 0) cell_neighbours.push_back(this->floor[i][j-1]);
            if (j + 1 < sizeWidth) cell_neighbours.push_back(this->floor[i][j+1]);

            floor[i][j]->setNeighbours(cell_neighbours);
        }
    }
}

Cell* Game::getCellAtDirection(Direction dir) {
    Position pos = p->getCell()->getPosition();
    int row = pos.row;
    int column = pos.column;
    switch (dir) {
    case NO:
        return floor[row-1][column];
    case SO:
        return floor[row+1][column];
    case EA:
        return floor[row][column+1];
    case WE:
        return floor[row][column-1];
    case NE:
        return floor[row-1][column+1];
    case NW:
        return floor[row-1][column-1];
    case SE:
        return floor[row+1][column+1];
    case SW:
        return floor[row+1][column-1];
    case NoDirection:
        return nullptr;
    }
}

void Game::usePotion(Direction dir) {
    setGameMessage("");

    Cell* c = getCellAtDirection(dir);
    Potion* potion = dynamic_cast<Potion*>(c->getEntity());
    std::ostringstream o;

    if (potion != nullptr) {
        std::string potionMessage = potion->useItem(p);
        PotionType potionType = potion->getPotionType();
        bool isKnown = false;
        for (PotionType type : knownPotions) {
            if (type == potionType) isKnown = true;
        }
        if (!(isKnown)) knownPotions.push_back(potionType);
        o << potionMessage << " ";
    } else {
        o << "PC is hallucinating, there is no potion. ";
    }
    setGameMessage(o.str());
    moveEnemies();
}

void Game::moveEnemies() {
    std::cout << "move enemies is called" << std::endl;
    std::string curMessage = getGameMessage();
    std::ostringstream o;

    int sizeHeight = this->floor.size();
    int sizeWidth = this->floor[0].size();

    for (int i = 0; i < sizeHeight; ++i) {
        for (int j = 0; j < sizeWidth; ++j) {
            std::cout << "reached inner loop" << std::endl;
            if (floor[i][j]->getHasEntity()) {
                bool playerIsNeighbour = false;
                Enemy* enemy = dynamic_cast<Enemy*>(floor[i][j]->getEntity());
                if (enemy == nullptr) std::cout << "enemy is nullptr" << std::endl;
                if (enemy != nullptr) {
                    std::cout << "enemy is not nullptr" << std::endl;
                    if (!(enemy->getHasAlreadyMoved())) {
                        std::cout << "enemy has moved wtd" << std::endl;
                        std::vector<Cell*> enemyNeighbours = enemy->getCell()->getNeighbours();
                        for (Cell* cell : enemyNeighbours) {
                            if (cell->getSymbol() == '@') {
                                playerIsNeighbour = true;
                                if (enemy->getIsHostile()) {
                                    enemy->attack(p);
                                } else {
                                    if (enemy->getIsGuardian()) {
                                        bool shouldAttack = false;
                                        std::vector<Item*> guardedItems = enemy->getGuardedItems();
                                        for (Item* item : guardedItems) {
                                            if (item->getCell()->isNeighbour(cell)) {
                                                shouldAttack = true;
                                            }
                                        }
                                        if (shouldAttack) enemy->attack(p);
                                    }
                                }
                                break;
                            }
                        }
                        if (!(enemy->getIsGuardian())) {
                            if (!(playerIsNeighbour)) {
                                std::cout << "i like men" << std::endl;
                                Cell* newCell = getRandomValidNeighbour(floor[i][j]);
                                if (newCell == nullptr) std::cout << "newCell is nullptr" << std::endl;
                                newCell->setEntity(enemy);
                                floor[i][j]->setEntity(nullptr);
                                enemy->setCell(newCell);
                            }
                        }
                    } else {
                        continue;
                    }
                }
            }
        }
    }

    // reset movement
    for (Enemy* e : enemies) {
        e->setHasAlreadyMoved(false);
    }
}



void Game::deleteEntity(Entity* e) {
    if (dynamic_cast<Item*>(e)) {
        Item* itemToDelete = dynamic_cast<Item*>(e);
        for (int i = 0; i < items.size(); ++i) {
            if (items[i] == itemToDelete) {
                items.erase(items.begin() + i);
                break;
            }
        }
        delete itemToDelete;
    } else {
        Enemy* enemyToDelete = dynamic_cast<Enemy*>(e);
        for (int i = 0; i < enemies.size(); ++i) {
            if (enemies[i] == enemyToDelete) {
                enemies.erase(enemies.begin() + i);
                break;
            }
        }
        if (enemyToDelete->getIsGuardian()) {
            std::vector<Item*> protectedItems = enemyToDelete->getGuardedItems();
            for (Item* item : protectedItems) {
                item->checkProtectors(enemyToDelete);
            }
        }
        if (enemyToDelete->getHasItem()) {
            Entity* e = generateEntity(enemyToDelete->getItemSymbol());
            Item* i = dynamic_cast<Item*>(e);
            if (i == nullptr) {
                delete e;
            } else {
                items.push_back(i);
                Cell* currentCell = enemyToDelete->getCell();
                currentCell->setEntity(i);
                i->setCell(currentCell);
            }
        }
        delete enemyToDelete;
    }
}

int Game::getCurrentFloor() const {
    return currentFloor;
}
