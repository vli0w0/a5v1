CXX = g++
CXXFLAGS = -std=c++14 -MMD -Werror=vla
EXEC = sorcery
OBJECTS = main.o iohandler.o player.o pinfo.o board.o subject.o tsubject.o observer.o card.o minion.o enchantment.o spell.o ritual.o ability.o actability.o trigability.o ascii_graphics.o dinfo.o myinfo.o tinfo.o tstate.o textdisplay.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
