## This Makefile is for Windows only! Your python path could be different!
PROGRAM = example_module
CXXFLAGS = -Wall -O2 -march=native

default: ${PROGRAM}.pyd

${PROGRAM}.pyd: ${PROGRAM}.o
	g++ -shared ${PROGRAM}.o -L"C:/ProgramData/Anaconda3/libs" -I"C:/ProgramData/Anaconda3/include" $(CXXFLAGS) -lpython37 -o ${PROGRAM}.pyd -lgomp

${PROGRAM}.o: ${PROGRAM}.cpp
	g++ -I"C:/ProgramData/Anaconda3/include" -D MS_WIN64 $(CXXFLAGS) -c ${PROGRAM}.cpp -o ${PROGRAM}.o -fopenmp

clean:
	rm -f ${PROGRAM}.pyd ${PROGRAM}.o
