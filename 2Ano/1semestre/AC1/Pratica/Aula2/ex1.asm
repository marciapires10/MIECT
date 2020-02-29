	.data
	.text
	.globl main
	
main: 	ori $t0, $0, 5
	ori $t1, $0, 8
	and $t2, $t0, $t1
	or $t3, $t0, $t1
	nor $t3, $t0, $t1
	xor $t4, $t0, $t1