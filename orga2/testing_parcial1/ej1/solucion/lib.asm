
section .data
	float_print_format: DB "%f", 0
	string_print_format: DB "%s", 0
	string_vacio: DB "NULL", 0
	tree_open_key: DB "(", 0
	tree_close_key: DB ")->", 0




section .text

global floatCmp
global floatClone
global floatDelete
global floatPrint

global strClone
global strLen
global strCmp
global strDelete
global strPrint

global docClone
global docDelete

global listAdd

global treeInsert
global treePrint

;*** Float ***

;int32_t floatCmp(float* a, float* b);
;float* a => RDI
;float* b => RSI
;retornar => EAX
;FLAGS:
;ZF => CERO
;SF	=> SIGNO
;PF	=> PARIDAD
;OF	=> OVERFLOW
;CF => CARRY
 floatCmp:
;No armamos stackframe porque no usamos la pila
	xor rax, rax
	movss xmm0, [rdi]
	comiss xmm0, [rsi]

	jb .a_menor_b
	jz .end
	jg .a_mayor_b
  	
  .a_mayor_b:
  	mov eax, -1
  	jmp .end
  .a_menor_b:
  	mov eax, 1

  .end:
	ret

extern malloc
;float* floatClone(float* a)
;float* a => RDI, la direccion a donde está el float a clonar
;return   => RAX


;Malloc pide en RDI la cantidad de bytes a asignar
floatClone:;ALINEAR LA PILA Y LO QUE HAY EN REGISTROS SE PIERDE
	push rbp
	mov rbp, rsp
	push rbx
	push r12

	mov rbx, rdi		;en rbx tengo la direccion a donde está el float a clonar
	mov rdi, 4
	call malloc		;Despues de esto en RAX, tengo un puntero a la dir asignada

	mov r9d, [rbx]
	mov [rax], r9d

	pop r12
	pop rbx
	pop rbp
	ret

;void floatDelete(float* a)
;float* a => RDI
extern free
floatDelete:
	push rbp
	mov rbp, rsp
	call free
	
	pop rbp
	ret

;void floatPrint(float* a, FILE *pFile);
;float* a 		=> RDI. Osea que en RDI tengo la posicion del float a (32bits)
;FILE* pFile	=> RSI. Osea que en RSI tengo la posicion de la info del archivo.


extern fprintf
;fprintf(pFile, "%i", *a);
;pFile 		=> RDI
;"%f", 0 	=> RSI
;*a(float)	=> xmm0	
floatPrint: 
	push rbp
	mov rbp, rsp

	movss xmm1, [rdi]
	cvtps2pd xmm0, xmm1 
	mov rdi, rsi
	mov rsi, float_print_format
	mov rax, 1

	call fprintf

	pop rbp
	ret





;*** String ***

;char* strClone(char* a);
;char* a   => RDI
;ret char* => RAX

;malloc
;RDI => cantidad de bytes a asignar
;retorna en RAX => dir asignada


strClone:
	push rbp
	mov rbp, rsp
	push r12
	push r13

	mov r13, rdi	;Guardamos en r13 para no perder el valor de rdi
			
	
	call strLen 	;en RAX tengo el largo de a-1
	inc rax
	mov r12, r13	;En R12 tengo la dir de a
	mov r13, rax	;En R13 tengo el largo de a, va a servir de contador
	mov rdi, rax
	call malloc		;Tengo en RAX la dir de clone

	xor rcx, rcx
  .ciclo:
  	mov r8b, [r12+rcx]
  	mov [rax+rcx], r8b

	inc rcx
	cmp r13, rcx

	jnz .ciclo


	pop r13
	pop r12
	pop rbp
	ret


;uint32_t strLen(char* a);
;char* a => RDI
;ret     => EAX (importante limpiarlo)
;"Hola" , 0
;72, 101, 108, 97, 0
;48, 6F,  ,6C, 61, 0
strLen:
	xor rax, rax
	dec rax
  .ciclo:
  	inc rax
  	cmp BYTE [rdi+rax], 0

  	jnz .ciclo
	ret

