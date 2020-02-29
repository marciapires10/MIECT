# Mapa de registos
# num: $t0
# p: $t1
# *p: $t2
 	.data
 	.eqv SIZE, 20
 	.eqv print_int10, 1
 	.eqv read_string, 8
 	
str: 	.space SIZE

 	.text
 	.globl main
 	
main: 	li $t0,0
	
	la $a0, str
	li $v0, read_string
	syscall
	
	li $a1, SIZE	# ...
	
 	la $t1,str # p = str;
 	
while: 	# while(*p != '\0')
 	lb $t2,($t1) #
 	beq $t2,0,endw # {
 	blt $t2,'0',endif # if(str[i] >='0' &&
 	bgt $t2,'9',endif # str[i] <= '9')
 	addi $t0,$t0,1 # num++;
 	
endif:
 	addiu $t1,$t1,1 # p++;
 	j while # }
 	
endw: 	la $a0,($t0) # print_int10(num);
	li $v0, print_int10
	syscall
	
 	jr $ra # termina o programa
