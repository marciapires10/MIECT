	.equ GET_CHAR, 2
	.equ PUT_CHAR, 3
	.data
	
	.text
	.globl main

main:
while:	li $v0, GET_CHAR
	syscall
	move $t0, $v0

if:	beq $t0, '\n', endw
	move $a0, $t0
	li $v0, PUT_CHAR
	syscall
	
	j while

endw:	li $v0, 1
	jr $ra