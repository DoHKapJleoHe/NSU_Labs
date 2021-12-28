razlojenie(unsigned long long):
push {r4, r5, r6, r7, r8, r9, r10, r11, lr}
sub sp, sp, #4
mov r5, r0
orrs r0, r0, r1
beq .LBB0_4
mov r4, r1
mov r6, #0
mov r7, #0
mov r9, #0
mov r10, #0
.LBB0_2: @ =>This Inner Loop Header:
Depth=1
mov r0, r6
mov r1, r7
bl __aeabi_ul2d
mov r3, r1
mov r1, #267386880
mov r2, r0
mov r0, #0
orr r1, r1, #-1342177280
bl pow
mov r11, r0
mov r0, #1
mov r8, r1
lsl r1, r7, #1
orr r0, r0, r6, lsl #1
orr r1, r1, r6, lsr #31
bl __aeabi_ul2d
mov r2, r0
mov r3, r1
mov r0, r11
mov r1, r8
bl __aeabi_ddiv
mov r2, r0
mov r3, r1
mov r0, r9
mov r1, r10
bl __aeabi_dadd
adds r6, r6, #1
mov r9, r0
mov r10, r1
adc r7, r7, #0
subs r5, r5, #1
sbc r4, r4, #0
orrs r0, r5, r4
bne .LBB0_2
mov r3, #1048576
mov r0, r9
mov r1, r10
mov r2, #0
orr r3, r3, #1073741824
bl __aeabi_dmul
add sp, sp, #4
pop {r4, r5, r6, r7, r8, r9, r10, r11, lr}
bx lr
.LBB0_4:
mov r0, #0
mov r1, #0
add sp, sp, #4
pop {r4, r5, r6, r7, r8, r9, r10, r11, lr}
bx lr
main:
push {r4, r5, r6, r7, r8, r9, r10, r11, lr}
sub sp, sp, #20
mov r4, r1 // копируем значение из r1 в r4
add r1, sp, #12
mov r0, #4
bl clock_gettime
ldr r6, [r4, #4]
mov r0, r6
bl strlen
cmp r0, #1 // для for. i сравнивается с 1
blt .LBB1_8
mov r5, r0
ldrb r0, [r6] // в r0 положил значение из стека, т.е. в r6
лежит argv
sub r0, r0, #48 // вычитание 48
bl __aeabi_i2d
sub r9, r5, #1
mov r6, r0
mov r7, r1
mov r0, r9
bl __aeabi_i2d
mov r3, r1
mov r1, #2359296
mov r2, r0
mov r0, #0
orr r1, r1, #1073741824
bl pow
mov r2, r0
mov r3, r1
mov r0, r6
mov r1, r7
bl __aeabi_dmul
mov r2, #0
mov r3, #0
bl __aeabi_dadd
bl __aeabi_d2ulz
mov r6, r0
mov r7, r1
cmp r9, #0
beq .LBB1_4
sub r5, r5, #2
mov r10, #1
str r4, [sp] @ 4-byte Spill
.LBB1_3: @ =>This Inner Loop Header:
Depth=1
ldr r0, [r4, #4]
ldrb r0, [r0, r10]
sub r0, r0, #48
bl __aeabi_i2d
mov r4, r0
mov r0, r5
mov r11, r1
bl __aeabi_i2d
mov r3, r1
mov r1, #2359296
mov r2, r0
mov r0, #0
orr r1, r1, #1073741824
bl pow
mov r8, r0
mov r9, r1
mov r0, r6
mov r1, r7
bl __aeabi_ul2d
mov r6, r0
mov r0, r4
ldr r4, [sp] @ 4-byte Reload
mov r7, r1
mov r1, r11
mov r2, r8
mov r3, r9
bl __aeabi_dmul
mov r2, r6
mov r3, r7
bl __aeabi_dadd
bl __aeabi_d2ulz
sub r5, r5, #1
mov r6, r0
mov r7, r1
add r10, r10, #1
cmn r5, #1
bne .LBB1_3
.LBB1_4:
orrs r0, r6, r7
beq .LBB1_9
mov r4, #0
mov r5, #0
mov r9, #0
mov r10, #0
.LBB1_6: @ =>This Inner Loop Header:
Depth=1
mov r0, r4
mov r1, r5
bl __aeabi_ul2d
mov r3, r1
mov r1, #267386880
mov r2, r0
mov r0, #0
orr r1, r1, #-1342177280
bl pow
mov r11, r0
mov r0, #1
mov r8, r1
lsl r1, r5, #1
orr r0, r0, r4, lsl #1
orr r1, r1, r4, lsr #31
bl __aeabi_ul2d
mov r2, r0
mov r3, r1
mov r0, r11
mov r1, r8
bl __aeabi_ddiv
mov r2, r0
mov r3, r1
mov r0, r9
mov r1, r10
bl __aeabi_dadd
adds r4, r4, #1
mov r9, r0
mov r10, r1
adc r5, r5, #0
subs r6, r6, #1
sbc r7, r7, #0
orrs r0, r6, r7
bne .LBB1_6
mov r3, #1048576
mov r0, r9
mov r1, r10
mov r2, #0
orr r3, r3, #1073741824
bl __aeabi_dmul
mov r2, r0
mov r3, r1
b .LBB1_10
.LBB1_8:
mov r2, #0
mov r3, #0
b .LBB1_10
.LBB1_9:
mov r3, #0
mov r2, #0
.LBB1_10:
ldr r0, .LCPI1_0
bl printf
add r1, sp, #4
mov r0, #4
bl clock_gettime
ldr r0, [sp, #12]
ldmib sp, {r1, r7}
ldr r6, [sp, #16]
sub r0, r1, r0
bl __aeabi_i2d
mov r4, r0
sub r0, r7, r6
mov r5, r1
bl __aeabi_i2d
ldr r2, .LCPI1_1
ldr r3, .LCPI1_2
bl __aeabi_dmul
mov r2, r4
mov r3, r5
bl __aeabi_dadd
mov r2, r0
ldr r0, .LCPI1_3
mov r3, r1
bl printf
mov r0, #0
add sp, sp, #20
pop {r4, r5, r6, r7, r8, r9, r10, r11, lr}
bx lr
.LCPI1_0:
.long .L.str
.LCPI1_1:
.long 3894859413 @ 0xe826d695
.LCPI1_2:
.long 1041313291 @ 0x3e112e0b
.LCPI1_3:
.long .L.str.1
.L.str:
.asciz "%f\n"
.L.str.1:
.asciz "Time taken: %lf sec.\n"
