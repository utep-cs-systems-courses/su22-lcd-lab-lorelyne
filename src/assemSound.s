
	.arch	msp430g2553
	.p2align 1,0

	.text

jt:
	.word case0
	.word case1
	.word case2
	.word case3

	.global assemSound

assemSound:
	sub #2, r1
	mov #0, 0(r12)

	cmp #4, r12
	jhs end

	cmp #0, r12		;del
	jl end
	
	add r12, r12
	mov jt(r12), r0

case0:
	mov #400, 0(r1)
	mov 0(r1), r12
	call #buzzer_set_period

	jmp end
	
case1:
	mov #600, 0(r1)
	mov 0(r1), r12
	call #buzzer_set_period

	jmp end

case2:
	mov #700, 0(r1)
	mov 0(r1), r12
	call #buzzer_set_period

	jmp end

case3:
	mov #800, 0(r1)
	mov 0(r1), r12
	call #buzzer_set_period

	jmp end

	
end:
	/*
	r1 [*p(800)][][][]
	r1[0] -> r12 (*pointer(int 800))
	buzzer_set_period(r12)
	*/
	add #2, r1   	;r1 stack pointer 
	pop r0		;reset program counter 

	

	
