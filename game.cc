#include "game.h"
#include "cell.h"
#include "player.h"
#include "enemy.h"
#include "item.h"

Game::Game(int raceSelect, std::string floorPlanSrc, GameMode mode, std::default_random_engine& rng) :
    floorPlanSrc{floorPlanSrc}, mode{mode}, rng{rng} {
        this->p = generatePlayer(raceSelect);
        if (mode == GameMode::Normal || mode == GameMode::DLC) {
            floorPlanSrc = "FloorPlans/default.txt";
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
        std::cout << "You win." << std::endl; // TODO: remove
        isOver = true;
        return;
    }

    removeFloorEntities();
    isStairsVisible = false;
    loadFloorFromFile();

    int index;
    Cell* randomCell;
    std::vector<Cell*> cells = getEmptyCells();

    // If not testing, generate all entities ourselves
    if (mode != GameMode::Testing) {

        // Player position
        randomCell = getRandomEmptyCellFromRandomChamber(cells); // TODO:
        index = getIndexOfCell(randomCell, cells); // TODO:
        p->setCell(randomCell);
        randomCell->setEntity(p);
        cells.erase(cells.begin() + index);

        // Staircase position
        int playerChamber = p->getCell()->getChamber();
        randomCell = getRandomEmptyCellFromRandomChamber(cells, playerChamber);
        index = getIndexOfCell(randomCell, cells);
        randomCell->setIsStairCase(true);
        cells.erase(cells.begin() + index);

        // Potion generation + position
        int potionSpawnCap = 10;
        for (int potionCount = 0; potionCount < potionSpawnCap; ++potionCount) {
            std::uniform_int_distribution<unsigned> selectPotionType(0, 5);
            int potionType = selectPotionType(rng);
            Entity* e = generateEntity(potionType);
            randomCell = getRandomEmptyCellFromRandomChamber(cells);
            index = getIndexOfCell(randomCell, cells);
            e->setCell(randomCell);
            randomCell->setEntity(e);
            cells.erase(cells.begin() + index);
        }

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
            if (i->getNeedsProtection()) {
                char protectorType = i->getProtectorType();
                Entity* e = generateEntity(protectorType);
                Cell* itemCell = i->getCell();
                randomCell = getRandomValidNeighbour(itemCell);
                if (randomCell == nullptr) randomCell = overrideRandomValidNeighbour(itemCell); // TODO:
                index = getIndexOfCell(randomCell, cells);
                e->setCell(randomCell);
                randomCell->setEntity(e);
                if (index == -1) {
                    // no valid spots for an enemy to protect this treasure.
                    enemies.erase(enemies.begin() + enemyCount);
                    delete e;
                    continue;
                } else {
                    cells.erase(cells.begin() + index);
                }
                // parse through items again, for those that are neighbours that need protection and not current item, add to this Enemy's guarding list.
                std::vector<Item*> guardingItems;
                for (Item* i2: items) {
                    if (i2->getNeedsProtection() && i2 != i && randomCell->isNeighbour(i2->getCell())) { // TODO:
                        guardingItems.push_back(i2);
                    }
                }
                guardingItems.push_back(i);
                Enemy* temp = std::dynamic_cast<Enemy*>(e); // might not need, I could just use enemies vec
                if (temp) temp->setGuardedItems(guardedItems); // should modify original pointer
                ++enemyCount;
            }
            // TODO: go through items that needed protection, set them to isProtected = true;
            if (enemyCount == enemySpawnCap) break;
        }

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

    // TODO: set Enemy::guardedItems for Testing GameMode, in loadfloorfromfile

    int numEnemies = enemies.size();
    std::uniform_int_distribution<unsigned> selectCompassHolder(0, numEnemies-1);
    int compassIndex = selectCompassHolder(rng);
    enemies[compassIndex]->setHasItem(true); // should overwrite any other item if any
    enemies[compassIndex]->setItemType('C');

    // TODO: set game action msg
}

std::vector<Cell*> getEmptyCellsFromChamber(std::vector<Cell*> cells, int chamber) {
    std::vector<Cell*> emptyCells;
    for (int i = 0; i < cells.size(); ++i) {
        if (cells[i]->getChamber() == chamber && cells[i]->getType() == FloorType::tile) {
            emptyCells.push_back(cells[i]);
        }
    }
    return emptyCells;
}

