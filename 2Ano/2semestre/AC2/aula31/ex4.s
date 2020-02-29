        .equ SFR_BASE_HI, 0xBF88
        .equ TRISE, 0x6100
        .equ LATE, 0x6120
        .equ READ_CORE_TIMER, 11
        .equ RESET_CORE_TIMER, 12
        .equ K, 20000

        .data

        .text
        .globl main

# DELAY

       
delay:  move $t0, $a0

for:    ble $t0, $0, endf
        
        li $v0, RESET_CORE_TIMER
        syscall

while_1:li $v0, READ_CORE_TIMER
        syscall

        blt $v0, K, while_1

        subu $t0, $t0, 1

        j for

endf:   jr $ra



# RESTO



main:   subu $sp, $sp, 4
        sw $ra, 0($sp)

        

        lui $t1, SFR_BASE_HI

        # porto RE0 como saída
        lw $t2, TRISE($t1)
        andi $t2, $t2, 0xFFFE
        sw $t2, TRISE($t1)

        li $s0, 0

while:  lw $t3, LATE($t1)
        andi $t3, $t3, 0xFFFE
        or $t3, $t3, $s0
        sw $t3, LATE($t1)

        li $a0, 500
        jal delay

        xori $s0, $s0, 1

        j while

        lw $ra, 0($sp)
        addiu $sp, $sp, 4

        jr $ra