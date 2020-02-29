	.equ PRINT_STR, 8
	.equ IN_KEY, 1
	.data

str:	.asciiz "Key pressed\n"
	
	.text
	.globl main

main:

while:	li $v0, IN_KEY
		syscall
	move $t0, $v0

while2: beq $t0, 0, while

if:	beq $t0, '\n', endw

	la $a0, str
	li $v0, PRINT_STR
	syscall

	j while

endw: 	li $v0, 0
	jr $ra