.arm
.text
.global main

main:
STMDB R13!,{R0-R12}
MOV R4,#2
LDR R1,=Values
LDR R0,[R1]
MOV R1,#1
LDR R3,=Results
MOV R2,#20
loop:
BL LFSR
ADD R4,R4,#1
CMP R4,R2
STRB R1,[R3],#1
AND R1,R1,#0x0000000F
BLE loop
end:
LDMIA R13!,{R0-R12}
LFSR:
STMDB R13!,{R5-R12}
MOV R6,#0
MOVS R5,R1,LSL #1
ADC R5,R5,R6
EOR R1,R0,R5
LDMIA R13!,{R5-R12}
MOV PC,LR

.data
Values:
.word 0x8
Results:
.byte 0x00,0x00,0x00,0x00
.byte 0x00,0x00,0x00,0x00
.byte 0x00,0x00,0x00,0x00
.byte 0x00,0x00,0x00,0x00
.byte 0x00,0x00,0x00,0x00
