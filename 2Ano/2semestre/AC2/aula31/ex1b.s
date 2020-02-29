        .equ SFR_BASE_HI, 0xBF88

        .equ TRISE, 0x6100
        .equ TRISB, 0x6040
        .equ LATE, 0x6120
        # .equ PORTB 0x6050
        .equ READ_CORE_TIMER, 11
        .equ RESET_CORE_TIMER, 12
        .equ K, 20000

        .data

        .text
        .globl main

# DELAY

       
delay:  move $t4, $a0 # para trabalhar com a variável que passamos em argumento

for:    ble $t4, $0, endf
        
        li $v0, RESET_CORE_TIMER # chama a função
        syscall

while_1:li $v0, READ_CORE_TIMER # chama a função
        syscall

        blt $v0, K, while_1 

        subu $t4, $t4, 1

        j for

endf:   jr $ra

# RESTO

main:   subu $sp, $sp, 4
        sw $ra, 0($sp)

        lui $t0, SFR_BASE_HI

        # portos como saídas
        lw $t1, TRISE($t0)
        andi $t1, $t1, 0xFFF0
        sw $t1, TRISE($t0)

        li $t2, 15 # counter = 0;

while:  li $a0, 1000 # frequência de 4Hz
        jal delay

        addi $t2, $t2, -1
        andi $t2, $t2, 0x000F

        lw $t3, LATE($t0)
        andi $t3, $t3, 0xFFF0
        or $t3, $t3, $t2
        sw $t3, LATE($t0)

        j while

        lw $ra, 0($sp)
        addiu $sp, $sp, 4

        jr $ra
