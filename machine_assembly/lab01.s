				;		Daniel Shields, Christopher Boumalhab
				
				;##########################################
				;		Lab 01 Gnome Sort Skeleton
				;##########################################
				
data_to_sort		dcd		17, 80, 2, 3, 18, 54, 29, 11, 15, 40
list_elements		dcd		10
				
main
				ldr		r3, =data_to_sort   ; Load the starting address of the first
				;		of element of the array of numbers into r3
				ldr		r4, =list_elements  ; address of number of elements in the list
				ldr		r4, [r4]            ; number of elements in the list
				
				add		r5, r3, #400	 ; location of first element of linked list - "head pointer"
				;		(note that I assume it is at a "random" location
				;		beyond the end of the array.)
				;		mov		r6, r5	;address of curr starts at the head node
				;
				;
				;		mov		r1, #0 ; i = 0 loop counter
				;		mov		r9, #0 ; register to hold 0
				mov		r0, #0 ; i = 0
				mov		r7, #0 ; prev
				mov		r8, #0 ; next
				mov		r11, #0
				
				
				
				
				
				
				;#################################################################################
				;		Include any setup code here prior to the loop that will create the linked list
				;#################################################################################
				b		list_loop
				;#################################################################################
				;		Start a loop here to load elements in the array and add them to a linked list
				;#################################################################################
list_loop
				cmp		r0, r4
				beq		start_sorting
				lsl		r10, r0, #2 ; r10 = i * 4
				ldr		r9, [r3, r10] ;
				add		r8, r5, #32 ; curr -> next = &arr[i+1]
				bl		insert
				mov		r7, r5 ; prev is now equal to curr
				add		r5, r5, #32 ; curr = next
				add		r0, r0, #1 ; i++
				b		list_loop
				
				;#################################################################################
				;		Add insert, swap, delete functions here
				;#################################################################################
insert
				;		str		r8, [r6, #8] ; curr-> next = &new
				;		str		r7, [r8] ; load data from array[i] into newNode
				;		str		r6, [r8, #4] ; newNode -> prev = &curr
				;		str		r9, [r8, #8] ;
				;		mov		r15, r14 ; return PC to list_loop
				str		r9, [r5] ; store arr[i] into curr
				str		r7, [r5, #4] ; store
				sub		r12, r4, #1
				cmp		r0, r12
				beq		last_node
				str		r8, [r5, #8] ; store
				mov		r15, r14 ; return
				
last_node
				str		r11, [r5, #8]
				mov		r15, r14
				
				
				;#################################################################################
				;		This ends the program. You can branch to `done` or move this code as you'd like,
				;		BUT it is important this is executed (last) to end execution cleanly.
				;#################################################################################
start_sorting
				add		r5, r3, #400
				mov		r11, #0 ; just a register that holds 0
				mov		r0, #0 ; i = 0
				mov		r6, r5 ; r6 = &curr_node
				
				
while_loop
				cmp		r0, r4 ; r4 is the length of the list bruv, r0 is i
				bge		delete_dup
				ldr		r7, [r6] ; r7 = curr_node -> value
				ldr		r8, [r6, #4] ; r8 = & curr ->prev
				cmp		r0, r11
				beq		check_first_cond ; check the first condition
				ldr		r9, [r8] ; r9 = curr->prev
				cmp		r7, r9
				bge		check_first_cond ; check the first cond
				b		else_statement ;
				
check_first_cond
				;;		incrementing to next node in list
				add		r0, r0, #1 ; i++
				ldr		r6, [r6, #8] ; curr = curr->next
				b		while_loop
				
				
else_statement
				bl		swap
				sub		r0, r0, #1 ; pos--
				b		while_loop
				
swap
				
				ldr		r10, [r6, #8] ; r10 = &curr->next
				ldr		r12, [r8, #4] ; r12 = &arr[pos-1] -> prev
				str		r8, [r6, #8] ; curr.next = prev
				str		r6, [r8, #4] ; prev.prev = curr
				str		r12, [r6, #4] ; curr.prev = prev.prev
				str		r10, [r8, #8] ; prev.next = OG curr.next
				
				mov		r1, #1 ; value of pos = 1 for edge case
				mov		r2, #9 ; value of last element for edge case
				cmp		r0, r2
				bne		access_last
				cmp		r0, r1
				bne		access_first
				
				
access_last
				str		r8, [r10, #4] ; OG curr.next.prev = curr.prev
				cmp		r0, r1
				bne		access_first
				mov		r5, r6
				mov		r15, r14
				
access_first
				str		r6, [r12, #8] ; prev.prev.next = curr
				mov		r15, r14
				
delete_dup
				mov		r6, r5 ; r6 = &curr initialized to &head node
				mov		r0, #0 ; holds 0
				
while_not_null
				ldr		r7, [r6] ; r7 = curr->val
				ldr		r8, [r6, #8] ; r8 = &curr->next
				cmp		r8, r0
				beq		done
				ldr		r9, [r8] ; r9 = curr-> next -> val
				cmp		r7, r9
				bne		increment_node ; continue if not equal
				bl		delete
				b		while_not_null
				
increment_node
				mov		r6, r8 ; curr = curr->next
				b		while_not_null
				
delete
				ldr		r10, [r8, #8] ; r10 = curr->next->next
				str		r10, [r6, #8] ; curr->next = r10
				str		r6, [r10, #4] ; r10 -> prev = curr
				mov		r15, r14 ; return to that jawn
				
				
				
done
				end
				
				
