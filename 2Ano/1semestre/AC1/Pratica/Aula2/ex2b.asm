	.data
	.text
	.globl main
	
main: 	li $t0, 0x12345678
	
	sll $t2, $t0, 16
	srl $t3, $t0, 16
	sra $t4, $t0, 16
	jr $ra
	