;int32_t strCmp(char* a, char* b)
;char *a => RDI
;char *b => RSI
;ret 	 => RAX
;a<b 	 => 1
;a==b	 => 0
;a>b	 => -1

strCmp:
	push rbp
	mov rbp, rsp

	xor rcx, rcx
	xor rax, rax

  .ciclo:
  	mov r8b, [rdi+rcx]	;Guardamos la letra de A
  	cmp BYTE r8b, [rsi+rcx]; Comparamos
  	jg  .mayor
  	jl  .menor
  	cmp r8b, 0			;Termino A
  	jz  .listo_a
  	cmp BYTE [rsi+rcx], 0	;Termino B
  	jz .mayor
  	inc rcx
  	jmp .ciclo

  .listo_a:
  	cmp BYTE [rsi+rcx], 0	
  	jz 	.end						;Tambien termino b
  	jmp .menor

  .mayor:
  	mov eax, -1
  	jmp .end

  .menor:
  	mov eax, 1
  	jmp .end

  .end:
	pop rbp
	ret


strDelete:
	push rbp
	mov rbp, rsp
	call free
	
	pop rbp
	ret


;void strPrint(char* a, FILE *pFile);
;char* a 		=> RDI. Osea que en RDI tengo la posicion del texto.
;FILE* pFile	=> RSI. Osea que en RSI tengo la posicion de la info del archivo.


;fprintf(pFile, "%s", *a);
;pFile 		=> RDI
;"%s", 0 	=> RSI
;char* a	=> RDX
;cant xmm	=> 	RAX (0)


;fprintf(pFile, "NULL");
;pFile 		=> RDI
;"NULL", 0 	=> RSI
;cant xmm	=> 	RAX (0)

strPrint:
	push rbp
	mov rbp, rsp
	push r12
	push r13
	mov r12, rdi
	mov r13, rsi

	call strLen
	mov rdi, r13					;Guardamos en RDI la dir al archivo

	cmp rax, 0
	jz 	.null
	jmp .not_null
  
  .null:
  	mov rsi, string_vacio
  	jmp .f_call

  .not_null:
	mov rdx, r12					;rdx tiene la dir al texto
	mov rsi, string_print_format

  .f_call:
	xor rax, rax
	call fprintf

	pop r13
	pop r12
	pop rbp
	ret

;*** Document ***
%define off_count 	0
%define off_values	8
%define doc_size	16
%define off_type	0
%define off_elem 	8
%define box_size 	16
%define void_size	8



;document_t* docClone(document_t* a);
;document_t* a	=> RDI	Direccion al documento a copiar
;return 		=> RAX	Direccion dada por malloc

;1) Pedir espacio para la raiz (16bytes) GUARDAR COMO ORO LA DIR
;2) Averiguar cuantos elementos tenemos
;3) Pedir espacio para todos las cajitas. (16bytes * #elems)
;4) LLenar size y dir a primer cajita
;5)Loopear las cajitas e ir:
;	1) Asignando el tipo de dato en type (offset 0)
;	2) Clonando el valor correspondiente (llamar a C)

