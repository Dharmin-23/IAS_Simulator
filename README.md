# IAS_Simulator
============IAS IMPLEMENTATION IN C/C++ LANGUAGUE ============

In the following assignment we aim to emulate the various ISA instuction set, and process using IAS computer.

The registers involved in IAS computer are:
AC  : Accumulator
	Accumulate/hold results of an ALU operation

IR  : Instructions Register
	8 bit opcode of the instruction to be executed
	
IBR : Instructions Buffer register
	Holds the RHS instruction temporarily

MQ  : Multiplier/Quotioent Register
	LSB of product

MBR : Memory BUffer register
	Contains a word to be read/stored in memory or I/O

MAR : Memory Adress register
	Specifies the address in memory of the word to be written/read into MBR

PC  : Program Counter
	Holds the next instruction’s address

Running of Program consisits of two cycles:
i) Fetch cycle:
	 Opcode of the next instruction is loaded into the IR and the address portion is loaded into the MAR. 
	 In this phase the Program Counter(PC) value is moved to the Memory Address Register(MAR) and the value at the memory location MAR is fed into the Memory Buffer Register(MBR).
         Once this is done, the OPCODE of the LEFT instruction is loaded into the Instruction Register(IR)and the address portion is loaded into the MAR and the right instruction is loaded into the Instruction Buffer Register(IBR).

ii) Execute Cycle : Consists of 2 types:
	Decode Cycle:In this phase the data stored in the registers is decoded based on the instruction OPCODE 
                value and the corresponding control signals are sent to move the data around or 
                perform specific tasks. The "binary data" is well read and converted into an assembly
                language for the execute phase.
	
	Execute Cycle: In this phase the ALU performs the tasks as specified by the assembly language for a 
                particular C/C++ program.

To emulate the above cycles, we have displayed the value stored in each register.
The steps to run the program are as follows:

i) Choose the required operation to be performed.

ii) Input the value of variables.

iii) Check the value stored in each memory location, toggle through the options displayed. Increment or decrement through the memory, or choose execute.
To go into the execution cycle. The instructions are hard-coded into the memory hence choose the memory location from where one wishes to execute the instructions.

iv) Decrement to the memory location where the answer is going to be stored.

v) EXIT to exit the code.

Here,we tried to execute different programes as examples by asking for choices from user:-
 1 --> Simple Addition
 2 --> Simple Subtraction (2nd Number - 1st Number)
 3 --> Simple Multiplication
 4 --> Simple Division (Displays Quotient) (2nd Number / 1st Number)
 5 --> Example Program in Question pdf
 6 --> Factorial of a number


=============================
+  IMT2020127 Dharmin Mehta +
+  IMT2020088 Heet Vasani   +
=============================
