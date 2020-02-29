# Mapa de registos
# n: $a0 -> $s0
# b: $a1 -> $s1
# s: $a2 -> $s2
# p: $s3
# digit: $t0
# Sub-rotina intermédia

itoa: 	subu $sp,$sp,24 # reserva espaço na stack
	sw $ra,($sp)
 	sw $s0,4($sp) # guarda registos $sx e $ra
 	sw $s1,8($sp)
 	sw $s2,12($sp)
 	sw $s3,16($sp)
 	sw $s4,20($sp)
 	
 	
 	move $s0,$a2 # copia n, b e s para registos
 	move $s1,$a0 # "callee-saved"
 	move $s2,$a1
 	move $s3,$a2 # p = s;
 	
 	
do: # do {
 	rem $s3,$s1,$s2 #
 	div $s1,$s1,$s2
 	
 	b?? $s0,... # } while(n > 0);
 	sb $0,0($s3) # *p = 0;
 	(...) #
 	jal strrev # strrev( s );
 	(...) # return s;
 	lw $s0,... # repõe registos $sx e $ra
 	(...)
 	addu $sp,... # liberta espaço na stack
 	jr $ra #