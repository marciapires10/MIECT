                .equ SFR_BASE_HI, 0xBF88

                .equ TRISE, 0x6100
                .equ LATE, 0x6120
                .equ TRISB, 0x6040
                .equ PORTB, 0x6050

                .equ READ_CORE_TIMER, 11
                .equ RESET_CORE_TIMER, 12
                .equ K, 20000

                .data
                
                .text
                .globl main

# Delay

delay:  move $t0, $a0
        
for:    ble $t0, $0, endfor

        li $v0, RESET_CORE_TIMER
        syscall

while_1:li $v0, READ_CORE_TIMER
        syscall

        blt $v0, K, while_1

        subu $t0, $t0, 1

        j for

endfor: jr $ra

# Função

main:   subu $sp, $sp, 4
        sw $ra, 0($sp)

        lui $t1, SFR_BASE_HI

        # saídas
        lw $t2, TRISE($t1)
        andi $t2, $t2, 0xFFF0
        sw $t2, TRISE($t1)

        # entradas
        lw $t3, TRISB($t1)
        andi $t3, $t3, 0xFFF0
        ori $t3, $t3, 0x000F
        sw $t3, TRISB($t3)

        li $t4, 0x0001 # counter = 0;

while:  li $a0, 500
        jal delay

        lw $t5, PORTB($t1)
        andi $t5, $t5, 0x0002 # reter o valor de RB1
        sw $t5, PORTB($t1)

if:     beq $t5, 0, else

if_1:   bne $t4, 0x0008, else_1
        li $t4, 0x0001

        j endif

else_1: sll $t4, $t4, 1
        
        j endif

else:   

if_2:   bne $t4, 0x0001, else_2
        li $t4, 0x0008
        
        j endif
        
else_2: srl $t4, $t4, 1


endif:  lw $t7, LATE($t1)
        andi $t7, $t7, 0xFFF0
        or $t7, $t7, $t4
        sw $t7, LATE($t1)

        j while

        lw $ra, 0($sp)
        addiu $sp, $sp, 4

        jr $ra





