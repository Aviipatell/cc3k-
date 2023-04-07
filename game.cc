#include "game.h"

Game::Game(int raceSelect, bool DLCSelect, bool isTesting, std::string floorPlanSrc, std::default_random_engine& rng) :
    DLC{DLCSelect}, isTesting{isTesting}, floorPlanSrc{floorPlanSrc}, rng{rng} {
        Player* p = generatePlayer(raceSelect); // TODO: define+declare this function

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
            while (std::getline(source, currentLine)) {
                if (lineCount < lowerBound) continue;
                if (lineCount > upperBound) break;

                // go through all the characters in the line
                std::istringstream iss{currentLine};
                char currentChar;
                std::vector<Cell*> currentRow;
                while (iss >> std::noskipws >> currentChar) {
                    // create cell, chamber detection done simulatenously
                }

            }
    } else {
        std::cout << "Unable to open file." << std::endl;
        source.close(); // TODO: maybe throw an exception?
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
