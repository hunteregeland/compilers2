

# -----------------------
# function declarations

addValue:

	add $t0, $a1, $a2         # add the two values into $t0
	sw $t0, addValueresult      # store the sum into target variable

	lw $t0, addValueresult   # load the value of the first variable into $t0
	sw $t0, addValueReturn   # store the value of the first variable into the second

	jr $ra       # return to main

endloop:

	jal next       # return to main