;Dir primer cajita 0x6309520
extern getCloneFunction
docClone:
	push rbp
	mov rbp, rsp
	push r12
	push r13
	push r14
	push r15

	mov r13, rdi				;Guardamos en R13 la dir del doc original
	mov rdi, doc_size			;Pasamos a RDI la cantidad de bytes a pedir
	call malloc					;RAX la dir de la raiz (retorno)
	mov r12, rax				;IMPORTANTE NO TOCAR, es el valor de retorno


	xor r14, r14				;Limpiamos R14
	mov r14d, [r13+off_count]	;Guardamos en R14 la cantidad de cajitas
	mov edi, r14d				;Pasamos a RDI la cantidad de cajitas
	imul rdi, box_size			;Conseguimos en R9 la #bytes a pedir
	call malloc					;RAX la dir de la primer cajita a crear

	
	mov [r12+off_count],  r14d	;Copiamos la cantidad de cajitas en el doc nuevo
	mov [r12+off_values], rax	;Copiamos la dir a la primer cajita nueva

	xor r15, r15				;Limpiamos r15 para usarlo de contador
  
  .ciclo:
  	xor rdi, rdi				;Limpiamos RDI
  	mov rdi, [r13+off_values]	;RDI es la dir de la primer cajita original

  .guardar_tipo:
  	mov rsi, box_size			;Movemos box_size a RSI
  	imul rsi, r15				;Ahora en RSI está el desplazamiento cajil(R15*box_size)

  	lea rdi, [rdi + rsi]		;En RDI, tenemos la dir de la cajita i original	
  	xor r9, r9					;Limpiamos R9
  	mov r9d, [rdi+off_type]		;Guardamos en R9D el tipo de dato de la caja i original

  	xor r8,  r8					;Limpiamos R8
  	mov r8,  [r12+off_values]	;R8 es la dir de la primer cajita nueva

  	lea r8,  [r8 + rsi]			;R8 es la dir de la cajita i nueva
  	mov [r8+off_type], r9d		;Guardamos en la cajita el valor del tipo

  .guardar_cosas:
  	push rsi					;Guardamos desplazamiento cajil
  	push r8						;Guardamos dir cajita i nueva
  	push rdi					;Guardamos dir cajita i original
  	push rbx					;Alinea la pila

  .guardar_dato:
  	mov rdi, r9					;Pasamos a RDI el tipo de dato 
  	call getCloneFunction		;En RAX tenemos la dir de la funcion para clonar

  .recuperar_cosas_1:
  	pop rbx						;Alineo pila
  	pop rdi						;Recupero dir cajita i original

  	mov rdi, [rdi+off_elem]		;En RDI tenemos la dir del elemento i
  	call rax					;Conseguimos la dir del dato clonado en RAX

  .recuperar_cosas_2:
  	pop r8						;Recupero dir cajita i nueva
  	pop rsi						;(Alineo la pila creo)

  	mov [r8+off_elem], rax		;Guardamos la dir del dato clonado en la cajita	

  	inc r15						;Incrementamos contador
  	cmp r15, r14				;Comparamos con END
  	jnz .ciclo					;Volvemos si hace falta

  .end:
  	mov rax, r12				;Guardamos dir de doc nuevo en el retorno

  	pop r15
  	pop r14
	pop r13
	pop r12
	pop rbp
	ret


;1)Agarrarnos la dir a primer cajita y guardarla en la pila
;2)Agarrarnos la cantidad de cajitas
;3)Hacer el free de raiz
;4)Loopear caijtas
;	1) Hacer el free del puntero del dato
;5)Hacer el free de la cajita entera
;void docDelete(document_t* a);
;document_t* a	=> RDI
docDelete:
	push rbp
	mov rbp, rsp
	push r12		
	push r13
	push r14
	push r15						;Alinea la pila

	mov r12d, [rdi + off_count]		;En R12 tenemos la cantidad de cajitas
	mov r13, [rdi + off_values]		;En r13 tenemos la dir a la primer cajita

	call free						;Aca liberamos la raiz

	xor r14, r14					;R14 es el contador

  .ciclo:
  	mov rsi, box_size				;Movemos box_size a RSI
  	imul rsi, r14					;Ahora en RSI está el desplazamiento cajil(R14*box_size)

  	lea rdi, [r13 + rsi + off_elem]	;En RDI, tenemos la dir del puntero al elem a borrar	
  	mov rdi, [rdi]
  	call free						;Liberamos puntero

  	inc r14							;Incrementamos contador
  	cmp r14d, r12d					;Comparamos contador con cantidad de cajitas
  	jnz .ciclo						;Seguimos ciclando si hace falta


  	mov rdi, r13					;Movemos a RDI la direccion de la primer cajita
  	call free


	pop r15
	pop r14
	pop r13
	pop r12
	pop rbp
	ret

;*** List ***
%define off_type    0
%define off_size    4
%define off_first   8
%define off_last    16
%define list_size   24

%define off_data    0
%define off_next   	8
%define off_prev   	16
%define box_size	24


;void listAdd(list_t* l, void* data);
;list_t* l		=> RDI
;void* data		=> RSI


