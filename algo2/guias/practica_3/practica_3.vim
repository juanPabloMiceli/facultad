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
syn keyword tadADT ArregloDimensionable Bool Cola ColaAcotada ColaDePrioridad Conjunto Diccionario Famoso Multiconjunto Nat Pila Secuencia String ÁrbolBinario
hi tadADT cterm=bold,underline ctermfg=2
syn keyword tadSort ab ad bool cacotada cola colaPrior conj dicc multiconj nat pila secu string α κ σ
hi tadSort ctermfg=2
syn keyword tadKeyword <=> =obs ES Fin TAD abstracción axiomas basicos de else exporta fi formales función generadores generos if igualdad invariante observacional observadores operaciones otras parametros representación then usa ⇒ ⇒L ⇔ ∀ ∃ ∧ ∧L ∨ ∨L
hi tadKeyword cterm=bold
syn keyword tadConstructor  •  Ag apilar bin crearArreglo definir encolar false nil suc true vacia vacía vacío zero ∅ ⟨ ⟨⟩ ⟩
hi tadConstructor ctermfg=4
syn keyword tadEliminator =0? capacidad def? der desapilar desencolar fin izq nil? obtener pred prim próximo raíz tam tope vacía? verCola π₁ π₂ π₃ π₄ ∊
hi tadEliminator ctermfg=1
syn keyword tadOtherOperations  ◦  # & altura borrar claves com dameUno esHoja? está inorder long máx mín postorder preorder sinUno tamaño últ ∅? ⊆
hi tadOtherOperations ctermfg=5
hi tadVariable cterm=italic
syn region tadComment start="--" end="$" keepend
hi tadComment cterm=italic ctermfg=6
syn sync minlines=200
syn sync maxlines=500
