razlojenie(unsigned long long):
push {r11, lr}
mov r11, sp
sub sp, sp, #32
str r1, [r11, #-4]
str r0, [r11, #-8]
mov r0, #0 // обнулили регистр
str r0, [sp, #20] // здесь лежит pi
str r0, [sp, #16] // здесь лежит pi
str r0, [sp, #12] // здесь лежит n
str r0, [sp, #8] // здесь лежит n
b .LBB0_1
.LBB0_1: @ =>This Inner Loop Header:
Depth=1
ldr r0, [r11, #-8]
ldr r1, [r11, #-4]
orr r0, r0, r1
cmp r0, #0 // это цикл while
beq .LBB0_3 // перейти, если равно
b .LBB0_2 // просто перейти
.LBB0_2: //тут находится тело цикла while @ in Loop: Header=BB0_1
Depth=1
ldr r2, [sp, #8] // выгружаем n
ldr r3, [sp, #12] // выгружаем n
mvn r0, #0
bl
_ZSt3powIiyEN9__gnu_cxx11__promote_2IT_T0_NS0_9__promoteIS2_Xsr3std12__is_
integerIS2_EE7__valueEE6__typeENS4_IS3_Xsr3std12__is_integerIS3_EE7__value
EE6__typeEE6__typeES2_S3_
str r0, [sp] @ 4-byte Spill
str r1, [sp, #4] @ 4-byte Spill
ldr r2, [sp, #8]
ldr r0, [sp, #12]
lsl r0, r0, #1
orr r1, r0, r2, lsr #31
mov r0, #1
orr r0, r0, r2, lsl #1
bl __aeabi_ul2d
mov r2, r0
ldr r0, [sp] @ 4-byte Reload
mov r3, r1
ldr r1, [sp, #4] @ 4-byte Reload
bl __aeabi_ddiv
mov r2, r0
mov r3, r1
ldr r0, [sp, #16]
ldr r1, [sp, #20]
bl __aeabi_dadd
str r1, [sp, #20]
str r0, [sp, #16]
// дальше выполняются доп. действия: прибавление 1, вычитание 1
ldr r1, [sp, #8]
ldr r0, [sp, #12]
adds r1, r1, #1
adc r0, r0, #0
str r1, [sp, #8]
str r0, [sp, #12]
ldr r1, [r11, #-8]
ldr r0, [r11, #-4]
subs r1, r1, #1 // отнимает 1, обновляет флаги, т.е. сразу
деалет проверку на равенство 1
sbc r0, r0, #0
str r1, [r11, #-8]
str r0, [r11, #-4]
b .LBB0_1
.LBB0_3:
ldr r0, [sp, #16]
ldr r1, [sp, #20]
mov r2, #0
mov r3, #1048576
orr r3, r3, #1073741824
bl __aeabi_dmul
str r1, [sp, #20]
str r0, [sp, #16]
ldr r0, [sp, #16]
ldr r1, [sp, #20]
mov sp, r11
pop {r11, lr}
bx lr
main:
push {r11, lr} // положить значения из l11(база кадра), lr в
стек
mov r11, sp // делаем вершину стека базой кадра
sub sp, sp, #104 // смещаем вершину стека на 104 байта вниз
mov r2, #0 // кладём в r2 0, т.е. обнуляем регистр (pi)
str r2, [sp, #44] //грузим значение r2 sp - 44
@4-byte Spill
str r2, [r11, #-4] // кладём значение в r11 - 4
str r0, [r11, #-8] // это argc
str r1, [r11, #-12] // Это argv
mov r0, #4 // грузим 4 в r0
sub r1, r11, #20 // r1 = r11 - 20
bl clock_gettime
ldr r0, [r11, #-12] // выгрузить значение из r0 в r11 - 12
ldr r0, [r0, #4]
bl strlen
mov r1, r0 // копировать значение r0 в r1
ldr r0, [sp, #44] @ 4-byte Reload
str r1, [r11, #-32] // length
str r0, [r11, #-36] // N
str r0, [r11, #-40]
str r0, [r11, #-44] // i итератор цикла for
b .LBB2_1 // тут по-идее начинается for
.LBB2_1: @ =>This Inner Loop Header:
Depth=1
ldr r0, [r11, #-44] // кладём в регистр значение из стека по
адресу
ldr r1, [r11, #-32]
cmp r0, r1
bge .LBB2_4
b .LBB2_2
.LBB2_2: @ in Loop: Header=BB2_1 Depth=1
ldr r0, [r11, #-12]
ldr r0, [r0, #4]
ldr r1, [r11, #-44]
str r1, [sp, #16] @ 4-byte Spill
ldrb r0, [r0, r1]
sub r0, r0, #48
bl __aeabi_i2d
mov r2, r0
ldr r0, [sp, #16] @ 4-byte Reload
str r2, [sp, #28] @ 4-byte Spill
str r1, [sp, #32] @ 4-byte Spill
ldr r1, [r11, #-32] //
mvn r0, r0
add r1, r0, r1
mov r0, #10
bl
_ZSt3powIiiEN9__gnu_cxx11__promote_2IT_T0_NS0_9__promoteIS2_Xsr3std12__is_
integerIS2_EE7__valueEE6__typeENS4_IS3_Xsr3std12__is_integerIS3_EE7__value
EE6__typeEE6__typeES2_S3_
str r0, [sp, #20] @ 4-byte Spill
str r1, [sp, #24] @ 4-byte Spill
ldr r0, [r11, #-40]
ldr r1, [r11, #-36]
bl __aeabi_ul2d
ldr r2, [sp, #20] @ 4-byte Reload
ldr r3, [sp, #24] @ 4-byte Reload
mov r12, r0
ldr r0, [sp, #28] @ 4-byte Reload
str r12, [sp, #36] @ 4-byte Spill
mov r12, r1
ldr r1, [sp, #32] @ 4-byte Reload
str r12, [sp, #40] @ 4-byte Spill
bl __aeabi_dmul
ldr r2, [sp, #36] @ 4-byte Reload
ldr r3, [sp, #40] @ 4-byte Reload
bl __aeabi_dadd
bl __aeabi_d2ulz
str r1, [r11, #-36]
str r0, [r11, #-40]
b .LBB2_3
.LBB2_3: @ in Loop: Header=BB2_1 Depth=1
ldr r0, [r11, #-44]
add r0, r0, #1
str r0, [r11, #-44]
b .LBB2_1
.LBB2_4:
ldr r0, [r11, #-40] // это по-идее тоже аргумент для функции
ldr r1, [r11, #-36] // аргумент для функции разложения
bl razlojenie(unsigned long long) // вызывается сама функция
str r1, [sp, #52] // сюда функция разложения вернёт значение
str r0, [sp, #48] // сюда по-идее тоже вернёт(зачем??? )
ldr r2, [sp, #48]
ldr r3, [sp, #52]
ldr r0, .LCPI2_0
bl printf
mov r0, #4
sub r1, r11, #28
bl clock_gettime
ldr r0, [r11, #-28]
ldr r1, [r11, #-24]
str r1, [sp] @ 4-byte Spill
ldr r1, [r11, #-20]
ldr r2, [r11, #-16]
str r2, [sp, #4] @ 4-byte Spill
sub r0, r0, r1
bl __aeabi_i2d
mov r2, r0
ldr r0, [sp] @ 4-byte Reload
str r2, [sp, #8] @ 4-byte Spill
mov r2, r1
ldr r1, [sp, #4] @ 4-byte Reload
str r2, [sp, #12] @ 4-byte Spill
sub r0, r0, r1
bl __aeabi_i2d
ldr r2, .LCPI2_1
ldr r3, .LCPI2_2
bl __aeabi_dmul
ldr r2, [sp, #8] @ 4-byte Reload
ldr r3, [sp, #12] @ 4-byte Reload
bl __aeabi_dadd
mov r2, r0
mov r3, r1
ldr r0, .LCPI2_3
bl printf
mov r0, #0
mov sp, r11
pop {r11, lr}
bx lr
.LCPI2_0:
.long .L.str
.LCPI2_1:
.long 3894859413 @ 0xe826d695
.LCPI2_2:
.long 1041313291 @ 0x3e112e0b
.LCPI2_3:
.long .L.str.1
.L.str:
.asciz "%f\n"
.L.str.1:
.asciz "Time taken: %lf sec.\n"
