imap \Ga α
imap \alpha α
imap \beta β
imap \Gp π
imap \pi π
imap \Gk κ
imap \kappa κ
imap \Gs σ
imap \sigma σ
imap \times ×
imap \x ×
imap \to →
imap \-> →
imap \_1 ₁
imap \_2 ₂
imap \_3 ₃
imap \_4 ₄
imap \forall ∀
imap \all ∀
imap \exists ∃
imap \ex ∃
imap \imp ⇒
imap \=> ⇒
imap \iff ⇔
imap \land ∧
imap \and ∧
imap \lor ∨
imap \or ∨
imap \notin ∉
imap \in ∈
imap \a á
imap \e é
imap \i í
imap \noteq ≠
imap \le ≤
imap \<= ≤
imap \ge ≥
imap \>= ≥
imap \cap ∩
imap \cup ∪
imap \equiv ≡
imap \=== ≡
imap \bN ℕ
imap \bZ ℤ
imap \langle ⟨
imap \< ⟨
imap \rangle ⟩
imap \> ⟩
imap \. •
imap \bu •
imap \o ◦
imap \circ ◦
imap \emptyset ∅
imap \0 ∅
imap \subseteq ⊆
imap \not ¬
if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif
set iskeyword+=?,=,&,#,<,>
syn keyword tadADT ArregloDimensionable Bool Cola ColaDePrioridad Conjunto Diccionario Famoso Fila Multiconjunto Nat Persona Pila Secuencia String ÁrbolBinario
hi tadADT cterm=bold,underline ctermfg=2
syn keyword tadSort ab ad bool cola colaPrior conj dicc fila multiconj nat persona pila secu string α κ σ
hi tadSort ctermfg=2
syn keyword tadKeyword <=> =obs ES Fin TAD axiomas basicos else exporta fi formales generadores generos if igualdad observacional observadores operaciones otras parametros then usa ⇒ ⇒L ⇔ ∀ ∃ ∧ ∧L ∨ ∨L
hi tadKeyword cterm=bold
syn keyword tadConstructor  •  Ag abrirVentanilla apilar atender bin colarseAdelanteDe crearArreglo definir encolar false llegar nil retirarse suc true vacía vacío zero ∅ ⟨ ⟨⟩ ⟩
hi tadConstructor ctermfg=4
syn keyword tadEliminator =0? def? der desapilar desencolar esperando fin izq nil? obtener posicion pred prim próximo raíz seColó? tam tope vacía? π₁ π₂ π₃ π₄ ∊
hi tadEliminator ctermfg=1
syn keyword tadOtherOperations  ◦  # & altura borrar claves com dameUno esHoja? está inorder long longitud máx mín postorder preorder sinUno tamaño vacía últ ∅? ⊆
hi tadOtherOperations ctermfg=5
hi tadVariable cterm=italic
syn region tadComment start="--" end="$" keepend
hi tadComment cterm=italic ctermfg=6
syn sync minlines=200
syn sync maxlines=500
