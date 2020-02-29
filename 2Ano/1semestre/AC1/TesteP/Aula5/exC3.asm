# Mapa de registos:



	.data
	
array:	.word str1,str2,str3

str1:	.asciiz "Array"
str2:	.asciiz "de"
str3:	.asciiz "ponteiros"
str4:	.asciiz "\nString #"
str5:	.asciiz ": "
	
	.eqv SIZE,3
	.eqv print_string,4
	.eqv print_char,11
	.eqv print_int10,1
	.text
	.globl main
	
main:	li $t0,0	# i = 0;
	
	
for:	bge $t0,SIZE,endf	# i < SIZE
	
	la $a0,str4
	li $v0,print_string
	syscall
	
	la $a0,($t0)
	li $v0,print_int10
	syscall
	
	la $a0,str5
	li $v0,print_string
	syscall
	
	la $t1,array
	li $t2,0	# j = 0
	

	sll $t3,$t0,2
	add $t3,$t3,$t1
	lw $t4,0($t3)		# t5 = array[i]
	
while: 	add $t5,$t2,$t4
	lb $t6,0($t5)
	
	beq $t6,'\0',endw
	
	la $a0,0($t6)
	li $v0,print_char
	syscall
	
	li $a0,'-'
	li $v0,print_char
	syscall
	
	addi $t2,$t2,1
	
	j	while
	
endw:	addi $t0,$t0,1
	j for
	
endf:	jr $ra
	
	
