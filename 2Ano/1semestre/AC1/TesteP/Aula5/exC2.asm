# Mapa de registos:
# array: $t0
# i: $t1
# p: $t3

	.data

array:	.word str1,str2,str3
str1:	.asciiz "Array"
str2:	.asciiz "de"
str3:	.asciiz "ponteiros"

	.eqv print_string,4
	.eqv print_char,11
	.eqv SIZE,3
	
	.text
	.globl main
	
main:	
	li $t2,SIZE
	sll $t2,$t2,2	
	la $t3,array	# p = array
	addu $t4,$t3,$t2	# pultimo = array + SIZE
	
	
for:	bge $t3,$t4, endf	# (p < pultimo)
	
	lw $t5,0($t3)
	

	la $a0,0($t5)
	li $v0,print_string
	syscall
	
	li $a0,'\n'
	li $v0,print_char
	syscall
	
	add $t3,$t3,4
	
	j	for
endf:	jr $ra
