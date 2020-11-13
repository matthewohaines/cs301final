EXECS = Processor
OBJS = Processor.o InstructionMemory.o ASM.o ASMParser.o Instruction.o Opcode.o RegisterTable.o MainControlUnit.o Multiplexor.o SignExtendUnit.o ALU.o PCCounter.o RegisterFile.o ALUControlUnit.o

CC = g++
CCFLAGS = -std=c++17

all: $(EXECS)

Processor: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

%.o: %.cpp %.h
	$(CC) $(CCFLAGS) -c $<

%.o: lab5/%.cpp lab5/%.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

clean:
	/bin/rm -f a.out $(OBJS) $(EXECS)