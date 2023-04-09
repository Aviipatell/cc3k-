#include "game.h"
#include "cell.h"
#include "player.h"
#include "enemy.h"
#include "item.h"

Game::Game(int raceSelect, std::string floorPlanSrc, GameMode mode, std::default_random_engine& rng) :
    floorPlanSrc{floorPlanSrc}, mode{mode}, rng{rng} {
        this->p = generatePlayer(getPlayerType(raceSelect));
        if (mode == GameMode::Normal || mode == GameMode::DLC) {
            floorPlanSrc = "FloorPlans/default.txt";
        }
        // Generate BS Floor
        std::uniform_int_distribution<unsigned> selectBSFloor(1, 5);
        this->barrierSuitFloor = selectBSFloor(rng);
        generateNewFloor();
}

void Game::generateNewFloor(){
    ++currentFloor;
    if (currentFloor > 5) {
        std::cout << "You win." << std::endl; // TODO: remove, this is just temporary
        isOver = true;
        return;
    }

    removeFloorEntities();
    isStairsVisible = false;
    loadFloorFromFile();

    // If not testing, proceed to generate + set all required entities
    if (mode != GameMode::Testing) {
        int index;
        std::vector<Cell*> cells;
        std::vector<Cell*> chamberCells;
        for (int row = 0; row < floor.size(); ++row) {
            for (int column = 0; column < floor[row].size(); ++column) {
                if (floor[row][column]->getType() == FloorType::tile) {
                    cells.push_back(floor[row][column]);
                }
            }
        }

        // Generate player with equal probability
        std::uniform_int_distribution<unsigned> selectChamber(1, 5);
        int playerChamber = selectChamber(rng);
        chamberCells = getEmptyCellsFromChamber(cells, playerChamber);
        // NOTE: no need for this while block below..
        while (chamberCells.size() == 0) {
            playerChamber = selectChamber(rng);
            chamberCells = getEmptyCellsFromChamber(cells, playerChamber);
        }
        std::uniform_int_distribution<unsigned> selectPlayerCell(0, chamberCells.size()-1);
        index = selectPlayerCell(rng);
        p->setCell(cells[index]);
        cells[index]->setEntity(p);
        // remove player cell from vector of available cells
        cells.erase(cells.begin() + index); // should not delete the actual cell

        // Generate staircase with equal probability
        int stairCaseChamber = selectChamber(rng);
        chamberCells = getEmptyCellsFromChamber(cells, stairCaseChamber);
        while (playerChamber == stairCaseChamber || chamberCells.size() == 0) {
            stairCaseChamber = selectChamber(rng);
            chamberCells = getEmptyCellsFromChamber(cells, stairCaseChamber);
        }
        std::uniform_int_distribution<unsigned> selectStairCaseCell(0, cells.size()-1);
        index = selectStairCaseCell(rng);
        while (cells[index]->getChamber() == p->getCell()->getChamber()) {
            index = selectStairCaseCell(rng);
        }
        cells[index]->setIsStairCase(true);
        cells.erase(cells.begin() + index);

        // Generate potions with equal probability
        // -> 10 potions per floor,
        // -> any chamber has 1/5 chance to spawn a potion
        // -> 1/6 chance to spawn a particular potion


        // basically:
        // -> loop through this 10 times
        // -> randomly choose an available chamber, 1/5 chance
        // -> randomly choose an empty/availble cell in said chamber.
        // -> pick a number from 1-6 to represent the 6 potions, and generate it.
        int potionSpawnCap = 10;
        for (int potionCount = 0; potionCount < potionSpawnCap; ++potionCount) {
            int potionChamber = selectChamber(rng);
            chamberCells = getEmptyCellsFromChamber(cells, potionChamber);
            while (chamberCells.size() == 0) {
                potionChamber = selectChamber(rng);
                chamberCells = getEmptyCellsFromChamber(cells, playerChamber);
            }
            std::uniform_int_distribution<unsigned> selectPotionCell(0, chamberCells.size()-1);
            index = selectPotionCell(rng);
            std::uniform_int_distribution<unsigned> selectPotionType(0, 5);
            int potionType = selectPotionType(rng);
            Item* i = generateItem(getItemType(potionType)); //TODO: create this function
            items.push_back(i);
            i->setCell(cells[index]);
            cells[index]->setEntity(i);
            cells.erase(cells.begin() + index);
            // convert potionType int to char
        }

        // Generate gold
        int goldSpawnCap = 10;
        for (int goldCount = 0; goldCount < goldSpawnCap; ++goldCount) {
            int goldChamber = selectChamber(rng);
            chamberCells = getEmptyCellsFromChamber(cells, goldChamber);
            while (chamberCells.size() == 0) {
                goldChamber = selectChamber(rng);
                chamberCells = getEmptyCellsFromChamber(cells, goldChamber);
            }
            std::uniform_int_distribution<unsigned> selectGoldCell(0, chamberCells.size()-1);
            index = selectGoldCell(rng);
            std::uniform_int_distribution<unsigned> selectGoldType(1, 8);
            int goldType = selectGoldType(rng);
            int filteredGoldType;
            // if 1-5, normal gold. if 6-7, small goard. if 8, dragon hoard
            if (goldType <= 5) {
                filteredGoldType = 6;
            } else if (goldType <= 7) {
                filteredGoldType = 7;
            } else {
                filteredGoldType = 8;
            }
            Item* i = generateItem(filteredGoldType);
            items.push_back(i);
            i->setCell(cells[index]);
            cells[index]->setEntity(i);
            cells.erase(cells.begin() + index);
        }

        // Generate barrier suit
        if (currentFloor == barrierSuitFloor) {
            int barrierSuitChamber = selectChamber(rng);
            chamberCells = getEmptyCellsFromChamber(cells, barrierSuitChamber);
            while (chamberCells.size() == 0) {
                barrierSuitChamber = selectChamber(rng);
                chamberCells = getEmptyCellsFromChamber(cells, barrierSuitChamber);
            }
            std::uniform_int_distribution<unsigned> selectBSCell(0, cells.size()-1);
            index = selectBSCell(rng);
            Item* i = generateItem('B'); // TODO: set up enum for all these vals
            items.push_back(i);
            i->setCell(cells[index]);
            cells[index]->setEntity(i);
            cells.erase(cells.begin() + index);
        }

        // Generate enemies
        int enemySpawnCap = 20;
        int enemyCount = 0;
        for (int i = 0; i < items.size(); ++i) {
            if (items[i].getIsProtected()) {
                Enemy* e = generateEnemy('D');
                items[i]->setProtector(e);
            }
            ++enemyCount;
        }

        for (; enemyCount < 20; ++enemyCount) {
            // generate enemy
            std::uniform_int_distribution<unsigned> selectEnemyType(1, 18);
            int enemyType = selectEnemyType(rng);
            char filteredEnemyType;
            if (enemyType < 5) {
                // Werewolf: 4/18 odds
                filteredEnemyType = 'W';
            } else if (enemyType < 8) {
                // Vampire: 3/18 odds
                filteredEnemyType = 'V';
            } else if (enemyType < 13) {
                // Goblin: 5/18 odds.
                filteredEnemyType = 'N';
            } else if (enemyType < 15) {
                // Troll: 2/18 odds
                filteredEnemyType = 'X';
            } else if (enemyType < 17) {
                // Pheonix: 2/18 odds
                filteredEnemyType = 'X';
            } else {
                // Merchant: 2/18 odds
                filteredEnemyType = 'M';
            }
            Enemy* e = generateEnemy(filteredEnemyType);
            enemies.push_back(e);

            // get enemy position
            int enemyChamber = selectChamber(rng);
            chamberCells = getEmptyCellsFromChamber(cells, enemyChamber);
            while (chamberCells.size() == 0) {
                enemyChamber = selectChamber(rng);
                chamberCells = getEmptyCellsFromChamber(cells, enemyChamber);
            }
            std::uniform_int_distribution<unsigned> selectEnemyCell(0, chamberCells.size() - 1);
            index = selectEnemyCell(rng);
            e->setCell(cells[index]);
            cells[index]->setEntity(e);
            cells.erase(cells.begin() + index);
        }

        // -> get a vector of all floor tiles in vector<<>> floor
        // -> uniform distribution from 0 to cells.size() to pick cell for player
        // -> then, again for stairs (repeat until picked cell !in player chamber)
        // -> NOTE: remove picked cells from our vector of cells as we go on

        // -> 1. set player position
        // -> 2. set stairs (ensure player and stairs are in a different chamber)
        // -> 3. generate + set potions
        // -> 4. generate + set gold
        // -> 5. potentially generate barrier suit
        // -> 5. generate + set dragons for dragon hoards and barrier suit
        // -> 6. generate + set remaining enemies
    } else {
        // Floor entities have already been loaded in
    }

    // if DLC mode, where chance of any enemy having an item, override selected enemies item
    int numEnemies = enemies.size();
    std::uniform_int_distribution<unsigned> selectCompassHolder(0, numEnemies - 1);
    int compassHolderIndex = selectCompassHolder(rng);
    enemies[compassHolderIndex]->setHasCompass(true);

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
                FloorType cellType = c->getType();
                assignChambers(c, assignedChambers);
                currentRow.push_back(c);
                ++column;

                if (mode != GameMode::Testing) continue;

                if (cellType == FloorType::player) {
                    p->setCell(c);
                    c->setEntity(p);
                } else if (cellType == FloorType::enemy) {
                    Enemy* e = generateEnemy()

                    Enemy* e = generateEnemy(c->getSymbol());
                    e->setCell(c);
                    c->setEntity(e);
                    enemies.push_back(e);
                    if (c->getSymbol() == 'D') {
                        //TODO: add check to make sure dynamic_cast is not null
                        dragons.push_back(std::dynamic_cast<Dragon*>(e));
                    }
                } else if (c->getType() == FloorType::item) {
                    Item* i = generateItem(c->getSymbol());
                    i->setCell(c);
                    c->setEntity(i);
                    items.push_back(i);
                } else if (c->getType() == FloorType::staircase) {
                    c->setIsStairCase(true);
                }
            }
            // add row of cells to the floor
            floor.push_back(currentRow);
            ++lineCount;
        }

        //TODO:
        if (isTesting) {
            // set up any created dragons to protect their surrounding dragon hoard or bs
        }
        source.close();
    } else {
        std::cout << "Unable to open file." << std::endl;
        // TODO: maybe throw an exception?
    }
}

void Game::assignChambers(Cell* c, std::vector<int>& chambers) {
    Position cPos = c->getPosition();
    int cRow = cPos.row;
    int cColumn = cPos.column;
    FloorType cType = c->getType();

    if (!(cRow >= 1 && cColumn >= 1)) return;
    if (cType == FloorType::wall || cType == FloorType::door || cType == FloorType::passage || cType == FloorType::blank) return;

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

PlayerType Game::getPlayerType(int raceSelect) {
    PlayerType type;
    if (raceSelect == 0) {
        type = PlayerType::Human;
    } else if (raceSelect == 1) {
        type = PlayerType::Dwarf;
    } else if (raceSelect == 2) {
        type = PlayerType::Elf;

    } else if (raceSelect == 3) {
        type = PlayerType::Orc;

    } else if (raceSelect == 4) {
        type = PlayerType::BonusRace1;
    } else {
        type = PlayerType::BonusRace2;
    }
    return type;
}

ItemType Game::getItemType(char itemType) {
    ItemType type;

}
