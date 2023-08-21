# VLSI Physical Design -  Lab-work Repository
This repository contains all the assignments and information from the VLSI Physical Design for ASICs special topic taught at PES University, EC Campus, for ECE students, by [Kunal Ghosh](https://www.linkedin.com/in/kunal-ghosh-vlsisystemdesign-com-28084836/) from [VLSI System Design](vlsisystemdesign.com)

This repo has been divided into various subfolders for different days of the coursework
Click on the links below to find the documents for each lab:
- [Lab 1](https://github.com/alfadelta10010/pes-asic-class/tree/main#day---1-lab-assignments)
- [Lab 2]() - WIP

## Set up instructions for the coursework
The software required is as follows:
- [RISC-V GNU Compiler Toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain)
	- :warning: GCC-12 gives compiling issues for the proxy kernel, using GCC-8.3 solves this issue. You can download the pre-compiled toolchain from [here](https://static.dev.sifive.com/dev-tools/riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-linux-ubuntu14.tar.gz)
- [Spike RISC-V ISA Simulator](https://github.com/riscv-software-src/riscv-isa-sim)
- [RISC-V Proxy Kernel and Boot loader](https://github.com/riscv-software-src/riscv-pk)


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
- Write the program  `unsignedLimits.c` [shown here](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/unsignedLimits.c)
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

- Write the program  `signedLimits.c` [shown here](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/signedLimits.c)
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
cat load.s 
.section text
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