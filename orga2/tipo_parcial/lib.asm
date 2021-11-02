section .text

global azar
azar:
	mov rdi, [rsp]
	and rdi, 0x1
	cmp di, 0x7f
	jl .true
	jge .false


  .true:
  	mov eax, 1
  	jmp .end
  .false:
  	mov eax, 0

  	ret