;1)Guardar punteros a raiz y data en la pila
;2)Pedir memoria para la cajita nueva
;2b) Pedir dir a la funcion de comparacion
;3)Guardar puntero a data en la cajita
;4)Guardar puntero a cajita en algun lado
;5)Loopear caijtas
;	1) Comparar (Requiere guardar datos)
;	2) Cuando llegamos:
; 	3a)Si es principio:
;   	1)Prev del siguiente sea 0
;   	2)first sea Next de current
;   	3)liberar current
; 	3b)Si es medio:
;   	1)Next del anterior apunte a Next de current
;   	2)Prev del siguiente apunte a Prev de current
;   	3)Liberar current
; 	3c)Si es fin:
;   	1)Next del anterior sea 0
;   	2)last sea prev de current
;   	3)liberar current
; 4)Aumentar size

extern getCompareFunction
listAdd:
	push rbp
	mov rbp, rsp
	sub rsp, 8					;[RSP-8] alinea la pila
	push r12					;En R12 vamos a guardar la dir a la raiz
	push r13					;En R13 vamos a guardar la dir a la data
	push r14					;R14 va a ser la cantidad de cajitas
	push r15					;R15 va a ser el contador
	push rbx					;En RBX vamos a tener la dir a la funcion


	mov r12, rdi				;Guardamos la direccion a la raiz
	mov r13, rsi				;Guardamos la direccion a la data

	mov rdi, box_size			;Le pido a malloc 24bytes
	call malloc					;En RAX tengo la dir a la caja nueva

	mov [rax+off_data], r13		;Guardo la data en la cajita nueva
	mov r13, rax				;Guardo en R13 la dir a la cajita nueva

	mov edi, [r12 + off_type]	;Guardo en RDI el tipo
	call getCompareFunction		;En RAX tenemos la dir a cmpFunc

	mov rbx, rax				;En RBX tengo la dir a la funcion

	mov r14, [r12+off_first]	;Movemos a R14 la dir a la primer cajita

	mov rdi, [r12]				;Conseguimos el size y type de la lista
  	sar rdi, 32					;Nos quedamos solo el size
  	cmp rdi, 0
  	jz .insertar_unico

  .ciclo:
  	
  	mov rdi, [r13]				;En RDI tenemos la data de la cajita nueva
  	mov rsi, [r14]				;En RSI tenemos la data de la cajita i
  	call rbx					;Comparamos data nueva con data cajita i
  	;Si RAX == -1:
  	;	Cajita nueva > Cajita i (salir)
  	;Si RAX == 0:
  	;	Cajita nueva = Cajita i (salir)
  	;Si RAX == 1:
  	;	Cajita nueva < Cajita i
  	cmp eax, 0					;Chequeamos si cajita nueva es menor a cajita i
  	jge .end_ciclo				;Si es mayor o igual terminamos el ciclo

  	cmp QWORD [r14+off_next], 0	;Chequeamos si existe next
  	jz .insertar_final			;Si no existe insertamos al final

  	mov r14, [r14+off_next]		;Avanzamos a la proxima cajita
  	jnz .ciclo					;Ciclamos de nuevo

  .end_ciclo:
  	cmp QWORD [r14+off_prev], 0	;Chequeamos si existe Prev
  	jz .insertar_primero		;Si no existe insertamos al principio

 .insertar_medio:
 	mov [r13+off_next], r14		;Next de la cajita nueva es la cajita con la que salimos del ciclo
 	mov rdi, [r14+off_prev]		;Nos guardamos el anterior a la nueva cajita
 	mov [r13+off_prev], rdi		;Prev de la cajita nueva es la cajita anterior
 	mov [rdi+off_next], r13		;Next de la cajita anterior es la cajita nueva
 	mov [r14+off_prev], r13		;Prev de la cajita siguiente es la cajita nueva

  	jmp .end

  .insertar_primero:
  	mov QWORD [r13+off_prev], 0	;Prev de la nueva cajita es 0
  	mov [r13+off_next], r14		;Next de la nueva cajita es la que antes era la Primer cajita
  	mov [r14+off_prev], r13		;Prev de la primer cajita vieja, ahora es la nueva cajita
  	mov [r12+off_first], r13	;First de la raiz es la cajita nueva
  	jmp .end


  .insertar_final:
  	mov QWORD [r13+off_next], 0	;Next de la nueva cajita es 0
  	mov [r13+off_prev], r14		;Prev de la nueva cajita es la que antes era la ultima cajita
  	mov [r14+off_next], r13		;Next de la ultima cajita vieja, ahora es la nueva cajita
  	mov [r12+off_last], r13		;Last de la raiz es la cajita nueva
  	jmp .end

  .insertar_unico:
  	mov QWORD [r13+off_next], 0	;Next de la nueva cajita es 0
  	mov QWORD [r13+off_prev], 0	;Prev de la nueva cajita es 0
  	mov [r12+off_first], r13	;First de la raiz es la nueva cajita
  	mov [r12+off_last], r13		;Last de la raiz es la nueva cajita
  	jmp .end



  .end:
  	inc dword [r12+off_size] 

	pop rbx
	pop r15
	pop r14
	pop r13
	pop r12

	add rsp, 8

	pop rbp
	ret

