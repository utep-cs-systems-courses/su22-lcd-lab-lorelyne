
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
	sub #2, r1.  ; stack
	mov #0, 0(r12) ;case#

	cmp #4, r12 ;r12 - 4 
	jhs end  ;jump to end if higher or equal to 4

	cmp #0, r12		;r12 - 0
	jl end ;jump to end if less than 0
	
	add r12, r12. ; get offset becuase each entry is 2 bytes
	mov jt(r12), r0. ;moves value we want to PC to be read

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
	add #2, r1   	;r1 stack pointer 
	pop r0		;pop stack 

	

	
