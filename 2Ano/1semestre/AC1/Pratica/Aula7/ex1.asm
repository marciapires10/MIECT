# Mapa de registos
# res: $v0
# s: $a0
# *s: $t0
# digit: $t1
# Sub-rotina terminal: não devem ser usados registos $sx

	.data
str:	.asciiz "2016 e 2020 sao anos bissextos"
	
	.eqv print_int, 1
	
	.text
	.globl main
	
main:	addiu $sp, $sp, -4
	sw $ra, ($sp)
	
	la $a0, str
	jal atoi
	
	move $a0,$v0
	li $v0, print_int
	syscall
	
	lw $ra,($sp)
	
	addiu $sp,$sp,4
	
	li $v0,0
	
	jr $ra
	
	
atoi: li $v0,0 # res = 0;

while: lb $t0,($a0) # while(*s >= ...)

 	blt $t0,'0',endW #
 	bgt $t0,'9',endW  # {
 	sub $t1,$t0,'0' # digit = *s – '0'
 	addiu $a0, $a0,1 # s++;
 	mul $v0,$v0,10 # res = 10 * res;
 	add $v0,$v0,$t1 # res = 10 * res + digit;
 	j while # }
 	
endW: 	jr $ra # termina sub-rotina