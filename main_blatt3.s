	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 15, 2
	.globl	_scalar_product                 ; -- Begin function scalar_product
	.p2align	2
_scalar_product:                        ; @scalar_product
	.cfi_startproc
; %bb.0:
	cmp	w3, #2
	b.eq	LBB0_4
; %bb.1:
	cmp	w3, #1
	b.eq	LBB0_5
; %bb.2:
	cbnz	w3, LBB0_6
; %bb.3:
	b	_scalar_standard
LBB0_4:
	b	_scalar_sorted
LBB0_5:
	b	_scalar_kahan
LBB0_6:
	stp	x29, x30, [sp, #-16]!           ; 16-byte Folded Spill
	mov	x29, sp
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
Lloh0:
	adrp	x0, l_str@PAGE
Lloh1:
	add	x0, x0, l_str@PAGEOFF
	bl	_puts
	movi	d0, #0000000000000000
	ldp	x29, x30, [sp], #16             ; 16-byte Folded Reload
	ret
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__literal16,16byte_literals
	.p2align	4, 0x0                          ; -- Begin function main
lCPI1_0:
	.quad	0x3ff0000000000000              ; double 1
	.quad	0x4000000000000000              ; double 2
lCPI1_1:
	.quad	0x4008000000000000              ; double 3
	.quad	0x4010000000000000              ; double 4
lCPI1_2:
	.quad	0x4014000000000000              ; double 5
	.quad	0x4010000000000000              ; double 4
lCPI1_3:
	.quad	0x4008000000000000              ; double 3
	.quad	0x4000000000000000              ; double 2
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #144
	stp	x20, x19, [sp, #112]            ; 16-byte Folded Spill
	stp	x29, x30, [sp, #128]            ; 16-byte Folded Spill
	add	x29, sp, #128
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
Lloh2:
	adrp	x8, ___stack_chk_guard@GOTPAGE
Lloh3:
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
Lloh4:
	ldr	x8, [x8]
	stur	x8, [x29, #-24]
Lloh5:
	adrp	x8, lCPI1_0@PAGE
Lloh6:
	ldr	q0, [x8, lCPI1_0@PAGEOFF]
Lloh7:
	adrp	x8, lCPI1_1@PAGE
Lloh8:
	ldr	q1, [x8, lCPI1_1@PAGEOFF]
	stp	q0, q1, [sp, #64]
	mov	x8, #4617315517961601024        ; =0x4014000000000000
	str	x8, [sp, #96]
Lloh9:
	adrp	x8, lCPI1_2@PAGE
Lloh10:
	ldr	q0, [x8, lCPI1_2@PAGEOFF]
Lloh11:
	adrp	x8, lCPI1_3@PAGE
Lloh12:
	ldr	q1, [x8, lCPI1_3@PAGEOFF]
	stp	q0, q1, [sp, #16]
	mov	x8, #4607182418800017408        ; =0x3ff0000000000000
	str	x8, [sp, #48]
	add	x0, sp, #64
	add	x1, sp, #16
	mov	w2, #5                          ; =0x5
	bl	_scalar_standard
	str	d0, [sp, #8]
	str	xzr, [sp]
Lloh13:
	adrp	x19, l_.str.1@PAGE
Lloh14:
	add	x19, x19, l_.str.1@PAGEOFF
	mov	x0, x19
	bl	_printf
	add	x0, sp, #64
	add	x1, sp, #16
	mov	w2, #5                          ; =0x5
	bl	_scalar_kahan
	str	d0, [sp, #8]
	mov	w8, #1                          ; =0x1
	str	x8, [sp]
	mov	x0, x19
	bl	_printf
	add	x0, sp, #64
	add	x1, sp, #16
	mov	w2, #5                          ; =0x5
	bl	_scalar_sorted
	str	d0, [sp, #8]
	mov	w8, #2                          ; =0x2
	str	x8, [sp]
	mov	x0, x19
	bl	_printf
	ldur	x8, [x29, #-24]
Lloh15:
	adrp	x9, ___stack_chk_guard@GOTPAGE
Lloh16:
	ldr	x9, [x9, ___stack_chk_guard@GOTPAGEOFF]
Lloh17:
	ldr	x9, [x9]
	cmp	x9, x8
	b.ne	LBB1_2
; %bb.1:
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #128]            ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #112]            ; 16-byte Folded Reload
	add	sp, sp, #144
	ret
LBB1_2:
	bl	___stack_chk_fail
	.loh AdrpLdrGotLdr	Lloh15, Lloh16, Lloh17
	.loh AdrpAdd	Lloh13, Lloh14
	.loh AdrpLdr	Lloh11, Lloh12
	.loh AdrpAdrp	Lloh9, Lloh11
	.loh AdrpLdr	Lloh9, Lloh10
	.loh AdrpLdr	Lloh7, Lloh8
	.loh AdrpAdrp	Lloh5, Lloh7
	.loh AdrpLdr	Lloh5, Lloh6
	.loh AdrpLdrGotLdr	Lloh2, Lloh3, Lloh4
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str.1:                               ; @.str.1
	.asciz	"Methode %d: Skalarprodukt = %.6f\n"

l_str:                                  ; @str
	.asciz	"Ung\303\274ltige Methode! Bitte 0, 1 oder 2 w\303\244hlen."

.subsections_via_symbols
