# Mapa de registos:
# str: $a0 -> $s0 (argumento � passado em $a0)
# p1: $s1 (registo callee-saved)
# p2: $s2 (registo callee-saved)
#

	.data
	.align 2
	
	.eqv print_string, 4

str: 	.asciiz "String para testar"	
	
	.text
	.globl main
	
exchange:
	lb $t0, 0($a0)
	lb $t1, 0($a1)
	
	sb $t1, 0($a0)
	sb $t0, 0($a1)
	
	jr $ra
	
main: 	subiu $sp, $sp, 4
	sw $ra, 0($sp)
	
	la $a0, str
	
	jal strrev
	
	move $a0, $v0
	
	li $v0, print_string
	syscall
	
	li $v0, 0
	
	lw $ra, 0($sp)
	addiu $sp, $sp, 4
	
	jr $ra
		
strrev: subu $sp,$sp,16 # reserva espa�o na stack
 	sw $ra,0($sp) # guarda endere�o de retorno
 	sw $s0,4($sp) # guarda valor dos registos
 	sw $s1,8($sp) # $s0, $s1 e $s2
 	sw $s2,12($sp) #
 	move $s0,$a0 # registo "callee-saved"
 	move $s1,$a0 # p1 = str
 	move $s2,$a0 # p2 = str
 	
while1: # while( *p2 != '\0' ) {
	beq $t0, '\0', endW1
 	addiu $s2, $s2, 1 # p2++;
 	lb $t0, 0($s2)
 	j while1 # }
 	
endW1: 	subiu $s2, $s2, 1 # p2--;  # ou ent�o addiu $s2, $s2, -1
 	
while2: # while(p1 < p2) {
 	bge $s1, $s2, endW2
 	move $a0, $s1 #
 	move $a1, $s2 #
 	jal exchange # exchange(p1,p2)
 	
 	addiu $s1, $s1, 1
 	subiu $s2, $s2, 1
 	
 	j while2 # }
endW2: 
 	move $v0,$s0 # return str
 	lw $ra, 0($sp) # rep�e endere�o de retorno
 	lw $s0, 4($sp) # rep�e o valor dos registos
 	lw $s1, 8($sp) # $s0, $s1 e $s2
 	lw $s2, 12($sp) #
 	addu $sp, $sp, 16 # liberta espa�o da stack
 	jr $ra # termina a sub-rotina