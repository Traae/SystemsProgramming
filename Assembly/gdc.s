.data

welcome: .asciz  "Let find the greatest common denominator!\n"
prompt1: .asciz  "Please enter your first integer: \n"
prompt2: .asciz "Please enter your second: \n"
input: .asciz "%d"
report: .asciz "The gdc is: %d. \n"
.align 2

.text
.align 2

.global main
.global gdc

.func main
main:
	push {fp, lr}
	add fp, sp, #4
	
	ldr r0, =welcome @ welcome message
	bl printf

	@ varibale space make
	sub sp, sp, #8
	@ fp - 8 = n1
	@ fp - 12 = n2
			
	ldr r0, =prompt1 @ first num, prompt and stomp
	bl printf
	ldr r0, =input
	sub r1, fp, #8
	bl scanf
				
	ldr r0, =prompt2   @ 2nd num
	bl printf
	ldr r0, =input
	sub r1, fp, #12
	bl scanf

	ldr r0, [fp, #-8]    @ set the values on r0, r1 for func call
	ldr r1, [fp, #-12]
	bl gdc

	mov r1, r0   @ report result
	ldr r0, =report
	bl printf

	sub sp, fp, #4
	pop {fp, pc}
.endfunc

@ greatest common denominator function. recurcive, returns result on r0
.func gdc
gdc:
	push {fp, lr}
	add fp, sp, #4

	mov r3, r0  @ make back ups for stuff
	mov r4, r1
	
	cmp r1, #0	@ if condition n2 !=0 
	beq else_false	   @ if: 
	bl __aeabi_idivmod  @ returns mod on r1
	mov r0, r4 	    @ set r0 to the old r1, saved in r4
	bl gdc		    @ pass n2 and n1%n2 back into function
	b skip_else
else_false:
	mov r0, r3  @ return this  n1, having been saved on r3 prior  
skip_else:
	sub sp, fp, #4
	pop {fp, pc}
.endfunc
