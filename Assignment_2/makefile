enigma: main.cpp FileSet.o Rotor.o Reflector.o PlugBoard.o Machine.o IOBoard.o errorCheck.o RfPgBase.o
	g++ -Wall -g main.cpp FileSet.o Rotor.o Reflector.o PlugBoard.o Machine.o IOBoard.o errorCheck.o RfPgBase.o -o enigma

Machine.o: Machine.cpp Machine.hpp Rotor.hpp Reflector.hpp PlugBoard.hpp errors.h errorCheck.h RfPgBase.hpp
	g++ -Wall -g -c Machine.cpp

IOBoard.o: IOBoard.cpp IOBoard.h
	g++ -Wall -g -c IOBoard.cpp

errorCheck.o: errorCheck.cpp errorCheck.h errors.h
	g++ -Wall -g -c errorCheck.cpp

FileSet.o: FileSet.cpp FileSet.hpp errors.h errorCheck.h
	g++ -Wall -g -c FileSet.cpp

Rotor.o: Rotor.cpp Rotor.hpp errors.h errorCheck.h
	g++ -Wall -g -c Rotor.cpp

Reflector.o: Reflector.cpp Reflector.hpp RfPgBase.hpp errors.h errorCheck.h
	g++ -Wall -g -c Reflector.cpp

PlugBoard.o: PlugBoard.cpp PlugBoard.hpp RfPgBase.hpp errors.h errorCheck.h
	g++ -Wall -g -c PlugBoard.cpp

RfPgBase.o: RfPgBase.cpp  RfPgBase.hpp errors.h errorCheck.h
	g++ -Wall -g -c RfPgBase.cpp


clean: 
	rm -rf *.o enigma


