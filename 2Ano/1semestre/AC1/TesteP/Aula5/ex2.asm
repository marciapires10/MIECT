# Mapa de registos
# p: $t0
# *p: $t1
# lista+Size: $t2
 	.data
str1: 	.asciiz "; "

str2: 	.asciiz "\nConteudo do array:\n"

lista:	.word 8,-4,3,5,124,-15,87,9,27,15 # a diretiva ".word" alinha num endereço
 						# múltiplo de 4
 	.eqv print_int10,1
 	.eqv print_string,4
 	.eqv SIZE,10
 	.text
 	.globl main
 	
main: 	la $a0, str2 # print_string(...)
	li $v0, print_string
	syscall
	
 	la $t0,lista # p = lista
 	li $t2,SIZE #
 	sll $t2,$t2,2 #
 	addu $t2,$t0,$t2 # $t2 = lista + SIZE;
 	
while: 	bgeu $t0,$t2, endw # while(p < lista+SIZE) {
 	lw $t1,($t0) # $t1 = *p;
 	
 	la $a0,($t1)
 	li $v0, print_int10 # print_int10( *p );
 	syscall
 	
 	la $a0, str1
 	li $v0, print_string # print_string(...);
 	syscall
 	
 	addu $t0,$t0,4 # p++;
 	j while # }
 	
endw:	jr $ra # termina o programa 
