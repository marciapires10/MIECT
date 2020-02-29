# Mapa de registos
# aux: $t3
# houve_troca: $t4
# i: $t5
# lista: $t6
# lista + i: $t7

 	.data
 	.eqv FALSE,0
 	.eqv TRUE,1
 	.eqv SIZE,10
 	
 	.text
 	.globl main
 	
lista: .word 4, 2
 	
 	
main: 	(...) 	# código para leitura de valores
 	la $t6,lista #
 	
 	
do: 		# do {
 	li $t4,FALSE # houve_troca = FALSE;
 	li $t5,0 # i = 0;
 	
 
while: 	bge $t5, 9, endw # while(i < SIZE-1){
	
	
if: 	sll $t7,$t5,4 	# $t7 = i * 4
 	addu $t7,$t7,$t6	# $t7 = &lista[i]
 	lw $t8,0($t7) # $t8 = lista[i]
 	lw $t9,4($t7) # $t9 = lista[i+1]
 	ble $t8,$t9,endif # if(lista[i] > lista[i+1]){
 	sw $t8,4($t7) # lista[i+1] = $t8
 	sw $t9,0($t7) # lista[i] = $t9
 	li $t4,TRUE #
 	# }
 	
 	
endif: 	addi $t5, $t5, 1 # i++;
 	j while # }
 	beq $t4, TRUE, do # } while(houve_troca == TRUE);
 	#(...) # codigo de impressao do
	# conteudo do array
	
	
endw: 	jr $ra # termina o programa