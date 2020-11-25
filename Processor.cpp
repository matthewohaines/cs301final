#include <iostream>
#include "InstructionMemory.h"
#include "ALU.h"
#include "MainControlUnit.h"
#include "Multiplexor.h"
#include "SignExtendUnit.h"
#include "PCCounter.h"
#include "RegisterFile.h"

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
  int instCount = 0;
  PCCounter *PC = new PCCounter;
  int PCount;
  InstructionMemory *instrMem = new InstructionMemory(program_input, debug_mode);
  MainControlUnit *control = new MainControlUnit();
  // RegisterFile *registers = new RegisterFile(register_file_input);
  SignExtendUnit *signExtend = new SignExtendUnit();
  Multiplexor *muxRegInput = new Multiplexor();
  Multiplexor *muxALUInput = new Multiplexor();
  Multiplexor *muxWriteBack = new Multiplexor();
  Multiplexor *muxJump = new Multiplexor();
  Multiplexor *muxBranch = new Multiplexor();

  int maxAddress = instrMem->getMaxAddress();

  if (debug_mode == true){
    cout << "------------ Start running program -------------" << endl;
  }

  // loop
  // cout << "------------ Iteration " << count << "-------------" << endl;
  while ((PCount = PC->getCount()) < maxAddress) {
    if (output_mode.compare("single_step") == 0){
      cout << "Single step output mode, enter a character to continue: ";
      char c;
      cin >> c;
    }

    cout << std::dec << "------------------------------ Iteration " << instCount
         << " " << "------------------------------" << endl;
    // PCount = PC->getCount();

    cout << std::hex << "PC output: 0x" << PCount << endl << endl;

    instrMem->printMIPSInst(PCount);

    if (debug_mode == true)
      instrMem->printBinaryInst(PCount);

    instrMem->decode(PCount);
    instrMem->printInput();
    instrMem->printOutput();

    // cout << "opcode = " << instrMem->getOpcode() << endl;

    control->setControls(instrMem->getOpcode());
    control->printInput();
    control->printOutput();

    PC->setCount(PCount + 4);

    instCount ++;

    cout << endl;
  }



  // instrMem->printMIPSInst(0x400000);
  // instrMem->printBinaryInst(0x400000);
  // instrMem->printMIPSInst(PCount);

  // cout << instrMem->decode(0x400000) << endl;
  // cout << instrMem->decode(0x400004) << endl;
  // cout << instrMem->decode(0x400008) << endl;

  // string cow = "wow wow wee wow wow";
  // cout << cow << endl;
  // string moo = removeWhitespace(cow);
  // cout << moo << endl;
  // cout << cow << endl;


  delete PC;
  delete instrMem;
  delete control;
  // delete registers;
  delete signExtend;
  delete muxRegInput;
  delete muxALUInput;
  delete muxWriteBack;
  delete muxJump;
  delete muxBranch;
}
