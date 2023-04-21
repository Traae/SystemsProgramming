@
@ Created by Michael McGregor on 10/25/19.
@


.text
.align 2
.global my_strcat
.global my_strncat
.global my_strchr
.global my_strrchr
.global my_strcmp
.global my_strncmp
.global my_strcpy
.global my_strncpy
.global my_strdup
.global my_strndup
.global my_strlen
.global my_strstr

.func my_strcat
my_strcat:
    @ Temporary - simply return back to caller without taking any action
    bx      lr
.endfunc

.func my_strncat
my_strncat:
    @ Temporary - simply return back to caller without taking any action
    bx      lr
.endfunc

@ Modified pointer passed in before returning to test program. Modify this to implement.
.func my_strchr
my_strchr:
	push	{fp, lr}
	add	fp, sp, #4

	add	r0, r0, #2
	sub	sp, fp, #4
	pop	{fp, pc}
@    bx      lr
.endfunc

.func my_strrchr
my_strrchr:
    @ Temporary - simply return back to caller without taking any action
    bx      lr
.endfunc

.func my_strcmp
my_strcmp:
    @ Temporary - simply return back to caller without taking any action
    bx      lr
.endfunc

.func my_strncmp
my_strncmp:
    @ Temporary - simply return back to caller without taking any action
    bx      lr
.endfunc

.func my_strcpy
my_strcpy:
    @ Temporary - simply return back to caller without taking any action
    bx      lr
.endfunc

.func my_strncpy
my_strncpy:
    @ Temporary - simply return back to caller without taking any action
    bx      lr
.endfunc

.func my_strdup
my_strdup:
    mov     r0, #0 @ Return NULL or strdup() will segfault. Remove before flight.
    bx      lr
.endfunc

.func my_strndup
my_strndup:
    mov     r0, #0 @ Return NULL or strdup() will segfault. Remove before flight.
    bx      lr
.endfunc

@ This function is implemented by Michael McGregor as an example implementation.
@ It should work without issues.
@ Feel free to use this as an example for the other functions
.func my_strlen
my_strlen:
	push	{fp, lr}
	add	fp, sp, #4

	sub	sp, sp, #8 @ fp-8, fp-12

	str	r0, [fp, #-8] @ char *s saved in stack
	mov	r0, #0
	str	r0, [fp, #-12] @ int retval = 0;

	@ while(s[retval] != 0) retval++;
	while_begin:
		ldr	r0, [fp, #-8]
		ldr	r1, [fp, #-12]
		add	r0, r0, r1
		ldrb	r0, [r0]
		cmp	r0, #0
		beq	while_end

		@ iterate retval
		ldr	r0, [fp, #-12]
		add	r0, r0, #1
		str	r0, [fp, #-12]
		b	while_begin
		
	while_end:
	ldr	r0, [fp, #-12]

	sub	sp, fp, #4
	pop	{fp, pc}
.endfunc

.func my_strstr
my_strstr:
    @ Temporary - simply return back to caller without taking any action
    bx      lr
.endfunc
