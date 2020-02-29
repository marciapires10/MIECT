        .equ SR_BASE_H1, 0xBF88
        
        .equ TRISE, 0x6100
        .equ TRISB, 0x6040
        .equ PORTB, 0x6050 
        .equ LATE, 0x6120

        .data

        .text
        .globl main

main:   lui $t1, SR_BASE_H1

        # porto RE0 como saída
        lw $t2, TRISE($t1)
        andi $t2, $t2, 0xFFFE
        sw $t2, TRISE($t1)

        # porto RB0 como entrada
        lw $t3, TRISB($t1)
        andi $t3, $t3, 0xFFFE
        ori $t3, $t3, 0x0001
        sw $t3, TRISB($t1)

while:  lw $t4, PORTB($t1)
        andi $t4, $t4, 0x0001


        lw $t5, LATE($t1)
        andi $t5, $t5, 0xFFFE
        xor $t5, $t4, 1
        sw $t5, LATE($t1)

        j while

        jr $ra




