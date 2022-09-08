// Copyright (c) 2020 University of Florida
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// Greg Stitt
// University of Florida
//
// This example demonstrates how to use the AFU OPAE wrapper class to 
// communicate with a simple AFU that implements an adder.
//
// See TODO comments to see what to complete for the exercise.

#include <cstdlib>
#include <iostream>

#include <opae/utils.h>

#include "AFU.h"

using namespace std;

// Auto-generated by OPAE's afu_json_mgr script
#include "afu_json_info.h"

//=========================================================
// TODO: Define constants with the addresses of the adder's
// input registers and output registers. Make sure these
// match those used in your afu.sv file.
//
// NOTE: Ideally this could be generated with a .json file just like the
// AFU_ACCEL_UUID. Without auto-generation, you must manually ensure that
// the addresses match between the RTL code and software code.
//=========================================================




#define NUM_TESTS 100

int main(int argc, char *argv[]) {

  try {
    // TODO: create instance of AFU class with AFU AFU_ACCEL_UUID 

        
    // Add values in the FPGA by transferring adder I/O over MMIO
    unsigned errors = 0;
    for (uint64_t i=0; i < NUM_TESTS; i++) {
      
      uint64_t in0, in1;
      in0 = rand();
      in1 = rand();

      // TODO: Write in0 and in1 to the adder's input registers
      
      // TODO: Read from the adder's output register and store the result in sum.
      uint64_t sum;

      if (sum != in0 + in1) {
	cerr << "ERROR: " << in0 << "+" << in1 << "=" << sum 
	     << " instead of " << in0 + in1 << endl;
	errors ++;
      }
    }

    if (errors == 0) {
      cout << "All tests succeeded." << endl;
      return EXIT_SUCCESS;
    }
    else {
      cout << errors << " tests failed." << endl;
      return EXIT_FAILURE;
    }
  }
  // Exception handling for all the runtime errors that can occur within 
  // the AFU wrapper class.
  catch (const fpga_result& e) {    
    
    // Provide more meaningful error messages for each exception.
    if (e == FPGA_BUSY) {
      cerr << "ERROR: All FPGAs busy." << endl;
    }
    else if (e == FPGA_NOT_FOUND) { 
      cerr << "ERROR: FPGA with accelerator " << AFU_ACCEL_UUID 
	   << " not found." << endl;
    }
    else {
      // Print the default error string for the remaining fpga_result types.
      cerr << "ERROR: " << fpgaErrStr(e) << endl;    
    }
  }
  catch (const runtime_error& e) {    
    cerr << e.what() << endl;
  }
  catch (const opae::fpga::types::no_driver& e) {
    cerr << "ERROR: No FPGA driver found." << endl;
  }

  return EXIT_FAILURE;
}
