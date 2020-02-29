	.equ READ_INT10, 5
	.equ PRINT_INT, 6
	.equ PRINT_INT10, 7
	.equ PRINT_STR, 8
	.data

prompt: .asciiz "\nIntroduza um numero (sinal e módulo): "
base2:	.asciiz "\nValor lido em base 2: "
base16:	.asciiz "\nValor lido em base 16: "
base10u:.asciiz "\nValor lido em base 10 (unsigned): "
base10s:.asciiz "\nValor lido em base 10 (signed): "

	.text
	.globl main

main:	la $a0, prompt
	li $v0, PRINT_STR
	syscall

	li $v0, READ_INT10
	syscall
	move $t0, $v0

	la $a0, base2
	li $v0, PRINT_STR
	syscall
	
	move $a0, $t0,
	li $a1, 2
	li $v0, PRINT_INT
	syscall

	la $a0, base16
	li $v0, PRINT_STR
	syscall

	move $a0, $t0
	li $a1, 16
	li $v0, PRINT_INT
	syscall

	la $a0, base10u
	li $v0, PRINT_STR
	syscall

	move $a0, $t0
	li $a1, 10
	li $v0, PRINT_INT	
	syscall

	la $a0, base10s
	li $v0, PRINT_STR
	syscall
	
	move $a0, $t0
	li $v0, PRINT_INT10
	syscall
	
	jr $ra 