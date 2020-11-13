#include <iostream>
#include "InstructionMemory.h"
#include "ALU.h"
#include "MainControlUnit.h"
#include "Multiplexor.h"
#include "SignExtendUnit.h"

using namespace std;

/*
 * Simpulates a processor!!!
 * Prints all inputs and outputs of objects.
 *
 *
 */

bool isWhitespace(char c)    { return (c == ' '|| c == '\t'); };

string removeWhitespace(string str){
  int count = 0;
  return "";
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
    while(getline(in, line)){
      // get rid of comments (could contain "=")
      string::size_type idx = line.find('#');
      if (idx != string::npos)
	      line = line.substr(0,idx);

      // looking for "=" to find parameters
      string::size_type idx1 = line.find('=');
      if (idx1 != string::npos) {
        param = line.substr(0,idx1);

        // cout << line << endl;
        // cout << line.substr(idx1 - 5, 5) << endl;

        // set the parameters
        if (param.find("program_input") != -1){
          program_input = line.substr(idx1 + 1);
        }
        else if (param.find("memory_contents_input") != -1) {
          memory_contents_input = line.substr(idx1 + 1);
        }
        else if (param.find("register_file_input") != -1) {
          register_file_input = line.substr(idx1 + 1);
        }
        else if (param.find("output_mode") != -1) {
          output_mode = line.substr(idx1 + 1);
        }
        else if (param.find("debug_mode") != -1) {
          if (line.substr(idx1 + 1, 4).compare("true") == 0)
            debug_mode = true;
          else if (line.substr(idx1 + 1, 5).compare("false") == 0)
            debug_mode = false;
        }
        else if (param.find("print_memory_contents") != -1) {
          if (line.substr(idx1 + 1, 4).compare("true") == 0)
            print_memory_contents = true;
          else if (line.substr(idx1 + 1, 5).compare("false") == 0)
            print_memory_contents = false;
        }
        else if (param.find("output_file") != -1) {
          output_file = line.substr(idx1 + 1);
        }
        else if (param.find("write_to_file") != -1) {
          if (line.substr(idx1 + 1, 4).compare("true") == 0)
            write_to_file = true;
          else if (line.substr(idx1 + 1, 5).compare("false") == 0)
            write_to_file = false;
        }
      }

      // string::size_type idx = line.find('=');
      // if (idx != string::npos)
	    //   param = line.substr(0,idx);

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


  InstructionMemory *instrMem = new InstructionMemory(program_input);

  instrMem->printMIPSInst(0x400000);
  instrMem->printBinaryInst(0x400000);

  // cout << instrMem->decode(0x400000) << endl;
  // cout << instrMem->decode(0x400004) << endl;
  // cout << instrMem->decode(0x400008) << endl;


  delete instrMem;

}
