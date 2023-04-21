.text
prompt1:	.asciz	"Please input a string to be parsed\n"
prompt2:	.asciz	"Please input a char to use as the delimiter\n"
scan_char:	.asciz	"%c"
.align 2

@ struct string_array		@ base address
@	int num_of_elements;	@ +0
@	char** array_of_strings;@ +4

.global main
.func main
main:
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8	@ fp-8 = str*, fp-12 = char

	mov	r0, #1024
	bl	malloc
	str	r0, [fp, #-8]

	ldr	r0, =prompt1
	bl	printf

	mov	r0, #0
	ldr	r1, [fp, #-8]
	mov	r2, #1024
	bl	read

	ldr	r0, =prompt2
	bl	printf

	ldr	r0, =scan_char
	add	r1, fp, #-12
	bl	scanf

	ldr	r0, [fp, #-8]
	ldrb	r1, [fp, #-12]
	bl	tokenize

	ldr	r0, [fp, #-8]
	bl	free

	sub	sp, fp, #4
	pop	{fp, pc}
.endfunc

@ struct string_array tokenize(char* str, char token)
.global	tokenize
@ "This is a test string"
@ "This", "is", "a", "test", "string"
debug1:	.asciz	"\"%s\" - \'%c\'"
debug2:	.asciz	"\"%s\"\n"
.align 2
.func	tokenize
tokenize:
	push	{fp, lr}
	add	fp, sp, #4

	@ fp-8 = str
	@ fp-12 = token
	@ fp-16 = curr_ptr
	@ fp-20 = string_count
	@ fp-24 = struct *string_array
	@ fp-28	= int i
	sub	sp, sp, #24
	str	r0, [fp, #-8]  @ str
	strb	r1, [fp, #-12] @ token
	str	r0, [fp, #-16] @ curr_ptr = str	
	mov	r0, #1
	str	r0, [fp, #-20]

	mov	r0, #8
	bl	malloc
	str	r0, [fp, #-24]


	@ while (str[i] != \0)
	@   if str[i] == token then count++
	
tokenize_while1_comp:
	ldr	r0, [fp, #-16]
	ldrb	r0, [r0]
	mov	r1, #0
	cmp	r0, r1
	beq	tokenize_while1_end

@ tokenize_while1_exec:
	@ if (str[i] == token)
	ldr	r0, [fp, #-16]
	ldrb	r0, [r0]
	ldrb	r1, [fp, #-12]
	cmp	r0, r1
	bne	tokenize_while1_exec_if_end
	
	@ I found a delimiter
	ldr	r0, [fp, #-20]
	add	r0, r0, #1
	str	r0, [fp, #-20]	@ count
tokenize_while1_exec_if_end:
	@ increment
	ldr	r0, [fp, #-16]
	add	r0, r0, #1
	str	r0, [fp, #-16]
	b	tokenize_while1_comp
tokenize_while1_end:
	ldr	r0, [fp, #-8]
	str	r0, [fp, #-16]	@ Reset curr_ptr = str

	@ Now we have number of strings, setup array
	ldr	r0, [fp, #-24]
	add	r0, r0, #0 	@ offset of num_of_elements
	ldr	r1, [fp, #-20]
	str	r1, [r0]

	push	{r0}
	mul	r0, r1, #4
	bl	malloc
	mov	r1, r0
	pop	{r0}

	add	r0, r0, #4
	str	r1, [r0]

	@ count is stored in struct
	@ array is setup with base address stored in struct+4

	mov	r0, #0
	str	r0, [fp, #-28]	@ i = 0
	@ while (str[i] != \0)
	
tokenize_while2_comp:
	ldr	r0, [fp, #-16]
	ldrb	r0, [r0]
	mov	r1, #0
	cmp	r0, r1
	beq	tokenize_while2_end

@ tokenize_while2_exec:
	@ if (str[i] == token)
	ldr	r0, [fp, #-16]
	ldrb	r0, [r0]
	ldrb	r1, [fp, #-12]
	cmp	r0, r1
	bne	tokenize_while2_exec_if_end
	
	@ I found a delimiter
	ldr	r0, [fp, #-16]
	mov	r1, #0
	strb	r1, [r0]	@ Replace delimiter with NUL
@@	add	r0, r0, #1
@@	str	r0, [fp, #-16]
	
	@ Lets store the string into the array
	ldr	r0, [fp, #-24]	@ struct
	add	r0, r0, #4	@ address in struct of array ptr
	ldr	r0, [r0]	@ ptr to array
	ldr	r1, [fp, #-28]	@ i
	mul	r1, r1, #4
	add	r0, r0, r1	@ base address + i*4

	ldr	r1, [fp, #-8]	@ addr of begin of str
	str	r1, [r0]	@ str_array[i] = str;

	@ increment i
	ldr	r0, [fp, #-28]
	add	r0, r0, #1
	str	r0, [fp, #-28]
	@ reset str
	ldr	r0, [fp, #-16]
	add	r0, r0, #1
	str	r0, [fp, #-8]
	

tokenize_while2_exec_if_end:
	@ increment
	ldr	r0, [fp, #-16]
	add	r0, r0, #1
	str	r0, [fp, #-16]
	b	tokenize_while2_comp
tokenize_while2_end:

@	mov	r2, r1
@	mov	r1, r0
@	ldr	r0, =debug1
@	bl	printf
	ldr	r0, =debug2
	ldr	r1, [fp, #-8]
	bl	printf

	sub	sp, fp, #4
	pop	{fp, pc}
.endfunc
