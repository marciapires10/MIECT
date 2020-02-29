# O argumento da fun��o � passado em $a0
# O resultado � devolvido em $v0
# Sub-rotina terminal: n�o devem ser usados registos $sx
	
	.data
s_hdr: 	.asciiz "O comprimento do string �: "
str: 	.asciiz "String para testar"
	
	.eqv print_string, 4
	.eqv print_int, 1
	
	
	.text
	.globl main
	
main:	addiu $sp, $sp, -4 	# space for $ra
	sw $ra, 0($sp) 		# save $ra
	
	la $a0, s_hdr		# print_string
	li $v0, print_string
	syscall
	
	la $a0, str 		# pass arg0 in $a0
	jal strlen		# call 'strlen'
	
	move $a0, $v0		# use return in $v0		
	li $v0, print_int	# print_int10(strlen(str))
	syscall
	
#	lw  $ra, ($sp)	# restore $ra
	addiu $sp, $sp, 4 	# restore $sp
	
	li $v0, 0		# return 0
	jr	$ra
	
# ---------------------------

strlen: li $t1,0 # len = 0;

while: 	lb $t0, 0($a0) 		# while(*s++ != '\0')
 	addiu $a0,$a0,1 #
 	beq $t0,'\0',endw # {
 	addi $t1, $t1, 1 # len++;
 	j while # }
 	
endw: 	move $v0,$t1 # return len;
 	jr $ra #
