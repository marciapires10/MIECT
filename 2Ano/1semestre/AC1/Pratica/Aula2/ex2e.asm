	.data
	.text
	.globl main
	
main: 	ori $t0, $0, 3

	srl $t1, $t0, 4
	xor $t0, $t0, $t1 
	
	srl $t2, $t0, 2
	xor $t0, $t0, $t2
	
	srl $t3, $t0, 1
	xor $t0, $t0, $t3
	
	jr $ra  