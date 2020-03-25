.arm
.text
.global main

main:
STMDB R13!,{R0-R12,R14}
LDR R6,=Table
MOV R7,#0x14
MOV R9,#OxC0
MOV R1,#0
SUB R8,R7,#1
BL InsertionSort
BL CheckIfSorted
end:
LDMIA R13!,{R0-R12,PC}

InsertionSort:
STMDB R13!,{R0,R2,R3,R4,R5}
TableSizeMinus1IsGreaterThanFirstElementPosition:
ADD R3,R1,#1
LDRB R0,[R6,R1]
MOV R2,R1
TableSizeIsGreaterThanNextElementPosition:
LDRB R4,[R6,R3]
CMP R0,R4
BLE SmallestElementIsLessOrEqualThanNextElement
MOV R2,R3
MOV R0,R4
SmallestElementIsLessOrEqualThanNextElement:
ADD R3,R3,#1
CMP R7,R3
BGT TableSizeIsGreaterThanNextElementPosition
LDRB R5,[R6,R1]
STRB R0,[R6,R1]
STRB R5,[R6,R2]
ADD R1,R1,#1
CMP R8,R1
BGT TableSizeMinus1IsGreaterThanFirstElementPosition
LDMIA R13!,{R0,R2,R3,R4,R5}
MOV PC,LR

CheckIfSorted:
STMDB R13!,{R0,R1,R3,R4}
MOV R0,#0
MOV R3,#1
NextElementPositionIsLessOrEqualThanTableSizeMinus1:
LDRB R1,[R6,R0]
LDRB R4,[R6,R3]
CMP R1,R4
BLE PreviousElementIsLessOrEqualThanNextElement
MOV R9,#0xFFFFFFFF
PreviousElementIsLessOrEqualThanNextElement:
ADD R0,R0,#1
ADD R3,R3,#1
CMP R3,R8
BLE NextElementPositionIsLessOrEqualThanTableSizeMinus1
LDMIA R13!,{R0,R1,R3,R4}
MOV PC,LR

.data
Table:
.byte 0x45,0x82,0xDA,0x10,0x98
.byte 0x23,0x23,0x66,0x34,0xAA
.byte 0x57,0x35,0xBD,0xAC,0x78
.byte 0x09,0x12,0x44,0x39,0xDA
