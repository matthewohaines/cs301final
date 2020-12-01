loop: add $1, $2, $3
			sub $4, $5, $1
			addi $6, $4, 148
			slt $7, $8, $6
			lw $2, -4($10)
			sw $6, 4($10)
			beq $7, $11, loop
			j end

beq	$1, $2, 0x200
beq	$1, $2, 0x1e00
j	0x40000c
add	$3, $4, $8
addi	$2, $1, 100
sub	$2, $3, $9
slt	$1, $2, $10
slt	$1, $2, $3
lw	$1, 12($27)
sw      $17, 8($26)

add	$3, $4, $8
sub	$2, $3, $9
label1: addi	$2, $1, 100
slt	$1, $2, $10
lw	$1, 12($27)
sw  $17, 8($26)
beq	$1, $2, 0x40004c   # at address 0x40004c
j	0x400054

beq	$1, $2, label1
#lw $12, 700($4)

end: addi $17, $18, 4

# need to check branches to address before it and
# negative imm values ex. -700($2) needs to be two's
# compliment
