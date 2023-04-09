#include "controller.h"
#include "game.h"

Controller::Controller(bool isTesting, std::string floorPlanSrc, bool isSeeded, unsigned seed) : floorPlanSrc{floorPlanSrc} {
    this->mode = (isTesting) ? GameMode::Testing : GameMode::Normal;
    if (isSeeded) {
        this->rng.seed(seed);
    } else {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        this->rng.seed(seed);
    }
};

Controller::~Controller() {
    if (g != nullptr) {
        delete g;
    }
}

void Controller::startGame() {
    std::cout << "Welcome to CC3K+." << std::endl;
    std::cout << "Would you like to play the normal version or the enhanced version? (n or e)" << std::endl;
    std::cout << "n: Normal version." << std::endl;
    std::cout << "e: Enhanced version." << std::endl;

    std::cout << "Welcome to CC3K+." << std::endl;

    bool DLCSelect = false;

    if (mode == GameMode::Normal) {
        // prompt user for normal or enhanced game
        std::cout << "Would you like to play the normal version or the enhanced version of the game? (n or e)" << std::endl;
        std::cout << "n: Normal version." << std::endl;
        std::cout << "e: Enhanced version." << std::endl;
        char cmd;
        std::cin >> cmd;

        // validity check loop
        while (!(cmd == 'n' || cmd == 'e')) {
            std::cout << "Invalid input. Please select (n) for normal version, (e) for enhanced version." << std::endl;
            std::cin >> cmd;
        }

        // enable DLC if user selected enhanced version
        if (cmd == 'e') mode = GameMode::DLC;
    }

    int raceSelect;
    int raceCount = (mode == GameMode::DLC) ? 6 : 4;
    std::cout << "Please select your character's race:" << std::endl;

    std::cout << "(1): Human" << std::endl;
    std::cout << "(2): Dwarf" << std::endl;
    std::cout << "(3): Elf" << std::endl;
    std::cout << "(4): Orc" << std::endl;

    if (mode == GameMode::DLC) {
        std::cout << "(5): BonusRace1" << std::endl;
        std::cout << "(6): BonusRace2" << std::endl;
        raceCount = 6;
    }

    std::cin >> raceSelect;

    while (raceSelect < 1 || raceSelect > raceCount) {
        std::cout << "Invalid input. Please select your character's race." << std::endl;
        std::cin >> raceSelect;
    }

    Game* g = new Game{raceSelect-1, floorPlanSrc, mode, rng};
}

void Controller::restartGame() {
    if (this->g != nullptr) {
        delete g;
    }
    startGame();
}

void Controller::quitGame() {
    if (this->g != nullptr) {
        delete g;
    }
}

//TODO: need to implement
void Controller::printGame() {

}

bool Controller::playerAction(char dir1, char dir2, char actionType) {

}

bool Controller::isGameOver() {

}

std::string Controller::getMsg() {
    return msg;
}
