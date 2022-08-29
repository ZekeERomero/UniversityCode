* C- compiler version C-F21
* Built: Dec 12, 2021 (toffset telemetry)
* Author: Ezequiel E. Romero
* File compiled:  example.tm
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION input
  1:     ST  3,-1(1)	Store return address 
  2:     IN  2,2,2	Grab int input 
  3:     LD  3,-1(1)	Load return address 
  4:     LD  1,0(1)	Adjust fp 
  5:    JMP  7,0(3)	Return 
* END FUNCTION input
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION output
  6:     ST  3,-1(1)	Store return address 
  7:     LD  3,-2(1)	Load parameter 
  8:    OUT  3,3,3	Output integer 
  9:     LD  3,-1(1)	Load return address 
 10:     LD  1,0(1)	Adjust fp 
 11:    JMP  7,0(3)	Return 
* END FUNCTION output
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputb
 12:     ST  3,-1(1)	Store return address 
 13:    INB  2,2,2	Grab bool input 
 14:     LD  3,-1(1)	Load return address 
 15:     LD  1,0(1)	Adjust fp 
 16:    JMP  7,0(3)	Return 
* END FUNCTION inputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputb
 17:     ST  3,-1(1)	Store return address 
 18:     LD  3,-2(1)	Load parameter 
 19:   OUTB  3,3,3	Output bool 
 20:     LD  3,-1(1)	Load return address 
 21:     LD  1,0(1)	Adjust fp 
 22:    JMP  7,0(3)	Return 
* END FUNCTION outputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputc
 23:     ST  3,-1(1)	Store return address 
 24:    INC  2,2,2	Grab char input 
 25:     LD  3,-1(1)	Load return address 
 26:     LD  1,0(1)	Adjust fp 
 27:    JMP  7,0(3)	Return 
* END FUNCTION inputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputc
 28:     ST  3,-1(1)	Store return address 
 29:     LD  3,-2(1)	Load parameter 
 30:   OUTC  3,3,3	Output char 
 31:     LD  3,-1(1)	Load return address 
 32:     LD  1,0(1)	Adjust fp 
 33:    JMP  7,0(3)	Return 
* END FUNCTION outputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outnl
 34:     ST  3,-1(1)	Store return address 
 35:  OUTNL  3,3,3	Output a newline 
 36:     LD  3,-1(1)	Load return address 
 37:     LD  1,0(1)	Adjust fp 
 38:    JMP  7,0(3)	Return 
* END FUNCTION outnl
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
* TOFF set: -2
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF set: -6
 40:    LDC  3,3(6)	load size of array hi
 41:     ST  3,-2(1)	save size of array hi
  1:    LIT  "man"
 42:    LDA  3,-1(0)	Load address of char array 
 43:    LDA  4,-3(1)	address of lhs 
 44:     LD  5,1(3)	size of rhs 
 45:     LD  6,1(4)	size of lhs 
 46:    SWP  5,6,6	pick smallest size 
 47:    MOV  4,3,5	array op = 
* Compound Body
* TOFF set: -9
* FOR
 48:    LDC  3,0(6)	Load integer constant 
 49:     ST  3,-6(1)	save starting value in index variable 
 50:    LDA  3,-3(1)	Load address of base of array hi
 51:     LD  3,1(3)	Load array size 
 52:     ST  3,-7(1)	save stop value 
 53:    LDC  3,1(6)	default increment by 1 
 54:     ST  3,-8(1)	save step value 
 55:     LD  4,-6(1)	loop index 
 56:     LD  5,-7(1)	stop value 
 57:     LD  3,-8(1)	step value 
 58:    SLT  3,4,5	Op < 
 59:    JNZ  3,1(7)	Jump to loop body 
* COMPOUND
* TOFF set: -9
* Compound Body
* EXPRESSION
* CALL output
 61:     ST  1,-9(1)	Store fp in ghost frame for output
* TOFF dec: -10
* TOFF dec: -11
* Param 1
 62:     LD  3,-6(1)	Load variable i
 63:     ST  3,-11(1)	Push parameter 
* TOFF dec: -12
* Param end output
 64:    LDA  1,-9(1)	Ghost frame becomes new active frame 
 65:    LDA  3,1(7)	Return address in ac 
 66:    JMP  7,-61(7)	CALL output
 67:    LDA  3,0(2)	Save the result in ac 
* Call end output
* TOFF set: -9
* EXPRESSION
* CALL outputc
 68:     ST  1,-9(1)	Store fp in ghost frame for outputc
* TOFF dec: -10
* TOFF dec: -11
* Param 1
 69:    LDC  3,58(6)	Load char constant 
 70:     ST  3,-11(1)	Push parameter 
