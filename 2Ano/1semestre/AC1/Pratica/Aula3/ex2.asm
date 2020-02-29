						# Mapa de registos:
						#  $t0 � value
						#  $t1 � bit
						#  $t2 - i

	.data
str1:	.asciiz "Introduza um numero: " 
str2: 	.asciiz "\nO valor em bin�rio e': "

	.eqv print_char, 11
	.eqv print_string, 4
	.eqv read_int, 5

	.text
	.globl main
main:	la $a0, str1			
	li $v0, print_string 		# (instru��o virtual)
	syscall				# print_string(str1);
	
	ori $v0, $0, read_int		# value=read_int();
	syscall
	or $t0, $v0, $0
	
	la $a0, str2			# print_string("\nO valor em bin�rio e': ");
	li $v0, print_string
	syscall
	
	li $t2, 0			# i=0
	
for: 	bge $t2, 32, endfor		# while( i < 32) {

	rem $t3, $t2, 4			# if((i % 4) == 0) // resto da divis�o inteira 
	bne $t3, $0, endSep
	ori $v0, $0, print_char		# print_char(' ');
	ori $a0, $0, 0x20
	syscall
endSep:					# end of character separation
	
	andi $t1, $t0 ,0x80000000	#    bit = value & 0x80000000;  // isola bit 31 
	
	beq $t1, $0, else		#   if (bit != 0)
	ori $v0, $0, print_char		#       print_char('1');
	ori $a0, $0, 0x31
	syscall
	
	j endif
	
else: 					#   else
	ori $v0, $0, print_char		#       print_char('0');
	ori $a0, $0, 0x30	
	syscall	

endif:	
	sll $t0, $t0, 1			#   value = value << 1;	     // shift left de 1 bit
	
	addi $t2, $t2, 1		#   i++;
	
	j for				# }
	
endfor:
	
	jr $ra				# fim do programa
	

						# void main(void)
						# {
						#     unsigned int value, bit, i;
						#     print_string("Introduza um numero: ");
						#     value = read_int();
						#     print_string("\nO valor em bin�rio e': ");
						#     for(i=0; i < 32; i++)
						#     {
						# 	  bit = value & 0x80000000;  // isola bit 31 
						#	  if(bit != 0)
						# 	      print_char('1');
						# 	  else
						# 	      print_char('0');
						# 	  value = value << 1;	     // shift left de 1 bit
						#     } 
						# }