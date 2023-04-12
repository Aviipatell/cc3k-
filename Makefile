CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
OBJECTS = barrierSuit.o baStatus.o bdStatus.o cell.o character.o compass.o controller.o dragon.o dwarf.o elf.o enemy.o entity.o game.o goblin.o gold.o human.o item.o main.o merchant.o orc.o phoenix.o phStatus.o player.o potion.o rhStatus.o statusEffect.o troll.o vampire.o waStatus.o wdStatus.o werewolf.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