;*** Tree ***
%define off_first       0
%define off_size        8
%define off_typeKey     12
%define off_duplicate   16
%define off_typeData    20
%define s_tree_size     24

%define off_key         0
%define off_values      8   
%define off_left        16
%define off_right       24
%define s_treeNode_size 32


%define data_clone_func  [RBP-8]
%define key_clone_func  [RBP-16]
%define key_cmp_func    [RBP-24]

;int treeInsert(tree_t* tree, void* key, void* data);
;tree_t* tree 	=> RDI
;void*	 key	=> RSI
;void*	 data	=> RDX
;Ret			=> RAX

;1)Guardar todo
;2)Llamar a malloc para pedir una cajita(guardar direccion)
;3)Llamar a findCmp y guardar la direccion.
;4)Si first == 0:
;	4a)first = dir cajita
;	4b)left y right = 0
;	4c)Guardar key en la cajita
;	4d)Crear una lista vacia
;	4e)Saltar a insert
;5)Si first != 0:
;6)Empieza el ciclo
;7)Si clave nueva == clave iesima:
;	7a)Si duplicate == 0  => RETURN 0
;	7b)Si duplicate != 0
;		6b.1)Saltar a insert
;8)Si clave nueva < clave iesima:
;	8a)Si left == 0:
;		8a.1)Generar
;	8b)Movemos la cajita actual a izq
;
;9)Si clave nueva > clave
;	9a)Si right == 0:
;		9a.1)Generar
;	9b)Movemos la cajita actual a der

