	.text
	.globl main
#main: 	ori $t0, $0, 3
main:	ori $v0, $0, 5 #syscall read_int
	syscall 
	#ori $t2, $0, 8
	#add $t1, $t0, $t0
	#add $t1, $t1, $t2
	#jr $ra
	ori $t0, $v0, 0 #e nestes casos, pode-se substituir por move que move imediatamente o valor de $t0 e $v0
	#
	ori $t2, $0, 8 #nestes casos, em vez de ori pode-se usar li que carrega imediatamente o valor de 8 em t2
	add $t1, $t0, $t0 
	sub $t1, $t1, $t2
	#
	ori $a0, $t1, 0
	ori $v0, $0, 1 #syscall print_int
	syscall 
	#
	jr $ra
	
	#li e move são instruções virtuais 