void Game::loadFloorFromFile() {
    int lowerBound = (currentFloor - 1) * 5;
    int upperBound = (currentFloor * 5) - 1;
    int lineCount = 0;

    std::ifstream source{floorPlanSrc};
    if (source.is_open()) {
        std::string currentLine;
        std::vector<int> assignedChambers;
        while (std::getline(source, currentLine)) {
            if (lineCount < lowerBound) continue;
            if (lineCount > upperBound) break;

            // Parse characters in current line
            std::istringstream iss{currentLine};
            char currentChar;
            int row = lineCount - lowerBound;
            int column = 0;
            std::vector<Cell*> currentRow;
            while (iss >> std::noskipws >> currentChar) {
                Cell* c = new Cell{row, column, currentChar};
                assignChambers(c, assignedChambers);
                currentRow.push_back(c);
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
            floor.push_back(currentRow);
            ++lineCount;
        }
        source.close();
    } else {
        std::cout << "Unable to open file." << std::endl;
    }

    // Set up Guardian enemies
    if (mode == GameMode::Testing) {
        for (Enemy* enemy : enemies) {
            if (enemy->getIsGuardian()) {
                std::vector<Item*> guardedItems;
                Cell* enemyCell = enemy->getCell();
                for (Item* i: items) {
                    if (i->getNeedsProtection() && enemyCell->isNeighbour(i->getCell())) { // TODO:
                        guardedItems.push_back(i);
                    }
                }
                std::vector<Item*> guardedItems;
                enemy->setGuardedItems(guardedItems);
            }
        }
    }
}

Player* Game::generatePlayer(int playerType) {
    Player p;
    if (playerType == 0) {
        // Generate Human Player
        p = new Human{};
    } else if playerType == 1 {
        // Generate Dwarf Player
        p = new Dwarf{};
    } else if (playerType == 2) {
        // Generate Elf Player
        p = new Elf{};
    } else {
        // Generate Orc Player
        p = new Orc{};
    }
    return p;
 }

Entity* Game::generateEntity(char entityType) {
    switch(entityType) {
        case 'V':
            Enemy* v = new Vampire{}; // TODO: switch specifc classes to Enemy*
            enemies.push_back(v);
            return v;
        case 'W':
            Enemy* w = new Werewolf{};
            enemies.push_back(w);
            return w;
        case 'T':
            Enemy* t = new Troll{};
            enemies.push_back(t);
            return t;
        case 'N':
            Enemy* n = new Goblin{};
            enemies.push_back(n);
            return n;
        case 'M':
            Enemy* m = new Merchant{isMerchantHostile};
            enemies.push_back(m);
            return m;
        case 'D':
            Enemy* d = new Dragon{};
            enemies.push_back(d);
            return d;
        case 'X':
            Enemy* x = new Phoenix{};
            enemies.push_back(x);
            return x;
        case 'B':
            // barrier suit
            return;
        case '0':
            // RHPotion
            return;
        case '1':
            // BAPotion
            return;
        case '2':
            // BDPotion
            return;
        case '3':
            // PHPotion
            return;
        case '4':
            // WAPotion
            return;
        case '5':
            // WDPotion
            return;
        case '6':
            // Normal Gold
        case '7':
            // Small Hoard
        case '8':
            // Merchant Hoard
        case '9':
            // Dragon Hoard
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
    std::vector<Cell*> chamberCells = getEmptyCellsFromChamber(cells, chamber);
    while (chamberCells.size() == 0 || (restrictedChamber == chamber)) {
        chamber = selectChamber(rng);
        chamberCells = getEmptyCellsFromChamber(cells, chamber);
    }
    std::uniform_int_distribution<unsigned> selectCell(0, chamberCells.size() - 1);
    int cellIndex = selectCell(rng);
    return cells[cellIndex];
}

int Game::getIndexOf(Cell* cell, std::vector<Cell*> cells) {
    for (int i = 0; i < cells.size(); ++i) {
        if (cell == cells[i]) return i;
    }
    return -1;
}

Cell* getRandomValidNeighbour(Cell* cell) {
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

Cell* overrideRandomValidNeighbour(Cell* c) {
    std::vector<Cell*> selectedNeighbours;
    for (Cell* c : cell->getNeighbours()) {
        if (c->getType() == FloorType::Tile && !c->getIsStairCase()) {
                if (c->getHasEntity()) {
                    Entity* e = c->getEntity();
                    if (e->getSymbol() == 'P' || e->getSymbol() == 'G') {
                        deleteEntity(e); // TODO: create this function
                        c->setHasEntity(false);
                        selectedNeighbours.push_back(c);
                    }
                }
        }
    }
}

void Game::assignChambers(Cell* c, std::vector<int>& chambers) {
    Position cPos = c->getPosition();
    int cRow = cPos.row;
    int cColumn = cPos.column;
    FloorType cType = c->getType();

    if (!(cRow >= 1 && cColumn >= 1)) return;
    if (cType != FloorType::Tile) return;

    int topChamber = floor[cRow-1][cColumn]->getChamber();
    int leftChamber = floor[cRow][cColumn-1]->getChamber();
    int currentChamber;

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
