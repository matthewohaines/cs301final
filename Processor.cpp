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
  for (int i = 0; i < str.length(); i++){
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
  bool write_to_file = false;  // missing in final project doc list

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
      // get rid of comments (could contain "=")
      string::size_type idx = line.find('#');
      if (idx != string::npos)
	      line = line.substr(0,idx);

      // looking for "=" to find parameters
      string::size_type idx1 = line.find('=');
      if (idx1 != string::npos) {
        param = line.substr(0,idx1);
        value = removeWhitespace(line.substr(idx1 + 1));

        // set the parameters
        if (param.find("program_input") != -1){
          program_input = value;
        }
        else if (param.find("memory_contents_input") != -1) {
          memory_contents_input = value;
        }
        else if (param.find("register_file_input") != -1) {
          register_file_input = value;
        }
        else if (param.find("output_mode") != -1) {
          output_mode = value;
        }
        else if (param.find("debug_mode") != -1) {
          if (value.compare("true") == 0)
            debug_mode = true;
          else if (value.compare("false") == 0)
            debug_mode = false;
        }
        else if (param.find("print_memory_contents") != -1) {
          if (value.compare("true") == 0)
            print_memory_contents = true;
          else if (value.compare("false") == 0)
            print_memory_contents = false;
        }
        else if (param.find("output_file") != -1) {
          output_file = value;
        }
        else if (param.find("write_to_file") != -1) {
          if (value.compare("true") == 0)
            write_to_file = true;
          else if (value.compare("false") == 0)
            write_to_file = false;
        }
      }
    }
  }

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

  // initialize objects and other variables
  // fetch
  int instCount = 0;
  PCCounter *PC = new PCCounter;
  int PCount;
  // ALU *alu1 = new ALU();
  InstructionMemory *instrMem = new InstructionMemory(program_input, debug_mode);

  // decode
  ShiftLeft *shiftLeftJump = new ShiftLeft();
  bitset<32> jumpAdd;
  bitset<32> pc;
  int jumpAddress;
  MainControlUnit *control = new MainControlUnit();
  Multiplexor *muxRegInput = new Multiplexor();
  int writeReg;
  // RegisterFile *registers = new RegisterFile(register_file_input);
  SignExtendUnit *signExtend = new SignExtendUnit();
  int signExtendedImm;

  // execute
  ShiftLeft *shiftLeftBranch = new ShiftLeft();
  // ALU *alu2 = new ALU();
  Multiplexor *muxALUInput = new Multiplexor();
  int aluInput2;
  ALUControlUnit *aluControl = new ALUControlUnit();
  // ALU *alu3 = new ALU();

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
  }


  // loop
  while ((PCount = PC->getCount()) < maxAddress) {
    if (output_mode.compare("single_step") == 0){
      cout << "Single step output mode, enter a character to continue: ";
      char c;
      cin >> c;
    }

    cout << std::dec << "------------------------------ Iteration " << instCount
         << " " << "------------------------------" << endl;

    // fetch
    cout << "---------- PC ----------" << endl;
    cout << std::hex << "PC output: 0x" << PCount << endl << endl;

    instrMem->printMIPSInst(PCount);

    if (debug_mode == true)
      instrMem->printBinaryInst(PCount);

    instrMem->decode(PCount);
    cout << "---------- Instruction Memory ----------" << endl;
    instrMem->printInput();
    instrMem->printOutput();

    // alu1->compute(PCount, 4, 2);
    cout << "---------- ALU 1 ----------" << endl;
    // cout << "input:" << endl;
    // alu1->printInputs();
    // cout << "output:" << endl;
    // alu1->printOutputs();

    // decode
    shiftLeftJump->shiftLeft2(instrMem->getJumpAddress());
    cout << "---------- Shift-left 1 ----------" << endl;
    shiftLeftJump->printInput();
    shiftLeftJump->printOutput();

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
    control->printInput();
    control->printOutput();

    writeReg = muxRegInput->getResult(instrMem->getRt(), instrMem->getRd(), control->getRegDst());
    cout << "---------- Multiplexer 1 ----------\ninput:\n \t";
    muxRegInput->printInputs();
    cout << "output:\n \t";
    muxRegInput->printOutput();
    cout << endl;

    // registers->readRegisters(instrMem->getRs(), instrMem->getRt());
    cout << "---------- Registers (read) ----------" << endl;
    // registers->printReadInputs();
    // registers->printReadOutputs();

    signExtend->signExtend(instrMem->getImm());
    cout << "---------- Signextend ----------" << endl;
    signExtend->printInput();
    signExtend->printOutput();

    // execute
    shiftLeftBranch->shiftLeft2(signExtend->getSignExtended());
    cout << "---------- Shift-left 1 ----------" << endl;
    shiftLeftBranch->printInput();
    shiftLeftBranch->printOutput();

    // alu2->compute(alu1->getALUResult(), shiftLeftBranch->getResult(), 2);
    cout << "---------- ALU 2 ----------" << endl;
    // cout << "inputs:" << endl;
    // alu2->printInputs();
    // cout << "output:" << endl;
    // alu2->printOutputs();

    // aluInput2 = muxALUInput->getResult(registers->getReadData2(), signExtendedImm, control->getALUSrc())
    cout << "---------- Multiplexer 2 ----------\ninput:\n \t";
    // muxALUInput->printInputs();
    cout << "output:\n \t";
    // muxALUInput->printOutput();
    cout << endl;

    aluControl->setALUControl(control->getALUOp(), instrMem->getFunct());
    cout << "---------- ALU Control ----------" << endl;
    aluControl->printInput();
    aluControl->printOutput();

    // alu3->compute(registers->getReadData1(), aluInput2, aluControl->getALUControl());
    cout << "---------- ALU 3 ----------" << endl;
    // alu3->printInputs();
    // alu3->printOutputs();

    // memory
    // branchControl = control->getBranch() && alu3->getALUResult(); // hmm, don't think this will work...
    // addressBranch = muxBranch->getResult(alu1->getALUResult(), alu2->getALUResult(), branchControl);
    cout << "---------- Multiplexer 5 ----------\ninput:\n \t";
    // muxBranch->printInputs();
    cout << "output:\n \t";
    // muxBranch->printOutputs();
    cout << endl;

    // addressJump = muxJump->getResult(addressBranch, jumpAddress, control->getJump());
    cout << "---------- Multiplexer 4 ----------\ninput:\n \t";
    // muxJump->printInputs();
    cout << "output:\n \t";
    // muxJump->printOutputs();
    cout << endl;

    // input_address is not a string!!!
    // dataMem->readingAndWritingData(std::string input_address, control->getMemRead(), control->getMemWrite(), registers->getReadData2());
    cout << "---------- Data Memory ----------" << endl;
    // dataMem->printInput();
    // dataMem->printOutput();

    // writeBackData = muxWriteBack->getResult(dataMem->getReadData(), alu3->getALUResult(), control->getMemToReg());
    cout << "---------- Multiplexer 3 ----------\ninput:\n \t";
    // muxWriteBack->printInputs();
    cout << "output:\n \t";
    // muxWriteBack->printOutputs();
    cout << endl;

    // write back
    // Registers->writeBack(control->getRegWrite(), writeReg, writeBackData);
    cout << "---------- Registers (write back) ----------" << endl;
    // need to write this method still....
    // Registers->printWriteInput();

    // set PC
    // PC->setCount(addressJump);
    PC->setCount(PCount + 4);

    if (print_memory_contents == true) {
      cout << "---------- Print Memory Contents ----------" << endl;
      cout << "Registers:" << endl;
      // registers->printRegisterFile();
      cout << endl;

      cout << "Instruction Memory:" << endl;
      instrMem->printInstructionMemory();
      cout << endl;

      cout << "Data Memory" << endl;
      dataMem->printMemory();
      cout << endl;
    }

    instCount ++;
    cout << endl;
  }


  // if (write_to_file == true){
  //   ofstream myfile;
  //   myfile.open (output_file);

  //   cout << i.getEncoding() << endl;
  //   myfile << i.getEncoding() << endl;

  //   myfile.close();
  // }


  // int num = -12;
  // cout << "num: " << num << endl;
  // cout << "num in binary: " << bitset<16>(num) << endl;
  // cout << "num converted back to int: " << bitset<8>(num).to_ulong() << endl;


  delete PC;
  // delete alu1;
  delete instrMem;
  delete shiftLeftJump;
  delete control;
  // delete registers;
  delete signExtend;
  delete muxRegInput;
  delete muxALUInput;
  delete muxWriteBack;
  delete muxJump;
  delete muxBranch;\
  delete shiftLeftBranch;
  // delete alu2;
  delete aluControl;
  // delete alu3;
  delete dataMem;
}
