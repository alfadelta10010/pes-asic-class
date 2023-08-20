# VLSI Physical Design -  Lab-work Repository
This repository contains all the assignments and information from the VLSI Physical Design for ASICs special topic taught at PES University, EC Campus, for ECE students, by [Kunal Ghosh](https://www.linkedin.com/in/kunal-ghosh-vlsisystemdesign-com-28084836/) from [VLSI System Design](vlsisystemdesign.com)

This repo has been divided into various subfolders for different days of the coursework
Click on the links below to find the documents for each lab:
- [Lab 1](https://github.com/alfadelta10010/pes-asic-class/blob/main/day1/lab1.md)
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
