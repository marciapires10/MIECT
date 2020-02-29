        .equ SFR_BASE_H1, 0xBF88
        
        .equ TRISE, 0x6100
        .equ TRISB, 0x6040
        .equ LATE, 0x6120
        .equ PORTB, 0x6050
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

        lui $t5, SFR_BASE_H1

        # RE0 a RE3 como saídas
        lw $t1, TRISE($t5)
        andi $t1, $t1, 0xFFF0
        sw $t1, TRISE($t5)

        # RB0 a RB3 como entradas
        lw $t2, TRISB($t5)
        andi $t2, $t2, 0xFFF0
        ori $t2, $t2, 0x000F
        sw $t2, TRISB($t5)

        li $t4, 0

while:  li $a0, 667
        jal delay
    
        lw $t6, PORTB($t5)
        andi $t6, $t6, 0x0004
        sw $t6, PORTB($t5)

if:     beq $t6, 0, else
        andi $t7, $t4,0x0008

if_1:   beq $t7,0, else_1
        sll $t4, $t4, 1
        j jump_1

else_1: sll $t4, $t4, 1
        ori $t4, $t4, 0x0001 

jump_1: lw $t3, LATE($t5)
        andi $t3, $t3, 0xFFF0
        or $t3, $t3, $t4
        sw $t3, LATE($t5)

        j   endif

else:   andi $t7, $t4,0x0001

if_2:   beq $t7,0, else_2
        srl $t4, $t4, 1
        j jump_2

else_2: srl $t4, $t4, 1
        ori $t4, $t4, 0x0008

jump_2: lw $t3, LATE($t5)
        andi $t3, $t3, 0xFFF0
        or $t3, $t3, $t4
        sw $t3, LATE($t5)

endif:  j while

        lw $ra, 0($sp)
        addiu $sp, $sp, 4

        jr $ra