global docSimilar

section .text

; typedef struct s_docElem {
;   type_t type;				4 bytes 		pos 0
;   void* data;					8 bytes 		pos 8
; } docElem_t;					Ocupa 16 bytes

; typedef struct s_document {
;   int count;					4 bytes			pos 0
;   docElem_t* values;			8 bytes			pos 8
; } document_t;					Ocupa 16 bytes

%define off_type 	0
%define off_data 	8
%define elem_size	16

%define off_count 	0
%define off_values 	8
%define doc_size 	16





;int docSimilar(document_t* a, document_t* b, void* bitmap);
;document_t* a 	=> 	RDI
;document_t* b 	=> 	RSI
;void* bitmap 	=> 	RDX

extern getCompareFunction
docSimilar:
	push 	rbp
	mov 	rbp, rsp
	sub 	rsp, 8							;Alineo la pila
	push 	r12								;Voy a guardar en r12 la dir a doc uno
	push 	r13								;Voy a guardar en r13 la dir a doc dos
	push 	r14								;Voy a guardar en r14 la dir a bitmap
	push 	r15								;Voy a guardar en r15 el size del doc
	push 	rbx								;Voy a guardar en rbx el contador

	mov 	r12, rdi						;Guardo en r12 la dir a doc uno
	mov 	r13, rsi						;Guardo en r13 la dir a doc dos	
	mov 	r14, rdx						;Guardo en r14 la dir a bitmap

	lea 	rcx, [rdi + off_count]			;Ahora rcx tiene la direccion a la #elementos del documento uno
	lea 	r8,  [rsi + off_count]			;Ahora r8  tiene la direccion a la #elementos del documento dos

	mov 	rcx, [rcx]						;Levanto la #elementos del doc uno
	and 	rcx, 0xffff						;Limpio la basura que pudiera tener

	mov 	r8, [r8]						;Levanto la #elementos del doc dos
	and 	r8, 0xffff						;Limpio la basura que pudiera tener

	cmp 	rcx, r8							;Comparo los tamanios de los documentos
	jg 		.docUnoMayor					;Salto si doc uno tiene mas elementos
	jl 		.docDosMayor					;Salto si doc dos tiene mas elementos
	cmp 	rcx, 0							;Si son documentos vacios retorno
	jz 		.iguales						
	mov 	r15, rcx						;Guardo en r15 el tamanio de los docs (ya sabemos que son iguales)
	xor 	rbx, rbx						;Inicio contador en 0.


	lea 	r12, [r12 + off_values]			;Guardo en r12 la dir al puntero al primer elemento del doc uno
	lea 	r13, [r13 + off_values]			;Guardo en r13 la dir al puntero al primer elemento del doc dos
	
	mov 	r12, [r12]						;Levanto la dir a la primer cajita del doc uno en r12
	mov 	r13, [r13]						;Levanto la dir a la primer cajita del doc dos en r13

	.ciclo_tipos:
		mov 	rdi, rbx					;Muevo a rdi el contador
		mov 	rsi, [r14]					;Guardo en rsi el bitmap
		and 	rsi, 0xff					;Me quedo solo con el byte low
		call 	saltearCmp 					;Si devuelve cero en rax entonces hay que comparar
		cmp 	rax, 0						;Me fijo si hay que comparar o no
		jnz 	.noComparar

		mov 	r9, rbx						;Guardo el contador en r9
		imul 	r9, elem_size				;Tenemos en r9 el avance que tiene que hacer el puntero

		lea 	rdi, [r12 + r9]				;Ahora rdi apunta a la i-esima cajita
		add 	rdi, off_type				;Muevo rdi para que apunte al tipo del dato
		mov 	edi, [rdi]					;En rdi guardo el tipo de dato del doc1
		and 	rdi, 0xffff					;Limpio potencial basura del dato

		lea 	rsi, [r13 + r9]				;Ahora rsi apunta a la i-esima cajita
		add 	rsi, off_type				;Muevo rsi para que apunte al tipo del dato
		mov 	esi, [rsi]					;En rsi guardo el tipo de dato del doc2
		and 	rsi, 0xffff					;Limpio potencial basura del dato

		cmp 	rdi, rsi					;Comparo los tipos del doc1 vs doc2
		jg 		.docUnoMayor
		jl 		.docDosMayor			

		.noComparar:
		inc 	rbx							;Incremento el contador
		cmp 	rbx, r15					;Chequeo si termine
		jnz 	.ciclo_tipos				;Salto si hace falta


	xor 	rbx, rbx						;Reinicio el contador

	.ciclo_valores:
		mov 	rdi, rbx					;Muevo a rdi el contador
		mov 	sil, [r14]					;Guardo en rsi el bitmap
		and 	rsi, 0xff					;Me quedo solo con el byte low
		call 	saltearCmp 					;Si devuelve cero en rax entonces hay que comparar
		cmp 	rax, 0						;Me fijo si hay que comparar o no
		jnz 	._noComparar

		mov 	r9, rbx						;Guardo el contador en r9
		imul 	r9, elem_size				;Tenemos en r9 el avance que tiene que hacer el puntero

		lea 	rdi, [r12 + r9]				;Ahora rdi apunta a la i-esima cajita
		add 	rdi, off_type				;Muevo rdi para que apunte al tipo del dato
		mov 	edi, [rdi]

		call 	getCompareFunction			;Consigo en rax la dir a la funcion para comparar

		mov 	r9, rbx						;Guardo el contador en r9
		imul 	r9, elem_size				;Tenemos en r9 el avance que tiene que hacer el puntero

		lea 	rdi, [r12 + r9]				;Ahora rdi apunta a la i-esima cajita
		add 	rdi, off_data				;Muevo rdi para que apunte al puntero al dato
		mov 	rdi, [rdi]					;En rdi guardo el puntero al dato del doc1

		lea 	rsi, [r13 + r9]				;Ahora rsi apunta a la i-esima cajita
		add 	rsi, off_data				;Muevo rsi para que apunte al puntero al dato
		mov 	rsi, [rsi]					;En rsi guardo el puntero al dato del doc2

		call 	rax							;Llamo a la funcion de comparacion
											;Si doc1>doc2 => RAX = -1
											;Si doc1<doc2 => RAX =  1
											;Si doc1=doc2 => RAX =  0
		cmp 	eax, 0						;Comparo el resultado			
		jg 		.docDosMayor
		jl 		.docUnoMayor			

		._noComparar:
		inc 	rbx							;Incremento el contador
		cmp 	rbx, r15					;Chequeo si termine
		jnz 	.ciclo_valores				;Salto si hace falta


	.iguales:
	xor 	rax, rax 						;Seteamos rax en cero
	jmp 	.end							;Retornamos

	.docUnoMayor:
	mov 	rax, -1							;Seteamos rax en -1
	jmp 	.end							;Retornamos

	.docDosMayor:
	mov 	rax, 1							;Seteamos rax en 1 
	jmp 	.end							;Retornamos

	
	.end:
	pop 	rbx
	pop 	r15
	pop 	r14
	pop 	r13
	pop 	r12
	add 	rsp, 8
	pop 	rbp
  	ret