* TOFF dec: -12
* Param end outputc
 71:    LDA  1,-9(1)	Ghost frame becomes new active frame 
 72:    LDA  3,1(7)	Return address in ac 
 73:    JMP  7,-46(7)	CALL outputc
 74:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -9
* EXPRESSION
* CALL outputc
 75:     ST  1,-9(1)	Store fp in ghost frame for outputc
* TOFF dec: -10
* TOFF dec: -11
* Param 1
 76:    LDC  3,32(6)	Load char constant 
 77:     ST  3,-11(1)	Push parameter 
* TOFF dec: -12
* Param end outputc
 78:    LDA  1,-9(1)	Ghost frame becomes new active frame 
 79:    LDA  3,1(7)	Return address in ac 
 80:    JMP  7,-53(7)	CALL outputc
 81:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -9
* EXPRESSION
* CALL outputc
 82:     ST  1,-9(1)	Store fp in ghost frame for outputc
* TOFF dec: -10
* TOFF dec: -11
* Param 1
 83:    LDA  3,-3(1)	Load address of base of array hi
 84:     ST  3,-11(1)	Push left side 
* TOFF dec: -12
 85:     LD  3,-6(1)	Load variable i
* TOFF inc: -11
 86:     LD  4,-11(1)	Pop left into ac1 
 87:    SUB  3,4,3	compute location from index 
 88:     LD  3,0(3)	Load array element 
 89:     ST  3,-11(1)	Push parameter 
* TOFF dec: -12
* Param end outputc
 90:    LDA  1,-9(1)	Ghost frame becomes new active frame 
 91:    LDA  3,1(7)	Return address in ac 
 92:    JMP  7,-65(7)	CALL outputc
 93:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -9
* EXPRESSION
* CALL outputc
 94:     ST  1,-9(1)	Store fp in ghost frame for outputc
* TOFF dec: -10
* TOFF dec: -11
* Param 1
 95:    LDC  3,32(6)	Load char constant 
 96:     ST  3,-11(1)	Push parameter 
* TOFF dec: -12
* Param end outputc
 97:    LDA  1,-9(1)	Ghost frame becomes new active frame 
 98:    LDA  3,1(7)	Return address in ac 
 99:    JMP  7,-72(7)	CALL outputc
100:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -9
* EXPRESSION
* CALL outputc
101:     ST  1,-9(1)	Store fp in ghost frame for outputc
* TOFF dec: -10
* TOFF dec: -11
* Param 1
102:    LDC  3,44(6)	Load char constant 
103:     ST  3,-11(1)	Push parameter 
* TOFF dec: -12
* Param end outputc
104:    LDA  1,-9(1)	Ghost frame becomes new active frame 
105:    LDA  3,1(7)	Return address in ac 
106:    JMP  7,-79(7)	CALL outputc
107:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -9
* EXPRESSION
* CALL outputc
108:     ST  1,-9(1)	Store fp in ghost frame for outputc
* TOFF dec: -10
* TOFF dec: -11
* Param 1
109:    LDC  3,32(6)	Load char constant 
110:     ST  3,-11(1)	Push parameter 
* TOFF dec: -12
* Param end outputc
111:    LDA  1,-9(1)	Ghost frame becomes new active frame 
112:    LDA  3,1(7)	Return address in ac 
113:    JMP  7,-86(7)	CALL outputc
114:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -9
* TOFF set: -9
* END COMPOUND
* Bottom of loop increment and jump
115:     LD  3,-6(1)	Load index 
116:     LD  5,-8(1)	Load step 
117:    ADD  3,3,5	increment 
118:     ST  3,-6(1)	store back to index 
119:    JMP  7,-65(7)	go to beginning of loop 
 60:    JMP  7,59(7)	Jump past loop [backpatch] 
* END LOOP
* RETURN
120:    LDC  3,2(6)	Load integer constant 
121:    LDA  2,0(3)	Copy result to return register 
122:     LD  3,-1(1)	Load return address 
123:     LD  1,0(1)	Adjust fp 
124:    JMP  7,0(3)	Return 
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
125:    LDC  2,0(6)	Set return value to 0 
126:     LD  3,-1(1)	Load return address 
127:     LD  1,0(1)	Adjust fp 
128:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,128(7)	Jump to init [backpatch] 
* INIT
129:    LDA  1,-4(0)	set first frame at end of globals 
130:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
131:    LDA  3,1(7)	Return address in ac 
132:    JMP  7,-94(7)	Jump to main 
133:   HALT  0,0,0	DONE! 
* END INIT
