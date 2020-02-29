        .equ SFR_BASE_HI, 0xBF88

        .equ TRISE, 0x6100
        .equ TRISB, 0x6040
        .equ PORTB, 0x6050
        .equ LATE, 0x6120

        .data

        .text
        .globl main

main:   lui $t1, SFR_BASE_HI 
        
        # porto RE0 como saída
        lw $t2, TRISE($t1)
        andi $t2, $t2, 0xFFFE
        sw $t2, TRISE($t1)
        
        # porto RB0 como entrada
        lw $t3, TRISB($t1)
        andi $t3, $t3, 0xFFFE # fica a zero, and com 1 fica igual, and com 0 fica 0
        ori $t3, $t3, 0x0001 # com 0 fica igual, se for 1 e antes 0, 1;
        sw $t3, TRISB($t1)

        # RE0 = RB0
while:  lw $t4, PORTB($t1)
        andi $t4, $t4, 0x0001 # todos a 0, exceto o que eu quero, que fica com o mesmo valor

        lw $t5, LATE($t1)
        andi $t5, $t5, 0xFFFE # todos iguais exceto o último que fica a 0
        or $t5, $t5, $t4 # último bit leva o valor de $t4 (PORTB0)
        sw $t5, LATE($t1)

        j while

        jr $ra # é obrigatório mas nunca chega cá -> while(1) infinito



