	.data
	.text
	.globl main
	
main: 	ori $t0, $0, 2
	srl $t1, $t0, 1
	xor $t2, $t0, $t1
	jr $ra