        .equ READ_CORE_TIMER, 11
        .equ RESET_CORE_TIMER, 12
        .equ K, 20000


        .data

        .text
        .globl delay

delay:  move $a0, $t0

for:    ble $t0, $0, endf
        
        li $v0, RESET_CORE_TIMER
        syscall

        li $v0, READ_CORE_TIMER
        syscall

while:  bge $v0, K, endw

        subu $t0, $t0, 1

        j endw

endw:   j for

endf:   jr $ra