extern listNew
treeInsert:
	push rbp
	mov rbp, rsp
	sub rsp, 40
	push r12
	push r13
	push r14
	push r15					
	push rdx

	mov r12, rdi					;En r12 guardamos dir a raiz
	mov r13, rsi					;En r13 guardamos dir a key a insertar
	mov r14, rdx					;En r14 guardamos dir a data a insertar

	mov edi, [r12 + off_typeData]	;Movemos a rdi el tipo de dato de la data.
	call getCloneFunction			;Conseguimos cloneFunc para la data
	mov [rbp - 8], rax				;Guardo en [rbp-8] la funcion para clonar data
	mov edi, [r12 + off_typeKey]	;Movemos a rdi el tipo de dato de la key.
	call getCloneFunction			;Conseguimos cloneFunc para la key
	mov [rbp - 16], rax				;Guardo en [rbp-16] la funcion para clonar key
	mov edi, [r12 + off_typeKey]	;Movemos a rdi el tipo de dato de la key.
	call getCompareFunction			;Conseguimos CmpFunc para la key
	mov [rbp - 24], rax				;Guardo en [rbp-24] la funcion para comparar keys




	cmp dword [r12 + off_size], 0	;Chequeamos si hay nodos en la lista
	jz .generar_first				;Si no hay insertamos el primero

	mov r15, [r12 + off_first]		;Movemos a r15 la dir a la primer cajita

  .ciclo:

    mov rdi, r13					;En RDI tenemos la key a insertar
  	mov rsi, [r15]					;En RSI tenemos la key de la caja actual
  	call key_cmp_func				;Comparamos las keys
  	;Si EAX == -1:
  	;	Cajita nueva > Cajita i (der)
  	;Si EAX == 0:
  	;	Cajita nueva = Cajita i (ver que hacer)
  	;Si EAX == 1:
  	;	Cajita nueva < Cajita i	(izq)

  	cmp eax, 0						;Chequeamos si la key nueva es menor,mayor o igual

  	jl .es_mayor					;La key nueva es mayor
  	jg .es_menor					;La key nueva es menor
	je .es_igual					;La key nueva es igual

  .es_mayor:
  	cmp qword [r15 + off_right], 0	;Vemos si existe right
  	jz .generar_right				;Si no existe lo insertamos a derecha
  	mov r15, [r15 + off_right]		;Movemos la cajita actual a la derecha
  	jmp .ciclo

  .es_menor:
  	cmp qword [r15 + off_left], 0	;Vemos si existe left
  	jz .generar_left				;Si no existe lo insertamos a izquierda
  	mov r15, [r15 + off_left]		;Movemos la cajita actual a la izquierda
  	jmp .ciclo


  .es_igual:
  	xor rax, rax					;Seteamos rax en cero por si ya lo devolvemos
  	cmp dword [r12+off_duplicate], 0;Chequeamos si hay duplicados o no
  	jz .end							;Terminamos la funcion devvolviendo cero

	mov rdi, r14					;Guardamos en rdi la dir a la data a clonar
	call data_clone_func			;Clonamos la data

	mov rdi, [r15 + off_values]		;Movemos a rdi la dir a la lista de la cajita
	mov rsi, rax					;Movemos a rsi la dir a la data clonada
	call listAdd					;Agregamos data a la lista
	mov rax, 1
	jmp .end
									
  .generar_first:
  	lea r15, [r12 + off_first]		;En R15 tengo la dir del first
  	jmp .generar
  	
  .generar_left:
  	lea r15, [r15 + off_left]		;En R15 tengo la dir del first
  	jmp .generar

  .generar_right:
  	lea r15, [r15 + off_right]		;En R15 tengo la dir de right
  	jmp .generar

  .generar:
 	call generar_e_insertar			;Al llamarla en R15 esta la dir del padre
 	mov rax, 1						;Devolvemos 1 porque pudimos insertar
 	jmp .end


  .end:
	pop rdx
	pop r15
	pop r14
	pop r13
	pop r12
	add rsp, 40
	pop rbp
	ret



;generar_e_insertar:
;1)Pedir memoria
;2)Left y Right = 0
;3)Conectar el padre
;4)Clonar Key y guardarla
;5)Crear lista vacia
;6)Clonar valor a insertar
;7)ListAdd de la direccion y la data clonada


;En r12 guardamos dir a  raiz
;En r13 guardamos dir a   key
;En r14 guardamos dir a  data
;En r15 guardamos dir a padre
;En [RBP -  8] tenemos la funcion para clonar la data
;En [RBP - 16] tenemos la funcion para clonar la  key

generar_e_insertar:
	
	mov rdi, s_treeNode_size		;Pasamos a RDI la cantidad de memoria a pedir
	call malloc						;Tenemos en RAX la dir a la memoria nueva

	mov qword [rax + off_left], 0	;Seteamos Left en 0
	mov qword [rax + off_right], 0	;Seteamos Right en 0

	mov [r15], rax					;Conectamos el padre a la cajita nueva

	mov rdi, r13					;Pasamos a rdi la dir a la key a clonar
	call key_clone_func				;Clonamos la key

	mov rdi, [r15]					;En rdi tenemos la dir a la cajita nueva
	mov [rdi + off_key], rax		;Guardamos en la cajita nueva la key clonada

	mov edi, [r12 + off_typeData]	;Movemos a rdi el tipo de la data
	call listNew					;Creamos una lista con el tipo de la data, tenemos la dir en RAX

	mov rdi, [r15]					;En rdi tenemos la dir a la cajita nueva
	mov [rdi + off_values], rax		;Guardamos la lista nueva en la cajita nueva

	mov rdi, r14					;Guardamos en rdi la dir a la data a clonar
	call data_clone_func			;Clonamos la data

	mov rdi, [r15]					;En rdi tenemos la dir a la cajita nueva
	mov rdi, [rdi + off_values]		;Movemos a rdi la dir a la lista creada
	mov rsi, rax					;Movemos a rsi la dir a la data clonada
	call listAdd

	inc DWORD [r12 + off_size]		;Incrementamos el size
	ret


