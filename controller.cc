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

    this->g = new Game{raceSelect-1, floorPlanSrc, mode, rng};
    printGame();
    std::cout << "GAME PRINTED???" << std::endl;
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
    if (g != nullptr) g->print();
    // if (g == nullptr) std::cout << "null game" << std::endl;
}

bool Controller::playerAction(char dir1, char dir2, char actionType) {
    // bool isValid = isValidDirection(dir1, dir2)

    Direction dir = getValidDirection(dir1, dir2);

    if(dir != Direction::NoDirection){

        if(actionType == 'a'){
            g->attack(dir);
        }
        else if(actionType == 'u'){
            g->usePotion(dir);
        }
        else{
            g->movePlayer(dir);
        }
        return true;
    }
    else{
        setMsg("Invalid Input. Please enter a valid direction.");
    }
}

Direction Controller::getValidDirection(char dir1, char dir2){
    if (dir1 == 'n') {
        if (dir2 == 'o') {
            return Direction::NO;
        } else if (dir2 == 'e') {
            return Direction::NE;
        } else if (dir2 == 'w') {
            return Direction::NW;
        } else {
            return Direction::NoDirection;
        }
    } else if (dir1 == 'e') {
        if (dir2 == 'a') {
            return Direction::EA;
        } else if (dir2 == 'n') {
            return Direction::NE;
        } else if (dir2 == 's') {
            return Direction::SE;
        } else {
            return Direction::NoDirection;
        }
    } else if (dir1 == 'w') {
        if (dir2 == 'e') {
            return Direction::WE;
        } else if (dir2 == 'n') {
            return Direction::NW;
        } else if (dir2 == 's') {
            return Direction::SW;
        } else {
            return Direction::NoDirection;
        }
    } else if (dir1 == 's') {
        if (dir2 == 'o') {
            return Direction::SO;
        } else if (dir2 == 'e') {
            return Direction::SE;
        } else if (dir2 == 'w') {
            return Direction::SW;
        } else {
            return Direction::NoDirection;
        }
    } else {
        return Direction::NoDirection;
    }
}

bool Controller::isGameOver() {

}

std::string Controller::getMsg() {
    return msg;
}

void Controller::setMsg(std::string msg) {
    this->msg = msg;
}