;int contador		=> 	RDI
;int8_t bitmap 		=> 	SIL
;Return 			=>	RAX
;Hay que saltear 	=> RAX=1
;No hay que saltear => RAX=0
;|0000|0000|0000|0000|0000|0000|0000|00cc|  => RDI
;|0000|0000|0000|0000|0000|0000|0000|bmap|  => RSI

saltearCmp:
	push 	rbp
	mov 	rbp, rsp
	.ciclo:
		cmp 	rdi, 0 						;Tengo que hacer el shift tantas veces como el numero del contador
		jz 		.end_ciclo					;Saltamos si hace falta
		shr 	rsi, 1						;Shifteo a derecha para limpiar los bits menos significativos que no me interesan
		dec 	rdi							;Decremento el contador
		jmp 	.ciclo						;Vuelvo al ciclo
	.end_ciclo:
	shl 	rsi, 63							;Shifteo a izquierda para limpiar los bits mas significativos que no me interesan
	cmp 	rsi, 0							;Comparo rsi con cero.
											;Si da cero entonces el bit estaba apagado y hay que saltear
	jz 		.hayQueSaltear
	xor 	rax, rax						;Limpio porque no habia que saltear
	jmp 	.end

	.hayQueSaltear:
	mov rax, 1								;Guardo el resultado

	.end: 	
	pop 	rbp
	ret
