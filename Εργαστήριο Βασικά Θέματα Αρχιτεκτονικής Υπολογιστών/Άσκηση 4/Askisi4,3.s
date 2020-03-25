.arm
.text
.global main

main:
STMDB R13!,{R0-R12,R14}
LDR R0,=Values
MOV R6,#0
loop1:
LDR R1,=Const
ADD R1,R1,#6
LDR R2,[R0],#4
LDRB R3,[R1]
SUB R1,R1,#1
MOV R4,R3
BL Subrtn
ADD R6,R6,#1
CMP R6,#3
BLE loop1
end:
LDMIA R13!,{R0-R12,PC}

Subrtn:
STMDB R13!,{R4,R5,R7}
MOV R7,#0
loop2:
LDRB R3,[R1]
SUB R1,R1,#1
MUL R5,R4,R2
ADD R4,R5,R3
ADD R7,R7,#1
CMP R7,#5 
BLE loop2
STR R4,[R0,#0x0c]
LDMIA R13!,{R4,R5,R7}
MOV PC,LR

.data
Values:
.word 0x10
.word 0x50A
.word 0xCDCA
.word 0x80AB
.word 0,0,0,0

Const:
.byte 0x04,0x07,0x05
.byte 0x20,0x1A,0x12,0x06
 