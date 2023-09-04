# VLSI Physical Design -  Lab-work Repository
This repository contains all the assignments and information from the VLSI Physical Design for ASICs special topic taught at PES University, EC Campus, for ECE students, by [Kunal Ghosh](https://www.linkedin.com/in/kunal-ghosh-vlsisystemdesign-com-28084836/) from [VLSI System Design](vlsisystemdesign.com)

This repo has been divided into various subfolders for different days of the coursework
Click on the links below to find the documents for each lab:
- [Lab 1](https://github.com/alfadelta10010/pes-asic-class/tree/main#day---1-lab-assignments)
- [Lab 2](https://github.com/alfadelta10010/pes-asic-class/blob/main/README.md#day-2-assignments)
- [Day 1 - RTL](https://github.com/alfadelta10010/pes-asic-class/tree/main#day-1-assignments---rtl)
- [Day 2 - RTL](https://github.com/alfadelta10010/pes-asic-class/tree/main#day-2-assignments---rtl)
- [Day 3 - RTL](https://github.com/alfadelta10010/pes-asic-class/tree/main#day-3-assignments---rtl)

## Set up instructions for the coursework
The software required is as follows:
- [RISC-V GNU Compiler Toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain)
	- :warning: GCC-12 gives compiling issues for the proxy kernel, using GCC-8.3 solves this issue. You can download the pre-compiled toolchain from [here](https://static.dev.sifive.com/dev-tools/riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-linux-ubuntu14.tar.gz)
- [Spike RISC-V ISA Simulator](https://github.com/riscv-software-src/riscv-isa-sim)
- [RISC-V Proxy Kernel and Boot loader](https://github.com/riscv-software-src/riscv-pk)
- [YoSys]()
- [SkyLake130nm Library]()

For a simple set up, you can use the set-up script provided by the instructor with the following commands:
```bash
git clone https://github.com/kunalg123/riscv_workshop_collaterals.git
cd riscv_workshop_collaterals
chmod +x run.sh
./run.sh
```

## Day - 1 Lab assignments

### Assignment 1
- Write a program to calculate sum of numbers from 1 to n, and compile with x86-gcc
- The [code](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/1ton.c) is as follows:
![code](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/code.png "code")

- To compile and run with x86-gcc:
```bash
gcc sum1ton.c -o x86.out
./x86.out
```
- This gives the following output:
![x86 execution](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/x86_exec.png "x86 execution")

- This summarizes assignment 1.

### Assignment 2
- Disassemble the previous program to run on RISC-V processors
- The [code](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/1ton.c) can be compiled for RISC-V processors using riscv64-gcc:
```c
#include <stdio.h>
int main()
{
	int i, sum = 0, n = 5;
	for(i = 1; i <= n; i++)
	{
		sum = sum + i;
	}
	printf("Sum of numbers from 1 to %d is %d \n", n, sum);
	return 0;
}
```
- To disassemble, we run the following command:
```bash
riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o rv.o 1ton.c
```
- This generates the following output:
![RV Disassembly](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/rv_disassemble.png)

- To view the output, we use the following command:
```bash
riscv64-unknown-elf-objdump -d rv.o | less
```
- This generates the following output:
![RV Object Dump](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/rv_objdump.png)

- Scrolling down to the `main` function, we see that there are 15 instructions:
![RV Dump Main fn](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/rv_dump_main.png)

- If we change the optimization flag to `-Ofast` during disassembly, the number of instructions is reduced as shown below:
![RV Fast Disassembly](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/rv_disassemble_fast.png)
![RV Fast Object Dump](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/rvfast_dump_main.png)

- Here, we see there are 12 instructions in `main` function
- This concludes assignment 2

### Assignment 3
- Execute and debug the `1ton.c` on RISC-V simulator
- To compile with riscv64-gcc:
```bash
riscv64-unknown-elf-gcc -Ofast -mabi=lp64 -march=rv64i -o rv.out 1ton.c
```
- This gives the following output:
![rv compile](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/rv_compile.png "rv compile")

- To execute, we use the [Spike RISC-V ISA Simulator](https://github.com/riscv-software-src/riscv-isa-sim) as follows:
![rv execution](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/rv_exec.png "RV execution")

- To debug, we start `spike` in debug mode, using:
```bash
spike -d pk rv.out
```
- To move the Program counter from 0 to the first instruction, we execute all the instructions in between, using:
``` 
until pc 0 100b0
```
- To find contents of the register `a0` before being written, we use
```
reg 0 a0
```
- To execute the next instruction, press enter
- If we see the value of the register after execution, it has changed.
- The output as follows:
![Debug](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/rv_debug.png "RV debug")

- Seeing value of stack pointer update:
![Stack pointer](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/debug_sp.png "Stack Pointer")

- Upon calculating, the value has changed by 10
- This concludes assignment 3.

### Assignment 4
- Testing the limits of `long long int` on RV64I, on `unsigned` and `signed` integer.
- Write the program  `unsignedLimits.c` [shown here](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/unsignedLimits.c):
```c
#include <stdio.h>
#include <math.h>

int main(){
	unsigned long long int max = (unsigned long long int) (pow(2,64) -1);
	unsigned long long int min = (unsigned long long int) (pow(2,64) *(-1));
	printf("lowest number represented by unsigned 64-bit integer is %llu\n",min);
	printf("highest number represented by unsigned 64-bit integer is %llu\n",max);
	return 0;
}
```

- To compile and run with riscv64-gcc:
```bash
riscv64-unknown-elf-gcc -Ofast -mabi=lp64 -march=rv64i -o limits.o unsignedLimits.c
spike pk limits.o
```
- The output is as follows:
![RV64 Long Long uint Limits](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/rv_ulimits.png "RV64 long long uint limits")

- To test if it is the limit, we modify as follows:
```c
unsigned long long int max = (unsigned long long int) (pow(2,127) -1);
unsigned long long int min = (unsigned long long int) (pow(2,127) *(-1));
```
- The output is the same:
![RV64 Long Long uint, exceeding limits](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/rv_ulimits_extra.png "RV64 long long uint limits exceeding limits")

- To prove that the values do get changed, we modify as follows:
```c
unsigned long long int max = (unsigned long long int) (pow(2,5) -1);
unsigned long long int min = (unsigned long long int) (pow(2,5) *(-1));
```
- The output is as follows:
![RV64 Long Long uint, within limits](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/rv_ulimits_within.png "RV64 long long uint limits within limits")

- Write the program  `signedLimits.c` [shown here](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/signedLimits.c):
```c
#include <stdio.h>
#include <math.h>

int main(){
	long long int max = (long long int) (pow(2,5) -1);
	long long int min = (long long int) (pow(2,5) *(-1));
	printf("lowest number represented by 64-bit integer is %lld\n",min);
	printf("highest number represented by 64-bit integer is %lld\n",max);
	return 0;
}
```

- To compile and run with riscv64-gcc:
```bash
riscv64-unknown-elf-gcc -Ofast -mabi=lp64 -march=rv64i -o slimits.o signedLimits.c
spike pk slimits.o
```
- The output is as follows:
![RV64 Long Long int Limits](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/rv_limits.png "RV64 long long int limits")

- To test if it is the limit, we modify as follows:
```c
long long int max = (long long int) (pow(2,127) -1);
long long int min = (long long int) (pow(2,127) *(-1));
```
- The output is the same:
![RV64 Long Long int, exceeding limits](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/rv_limits_extra.png "RV64 long long int limits exceeding limits")

- To prove that the values do get changed, we modify as follows:
```c
long long int max = (long long int) (pow(2,5) -1);
long long int min = (long long int) (pow(2,5) *(-1));
```
- The output is as follows:
![RV64 Long Long int, within limits](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/assets/rv_limits_within.png "RV64 long long int limits within limits")

- This concludes assignment 4

## Day 2 Assignments

### Assignment 1
- Write `load.s` and `1to9_custom.c` as descibed in the algorithm
- `load.s`
```asm
.section .text
.global load
.type load, @function

load:
	add	a4, a0, zero
	add	a2, a0, a1
	add	a3, a0, zero
loop:	add	a4, a3, a4
	addi	a3, a3, 1
	blt	a3, a2, loop
	add	a0, a4, zero
	ret
```
- `1to9_custom.c`
```c
cat 1to9_custom.c 
#include <stdio.h>

extern int load(int x, int y);

int main()
{
	int result = 0;
	int count = 9;
	result = load(0x0, count + 1);
	printf("Sum of nos. from 1 to %d is %d\n", count, result);
}
```
- This concludes assignment 1

### Assignment 2
- Compile the code with the files and options with the following command:
```bash
riscv64-unknown-elf-gcc -Ofast -mabi=lp64 -march=rv64i -o 1to9_custom.o 1to9_custom.c load.s
```
![Compile](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2/assets/compile.png "Compile")

- To run, use the following command:
```bash
spike pk 1to9_custom.o
```
- This generates the following output:
![Execution](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2/assets/execute.png)

- Inspecting the object dump:
![Object dump](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2/assets/objdump.png)

- This concludes assignment 2

### Assignment 3
- To run C program on PicoRV32 
- Make the set-up script executable, and execute
```bash
chmod +x rv32im.sh
./rv32im.sh
```
![Executable](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2/assets/executable.png)
![Execution](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2/assets/execute2.png)

- This concludes assignment 3


## Day 1 Assignments - RTL

### Lab 1
- Simulating `good_mux.v` and seeing outputs in **gtkwave**
![Simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1_rtl/assets/iverilog_and_simulate.png)
![GTKWave](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1_rtl/assets/gtkwave.png)
- This concludes lab 1

### Lab 2 
- smth `good_mux.v` in YoSys
- First we read liberty file:
![liberty file](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1_rtl/assets/read-liberty.png)
- Next we read the verilog file:
![read verilog](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1_rtl/assets/read-verilog.png)

- Then we synthesize the top-level design
```
yosys> synth -top good_mux 

3. Executing SYNTH pass.

3.1. Executing HIERARCHY pass (managing design hierarchy).

3.1.1. Analyzing design hierarchy..
Top module:  \good_mux

3.1.2. Analyzing design hierarchy..
Top module:  \good_mux
Removed 0 unused modules.

3.2. Executing PROC pass (convert processes to netlists).

<removed extended output>

3.25. Printing statistics.

=== good_mux ===

   Number of wires:                  4
   Number of wire bits:              4
   Number of public wires:           4
   Number of public wire bits:       4
   Number of memories:               0
   Number of memory bits:            0
   Number of processes:              0
   Number of cells:                  1
     $_MUX_                          1

3.26. Executing CHECK pass (checking for obvious problems).
Checking module good_mux...
Found and reported 0 problems.
```
- Next we generate gate level file:
```
yosys> abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 

4. Executing ABC pass (technology mapping using ABC).

4.1. Extracting gate netlist of module `\good_mux' to `<abc-temp-dir>/input.blif'..
Extracted 1 gates and 4 wires to a netlist network with 3 inputs and 1 outputs.

4.1.1. Executing ABC.
Running ABC command: "<yosys-exe-dir>/yosys-abc" -s -f <abc-temp-dir>/abc.script 2>&1
ABC: ABC command line: "source <abc-temp-dir>/abc.script".
ABC: 
ABC: + read_blif <abc-temp-dir>/input.blif 
ABC: + read_lib -w /home/alphadelta1803/Desktop/folder/sky130RTLDesignAndSynthesisWorkshop/verilog_files/../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
ABC: Parsing finished successfully.  Parsing time =     0.11 sec
ABC: Scl_LibertyReadGenlib() skipped cell "sky130_fd_sc_hd__decap_12" without logic function.
<removed output>
ABC: + write_blif <abc-temp-dir>/output.blif 

4.1.2. Re-integrating ABC results.
ABC RESULTS:   sky130_fd_sc_hd__mux2_1 cells:        1
ABC RESULTS:        internal signals:        0
ABC RESULTS:           input signals:        3
ABC RESULTS:          output signals:        1
Removing temp directory.
```
- Part we are interested in:
```
ABC RESULTS:   sky130_fd_sc_hd__mux2_1 cells:        1
ABC RESULTS:        internal signals:        0
ABC RESULTS:           input signals:        3
ABC RESULTS:          output signals:        1
```
- Now we use `show` command to view the logic diagaram:
![show command](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1_rtl/assets/show-command.png)

## Day 2 Assignments - RTL
### Lab 1
- `multiple_modules.v`
```verilog
```
- Synthesizing the top module:
```
3.25. Printing statistics.

=== multiple_modules ===

   Number of wires:                  5
   Number of wire bits:              5
   Number of public wires:           5
   Number of public wire bits:       5
   Number of memories:               0
   Number of memory bits:            0
   Number of processes:              0
   Number of cells:                  2
     sub_module1                     1
     sub_module2                     1

=== sub_module1 ===

   Number of wires:                  3
   Number of wire bits:              3
   Number of public wires:           3
   Number of public wire bits:       3
   Number of memories:               0
   Number of memory bits:            0
   Number of processes:              0
   Number of cells:                  1
     $_AND_                          1

=== sub_module2 ===

   Number of wires:                  3
   Number of wire bits:              3
   Number of public wires:           3
   Number of public wire bits:       3
   Number of memories:               0
   Number of memory bits:            0
   Number of processes:              0
   Number of cells:                  1
     $_OR_                           1

=== design hierarchy ===

   multiple_modules                  1
     sub_module1                     1
     sub_module2                     1

   Number of wires:                 11
   Number of wire bits:             11
   Number of public wires:          11
   Number of public wire bits:      11
   Number of memories:               0
   Number of memory bits:            0
   Number of processes:              0
   Number of cells:                  2
     $_AND_                          1
     $_OR_                           1
```
- Upon running `show` command:
![show command](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/show_mulmodule.png)
- This is the hierarchical design
- Writing the verilog file gives us the following output:
```verilog
/* Generated by Yosys 0.32+66 (git sha1 b168ff99d, gcc 11.4.0-1ubuntu1~22.04 -fPIC -Os) */

module multiple_modules(a, b, c, y);
  input a;
  wire a;
  input b;
  wire b;
  input c;
  wire c;
  wire net1;
  output y;
  wire y;
  sub_module1 u1 (
    .a(a),
    .b(b),
    .y(net1)
  );
  sub_module2 u2 (
    .a(net1),
    .b(c),
    .y(y)
  );
endmodule

module sub_module1(a, b, y);
  wire _0_;
  wire _1_;
  wire _2_;
  input a;
  wire a;
  input b;
  wire b;
  output y;
  wire y;
  sky130_fd_sc_hd__and2_0 _3_ (
    .A(_1_),
    .B(_0_),
    .X(_2_)
  );
  assign _1_ = b;
  assign _0_ = a;
  assign y = _2_;
endmodule

module sub_module2(a, b, y);
  wire _0_;
  wire _1_;
  wire _2_;
  input a;
  wire a;
  input b;
  wire b;
  output y;
  wire y;
  sky130_fd_sc_hd__or2_0 _3_ (
    .A(_1_),
    .B(_0_),
    .X(_2_)
  );
  assign _1_ = b;
  assign _0_ = a;
  assign y = _2_;
endmodule
```
- Hierarchies are preserved

### Lab 2
- Writing a flat netlist
- Using `flatten` and `write_verilog -noattr multiple_modules_flat.v`, we get the following:
```verilog
/* Generated by Yosys 0.32+66 (git sha1 b168ff99d, gcc 11.4.0-1ubuntu1~22.04 -fPIC -Os) */

module multiple_modules(a, b, c, y);
  wire _0_;
  wire _1_;
  wire _2_;
  wire _3_;
  wire _4_;
  wire _5_;
  input a;
  wire a;
  input b;
  wire b;
  input c;
  wire c;
  wire net1;
  wire \u1.a ;
  wire \u1.b ;
  wire \u1.y ;
  wire \u2.a ;
  wire \u2.b ;
  wire \u2.y ;
  output y;
  wire y;
  sky130_fd_sc_hd__and2_0 _6_ (
    .A(_1_),
    .B(_0_),
    .X(_2_)
  );
  sky130_fd_sc_hd__or2_0 _7_ (
    .A(_4_),
    .B(_3_),
    .X(_5_)
  );
  assign _4_ = \u2.b ;
  assign _3_ = \u2.a ;
  assign \u2.y  = _5_;
  assign \u2.a  = net1;
  assign \u2.b  = c;
  assign y = \u2.y ;
  assign _1_ = \u1.b ;
  assign _0_ = \u1.a ;
  assign \u1.y  = _2_;
  assign \u1.a  = a;
  assign \u1.b  = b;
  assign net1 = \u1.y ;
endmodule
```
- Running `show` command
![show command](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/show_flatmodule.png)

- Executing submodule synthesis
![show command](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/show_submodule1.png)

- This concludes lab 2

### Lab 3.1
- Async Reset D-Flip Flop Synthesis and Simulations
- Simulation:
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/dff_async_res_sim1.png)
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/dff_async_res_sim2.png)

- Synthesis:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/dff_async_res_show.png)

### Lab 3.2
- Async Set D-Flip Flop Synthesis and Simulations
- Simulation:
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/dff_async_set_sim1.png)
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/dff_async_set_sim2.png)

- Synthesis:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/dff_async_set_show.png)

### Lab 3.3
- Sync reset D-Flip Flop Synthesis and Simulations
- Simulation:
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/dff_sync_reset_sim1.png)
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/dff_sync_reset_sim2.png)

- Synthesis:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/dff_sync_reset_show.png)

### Lab 4.1
- Running optimizations on `mult_2.v`
- Sythesis report:
![synthesis report](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/mul2_synth_report.png)
- `show` command:
![sshow](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/mul2_show.png)
- Netlist dumped by YoSys
```verilog
/* Generated by Yosys 0.32+66 (git sha1 b168ff99d, gcc 11.4.0-1ubuntu1~22.04 -fPIC -Os) */

module mul2(a, y);
  input [2:0] a;
  wire [2:0] a;
  output [3:0] y;
  wire [3:0] y;
  assign y = { a, 1'h0 };
endmodule
```

### Lab 4.2
- Running optimizations on `mult_8.v`
- Sythesis report:
![synthesis report](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/mul8_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day2_rtl/assets/mul8_show.png)
- Netlist dumped by YoSys
```verilog
/* Generated by Yosys 0.32+66 (git sha1 b168ff99d, gcc 11.4.0-1ubuntu1~22.04 -fPIC -Os) */

module mult8(a, y);
  input [2:0] a;
  wire [2:0] a;
  output [5:0] y;
  wire [5:0] y;
  assign y = { a, a };
endmodule
```

## Day 3 Assignments - RTL
### Lab 1
- Combinational Logic Operations
#### Lab 1.1
- `opt_check.v`
- Code:
```verilog
module opt_check (input a , input b , output y);
        assign y = a?b:0;
endmodule
```
- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/opt_check_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/opt_check_show.png)

#### Lab 1.2
- `opt_check2.v`
- Code:
```verilog
module opt_check2 (input a , input b , output y);
        assign y = a?1:b;
endmodule
```
- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/opt_check2_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/opt_check2_show.png)

#### Lab 1.3
- `opt_check3.v`
- Code:
```verilog
module opt_check3 (input a , input b, input c , output y);
        assign y = a?(c?b:0):0;
endmodule
```
- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/opt_check3_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/opt_check3_show.png)

#### Lab 1.4
- `opt_check4.v`
- Code:
```verilog
module opt_check4 (input a , input b , input c , output y);
	assign y = a?(b?(a & c ):c):(!c);
endmodule
```
- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/opt_check4_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/opt_check4_show.png)

#### Lab 1.5
- `multiple_module_opt.v`
- Code:
```verilog
module sub_module1(input a , input b , output y);
	assign y = a & b;
endmodule

module sub_module2(input a , input b , output y);
	assign y = a^b;
endmodule


module multiple_module_opt(input a , input b , input c , input d , output y);
	wire n1,n2,n3;
	sub_module1 U1 (.a(a) , .b(1'b1) , .y(n1));
	sub_module2 U2 (.a(n1), .b(1'b0) , .y(n2));
	sub_module2 U3 (.a(b), .b(d) , .y(n3));
	assign y = c | (b & n1);
endmodule
```
- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/mult_mod_opt_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/mult_mod_opt_show.png)

- END OF LAB 1

### Lab 2
- Sequential Logic Optimiztions
#### Lab 2.1
- `dff_const1.v`
- Code:
```verilog
module dff_const1(input clk, input reset, output reg q);
	always @(posedge clk, posedge reset)
		begin
			if(reset)
				q <= 1'b0;
			else
                q <= 1'b1;
		end
endmodule
```
- Simulation:
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const1_sim1.png)
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const1_sim2.png)

- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const1_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const1_show.png)

#### Lab 2.2
- `dff_const2.v`
- Code:
```verilog
module dff_const2(input clk, input reset, output reg q);
	always @(posedge clk, posedge reset)
		begin
        	if(reset)
                q <= 1'b1;
        	else
                q <= 1'b1;
		end
endmodule
```
- Simulation:
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const2_sim1.png)
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const2_sim2.png)

- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const2_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const2_show.png)

#### Lab 2.3
- `dff_const3.v`
- Code:
```verilog
module dff_const3(input clk, input reset, output reg q);
reg q1;

always @(posedge clk, posedge reset)
begin
        if(reset)
        begin
                q <= 1'b1;
                q1 <= 1'b0;
        end
        else
        begin
                q1 <= 1'b1;
                q <= q1;
        end
end
endmodule
```
- Simulation:
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const3_sim1.png)
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const3_sim2.png)

- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const3_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const3_show.png)

#### Lab 2.4
- `dff_const4.v`
- Code:
```verilog
module dff_const4(input clk, input reset, output reg q);
reg q1;

always @(posedge clk, posedge reset)
begin
        if(reset)
        begin
                q <= 1'b1;
                q1 <= 1'b1;
        end
        else
        begin
                q1 <= 1'b1;
                q <= q1;
        end
end

endmodule
```
- Simulation:
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const4_sim1.png)
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const4_sim2.png)

- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const4_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const4_show.png)

#### Lab 2.5
- `dff_const5.v`
- Code:
```verilog
module dff_const5(input clk, input reset, output reg q);
reg q1;

always @(posedge clk, posedge reset)
begin
        if(reset)
        begin
                q <= 1'b0;
                q1 <= 1'b0;
        end
        else
        begin
                q1 <= 1'b1;
                q <= q1;
        end
end

endmodule
```
- Simulation:
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const5_sim1.png)
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const5_sim2.png)

- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const5_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/dff_const5_show.png)

- END OF LAB 2

### Lab 3
- Sequential Optimisations for Unused Outputs
#### Lab 3.1
- `counter_opt.v`
- Code:
```verilog
module counter_opt (input clk , input reset , output q);
reg [2:0] count;
assign q = count[0];

always @(posedge clk ,posedge reset)
begin
        if(reset)
                count <= 3'b000;
        else
                count <= count + 1;
end
endmodule
```
- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/counter_opt_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/counter_opt_show.png)

#### Lab 3.2
- `counter_opt2.v`
- Code:
```verilog
module counter_opt2 (input clk , input reset , output q);
reg [2:0] count;
assign q = (count[2:0] == 3'b100);

always @(posedge clk ,posedge reset)
begin
        if(reset)
                count <= 3'b000;
        else
                count <= count + 1;
end

endmodule
```
- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/counter_opt2_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/counter_opt2_show.png)

- END OF LAB 3

## Day 4 Assignments - RTL
### Lab 1 
- GLS and Synthesis-Simulation Mismatch
#### Lab 1.1
- 'ternary_operator_mux.v'
```verilog
module ternary_operator_mux (input i0 , input i1 , input sel , output y);
	assign y = sel?i1:i0;
endmodule
```
- Simulation:
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day4_rtl/assets/tern_op_sim1.png)
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day4_rtl/assets/tern_op_sim2.png)

- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/tern_op_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/tern_op_show.png)

- GLS to Gate-Level Simulation
![gls simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day4_rtl/assets/tern_op_gls_sim1.png)
![gls simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day4_rtl/assets/tern_op_gls_sim2.png)

#### Lab 1.2
- 'bad_mux.v'
```verilog
module bad_mux (input i0 , input i1 , input sel , output reg y);
always @ (sel)
begin
	if(sel)
		y <= i1;
	else 
		y <= i0;
end
endmodule
```
- Simulation:
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day4_rtl/assets/bad_mux_sim1.png)
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day4_rtl/assets/bad_mux_sim2.png)

- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/bad_mux_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/bad_mux_show.png)

- GLS to Gate-Level Simulation
![gls simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day4_rtl/assets/bad_mux_gls_sim1.png)
![gls simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day4_rtl/assets/bad_mux_gls_sim2.png)

### Lab 2
- Synth-Sim Mismatch for Blocking Statement
- 'blocking_caveat.v'
```verilog
module blocking_caveat (input a , input b , input  c, output reg d); 
reg x;
always @ (*)
begin
	d = x & c;
	x = a | b;
end
endmodule
```
- Simulation:
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day4_rtl/assets/block_sim1.png)
![simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day4_rtl/assets/block_sim2.png)

- Synthesis report:
![synthesis](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/block_synth_report.png)
- `show` command:
![show](https://github.com/alfadelta10010/pes-asic-class/blob/main/day3_rtl/assets/block_show.png)

- GLS to Gate-Level Simulation
![gls simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day4_rtl/assets/block_gls_sim1.png)
![gls simulation](https://github.com/alfadelta10010/pes-asic-class/blob/main/day4_rtl/assets/block_gls_sim2.png)

- This concludes lab 2