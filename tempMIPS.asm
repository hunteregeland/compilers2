
.text
main:
# -----------------------

	la $a0, 20      # store value in $a0
	la $t0, Gx      # load variable address into $t0
	sw $a0, 0($t0)  # move value from $a0 into .word variable

	lw $a1, Gx         # load x into $a1 as a parameter

	li $a2, -5         # load -5 into $a2 as a parameter

	jal addValue       # goto function: addValue

	lw $t0, addValueReturn     # load the value of the first variable into $t0
	sw $t0, Gresult   # store the value of the first variable into the second

	li $v0, 4       # call code to print an string
	la $a0, TEMP0   # print stored string from above
	syscall

	lw $t0, Gresult       # load the value of result into $t0

	li $v0, 1       # call code to print an integer
	move $a0, $t0   # move the value of result into $a0
	syscall         # system call to print integer

	# -----------------------
	#  done, terminate program.

	li $v0, 10      # call code to terminate program
	syscall         # system call (terminate)
	.end main
