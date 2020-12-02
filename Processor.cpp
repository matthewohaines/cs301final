#include <iostream>
#include <iomanip>
#include <bitset>
#include "InstructionMemory.h"
#include "ALU.h"
#include "ALUControlUnit.h"
#include "MainControlUnit.h"
#include "Multiplexor.h"
#include "SignExtendUnit.h"
#include "PCCounter.h"
#include "RegisterFile.h"
#include "ShiftLeft.h"
#include "DataMemory.h"

using namespace std;

/*
 * Simpulates a processor!!!
 * Prints all inputs and outputs of objects.
 *
 *
 */

bool isWhitespace(char c)    { return (c == ' '|| c == '\t'); }

string removeWhitespace(string str){
  int count = 0; // non-whitespace characters

  // iterate through string, if we have a non-whitespace character, put it at
  // position count and increment count.
  for (size_t i = 0; i < str.length(); i++){
    if (!isWhitespace(str.at(i))){
      str.at(count++) = str.at(i);
    }
  }

  return str.substr(0, count);
}

int main(int argc, char *argv[])
{
  if(argc < 2){
    cerr << "Need to specify a configuration file to translate." << endl;
    exit(1);
  }

  //////////////////////////////////////////////////////////////////////////////
  // Read the configuration file
  bool formatCorrect = true;

  string configuration_file = argv[1];

  string program_input;
  string memory_contents_input;
  string register_file_input;
  string output_mode;
  bool debug_mode = false;
  bool print_memory_contents = false;
  string output_file;
  bool write_to_file = false;  // missing in final project doc (bulleted list)

  ifstream in;
  in.open(configuration_file.c_str());
  if(in.bad()){
    formatCorrect = false;
  }
  else{
    string line;
    string param;
    string value;
    while(getline(in, line)){
      // remove whitespace
      line = removeWhitespace(line);

      // get rid of comments (could contain "=")
      string::size_type idx = line.find('#');
      if (idx != string::npos)
	      line = line.substr(0,idx);

      // looking for "=" to find parameters
      string::size_type idx1 = line.find('=');
      if (idx1 != string::npos) {
        param = line.substr(0,idx1);
        value = line.substr(idx1 + 1);

        // set the parameters
        if (param.find("program_input") != string::npos){
          program_input = value;
        }
        else if (param.find("memory_contents_input") != string::npos) {
          memory_contents_input = value;
        }
        else if (param.find("register_file_input") != string::npos) {
          register_file_input = value;
        }
        else if (param.find("output_mode") != string::npos) {
          output_mode = value;
        }
        else if (param.find("debug_mode") != string::npos) {
          if (value.compare("true") == 0)
            debug_mode = true;
          else if (value.compare("false") == 0)
            debug_mode = false;
        }
        else if (param.find("print_memory_contents") != string::npos) {
          if (value.compare("true") == 0)
            print_memory_contents = true;
          else if (value.compare("false") == 0)
            print_memory_contents = false;
        }
        else if (param.find("output_file") != string::npos) {
          output_file = value;
        }
        else if (param.find("write_to_file") != string::npos) {
          if (value.compare("true") == 0)
            write_to_file = true;
          else if (value.compare("false") == 0)
            write_to_file = false;
        }
      }
    }
  }
  in.close();

  if(formatCorrect == false){
    cerr << "Format of configuration file is incorrect " << endl;
    exit(1);
  }

  if (debug_mode == true){
    cout << "Read configuration file:" << endl;
    cout << "\tprogram_input = " << program_input << endl;
    cout << "\tmemory_contents_input = " << memory_contents_input << endl;
    cout << "\tregister_file_input = " << register_file_input << endl;
    cout << "\toutput_mode = " << output_mode << endl;
    cout << "\tdebug_mode = " << debug_mode << endl;
    cout << "\tprint_memory_contents = " << print_memory_contents << endl;
    cout << "\toutput_file = " << output_file << endl;
    cout << "\twrite_to_file = " << write_to_file << endl << endl;
  }

  ofstream myfile;
  if (write_to_file == true){
    myfile.open (output_file);
    if (debug_mode == true){
      myfile << "Read configuration file:" << endl;
      myfile << "\tprogram_input = " << program_input << endl;
      myfile << "\tmemory_contents_input = " << memory_contents_input << endl;
      myfile << "\tregister_file_input = " << register_file_input << endl;
      myfile << "\toutput_mode = " << output_mode << endl;
      myfile << "\tdebug_mode = " << debug_mode << endl;
      myfile << "\tprint_memory_contents = " << print_memory_contents << endl;
      myfile << "\toutput_file = " << output_file << endl;
      myfile << "\twrite_to_file = " << write_to_file << endl << endl;
    }
  }

  // initialize objects and other variables
  // fetch
  int instCount = 1;
  PCCounter *PC = new PCCounter;
  int PCount;
  ALU *alu1 = new ALU();
  InstructionMemory *instrMem = new InstructionMemory(program_input, debug_mode);

  // decode
  ShiftLeft *shiftLeftJump = new ShiftLeft();
  bitset<32> jumpAdd;
  bitset<32> pc;
  int jumpAddress;
  MainControlUnit *control = new MainControlUnit();
  Multiplexor *muxRegInput = new Multiplexor();
  int writeReg;
  RegisterFile *registers = new RegisterFile(register_file_input);
  SignExtendUnit *signExtend = new SignExtendUnit();

  // execute
  ShiftLeft *shiftLeftBranch = new ShiftLeft();
  ALU *alu2 = new ALU();
  Multiplexor *muxALUInput = new Multiplexor();
  int aluInput2;
  ALUControlUnit *aluControl = new ALUControlUnit();
  ALU *alu3 = new ALU();

  // memory
  Multiplexor *muxBranch = new Multiplexor();
  int addressBranch;
  int branchControl;
  Multiplexor *muxJump = new Multiplexor();
  int addressJump;
  DataMemory *dataMem = new DataMemory(memory_contents_input);
  Multiplexor *muxWriteBack = new Multiplexor();
  int writeBackData;


  int maxAddress = instrMem->getMaxAddress();

  if (debug_mode == true){
    cout << "------------ Start running program -------------" << endl;
    if (write_to_file == true) {
      myfile << "------------ Start running program -------------" << endl;
    }
  }


  // loop
  while ((PCount = PC->getCount()) < maxAddress) {
    if (output_mode.compare("single_step") == 0){
      cout << "Single step output mode, enter a character to continue: ";
      char c;
      cin >> c;
      if (write_to_file == true) {
        myfile << "Single step output mode, enter a character to continue: " << endl;
      }
    }

    cout << dec << "------------------------------ Iteration " << instCount
         << " " << "------------------------------" << endl;
    if (write_to_file == true) {
      myfile << dec << "------------------------------ Iteration " << instCount
             << " " << "------------------------------" << endl;
    }

    // fetch
    cout << "---------- PC ----------" << endl;
    cout << hex << "output: 0x" << PCount << endl << endl;

    cout << hex << "MIPS instruction at address 0x" << PCount << ": " << endl;
    cout << "\t" << instrMem->getInstrMem().at(PCount).getMIPS() << endl << endl;

    if (debug_mode == true) {
      cout << hex << "Binary encoding of instruction at address 0x" << PCount << ": " << endl;
      cout << "\t" << instrMem->getInstrMem().at(PCount).getEncoding() << endl << endl;
    }

    instrMem->decode(PCount);
    cout << "---------- Instruction Memory ----------" << endl;
    cout << "input:" << endl;
    cout << hex << "\tPCount = 0x" << PCount << endl;
    cout << "output:" << endl;
    if (debug_mode == true) {
      cout << "In binary: " << endl;
      cout << "\topcode = " << instrMem->getCurrInstr().substr(0, 6) << endl;       // (Inst[31-26])
      cout << "\trs = " << instrMem->getCurrInstr().substr(6, 5) << endl;           // (Inst[25-21])
      cout << "\trt = " << instrMem->getCurrInstr().substr(11, 5) << endl;          // (Inst[20-16])
      cout << "\trd = " << instrMem->getCurrInstr().substr(16, 5) << endl;          // (Inst[15-11])
      cout << "\tshmat = " << instrMem->getCurrInstr().substr(21, 5) << endl;       // (Inst[10-6])
      cout << "\tfunct = " << instrMem->getCurrInstr().substr(26, 6) << endl;       // (Inst[5-0]
      cout << "\timmediate = " << instrMem->getCurrInstr().substr(16, 16) << endl;  // (Inst[15-0])
      cout << "\tjumpAddress = " << instrMem->getCurrInstr().substr(6, 26) << endl; // (Inst[25-0])

      cout << "In hexadecimal: " << endl;
    }
    cout << hex << "\topcode = 0x" << instrMem->getOpcode() << endl;
    cout << hex << "\trs = 0x" << instrMem->getRs() << endl;
    cout << hex << "\trt = 0x" << instrMem->getRt() << endl;
    cout << hex << "\trd = 0x" << instrMem->getRd() << endl;
    cout << hex << "\tshamt = 0x" << instrMem->getShamt() << endl;
    cout << hex << "\tfunct = 0x" << instrMem->getFunct() << endl;
    cout << hex << "\timmediate = 0x" << instrMem->getImm() << endl;
    cout << hex << "\tjumpAddress = 0x" << instrMem->getJumpAddress() << endl;
    cout << endl;



    alu1->compute(PCount, 4, 2);
    cout << "---------- ALU 1 ----------" << endl;
    cout << "inputs:" << endl;
    cout << hex << "\tinput 1 = 0x" << PCount << endl;
    cout << "\tinput 2 = 0x" << 4 << endl;
    cout << "\tcontrol = 0x" << 2 << endl;
    cout << "output:" << endl;
    cout << hex << "\tresult = 0x" << alu1->getALUResult() << endl;
    cout << endl;

    if (write_to_file == true) {
      myfile << "---------- PC ----------" << endl;
      myfile << hex << "output: 0x" << PCount << endl << endl;

      myfile << hex << "MIPS instruction at address 0x" << PCount << ": " << endl;
      myfile << "\t" << instrMem->getInstrMem().at(PCount).getMIPS() << endl << endl;
      if (debug_mode == true) {
        myfile << hex << "Binary encoding of instruction at address 0x" << PCount << ": " << endl;
        myfile << "\t" << instrMem->getInstrMem().at(PCount).getEncoding() << endl << endl;
      }

      myfile << "---------- Instruction Memory ----------" << endl;
      myfile << "input:" << endl;
      myfile << hex << "\tPCount = 0x" << PCount << endl;
      myfile << "output:" << endl;
      if (debug_mode == true) {
        myfile << "In binary: " << endl;
        myfile << "\topcode = " << instrMem->getCurrInstr().substr(0, 6) << endl;       // (Inst[31-26])
        myfile << "\trs = " << instrMem->getCurrInstr().substr(6, 5) << endl;           // (Inst[25-21])
        myfile << "\trd = " << instrMem->getCurrInstr().substr(11, 5) << endl;          // (Inst[20-16])
        myfile << "\trs = " << instrMem->getCurrInstr().substr(16, 5) << endl;          // (Inst[15-11])
        myfile << "\tshmat = " << instrMem->getCurrInstr().substr(21, 5) << endl;       // (Inst[10-6])
        myfile << "\tfunct = " << instrMem->getCurrInstr().substr(26, 6) << endl;       // (Inst[5-0]
        myfile << "\timmediate = " << instrMem->getCurrInstr().substr(16, 16) << endl;  // (Inst[15-0])
        myfile << "\tjumpAddress = " << instrMem->getCurrInstr().substr(6, 26) << endl; // (Inst[25-0])

        myfile << "In hexadecimal: " << endl;
      }
      myfile << hex << "\topcode = 0x" << instrMem->getOpcode() << endl;
      myfile << hex << "\trs = 0x" << instrMem->getRs() << endl;
      myfile << hex << "\trt = 0x" << instrMem->getRt() << endl;
      myfile << hex << "\trd = 0x" << instrMem->getRd() << endl;
      myfile << hex << "\tshamt = 0x" << instrMem->getShamt() << endl;
      myfile << hex << "\tfunct = 0x" << instrMem->getFunct() << endl;
      myfile << hex << "\timmediate = 0x" << instrMem->getImm() << endl;
      myfile << hex << "\tjumpAddress = 0x" << instrMem->getJumpAddress() << endl;
      myfile << endl;

      myfile << "---------- ALU 1 ----------" << endl;
      myfile << "inputs:" << endl;
      myfile << hex << "\tinput 1 = 0x" << PCount << endl;
      myfile << "\tinput 2 = 0x" << 4 << endl;
      myfile << "\tcontrol = 0x" << 2 << endl;
      myfile << "output:" << endl;
      myfile << hex << "\tresult = 0x" << alu1->getALUResult() << endl;
      cout << endl;
    }


    // decode
    shiftLeftJump->shiftLeft2(instrMem->getJumpAddress());
    cout << "---------- Shift-left 1 ----------" << endl;
    cout << "input:" << endl;
    cout << hex << "\t0x" << instrMem->getJumpAddress() << endl;
    cout << "output:" << endl;
    cout << hex << "\t0x" << shiftLeftJump->getResult() << endl << endl;

    // concatinating jump addres (already sifted left 2) with most significant
    // 4 digits of PC + 4
    jumpAdd = bitset<32>(shiftLeftJump->getResult());
    pc = bitset<32>(PCount);
    for (int i = 28; i < 32; i ++) {
      jumpAdd[i] = pc[i];
    }
    jumpAddress = jumpAdd.to_ulong();

    control->setControls(instrMem->getOpcode());
    cout << "---------- Control ----------" << endl;
    cout << "input: " << endl;
    cout << hex << "\topcode = 0x" << instrMem->getOpcode() << endl;
    cout << "output: " << endl;
    cout << hex << "\tRegDst = 0x" << control->getRegDst() << endl;
    cout << hex << "\tjump = 0x" << control->getJump() << endl;
    cout << hex << "\tbranch = 0x" << control->getBranch() << endl;
    cout << hex << "\tmemRead = 0x" << control->getMemRead() << endl;
    cout << hex << "\tmemToReg = 0x" << control->getMemToReg() << endl;
    cout << hex << "\tALUOp = 0x" << control->getALUOp() << endl;
    cout << hex << "\tmemWrite = 0x" << control->getMemWrite() << endl;
    cout << hex << "\tALUSrc = 0x" << control->getALUSrc() << endl;
    cout << hex << "\tregWrite = 0x" << control->getRegWrite() << endl;
    cout << endl;

    writeReg = muxRegInput->getResult(instrMem->getRt(), instrMem->getRd(), control->getRegDst());
    cout << "---------- Multiplexer 1 ----------" << endl;
    cout << "inputs: " << endl;
    cout << hex << "\trt = 0x" << instrMem->getRt() << endl;
    cout << hex << "\trd = 0x" << instrMem->getRd() << endl;
    cout << hex << "\tcontrol = 0x" << control->getRegDst() << endl;
    cout << "output:" << endl;
    cout << hex << "\tresult = 0x" << writeReg << endl;
    cout << endl;

    registers->readRegisters(instrMem->getRs(), instrMem->getRt());
    cout << "---------- Registers (read) ----------" << endl;
    cout << "inputs: " << endl;
    cout << hex << "\tRead register 1 = 0x" << instrMem->getRs() << endl;
    cout << hex << "\tRead register 2 = 0x" << instrMem->getRt() << endl;
    cout << "outputs:" << endl;
    cout << hex << "\tRead data 1 = 0x" << registers->getReadData1() << endl;
    cout << hex << "\tRead data 2 = 0x" << registers->getReadData2() << endl;
    cout << endl;

    signExtend->signExtend(instrMem->getImm());
    cout << "---------- Signextend ----------" << endl;
    cout << "input:" << endl;
    cout << hex << "\t0x" << setfill('0') << setw(4) << right << instrMem->getImm() << endl;
    cout << "output:" << endl;
    cout << hex << "\t0x" << setfill('0') << setw(8) << right << signExtend->getSignExtended() << endl;
    cout << endl;

    if (write_to_file == true) {
      myfile << "---------- Shift-left 1 ----------" << endl;
      myfile << "input:" << endl;
      myfile << hex << "\t0x" << instrMem->getJumpAddress() << endl;
      myfile << "output:" << endl;
      myfile << hex << "\t0x" << shiftLeftJump->getResult() << endl << endl;

      myfile << "---------- Control ----------" << endl;
      myfile << "input: " << endl;
      myfile << hex << "\topcode = 0x" << instrMem->getOpcode() << endl;
      myfile << "output: " << endl;
      myfile << hex << "\tRegDst = 0x" << control->getRegDst() << endl;
      myfile << hex << "\tjump = 0x" << control->getJump() << endl;
      myfile << hex << "\tbranch = 0x" << control->getBranch() << endl;
      myfile << hex << "\tmemRead = 0x" << control->getMemRead() << endl;
      myfile << hex << "\tmemToReg = 0x" << control->getMemToReg() << endl;
      myfile << hex << "\tALUOp = 0x" << control->getALUOp() << endl;
      myfile << hex << "\tmemWrite = 0x" << control->getMemWrite() << endl;
      myfile << hex << "\tALUSrc = 0x" << control->getALUSrc() << endl;
      myfile << hex << "\tregWrite = 0x" << control->getRegWrite() << endl;
      myfile << endl;

      myfile << "---------- Multiplexer 1 ----------" << endl;
      myfile << "inputs: " << endl;
      myfile << hex << "\trt = 0x" << instrMem->getRt() << endl;
      myfile << hex << "\trd = 0x" << instrMem->getRd() << endl;
      myfile << hex << "\tcontrol = 0x" << control->getRegDst() << endl;
      myfile << "output:" << endl;
      myfile << hex << "\tresult = 0x" << writeReg << endl;
      myfile << endl;

      myfile << "---------- Registers (read) ----------" << endl;
      myfile << "inputs: " << endl;
      myfile << hex << "\tRead register 1 = 0x" << instrMem->getRs() << endl;
      myfile << hex << "\tRead register 2 = 0x" << instrMem->getRt() << endl;
      myfile << "outputs:" << endl;
      myfile << hex << "\tRead data 1 = 0x" << registers->getReadData1() << endl;
      myfile << hex << "\tRead data 2 = 0x" << registers->getReadData2() << endl;
      myfile << endl;

      myfile << "---------- Signextend ----------" << endl;
      myfile << "input:" << endl;
      myfile << hex << "\t0x" << setfill('0') << setw(4) << right << instrMem->getImm() << endl;
      myfile << "output:" << endl;
      myfile << hex << "\t0x" << setfill('0') << setw(8) << right << signExtend->getSignExtended() << endl;
      myfile << endl;
    }


    // execute
    shiftLeftBranch->shiftLeft2(signExtend->getSignExtended());
    cout << "---------- Shift-left 2 ----------" << endl;
    cout << "input:" << endl;
    cout << hex << "\t0x" << signExtend->getSignExtended() << endl;
    cout << "output:" << endl;
    cout << hex << "\t0x" << shiftLeftBranch->getResult() << endl;
    cout << endl;


    alu2->compute(alu1->getALUResult(), shiftLeftBranch->getResult(), 2);
    cout << "---------- ALU 2 ----------" << endl;
    cout << "inputs:" << endl;
    cout << hex << "\tinput 1 = 0x" << alu1->getALUResult() << endl;
    cout << hex << "\tinput 2 = 0x" << shiftLeftBranch->getResult() << endl;
    cout << hex << "\tcontrol = 0x" << 2 << endl;
    cout << "output:" << endl;
    cout << hex << "\tresult = 0x" << alu2->getALUResult() << endl;
    cout << endl;

    aluInput2 = muxALUInput->getResult(registers->getReadData2(), signExtend->getSignExtended(), control->getALUSrc());
    cout << "---------- Multiplexer 2 ----------" << endl;
    cout << "inputs: " << endl;
    cout << hex << "\tread data 2 = 0x" << registers->getReadData2() << endl;
    cout << hex << "\tsignextended immediate = 0x" << signExtend->getSignExtended() << endl;
    cout << hex << "\tcontrol = 0x" << control->getALUSrc() << endl;
    cout << "output:" << endl;
    cout << hex << "\tresult = 0x" << aluInput2 << endl;
    cout << endl;

    aluControl->setALUControl(control->getALUOp(), instrMem->getFunct());
    cout << "---------- ALU Control ----------" << endl;
    cout << "inputs:" << endl;
    cout << hex << "\tALU opcode = 0x" << control->getALUOp() << endl;
    cout << hex << "\tfunction = 0x" << instrMem->getFunct() << endl;
    cout << "output:" << endl;
    cout << hex << "\tALU control = 0x" << aluControl->getALUControl() << endl;
    cout << endl;

    alu3->compute(registers->getReadData1(), aluInput2, aluControl->getALUControl());
    cout << "---------- ALU 3 ----------" << endl;
    cout << "inputs:" << endl;
    cout << hex << "\tinput 1 = 0x" << registers->getReadData1() << endl;
    cout << hex << "\tinput 2 = 0x" << aluInput2 << endl;
    cout << hex << "\tcontrol = 0x" << aluControl->getALUControl() << endl;
    cout << "output:" << endl;
    cout << hex << "\tresult = 0x" << alu3->getALUResult() << endl;
    cout << endl;

    if (write_to_file == true) {
      myfile << "---------- Shift-left 2 ----------" << endl;
      myfile << "input:" << endl;
      myfile << hex << "\t0x" << signExtend->getSignExtended() << endl;
      myfile << "output:" << endl;
      myfile << hex << "\t0x" << shiftLeftBranch->getResult() << endl;
      myfile << endl;

      myfile << "---------- ALU 2 ----------" << endl;
      myfile << "inputs:" << endl;
      myfile << hex << "\tinput 1 = 0x" << alu1->getALUResult() << endl;
      myfile << hex << "\tinput 2 = 0x" << shiftLeftBranch->getResult() << endl;
      myfile << hex << "\tcontrol = 0x" << 2 << endl;
      myfile << "output:" << endl;
      myfile << hex << "\tresult = 0x" << alu2->getALUResult() << endl;
      myfile << endl;

      myfile << "---------- Multiplexer 2 ----------" << endl;
      myfile << "inputs: " << endl;
      myfile << hex << "\tread data 2 = 0x" << registers->getReadData2() << endl;
      myfile << hex << "\tsignextended immediate = 0x" << signExtend->getSignExtended() << endl;
      myfile << hex << "\tcontrol = 0x" << control->getALUSrc() << endl;
      myfile << "output:" << endl;
      myfile << hex << "\tresult = 0x" << aluInput2 << endl;
      myfile << endl;

      myfile << "---------- ALU Control ----------" << endl;
      myfile << "inputs:" << endl;
      myfile << hex << "\tALU opcode = 0x" << control->getALUOp() << endl;
      myfile << hex << "\tfunction = 0x" << instrMem->getFunct() << endl;
      myfile << "output:" << endl;
      myfile << hex << "\tALU control = 0x" << aluControl->getALUControl() << endl;
      myfile << endl;

      myfile << "---------- ALU 3 ----------" << endl;
      myfile << "inputs:" << endl;
      myfile << hex << "\tinput 1 = 0x" << registers->getReadData1() << endl;
      myfile << hex << "\tinput 2 = 0x" << aluInput2 << endl;
      myfile << hex << "\tcontrol = 0x" << aluControl->getALUControl() << endl;
      myfile << "output:" << endl;
      myfile << hex << "\tresult = 0x" << alu3->getALUResult() << endl;
      myfile << endl;
    }



    // memory
    branchControl = control->getBranch() && alu3->getZero();
    addressBranch = muxBranch->getResult(alu1->getALUResult(), alu2->getALUResult(), branchControl);
    cout << "---------- Multiplexer 5 ----------" << endl;
    cout << "inputs: " << endl;
    cout << hex << "\tPC + 4 = 0x" << alu1->getALUResult() << endl;
    cout << hex << "\tbranch address = 0x" << alu2->getALUResult() << endl;
    cout << hex << "\tcontrol = 0x" << branchControl << endl;
    cout << "output:" << endl;
    cout << hex << "\tresult = 0x" << addressBranch << endl;
    cout << endl;

    addressJump = muxJump->getResult(addressBranch, jumpAddress, control->getJump());
    cout << "---------- Multiplexer 4 ----------" << endl;
    cout << "inputs: " << endl;
    cout << hex << "\tMUX 5 result = 0x" << addressBranch << endl;
    cout << hex << "\tjump address = 0x" << jumpAddress << endl;
    cout << hex << "\tcontrol = 0x" << control->getJump() << endl;
    cout << "output:" << endl;
    cout << hex << "\tresult = 0x" << addressJump << endl;
    cout << endl;

    dataMem->readingAndWritingData(alu3->getALUResult(), control->getMemRead(), control->getMemWrite(), registers->getReadData2());
    cout << "---------- Data Memory ----------" << endl;
    cout << "inputs: " << endl;
    cout << hex << "\taddress = 0x" << alu3->getALUResult() << endl;
    cout << hex << "\twrite data = 0x" << registers->getReadData2() << endl;
    cout << hex << "\tmemRead = 0x" << control->getMemRead() << endl;
    cout << hex << "\tmemWrite = 0x" << control->getMemWrite() << endl;
    cout << "output:" << endl;
    cout << hex << "\tread data = 0x" << dataMem->getReadData() << endl;
    cout << endl;

    writeBackData = muxWriteBack->getResult(dataMem->getReadData(), alu3->getALUResult(), control->getMemToReg());
    cout << "---------- Multiplexer 3 ----------" << endl;
    cout << "inputs: " << endl;
    cout << hex << "\tread data = 0x" << dataMem->getReadData() << endl;
    cout << hex << "\tALU 3 result = 0x" << alu3->getALUResult() << endl;
    cout << hex << "\tcontrol = 0x" << control->getMemToReg() << endl;
    cout << "output:" << endl;
    cout << hex << "\tresult = 0x" << writeBackData << endl;
    cout << endl;


    if (write_to_file == true) {
      myfile << "---------- Multiplexer 5 ----------" << endl;
      myfile << "inputs: " << endl;
      myfile << hex << "\tPC + 4 = 0x" << alu1->getALUResult() << endl;
      myfile << hex << "\tbranch address = 0x" << alu2->getALUResult() << endl;
      myfile << hex << "\tcontrol = 0x" << branchControl << endl;
      myfile << "output:" << endl;
      myfile << hex << "\tresult = 0x" << addressBranch << endl;
      myfile << endl;

      myfile << "---------- Multiplexer 4 ----------" << endl;
      myfile << "inputs: " << endl;
      myfile << hex << "\tMUX 5 result = 0x" << addressBranch << endl;
      myfile << hex << "\tjump address = 0x" << jumpAddress << endl;
      myfile << hex << "\tcontrol = 0x" << control->getJump() << endl;
      myfile << "output:" << endl;
      myfile << hex << "\tresult = 0x" << addressJump << endl;
      myfile << endl;

      myfile << "---------- Data Memory ----------" << endl;
      myfile << "inputs: " << endl;
      myfile << hex << "\taddress = 0x" << alu3->getALUResult() << endl;
      myfile << hex << "\twrite data = 0x" << registers->getReadData2() << endl;
      myfile << hex << "\tmemRead = 0x" << control->getMemRead() << endl;
      myfile << hex << "\tmemWrite = 0x" << control->getMemWrite() << endl;
      myfile << "output:" << endl;
      myfile << hex << "\tread data = 0x" << dataMem->getReadData() << endl;
      myfile << endl;

      myfile << "---------- Multiplexer 3 ----------" << endl;
      myfile << "inputs: " << endl;
      myfile << hex << "\tread data = 0x" << dataMem->getReadData() << endl;
      myfile << hex << "\tALU 3 result = 0x" << alu3->getALUResult() << endl;
      myfile << hex << "\tcontrol = 0x" << control->getMemToReg() << endl;
      myfile << "output:" << endl;
      myfile << hex << "\tresult = 0x" << writeBackData << endl;
      myfile << endl;
    }



    // write back
    registers->writeBack(control->getRegWrite(), writeReg, writeBackData);
    cout << "---------- Registers (write back) ----------" << endl;
    cout << "inputs: " << endl;
    cout << hex << "\twrite register = 0x" << writeReg << endl;
    cout << hex << "\twrite data = 0x" << writeBackData << endl;
    cout << hex << "\tregWrite = 0x" << control->getRegWrite() << endl;
    cout << endl;


    // set PC
    PC->setCount(addressJump);
    cout << "---------- PC ----------" << endl;
    cout << "input: 0x" << addressJump << endl << endl;


    if (write_to_file == true) {
      myfile << "---------- Registers (write back) ----------" << endl;
      myfile << "inputs: " << endl;
      myfile << hex << "\twrite register = 0x" << writeReg << endl;
      myfile << hex << "\twrite data = 0x" << writeBackData << endl;
      myfile << hex << "\tregWrite = 0x" << control->getRegWrite() << endl;
      myfile << endl;

      myfile << "---------- PC ----------" << endl;
      myfile << "input: 0x" << addressJump << endl << endl;
    }


    if (print_memory_contents == true) {
      cout << "---------- Print Memory Contents ----------" << endl;
      cout << "Registers:" << endl;
      for (int i = 0; i <= 31; i++)
      {
        cout << dec << i << " : " << hex << "0x" << registers->getRegister(i) << endl;
      }
      cout << endl;

      cout << "Instruction Memory:" << endl;
      cout << "address  : binary encoding                  : MIPS instruction" << endl;
      map<int, Instruction> instructionMemory = instrMem->getInstrMem();
      for (map<int, Instruction>::iterator it = instructionMemory.begin();
           it != instructionMemory.end(); ++it) {
        cout << hex << "0x" << it->first << " : " << it->second.getEncoding()
             << " : " << it->second.getMIPS() << endl;
      }
      cout << endl;

      cout << "Data Memory:" << endl;
      cout << "address    : data" << endl;
      map<int, int> dataMemory = dataMem->getDataMemory();
      for (map<int, int>::iterator it = dataMemory.begin(); it != dataMemory.end(); ++it) {
        cout << hex << "0x" << it->first << " : 0x" << it->second << endl;
      }
      cout << endl;


      if (write_to_file == true) {
        myfile << "---------- Print Memory Contents ----------" << endl;
        myfile << "Registers:" << endl;
        for (int i = 0; i <= 31; i++)
        {
          myfile << dec << i << " : " << hex << "0x" << registers->getRegister(i) << endl;
        }
        myfile << endl;

        myfile << "Instruction Memory:" << endl;
        myfile << "address  : binary encoding                  : MIPS instruction" << endl;
        map<int, Instruction> instructionMemory = instrMem->getInstrMem();
        for (map<int, Instruction>::iterator it = instructionMemory.begin();
            it != instructionMemory.end(); ++it) {
          myfile << hex << "0x" << it->first << " : " << it->second.getEncoding()
                 << " : " << it->second.getMIPS() << endl;
        }
        myfile << endl;

        myfile << "Data Memory:" << endl;
        myfile << "address    : data" << endl;
        map<int, int> dataMemory = dataMem->getDataMemory();
        for (map<int, int>::iterator it = dataMemory.begin(); it != dataMemory.end(); ++it) {
          myfile << hex << "0x" << it->first << " : 0x" << it->second << endl;
        }
        myfile << endl;
      }
    }

    instCount ++;
    cout << endl;
  }

  if (write_to_file == true) {
    myfile.close();
  }

  delete PC;
  delete alu1;
  delete instrMem;
  delete shiftLeftJump;
  delete control;
  delete registers;
  delete signExtend;
  delete muxRegInput;
  delete muxALUInput;
  delete muxWriteBack;
  delete muxJump;
  delete muxBranch;
  delete shiftLeftBranch;
  delete alu2;
  delete aluControl;
  delete alu3;
  delete dataMem;
}
