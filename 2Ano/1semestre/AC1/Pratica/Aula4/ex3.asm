	# Mapa de registos
	# p: $t0
	# pultimo: $t1
	# *p: $t2
	# soma: $t3
	
 	.data
 	
array:	.word 7692,23,5,234
 	.eqv print_int10,1
 	.eqv SIZE,4
 	.text
 	.globl main
 	
main: 	li $t3,0 # soma = 0;
 	li $t4,SIZE #
 	sub $t4,$t4,1 # $t4 = 3
 	sll $t4,$t4,2 # ou "mul $t4,$t4,4"
 	la $t0,...  # p = array;
 	addu $t1,$t0,... # pultimo = array + SIZE - 1;
 	
while: 				# while(p <= pultimo)
	b??u $t0,...,endw # {
 	... $t2,0(...) # $t2 = *p;
 	add $t3,... # soma = soma + (*p);
 	addu $t0,$t0,... # p++;
 	(...) # }
 	(...) # print_int10(soma);
 	jr $ra # termina o programa 