;void treePrint(tree_t* tree, FILE *pFile)
;tree_t* tree => RDI
;FILE * pfile => RSI

%define print_func r14


extern getPrintFunction
extern listPrint
treePrint:
	push rbp
	mov rbp, rsp
	push r14
	push r15

	mov r14, rdi					;Guardamos en r14 la dir del arbol
	mov r15, rsi					;Guardamos en r15 la dir del archivo

	mov edi, [rdi + off_typeKey]	;Guardamos en rdi el tipo de la key
	call getPrintFunction

	mov rdi, r14					;Devolvemos al lugar la dir del arbol
	mov rsi, r15					;Devolvemos al lugar la dir del archivo
	mov r14, rax 					;Pasamos a r14 la dir de printf_func

	cmp dword [rdi + off_size], 0	;Chequeamos si hay nodos en la lista
	jz .end							;Si no hay, no imprimimos nada

	mov rdi, [rdi + off_first]		;Si hay, movemos a rdi el primer nodo
	call treePrintNode 				;Llamamos a la funcion recursiva

  .end:
  	pop r15
  	pop r14
	pop rbp
	ret


;void treePrintNode(treeNode_t* node, FILE *pFile)
;tree_t* node => RDI
;FILE * pfile => RSI

;fprintf(pFile, "%i", *a);
;pFile 		=> RDI
;"%f", 0 	=> RSI
;*a(float)	=> xmm0	
treePrintNode:
	push r12							;Necesitamos R12
	push r13							;Necesitamos R13
	push rbx							;Alineamos la pila que desalineo Ret

	mov r12, rdi						;Guardo la dir del nodo
	mov r13, rsi						;Guardo la dir del archivo

	cmp qword [rdi + off_left], 0		;Chequeamos que exista izquierda
	jz .imprimir_nodo					;Me tengo que imprimir a mi

	
  .imprimir_izquierda:
	mov rdi, [r12 + off_left]			;Guardo en rdi la dir del nodo izquierdo
	mov rsi, r13						;Guardo en rsi la dir del archivo
	call treePrintNode					;Imprimimos subarbol izquierdo

; tree_open_key: DB "(", 0
; tree_close_key: DB ")->", 0
  .imprimir_nodo:
  .abrir_key:	
  	mov rdi, r13						;Movemos a rdi la dir del archivo
  	mov rsi, tree_open_key 				;Movemos a rsi el texto a imprimir
  	xor rax, rax						;Seteamos rax en 0
  	call fprintf						;Imprimimos el primer parentesis
 
  .imprimir_key:
  	mov rdi, [r12 + off_key]			;Movemos a rdi la dir a la key
  	mov rsi, r13						;Movemos a rsi la dir al archivo
  	call print_func						;Imprimimos la key

  .cerrar_key:	
  	mov rdi, r13						;Movemos a rdi la dir del archivo
  	mov rsi, tree_close_key				;Movemos a rsi el texto a imprimir
  	xor rax, rax						;Seteamos rax en 0
  	call fprintf						;Imprimimos el parentesis de cierre

  .imprimir_lista:
  	mov rdi, [r12 + off_values]			;Guardo la dir de la lista en rdi
  	mov rsi, r13						;Guardo en rsi la dir del archivo
  	call listPrint						;Imprimimos la lista


  .imprimir_derecha:
	cmp qword [r12 + off_right], 0		;Chequeamos que exista derecha
	jz .end								;No hay nada mas que imprimir

  	mov rdi, [r12 + off_right]			;Guardo en rdi la dir del nodo derecho
  	mov rsi, r13						;Guardo la dir del archivo
  	call treePrintNode 					;Imprimimos subarbol derecho

  .end:
  	pop rbx								;Alineamos la pila que desalineo Ret
  	pop r13							
  	pop r12
	ret