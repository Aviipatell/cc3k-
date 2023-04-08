#include "game.h"
#include "cell.h"
#include "player.h"
#include "enemy.h"
#include "item.h"

Game::Game(int raceSelect, bool DLCSelect, bool isTesting, std::string floorPlanSrc, std::default_random_engine& rng) :
    DLC{DLCSelect}, isTesting{isTesting}, floorPlanSrc{floorPlanSrc}, rng{rng} {

        this->p = generatePlayer(raceSelect); // TODO: define+declare this function

        // set floorPlanSrc for !isTesting case
        if (!isTesting) {
            floorPlanSrc = "FloorPlans/default.txt";
        }

        // determine barrierSuitFloor
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

            // go through all the characters in the line
            std::istringstream iss{currentLine};
            char currentChar;
            int row = lineCount - lowerBound;
            int column = 0;
            std::vector<Cell*> currentRow;
            while (iss >> std::noskipws >> currentChar) {

                Cell* c = new Cell{row, column, currentChar};
                assignChambers(c, assignedChambers);
                ++column;

                if (!isTesting) continue;

                if (c->getType() == FloorType::player) {
                    p->setCell(c);
                } else if (c->getType() == FloorType::enemy) {
                    Enemy* e = generateEnemy(c->getSymbol());
                    e->setCell(c);
                    enemies.push_back(e);
                } else if (c->getType() == FloorType::item) {
                    Item* i = generateItem(c->getSymbol());
                    items.push_back(i);
                } else if (c->getType() == FloorType::staircase) {
                    c->setIsStairCase(true);
                }
            }
            ++lineCount;
        }
        source.close();
    } else {
        std::cout << "Unable to open file." << std::endl;
        // TODO: maybe throw an exception?
    }

    if (isTesting) {
        // set up any created dragons to protect their surrounding dragon hoard or bs
    }

    if (!isTesting) {
        // Floor entities have not been generated yet.

        // -> 1. set player position
        // -> 2. set stairs (ensure player and stairs are in a different chamber)
        // -> 3. generate + set potions
        // -> 4. generate + set gold
        // -> 5. potentially generate barrier suit
        // -> 5. generate + set dragons for dragon hoards and barrier suit
        // -> 6. generate + set remaining enemies
    }

    // choose an enemy to hold the compass (uniform distribution between 0-19 or 1-20)
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
            for (int row = 0; row <= cRow; ++i) {
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
