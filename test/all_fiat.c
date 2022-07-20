// NOLINTBEGIN
/* curve description: curve25519 */
/* machine_wordsize = 64 (from "64") */
/* requested operations: carry_mul, carry_square */
/* n = 5 (from "5") */
/* s-c = 2^255 - [(1, 19)] (from "2^255 - 19") */
/* tight_bounds_multiplier = 1 (from "") */
/*  */
/* Computed values: */
/* carry_chain = [0, 1, 2, 3, 4, 0, 1] */
/* eval z = z[0] + (z[1] << 51) + (z[2] << 102) + (z[3] << 153) + (z[4] << 204)
 */
/* bytes_eval z = z[0] + (z[1] << 8) + (z[2] << 16) + (z[3] << 24) + (z[4] <<
 * 32) + (z[5] << 40) + (z[6] << 48) + (z[7] << 56) + (z[8] << 64) + (z[9] <<
 * 72) + (z[10] << 80) + (z[11] << 88) + (z[12] << 96) + (z[13] << 104) + (z[14]
 * << 112) + (z[15] << 120) + (z[16] << 128) + (z[17] << 136) + (z[18] << 144) +
 * (z[19] << 152) + (z[20] << 160) + (z[21] << 168) + (z[22] << 176) + (z[23] <<
 * 184) + (z[24] << 192) + (z[25] << 200) + (z[26] << 208) + (z[27] << 216) +
 * (z[28] << 224) + (z[29] << 232) + (z[30] << 240) + (z[31] << 248) */
/* balance = [0xfffffffffffda, 0xffffffffffffe, 0xffffffffffffe,
 * 0xffffffffffffe, 0xffffffffffffe] */

#include <stdint.h>
typedef unsigned char fiat_curve25519_uint1;
typedef signed char fiat_curve25519_int1;
typedef signed __int128 fiat_curve25519_int128;
typedef unsigned __int128 fiat_curve25519_uint128;

#if (-1 & 3) != 3
#error "This code only works on a two's complement system"
#endif

/*
 * The function fiat_curve25519_carry_mul multiplies two field elements and
 * reduces the result. Postconditions: eval out1 mod m = (eval arg1 * eval arg2)
 * mod m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0x18000000000000], [0x0 ~> 0x18000000000000], [0x0 ~>
 * 0x18000000000000], [0x0 ~> 0x18000000000000], [0x0 ~> 0x18000000000000]]
 *   arg2: [[0x0 ~> 0x18000000000000], [0x0 ~> 0x18000000000000], [0x0 ~>
 * 0x18000000000000], [0x0 ~> 0x18000000000000], [0x0 ~> 0x18000000000000]]
 * Output Bounds:
 *   out1: [[0x0 ~> 0x8000000000000], [0x0 ~> 0x8000000000000], [0x0 ~>
 * 0x8000000000000], [0x0 ~> 0x8000000000000], [0x0 ~> 0x8000000000000]]
 */
void fiat_curve25519_carry_mul(uint64_t out1[5], const uint64_t arg1[5],
                               const uint64_t arg2[5]) {
  fiat_curve25519_uint128 x1;
  fiat_curve25519_uint128 x2;
  fiat_curve25519_uint128 x3;
  fiat_curve25519_uint128 x4;
  fiat_curve25519_uint128 x5;
  fiat_curve25519_uint128 x6;
  fiat_curve25519_uint128 x7;
  fiat_curve25519_uint128 x8;
  fiat_curve25519_uint128 x9;
  fiat_curve25519_uint128 x10;
  fiat_curve25519_uint128 x11;
  fiat_curve25519_uint128 x12;
  fiat_curve25519_uint128 x13;
  fiat_curve25519_uint128 x14;
  fiat_curve25519_uint128 x15;
  fiat_curve25519_uint128 x16;
  fiat_curve25519_uint128 x17;
  fiat_curve25519_uint128 x18;
  fiat_curve25519_uint128 x19;
  fiat_curve25519_uint128 x20;
  fiat_curve25519_uint128 x21;
  fiat_curve25519_uint128 x22;
  fiat_curve25519_uint128 x23;
  fiat_curve25519_uint128 x24;
  fiat_curve25519_uint128 x25;
  fiat_curve25519_uint128 x26;
  uint64_t x27;
  uint64_t x28;
  fiat_curve25519_uint128 x29;
  fiat_curve25519_uint128 x30;
  fiat_curve25519_uint128 x31;
  fiat_curve25519_uint128 x32;
  fiat_curve25519_uint128 x33;
  uint64_t x34;
  uint64_t x35;
  fiat_curve25519_uint128 x36;
  uint64_t x37;
  uint64_t x38;
  fiat_curve25519_uint128 x39;
  uint64_t x40;
  uint64_t x41;
  fiat_curve25519_uint128 x42;
  uint64_t x43;
  uint64_t x44;
  uint64_t x45;
  uint64_t x46;
  uint64_t x47;
  uint64_t x48;
  uint64_t x49;
  fiat_curve25519_uint1 x50;
  uint64_t x51;
  uint64_t x52;
  x1 = ((fiat_curve25519_uint128)(arg1[4]) * ((arg2[4]) * UINT8_C(0x13)));
  x2 = ((fiat_curve25519_uint128)(arg1[4]) * ((arg2[3]) * UINT8_C(0x13)));
  x3 = ((fiat_curve25519_uint128)(arg1[4]) * ((arg2[2]) * UINT8_C(0x13)));
  x4 = ((fiat_curve25519_uint128)(arg1[4]) * ((arg2[1]) * UINT8_C(0x13)));
  x5 = ((fiat_curve25519_uint128)(arg1[3]) * ((arg2[4]) * UINT8_C(0x13)));
  x6 = ((fiat_curve25519_uint128)(arg1[3]) * ((arg2[3]) * UINT8_C(0x13)));
  x7 = ((fiat_curve25519_uint128)(arg1[3]) * ((arg2[2]) * UINT8_C(0x13)));
  x8 = ((fiat_curve25519_uint128)(arg1[2]) * ((arg2[4]) * UINT8_C(0x13)));
  x9 = ((fiat_curve25519_uint128)(arg1[2]) * ((arg2[3]) * UINT8_C(0x13)));
  x10 = ((fiat_curve25519_uint128)(arg1[1]) * ((arg2[4]) * UINT8_C(0x13)));
  x11 = ((fiat_curve25519_uint128)(arg1[4]) * (arg2[0]));
  x12 = ((fiat_curve25519_uint128)(arg1[3]) * (arg2[1]));
  x13 = ((fiat_curve25519_uint128)(arg1[3]) * (arg2[0]));
  x14 = ((fiat_curve25519_uint128)(arg1[2]) * (arg2[2]));
  x15 = ((fiat_curve25519_uint128)(arg1[2]) * (arg2[1]));
  x16 = ((fiat_curve25519_uint128)(arg1[2]) * (arg2[0]));
  x17 = ((fiat_curve25519_uint128)(arg1[1]) * (arg2[3]));
  x18 = ((fiat_curve25519_uint128)(arg1[1]) * (arg2[2]));
  x19 = ((fiat_curve25519_uint128)(arg1[1]) * (arg2[1]));
  x20 = ((fiat_curve25519_uint128)(arg1[1]) * (arg2[0]));
  x21 = ((fiat_curve25519_uint128)(arg1[0]) * (arg2[4]));
  x22 = ((fiat_curve25519_uint128)(arg1[0]) * (arg2[3]));
  x23 = ((fiat_curve25519_uint128)(arg1[0]) * (arg2[2]));
  x24 = ((fiat_curve25519_uint128)(arg1[0]) * (arg2[1]));
  x25 = ((fiat_curve25519_uint128)(arg1[0]) * (arg2[0]));
  x26 = (x25 + (x10 + (x9 + (x7 + x4))));
  x27 = (uint64_t)(x26 >> 51);
  x28 = (uint64_t)(x26 & UINT64_C(0x7ffffffffffff));
  x29 = (x21 + (x17 + (x14 + (x12 + x11))));
  x30 = (x22 + (x18 + (x15 + (x13 + x1))));
  x31 = (x23 + (x19 + (x16 + (x5 + x2))));
  x32 = (x24 + (x20 + (x8 + (x6 + x3))));
  x33 = (x27 + x32);
  x34 = (uint64_t)(x33 >> 51);
  x35 = (uint64_t)(x33 & UINT64_C(0x7ffffffffffff));
  x36 = (x34 + x31);
  x37 = (uint64_t)(x36 >> 51);
  x38 = (uint64_t)(x36 & UINT64_C(0x7ffffffffffff));
  x39 = (x37 + x30);
  x40 = (uint64_t)(x39 >> 51);
  x41 = (uint64_t)(x39 & UINT64_C(0x7ffffffffffff));
  x42 = (x40 + x29);
  x43 = (uint64_t)(x42 >> 51);
  x44 = (uint64_t)(x42 & UINT64_C(0x7ffffffffffff));
  x45 = (x43 * UINT8_C(0x13));
  x46 = (x28 + x45);
  x47 = (x46 >> 51);
  x48 = (x46 & UINT64_C(0x7ffffffffffff));
  x49 = (x47 + x35);
  x50 = (fiat_curve25519_uint1)(x49 >> 51);
  x51 = (x49 & UINT64_C(0x7ffffffffffff));
  x52 = (x50 + x38);
  out1[0] = x48;
  out1[1] = x51;
  out1[2] = x52;
  out1[3] = x41;
  out1[4] = x44;
}

/*
 * The function fiat_curve25519_carry_square squares a field element and reduces
 * the result. Postconditions: eval out1 mod m = (eval arg1 * eval arg1) mod m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0x18000000000000], [0x0 ~> 0x18000000000000], [0x0 ~>
 * 0x18000000000000], [0x0 ~> 0x18000000000000], [0x0 ~> 0x18000000000000]]
 * Output Bounds:
 *   out1: [[0x0 ~> 0x8000000000000], [0x0 ~> 0x8000000000000], [0x0 ~>
 * 0x8000000000000], [0x0 ~> 0x8000000000000], [0x0 ~> 0x8000000000000]]
 */
void fiat_curve25519_carry_square(uint64_t out1[5], const uint64_t arg1[5]) {
  uint64_t x1;
  uint64_t x2;
  uint64_t x3;
  uint64_t x4;
  uint64_t x5;
  uint64_t x6;
  uint64_t x7;
  uint64_t x8;
  fiat_curve25519_uint128 x9;
  fiat_curve25519_uint128 x10;
  fiat_curve25519_uint128 x11;
  fiat_curve25519_uint128 x12;
  fiat_curve25519_uint128 x13;
  fiat_curve25519_uint128 x14;
  fiat_curve25519_uint128 x15;
  fiat_curve25519_uint128 x16;
  fiat_curve25519_uint128 x17;
  fiat_curve25519_uint128 x18;
  fiat_curve25519_uint128 x19;
  fiat_curve25519_uint128 x20;
  fiat_curve25519_uint128 x21;
  fiat_curve25519_uint128 x22;
  fiat_curve25519_uint128 x23;
  fiat_curve25519_uint128 x24;
  uint64_t x25;
  uint64_t x26;
  fiat_curve25519_uint128 x27;
  fiat_curve25519_uint128 x28;
  fiat_curve25519_uint128 x29;
  fiat_curve25519_uint128 x30;
  fiat_curve25519_uint128 x31;
  uint64_t x32;
  uint64_t x33;
  fiat_curve25519_uint128 x34;
  uint64_t x35;
  uint64_t x36;
  fiat_curve25519_uint128 x37;
  uint64_t x38;
  uint64_t x39;
  fiat_curve25519_uint128 x40;
  uint64_t x41;
  uint64_t x42;
  uint64_t x43;
  uint64_t x44;
  uint64_t x45;
  uint64_t x46;
  uint64_t x47;
  fiat_curve25519_uint1 x48;
  uint64_t x49;
  uint64_t x50;
  x1 = ((arg1[4]) * UINT8_C(0x13));
  x2 = (x1 * 0x2);
  x3 = ((arg1[4]) * 0x2);
  x4 = ((arg1[3]) * UINT8_C(0x13));
  x5 = (x4 * 0x2);
  x6 = ((arg1[3]) * 0x2);
  x7 = ((arg1[2]) * 0x2);
  x8 = ((arg1[1]) * 0x2);
  x9 = ((fiat_curve25519_uint128)(arg1[4]) * x1);
  x10 = ((fiat_curve25519_uint128)(arg1[3]) * x2);
  x11 = ((fiat_curve25519_uint128)(arg1[3]) * x4);
  x12 = ((fiat_curve25519_uint128)(arg1[2]) * x2);
  x13 = ((fiat_curve25519_uint128)(arg1[2]) * x5);
  x14 = ((fiat_curve25519_uint128)(arg1[2]) * (arg1[2]));
  x15 = ((fiat_curve25519_uint128)(arg1[1]) * x2);
  x16 = ((fiat_curve25519_uint128)(arg1[1]) * x6);
  x17 = ((fiat_curve25519_uint128)(arg1[1]) * x7);
  x18 = ((fiat_curve25519_uint128)(arg1[1]) * (arg1[1]));
  x19 = ((fiat_curve25519_uint128)(arg1[0]) * x3);
  x20 = ((fiat_curve25519_uint128)(arg1[0]) * x6);
  x21 = ((fiat_curve25519_uint128)(arg1[0]) * x7);
  x22 = ((fiat_curve25519_uint128)(arg1[0]) * x8);
  x23 = ((fiat_curve25519_uint128)(arg1[0]) * (arg1[0]));
  x24 = (x23 + (x15 + x13));
  x25 = (uint64_t)(x24 >> 51);
  x26 = (uint64_t)(x24 & UINT64_C(0x7ffffffffffff));
  x27 = (x19 + (x16 + x14));
  x28 = (x20 + (x17 + x9));
  x29 = (x21 + (x18 + x10));
  x30 = (x22 + (x12 + x11));
  x31 = (x25 + x30);
  x32 = (uint64_t)(x31 >> 51);
  x33 = (uint64_t)(x31 & UINT64_C(0x7ffffffffffff));
  x34 = (x32 + x29);
  x35 = (uint64_t)(x34 >> 51);
  x36 = (uint64_t)(x34 & UINT64_C(0x7ffffffffffff));
  x37 = (x35 + x28);
  x38 = (uint64_t)(x37 >> 51);
  x39 = (uint64_t)(x37 & UINT64_C(0x7ffffffffffff));
  x40 = (x38 + x27);
  x41 = (uint64_t)(x40 >> 51);
  x42 = (uint64_t)(x40 & UINT64_C(0x7ffffffffffff));
  x43 = (x41 * UINT8_C(0x13));
  x44 = (x26 + x43);
  x45 = (x44 >> 51);
  x46 = (x44 & UINT64_C(0x7ffffffffffff));
  x47 = (x45 + x33);
  x48 = (fiat_curve25519_uint1)(x47 >> 51);
  x49 = (x47 & UINT64_C(0x7ffffffffffff));
  x50 = (x48 + x36);
  out1[0] = x46;
  out1[1] = x49;
  out1[2] = x50;
  out1[3] = x39;
  out1[4] = x42;
}

/* curve description: p224 */
/* machine_wordsize = 64 (from "64") */
/* requested operations: mul, square */
/* m = 0xffffffffffffffffffffffffffffffff000000000000000000000001 (from "2^224 -
 * 2^96 + 1") */
/*                                                                    */
/* NOTE: In addition to the bounds specified above each function, all */
/*   functions synthesized for this Montgomery arithmetic require the */
/*   input to be strictly less than the prime modulus (m), and also   */
/*   require the input to be in the unique saturated representation.  */
/*   All functions also ensure that these two properties are true of  */
/*   return values.                                                   */
/*  */
/* Computed values: */
/* eval z = z[0] + (z[1] << 64) + (z[2] << 128) + (z[3] << 192) */
/* bytes_eval z = z[0] + (z[1] << 8) + (z[2] << 16) + (z[3] << 24) + (z[4] <<
 * 32) + (z[5] << 40) + (z[6] << 48) + (z[7] << 56) + (z[8] << 64) + (z[9] <<
 * 72) + (z[10] << 80) + (z[11] << 88) + (z[12] << 96) + (z[13] << 104) + (z[14]
 * << 112) + (z[15] << 120) + (z[16] << 128) + (z[17] << 136) + (z[18] << 144) +
 * (z[19] << 152) + (z[20] << 160) + (z[21] << 168) + (z[22] << 176) + (z[23] <<
 * 184) + (z[24] << 192) + (z[25] << 200) + (z[26] << 208) + (z[27] << 216) */

#include <stdint.h>
typedef unsigned char fiat_p224_uint1;
typedef signed char fiat_p224_int1;
typedef signed __int128 fiat_p224_int128;
typedef unsigned __int128 fiat_p224_uint128;

#if (-1 & 3) != 3
#error "This code only works on a two's complement system"
#endif

/*
 * The function fiat_p224_addcarryx_u64 is an addition with carry.
 * Postconditions:
 *   out1 = (arg1 + arg2 + arg3) mod 2^64
 *   out2 = ⌊(arg1 + arg2 + arg3) / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0x1]
 */
void fiat_p224_addcarryx_u64(uint64_t *out1, fiat_p224_uint1 *out2,
                             fiat_p224_uint1 arg1, uint64_t arg2,
                             uint64_t arg3) {
  fiat_p224_uint128 x1;
  uint64_t x2;
  fiat_p224_uint1 x3;
  x1 = ((arg1 + (fiat_p224_uint128)arg2) + arg3);
  x2 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  x3 = (fiat_p224_uint1)(x1 >> 64);
  *out1 = x2;
  *out2 = x3;
}

/*
 * The function fiat_p224_subborrowx_u64 is a subtraction with borrow.
 * Postconditions:
 *   out1 = (-arg1 + arg2 + -arg3) mod 2^64
 *   out2 = -⌊(-arg1 + arg2 + -arg3) / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0x1]
 */
void fiat_p224_subborrowx_u64(uint64_t *out1, fiat_p224_uint1 *out2,
                              fiat_p224_uint1 arg1, uint64_t arg2,
                              uint64_t arg3) {
  fiat_p224_int128 x1;
  fiat_p224_int1 x2;
  uint64_t x3;
  x1 = ((arg2 - (fiat_p224_int128)arg1) - arg3);
  x2 = (fiat_p224_int1)(x1 >> 64);
  x3 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  *out1 = x3;
  *out2 = (fiat_p224_uint1)(0x0 - x2);
}

/*
 * The function fiat_p224_mulx_u64 is a multiplication, returning the full
 * double-width result. Postconditions: out1 = (arg1 * arg2) mod 2^64 out2 =
 * ⌊arg1 * arg2 / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0xffffffffffffffff]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0xffffffffffffffff]
 */
void fiat_p224_mulx_u64(uint64_t *out1, uint64_t *out2, uint64_t arg1,
                        uint64_t arg2) {
  fiat_p224_uint128 x1;
  uint64_t x2;
  uint64_t x3;
  x1 = ((fiat_p224_uint128)arg1 * arg2);
  x2 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  x3 = (uint64_t)(x1 >> 64);
  *out1 = x2;
  *out2 = x3;
}

/*
 * The function fiat_p224_cmovznz_u64 is a single-word conditional move.
 * Postconditions:
 *   out1 = (if arg1 = 0 then arg2 else arg3)
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 */
void fiat_p224_cmovznz_u64(uint64_t *out1, fiat_p224_uint1 arg1, uint64_t arg2,
                           uint64_t arg3) {
  fiat_p224_uint1 x1;
  uint64_t x2;
  uint64_t x3;
  x1 = (!(!arg1));
  x2 = ((fiat_p224_int1)(0x0 - x1) & UINT64_C(0xffffffffffffffff));
  x3 = ((x2 & arg3) | ((~x2) & arg2));
  *out1 = x3;
}

/*
 * The function fiat_p224_mul multiplies two field elements in the Montgomery
 * domain. Preconditions: 0 ≤ eval arg1 < m 0 ≤ eval arg2 < m Postconditions:
 *   eval (from_montgomery out1) mod m = (eval (from_montgomery arg1) * eval
 * (from_montgomery arg2)) mod m 0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]] arg2: [[0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]] Output Bounds: out1: [[0x0
 * ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
void fiat_p224_mul(uint64_t out1[4], const uint64_t arg1[4],
                   const uint64_t arg2[4]) {
  uint64_t x1;
  uint64_t x2;
  uint64_t x3;
  uint64_t x4;
  uint64_t x5;
  uint64_t x6;
  uint64_t x7;
  uint64_t x8;
  uint64_t x9;
  uint64_t x10;
  uint64_t x11;
  uint64_t x12;
  uint64_t x13;
  fiat_p224_uint1 x14;
  uint64_t x15;
  fiat_p224_uint1 x16;
  uint64_t x17;
  fiat_p224_uint1 x18;
  uint64_t x19;
  uint64_t x20;
  uint64_t x21;
  uint64_t x22;
  uint64_t x23;
  uint64_t x24;
  uint64_t x25;
  uint64_t x26;
  uint64_t x27;
  uint64_t x28;
  fiat_p224_uint1 x29;
  uint64_t x30;
  fiat_p224_uint1 x31;
  uint64_t x32;
  uint64_t x33;
  fiat_p224_uint1 x34;
  uint64_t x35;
  fiat_p224_uint1 x36;
  uint64_t x37;
  fiat_p224_uint1 x38;
  uint64_t x39;
  fiat_p224_uint1 x40;
  uint64_t x41;
  fiat_p224_uint1 x42;
  uint64_t x43;
  uint64_t x44;
  uint64_t x45;
  uint64_t x46;
  uint64_t x47;
  uint64_t x48;
  uint64_t x49;
  uint64_t x50;
  uint64_t x51;
  fiat_p224_uint1 x52;
  uint64_t x53;
  fiat_p224_uint1 x54;
  uint64_t x55;
  fiat_p224_uint1 x56;
  uint64_t x57;
  uint64_t x58;
  fiat_p224_uint1 x59;
  uint64_t x60;
  fiat_p224_uint1 x61;
  uint64_t x62;
  fiat_p224_uint1 x63;
  uint64_t x64;
  fiat_p224_uint1 x65;
  uint64_t x66;
  fiat_p224_uint1 x67;
  uint64_t x68;
  uint64_t x69;
  uint64_t x70;
  uint64_t x71;
  uint64_t x72;
  uint64_t x73;
  uint64_t x74;
  uint64_t x75;
  uint64_t x76;
  fiat_p224_uint1 x77;
  uint64_t x78;
  fiat_p224_uint1 x79;
  uint64_t x80;
  uint64_t x81;
  fiat_p224_uint1 x82;
  uint64_t x83;
  fiat_p224_uint1 x84;
  uint64_t x85;
  fiat_p224_uint1 x86;
  uint64_t x87;
  fiat_p224_uint1 x88;
  uint64_t x89;
  fiat_p224_uint1 x90;
  uint64_t x91;
  uint64_t x92;
  uint64_t x93;
  uint64_t x94;
  uint64_t x95;
  uint64_t x96;
  uint64_t x97;
  uint64_t x98;
  uint64_t x99;
  uint64_t x100;
  fiat_p224_uint1 x101;
  uint64_t x102;
  fiat_p224_uint1 x103;
  uint64_t x104;
  fiat_p224_uint1 x105;
  uint64_t x106;
  uint64_t x107;
  fiat_p224_uint1 x108;
  uint64_t x109;
  fiat_p224_uint1 x110;
  uint64_t x111;
  fiat_p224_uint1 x112;
  uint64_t x113;
  fiat_p224_uint1 x114;
  uint64_t x115;
  fiat_p224_uint1 x116;
  uint64_t x117;
  uint64_t x118;
  uint64_t x119;
  uint64_t x120;
  uint64_t x121;
  uint64_t x122;
  uint64_t x123;
  uint64_t x124;
  uint64_t x125;
  fiat_p224_uint1 x126;
  uint64_t x127;
  fiat_p224_uint1 x128;
  uint64_t x129;
  uint64_t x130;
  fiat_p224_uint1 x131;
  uint64_t x132;
  fiat_p224_uint1 x133;
  uint64_t x134;
  fiat_p224_uint1 x135;
  uint64_t x136;
  fiat_p224_uint1 x137;
  uint64_t x138;
  fiat_p224_uint1 x139;
  uint64_t x140;
  uint64_t x141;
  uint64_t x142;
  uint64_t x143;
  uint64_t x144;
  uint64_t x145;
  uint64_t x146;
  uint64_t x147;
  uint64_t x148;
  uint64_t x149;
  fiat_p224_uint1 x150;
  uint64_t x151;
  fiat_p224_uint1 x152;
  uint64_t x153;
  fiat_p224_uint1 x154;
  uint64_t x155;
  uint64_t x156;
  fiat_p224_uint1 x157;
  uint64_t x158;
  fiat_p224_uint1 x159;
  uint64_t x160;
  fiat_p224_uint1 x161;
  uint64_t x162;
  fiat_p224_uint1 x163;
  uint64_t x164;
  fiat_p224_uint1 x165;
  uint64_t x166;
  uint64_t x167;
  uint64_t x168;
  uint64_t x169;
  uint64_t x170;
  uint64_t x171;
  uint64_t x172;
  uint64_t x173;
  uint64_t x174;
  fiat_p224_uint1 x175;
  uint64_t x176;
  fiat_p224_uint1 x177;
  uint64_t x178;
  uint64_t x179;
  fiat_p224_uint1 x180;
  uint64_t x181;
  fiat_p224_uint1 x182;
  uint64_t x183;
  fiat_p224_uint1 x184;
  uint64_t x185;
  fiat_p224_uint1 x186;
  uint64_t x187;
  fiat_p224_uint1 x188;
  uint64_t x189;
  uint64_t x190;
  fiat_p224_uint1 x191;
  uint64_t x192;
  fiat_p224_uint1 x193;
  uint64_t x194;
  fiat_p224_uint1 x195;
  uint64_t x196;
  fiat_p224_uint1 x197;
  uint64_t x198;
  fiat_p224_uint1 x199;
  uint64_t x200;
  uint64_t x201;
  uint64_t x202;
  uint64_t x203;
  x1 = (arg1[1]);
  x2 = (arg1[2]);
  x3 = (arg1[3]);
  x4 = (arg1[0]);
  fiat_p224_mulx_u64(&x5, &x6, x4, (arg2[3]));
  fiat_p224_mulx_u64(&x7, &x8, x4, (arg2[2]));
  fiat_p224_mulx_u64(&x9, &x10, x4, (arg2[1]));
  fiat_p224_mulx_u64(&x11, &x12, x4, (arg2[0]));
  fiat_p224_addcarryx_u64(&x13, &x14, 0x0, x12, x9);
  fiat_p224_addcarryx_u64(&x15, &x16, x14, x10, x7);
  fiat_p224_addcarryx_u64(&x17, &x18, x16, x8, x5);
  x19 = (x18 + x6);
  fiat_p224_mulx_u64(&x20, &x21, x11, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x22, &x23, x20, UINT32_C(0xffffffff));
  fiat_p224_mulx_u64(&x24, &x25, x20, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x26, &x27, x20, UINT64_C(0xffffffff00000000));
  fiat_p224_addcarryx_u64(&x28, &x29, 0x0, x27, x24);
  fiat_p224_addcarryx_u64(&x30, &x31, x29, x25, x22);
  x32 = (x31 + x23);
  fiat_p224_addcarryx_u64(&x33, &x34, 0x0, x11, x20);
  fiat_p224_addcarryx_u64(&x35, &x36, x34, x13, x26);
  fiat_p224_addcarryx_u64(&x37, &x38, x36, x15, x28);
  fiat_p224_addcarryx_u64(&x39, &x40, x38, x17, x30);
  fiat_p224_addcarryx_u64(&x41, &x42, x40, x19, x32);
  fiat_p224_mulx_u64(&x43, &x44, x1, (arg2[3]));
  fiat_p224_mulx_u64(&x45, &x46, x1, (arg2[2]));
  fiat_p224_mulx_u64(&x47, &x48, x1, (arg2[1]));
  fiat_p224_mulx_u64(&x49, &x50, x1, (arg2[0]));
  fiat_p224_addcarryx_u64(&x51, &x52, 0x0, x50, x47);
  fiat_p224_addcarryx_u64(&x53, &x54, x52, x48, x45);
  fiat_p224_addcarryx_u64(&x55, &x56, x54, x46, x43);
  x57 = (x56 + x44);
  fiat_p224_addcarryx_u64(&x58, &x59, 0x0, x35, x49);
  fiat_p224_addcarryx_u64(&x60, &x61, x59, x37, x51);
  fiat_p224_addcarryx_u64(&x62, &x63, x61, x39, x53);
  fiat_p224_addcarryx_u64(&x64, &x65, x63, x41, x55);
  fiat_p224_addcarryx_u64(&x66, &x67, x65, x42, x57);
  fiat_p224_mulx_u64(&x68, &x69, x58, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x70, &x71, x68, UINT32_C(0xffffffff));
  fiat_p224_mulx_u64(&x72, &x73, x68, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x74, &x75, x68, UINT64_C(0xffffffff00000000));
  fiat_p224_addcarryx_u64(&x76, &x77, 0x0, x75, x72);
  fiat_p224_addcarryx_u64(&x78, &x79, x77, x73, x70);
  x80 = (x79 + x71);
  fiat_p224_addcarryx_u64(&x81, &x82, 0x0, x58, x68);
  fiat_p224_addcarryx_u64(&x83, &x84, x82, x60, x74);
  fiat_p224_addcarryx_u64(&x85, &x86, x84, x62, x76);
  fiat_p224_addcarryx_u64(&x87, &x88, x86, x64, x78);
  fiat_p224_addcarryx_u64(&x89, &x90, x88, x66, x80);
  x91 = ((uint64_t)x90 + x67);
  fiat_p224_mulx_u64(&x92, &x93, x2, (arg2[3]));
  fiat_p224_mulx_u64(&x94, &x95, x2, (arg2[2]));
  fiat_p224_mulx_u64(&x96, &x97, x2, (arg2[1]));
  fiat_p224_mulx_u64(&x98, &x99, x2, (arg2[0]));
  fiat_p224_addcarryx_u64(&x100, &x101, 0x0, x99, x96);
  fiat_p224_addcarryx_u64(&x102, &x103, x101, x97, x94);
  fiat_p224_addcarryx_u64(&x104, &x105, x103, x95, x92);
  x106 = (x105 + x93);
  fiat_p224_addcarryx_u64(&x107, &x108, 0x0, x83, x98);
  fiat_p224_addcarryx_u64(&x109, &x110, x108, x85, x100);
  fiat_p224_addcarryx_u64(&x111, &x112, x110, x87, x102);
  fiat_p224_addcarryx_u64(&x113, &x114, x112, x89, x104);
  fiat_p224_addcarryx_u64(&x115, &x116, x114, x91, x106);
  fiat_p224_mulx_u64(&x117, &x118, x107, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x119, &x120, x117, UINT32_C(0xffffffff));
  fiat_p224_mulx_u64(&x121, &x122, x117, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x123, &x124, x117, UINT64_C(0xffffffff00000000));
  fiat_p224_addcarryx_u64(&x125, &x126, 0x0, x124, x121);
  fiat_p224_addcarryx_u64(&x127, &x128, x126, x122, x119);
  x129 = (x128 + x120);
  fiat_p224_addcarryx_u64(&x130, &x131, 0x0, x107, x117);
  fiat_p224_addcarryx_u64(&x132, &x133, x131, x109, x123);
  fiat_p224_addcarryx_u64(&x134, &x135, x133, x111, x125);
  fiat_p224_addcarryx_u64(&x136, &x137, x135, x113, x127);
  fiat_p224_addcarryx_u64(&x138, &x139, x137, x115, x129);
  x140 = ((uint64_t)x139 + x116);
  fiat_p224_mulx_u64(&x141, &x142, x3, (arg2[3]));
  fiat_p224_mulx_u64(&x143, &x144, x3, (arg2[2]));
  fiat_p224_mulx_u64(&x145, &x146, x3, (arg2[1]));
  fiat_p224_mulx_u64(&x147, &x148, x3, (arg2[0]));
  fiat_p224_addcarryx_u64(&x149, &x150, 0x0, x148, x145);
  fiat_p224_addcarryx_u64(&x151, &x152, x150, x146, x143);
  fiat_p224_addcarryx_u64(&x153, &x154, x152, x144, x141);
  x155 = (x154 + x142);
  fiat_p224_addcarryx_u64(&x156, &x157, 0x0, x132, x147);
  fiat_p224_addcarryx_u64(&x158, &x159, x157, x134, x149);
  fiat_p224_addcarryx_u64(&x160, &x161, x159, x136, x151);
  fiat_p224_addcarryx_u64(&x162, &x163, x161, x138, x153);
  fiat_p224_addcarryx_u64(&x164, &x165, x163, x140, x155);
  fiat_p224_mulx_u64(&x166, &x167, x156, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x168, &x169, x166, UINT32_C(0xffffffff));
  fiat_p224_mulx_u64(&x170, &x171, x166, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x172, &x173, x166, UINT64_C(0xffffffff00000000));
  fiat_p224_addcarryx_u64(&x174, &x175, 0x0, x173, x170);
  fiat_p224_addcarryx_u64(&x176, &x177, x175, x171, x168);
  x178 = (x177 + x169);
  fiat_p224_addcarryx_u64(&x179, &x180, 0x0, x156, x166);
  fiat_p224_addcarryx_u64(&x181, &x182, x180, x158, x172);
  fiat_p224_addcarryx_u64(&x183, &x184, x182, x160, x174);
  fiat_p224_addcarryx_u64(&x185, &x186, x184, x162, x176);
  fiat_p224_addcarryx_u64(&x187, &x188, x186, x164, x178);
  x189 = ((uint64_t)x188 + x165);
  fiat_p224_subborrowx_u64(&x190, &x191, 0x0, x181, 0x1);
  fiat_p224_subborrowx_u64(&x192, &x193, x191, x183,
                           UINT64_C(0xffffffff00000000));
  fiat_p224_subborrowx_u64(&x194, &x195, x193, x185,
                           UINT64_C(0xffffffffffffffff));
  fiat_p224_subborrowx_u64(&x196, &x197, x195, x187, UINT32_C(0xffffffff));
  fiat_p224_subborrowx_u64(&x198, &x199, x197, x189, 0x0);
  fiat_p224_cmovznz_u64(&x200, x199, x190, x181);
  fiat_p224_cmovznz_u64(&x201, x199, x192, x183);
  fiat_p224_cmovznz_u64(&x202, x199, x194, x185);
  fiat_p224_cmovznz_u64(&x203, x199, x196, x187);
  out1[0] = x200;
  out1[1] = x201;
  out1[2] = x202;
  out1[3] = x203;
}

/*
 * The function fiat_p224_square squares a field element in the Montgomery
 * domain. Preconditions: 0 ≤ eval arg1 < m Postconditions: eval
 * (from_montgomery out1) mod m = (eval (from_montgomery arg1) * eval
 * (from_montgomery arg1)) mod m 0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]] Output Bounds: out1: [[0x0
 * ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
void fiat_p224_square(uint64_t out1[4], const uint64_t arg1[4]) {
  uint64_t x1;
  uint64_t x2;
  uint64_t x3;
  uint64_t x4;
  uint64_t x5;
  uint64_t x6;
  uint64_t x7;
  uint64_t x8;
  uint64_t x9;
  uint64_t x10;
  uint64_t x11;
  uint64_t x12;
  uint64_t x13;
  fiat_p224_uint1 x14;
  uint64_t x15;
  fiat_p224_uint1 x16;
  uint64_t x17;
  fiat_p224_uint1 x18;
  uint64_t x19;
  uint64_t x20;
  uint64_t x21;
  uint64_t x22;
  uint64_t x23;
  uint64_t x24;
  uint64_t x25;
  uint64_t x26;
  uint64_t x27;
  uint64_t x28;
  fiat_p224_uint1 x29;
  uint64_t x30;
  fiat_p224_uint1 x31;
  uint64_t x32;
  uint64_t x33;
  fiat_p224_uint1 x34;
  uint64_t x35;
  fiat_p224_uint1 x36;
  uint64_t x37;
  fiat_p224_uint1 x38;
  uint64_t x39;
  fiat_p224_uint1 x40;
  uint64_t x41;
  fiat_p224_uint1 x42;
  uint64_t x43;
  uint64_t x44;
  uint64_t x45;
  uint64_t x46;
  uint64_t x47;
  uint64_t x48;
  uint64_t x49;
  uint64_t x50;
  uint64_t x51;
  fiat_p224_uint1 x52;
  uint64_t x53;
  fiat_p224_uint1 x54;
  uint64_t x55;
  fiat_p224_uint1 x56;
  uint64_t x57;
  uint64_t x58;
  fiat_p224_uint1 x59;
  uint64_t x60;
  fiat_p224_uint1 x61;
  uint64_t x62;
  fiat_p224_uint1 x63;
  uint64_t x64;
  fiat_p224_uint1 x65;
  uint64_t x66;
  fiat_p224_uint1 x67;
  uint64_t x68;
  uint64_t x69;
  uint64_t x70;
  uint64_t x71;
  uint64_t x72;
  uint64_t x73;
  uint64_t x74;
  uint64_t x75;
  uint64_t x76;
  fiat_p224_uint1 x77;
  uint64_t x78;
  fiat_p224_uint1 x79;
  uint64_t x80;
  uint64_t x81;
  fiat_p224_uint1 x82;
  uint64_t x83;
  fiat_p224_uint1 x84;
  uint64_t x85;
  fiat_p224_uint1 x86;
  uint64_t x87;
  fiat_p224_uint1 x88;
  uint64_t x89;
  fiat_p224_uint1 x90;
  uint64_t x91;
  uint64_t x92;
  uint64_t x93;
  uint64_t x94;
  uint64_t x95;
  uint64_t x96;
  uint64_t x97;
  uint64_t x98;
  uint64_t x99;
  uint64_t x100;
  fiat_p224_uint1 x101;
  uint64_t x102;
  fiat_p224_uint1 x103;
  uint64_t x104;
  fiat_p224_uint1 x105;
  uint64_t x106;
  uint64_t x107;
  fiat_p224_uint1 x108;
  uint64_t x109;
  fiat_p224_uint1 x110;
  uint64_t x111;
  fiat_p224_uint1 x112;
  uint64_t x113;
  fiat_p224_uint1 x114;
  uint64_t x115;
  fiat_p224_uint1 x116;
  uint64_t x117;
  uint64_t x118;
  uint64_t x119;
  uint64_t x120;
  uint64_t x121;
  uint64_t x122;
  uint64_t x123;
  uint64_t x124;
  uint64_t x125;
  fiat_p224_uint1 x126;
  uint64_t x127;
  fiat_p224_uint1 x128;
  uint64_t x129;
  uint64_t x130;
  fiat_p224_uint1 x131;
  uint64_t x132;
  fiat_p224_uint1 x133;
  uint64_t x134;
  fiat_p224_uint1 x135;
  uint64_t x136;
  fiat_p224_uint1 x137;
  uint64_t x138;
  fiat_p224_uint1 x139;
  uint64_t x140;
  uint64_t x141;
  uint64_t x142;
  uint64_t x143;
  uint64_t x144;
  uint64_t x145;
  uint64_t x146;
  uint64_t x147;
  uint64_t x148;
  uint64_t x149;
  fiat_p224_uint1 x150;
  uint64_t x151;
  fiat_p224_uint1 x152;
  uint64_t x153;
  fiat_p224_uint1 x154;
  uint64_t x155;
  uint64_t x156;
  fiat_p224_uint1 x157;
  uint64_t x158;
  fiat_p224_uint1 x159;
  uint64_t x160;
  fiat_p224_uint1 x161;
  uint64_t x162;
  fiat_p224_uint1 x163;
  uint64_t x164;
  fiat_p224_uint1 x165;
  uint64_t x166;
  uint64_t x167;
  uint64_t x168;
  uint64_t x169;
  uint64_t x170;
  uint64_t x171;
  uint64_t x172;
  uint64_t x173;
  uint64_t x174;
  fiat_p224_uint1 x175;
  uint64_t x176;
  fiat_p224_uint1 x177;
  uint64_t x178;
  uint64_t x179;
  fiat_p224_uint1 x180;
  uint64_t x181;
  fiat_p224_uint1 x182;
  uint64_t x183;
  fiat_p224_uint1 x184;
  uint64_t x185;
  fiat_p224_uint1 x186;
  uint64_t x187;
  fiat_p224_uint1 x188;
  uint64_t x189;
  uint64_t x190;
  fiat_p224_uint1 x191;
  uint64_t x192;
  fiat_p224_uint1 x193;
  uint64_t x194;
  fiat_p224_uint1 x195;
  uint64_t x196;
  fiat_p224_uint1 x197;
  uint64_t x198;
  fiat_p224_uint1 x199;
  uint64_t x200;
  uint64_t x201;
  uint64_t x202;
  uint64_t x203;
  x1 = (arg1[1]);
  x2 = (arg1[2]);
  x3 = (arg1[3]);
  x4 = (arg1[0]);
  fiat_p224_mulx_u64(&x5, &x6, x4, (arg1[3]));
  fiat_p224_mulx_u64(&x7, &x8, x4, (arg1[2]));
  fiat_p224_mulx_u64(&x9, &x10, x4, (arg1[1]));
  fiat_p224_mulx_u64(&x11, &x12, x4, (arg1[0]));
  fiat_p224_addcarryx_u64(&x13, &x14, 0x0, x12, x9);
  fiat_p224_addcarryx_u64(&x15, &x16, x14, x10, x7);
  fiat_p224_addcarryx_u64(&x17, &x18, x16, x8, x5);
  x19 = (x18 + x6);
  fiat_p224_mulx_u64(&x20, &x21, x11, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x22, &x23, x20, UINT32_C(0xffffffff));
  fiat_p224_mulx_u64(&x24, &x25, x20, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x26, &x27, x20, UINT64_C(0xffffffff00000000));
  fiat_p224_addcarryx_u64(&x28, &x29, 0x0, x27, x24);
  fiat_p224_addcarryx_u64(&x30, &x31, x29, x25, x22);
  x32 = (x31 + x23);
  fiat_p224_addcarryx_u64(&x33, &x34, 0x0, x11, x20);
  fiat_p224_addcarryx_u64(&x35, &x36, x34, x13, x26);
  fiat_p224_addcarryx_u64(&x37, &x38, x36, x15, x28);
  fiat_p224_addcarryx_u64(&x39, &x40, x38, x17, x30);
  fiat_p224_addcarryx_u64(&x41, &x42, x40, x19, x32);
  fiat_p224_mulx_u64(&x43, &x44, x1, (arg1[3]));
  fiat_p224_mulx_u64(&x45, &x46, x1, (arg1[2]));
  fiat_p224_mulx_u64(&x47, &x48, x1, (arg1[1]));
  fiat_p224_mulx_u64(&x49, &x50, x1, (arg1[0]));
  fiat_p224_addcarryx_u64(&x51, &x52, 0x0, x50, x47);
  fiat_p224_addcarryx_u64(&x53, &x54, x52, x48, x45);
  fiat_p224_addcarryx_u64(&x55, &x56, x54, x46, x43);
  x57 = (x56 + x44);
  fiat_p224_addcarryx_u64(&x58, &x59, 0x0, x35, x49);
  fiat_p224_addcarryx_u64(&x60, &x61, x59, x37, x51);
  fiat_p224_addcarryx_u64(&x62, &x63, x61, x39, x53);
  fiat_p224_addcarryx_u64(&x64, &x65, x63, x41, x55);
  fiat_p224_addcarryx_u64(&x66, &x67, x65, x42, x57);
  fiat_p224_mulx_u64(&x68, &x69, x58, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x70, &x71, x68, UINT32_C(0xffffffff));
  fiat_p224_mulx_u64(&x72, &x73, x68, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x74, &x75, x68, UINT64_C(0xffffffff00000000));
  fiat_p224_addcarryx_u64(&x76, &x77, 0x0, x75, x72);
  fiat_p224_addcarryx_u64(&x78, &x79, x77, x73, x70);
  x80 = (x79 + x71);
  fiat_p224_addcarryx_u64(&x81, &x82, 0x0, x58, x68);
  fiat_p224_addcarryx_u64(&x83, &x84, x82, x60, x74);
  fiat_p224_addcarryx_u64(&x85, &x86, x84, x62, x76);
  fiat_p224_addcarryx_u64(&x87, &x88, x86, x64, x78);
  fiat_p224_addcarryx_u64(&x89, &x90, x88, x66, x80);
  x91 = ((uint64_t)x90 + x67);
  fiat_p224_mulx_u64(&x92, &x93, x2, (arg1[3]));
  fiat_p224_mulx_u64(&x94, &x95, x2, (arg1[2]));
  fiat_p224_mulx_u64(&x96, &x97, x2, (arg1[1]));
  fiat_p224_mulx_u64(&x98, &x99, x2, (arg1[0]));
  fiat_p224_addcarryx_u64(&x100, &x101, 0x0, x99, x96);
  fiat_p224_addcarryx_u64(&x102, &x103, x101, x97, x94);
  fiat_p224_addcarryx_u64(&x104, &x105, x103, x95, x92);
  x106 = (x105 + x93);
  fiat_p224_addcarryx_u64(&x107, &x108, 0x0, x83, x98);
  fiat_p224_addcarryx_u64(&x109, &x110, x108, x85, x100);
  fiat_p224_addcarryx_u64(&x111, &x112, x110, x87, x102);
  fiat_p224_addcarryx_u64(&x113, &x114, x112, x89, x104);
  fiat_p224_addcarryx_u64(&x115, &x116, x114, x91, x106);
  fiat_p224_mulx_u64(&x117, &x118, x107, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x119, &x120, x117, UINT32_C(0xffffffff));
  fiat_p224_mulx_u64(&x121, &x122, x117, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x123, &x124, x117, UINT64_C(0xffffffff00000000));
  fiat_p224_addcarryx_u64(&x125, &x126, 0x0, x124, x121);
  fiat_p224_addcarryx_u64(&x127, &x128, x126, x122, x119);
  x129 = (x128 + x120);
  fiat_p224_addcarryx_u64(&x130, &x131, 0x0, x107, x117);
  fiat_p224_addcarryx_u64(&x132, &x133, x131, x109, x123);
  fiat_p224_addcarryx_u64(&x134, &x135, x133, x111, x125);
  fiat_p224_addcarryx_u64(&x136, &x137, x135, x113, x127);
  fiat_p224_addcarryx_u64(&x138, &x139, x137, x115, x129);
  x140 = ((uint64_t)x139 + x116);
  fiat_p224_mulx_u64(&x141, &x142, x3, (arg1[3]));
  fiat_p224_mulx_u64(&x143, &x144, x3, (arg1[2]));
  fiat_p224_mulx_u64(&x145, &x146, x3, (arg1[1]));
  fiat_p224_mulx_u64(&x147, &x148, x3, (arg1[0]));
  fiat_p224_addcarryx_u64(&x149, &x150, 0x0, x148, x145);
  fiat_p224_addcarryx_u64(&x151, &x152, x150, x146, x143);
  fiat_p224_addcarryx_u64(&x153, &x154, x152, x144, x141);
  x155 = (x154 + x142);
  fiat_p224_addcarryx_u64(&x156, &x157, 0x0, x132, x147);
  fiat_p224_addcarryx_u64(&x158, &x159, x157, x134, x149);
  fiat_p224_addcarryx_u64(&x160, &x161, x159, x136, x151);
  fiat_p224_addcarryx_u64(&x162, &x163, x161, x138, x153);
  fiat_p224_addcarryx_u64(&x164, &x165, x163, x140, x155);
  fiat_p224_mulx_u64(&x166, &x167, x156, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x168, &x169, x166, UINT32_C(0xffffffff));
  fiat_p224_mulx_u64(&x170, &x171, x166, UINT64_C(0xffffffffffffffff));
  fiat_p224_mulx_u64(&x172, &x173, x166, UINT64_C(0xffffffff00000000));
  fiat_p224_addcarryx_u64(&x174, &x175, 0x0, x173, x170);
  fiat_p224_addcarryx_u64(&x176, &x177, x175, x171, x168);
  x178 = (x177 + x169);
  fiat_p224_addcarryx_u64(&x179, &x180, 0x0, x156, x166);
  fiat_p224_addcarryx_u64(&x181, &x182, x180, x158, x172);
  fiat_p224_addcarryx_u64(&x183, &x184, x182, x160, x174);
  fiat_p224_addcarryx_u64(&x185, &x186, x184, x162, x176);
  fiat_p224_addcarryx_u64(&x187, &x188, x186, x164, x178);
  x189 = ((uint64_t)x188 + x165);
  fiat_p224_subborrowx_u64(&x190, &x191, 0x0, x181, 0x1);
  fiat_p224_subborrowx_u64(&x192, &x193, x191, x183,
                           UINT64_C(0xffffffff00000000));
  fiat_p224_subborrowx_u64(&x194, &x195, x193, x185,
                           UINT64_C(0xffffffffffffffff));
  fiat_p224_subborrowx_u64(&x196, &x197, x195, x187, UINT32_C(0xffffffff));
  fiat_p224_subborrowx_u64(&x198, &x199, x197, x189, 0x0);
  fiat_p224_cmovznz_u64(&x200, x199, x190, x181);
  fiat_p224_cmovznz_u64(&x201, x199, x192, x183);
  fiat_p224_cmovznz_u64(&x202, x199, x194, x185);
  fiat_p224_cmovznz_u64(&x203, x199, x196, x187);
  out1[0] = x200;
  out1[1] = x201;
  out1[2] = x202;
  out1[3] = x203;
}

/* curve description: p256 */
/* machine_wordsize = 64 (from "64") */
/* requested operations: mul, square */
/* m = 0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff (from
 * "2^256 - 2^224 + 2^192 + 2^96 - 1") */
/*                                                                    */
/* NOTE: In addition to the bounds specified above each function, all */
/*   functions synthesized for this Montgomery arithmetic require the */
/*   input to be strictly less than the prime modulus (m), and also   */
/*   require the input to be in the unique saturated representation.  */
/*   All functions also ensure that these two properties are true of  */
/*   return values.                                                   */
/*  */
/* Computed values: */
/* eval z = z[0] + (z[1] << 64) + (z[2] << 128) + (z[3] << 192) */
/* bytes_eval z = z[0] + (z[1] << 8) + (z[2] << 16) + (z[3] << 24) + (z[4] <<
 * 32) + (z[5] << 40) + (z[6] << 48) + (z[7] << 56) + (z[8] << 64) + (z[9] <<
 * 72) + (z[10] << 80) + (z[11] << 88) + (z[12] << 96) + (z[13] << 104) + (z[14]
 * << 112) + (z[15] << 120) + (z[16] << 128) + (z[17] << 136) + (z[18] << 144) +
 * (z[19] << 152) + (z[20] << 160) + (z[21] << 168) + (z[22] << 176) + (z[23] <<
 * 184) + (z[24] << 192) + (z[25] << 200) + (z[26] << 208) + (z[27] << 216) +
 * (z[28] << 224) + (z[29] << 232) + (z[30] << 240) + (z[31] << 248) */

#include <stdint.h>
typedef unsigned char fiat_p256_uint1;
typedef signed char fiat_p256_int1;
typedef signed __int128 fiat_p256_int128;
typedef unsigned __int128 fiat_p256_uint128;

#if (-1 & 3) != 3
#error "This code only works on a two's complement system"
#endif

/*
 * The function fiat_p256_addcarryx_u64 is an addition with carry.
 * Postconditions:
 *   out1 = (arg1 + arg2 + arg3) mod 2^64
 *   out2 = ⌊(arg1 + arg2 + arg3) / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0x1]
 */
void fiat_p256_addcarryx_u64(uint64_t *out1, fiat_p256_uint1 *out2,
                             fiat_p256_uint1 arg1, uint64_t arg2,
                             uint64_t arg3) {
  fiat_p256_uint128 x1;
  uint64_t x2;
  fiat_p256_uint1 x3;
  x1 = ((arg1 + (fiat_p256_uint128)arg2) + arg3);
  x2 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  x3 = (fiat_p256_uint1)(x1 >> 64);
  *out1 = x2;
  *out2 = x3;
}

/*
 * The function fiat_p256_subborrowx_u64 is a subtraction with borrow.
 * Postconditions:
 *   out1 = (-arg1 + arg2 + -arg3) mod 2^64
 *   out2 = -⌊(-arg1 + arg2 + -arg3) / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0x1]
 */
void fiat_p256_subborrowx_u64(uint64_t *out1, fiat_p256_uint1 *out2,
                              fiat_p256_uint1 arg1, uint64_t arg2,
                              uint64_t arg3) {
  fiat_p256_int128 x1;
  fiat_p256_int1 x2;
  uint64_t x3;
  x1 = ((arg2 - (fiat_p256_int128)arg1) - arg3);
  x2 = (fiat_p256_int1)(x1 >> 64);
  x3 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  *out1 = x3;
  *out2 = (fiat_p256_uint1)(0x0 - x2);
}

/*
 * The function fiat_p256_mulx_u64 is a multiplication, returning the full
 * double-width result. Postconditions: out1 = (arg1 * arg2) mod 2^64 out2 =
 * ⌊arg1 * arg2 / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0xffffffffffffffff]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0xffffffffffffffff]
 */
void fiat_p256_mulx_u64(uint64_t *out1, uint64_t *out2, uint64_t arg1,
                        uint64_t arg2) {
  fiat_p256_uint128 x1;
  uint64_t x2;
  uint64_t x3;
  x1 = ((fiat_p256_uint128)arg1 * arg2);
  x2 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  x3 = (uint64_t)(x1 >> 64);
  *out1 = x2;
  *out2 = x3;
}

/*
 * The function fiat_p256_cmovznz_u64 is a single-word conditional move.
 * Postconditions:
 *   out1 = (if arg1 = 0 then arg2 else arg3)
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 */
void fiat_p256_cmovznz_u64(uint64_t *out1, fiat_p256_uint1 arg1, uint64_t arg2,
                           uint64_t arg3) {
  fiat_p256_uint1 x1;
  uint64_t x2;
  uint64_t x3;
  x1 = (!(!arg1));
  x2 = ((fiat_p256_int1)(0x0 - x1) & UINT64_C(0xffffffffffffffff));
  x3 = ((x2 & arg3) | ((~x2) & arg2));
  *out1 = x3;
}

/*
 * The function fiat_p256_mul multiplies two field elements in the Montgomery
 * domain. Preconditions: 0 ≤ eval arg1 < m 0 ≤ eval arg2 < m Postconditions:
 *   eval (from_montgomery out1) mod m = (eval (from_montgomery arg1) * eval
 * (from_montgomery arg2)) mod m 0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]] arg2: [[0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]] Output Bounds: out1: [[0x0
 * ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
void fiat_p256_mul(uint64_t out1[4], const uint64_t arg1[4],
                   const uint64_t arg2[4]) {
  uint64_t x1;
  uint64_t x2;
  uint64_t x3;
  uint64_t x4;
  uint64_t x5;
  uint64_t x6;
  uint64_t x7;
  uint64_t x8;
  uint64_t x9;
  uint64_t x10;
  uint64_t x11;
  uint64_t x12;
  uint64_t x13;
  fiat_p256_uint1 x14;
  uint64_t x15;
  fiat_p256_uint1 x16;
  uint64_t x17;
  fiat_p256_uint1 x18;
  uint64_t x19;
  uint64_t x20;
  uint64_t x21;
  uint64_t x22;
  uint64_t x23;
  uint64_t x24;
  uint64_t x25;
  uint64_t x26;
  fiat_p256_uint1 x27;
  uint64_t x28;
  uint64_t x29;
  fiat_p256_uint1 x30;
  uint64_t x31;
  fiat_p256_uint1 x32;
  uint64_t x33;
  fiat_p256_uint1 x34;
  uint64_t x35;
  fiat_p256_uint1 x36;
  uint64_t x37;
  fiat_p256_uint1 x38;
  uint64_t x39;
  uint64_t x40;
  uint64_t x41;
  uint64_t x42;
  uint64_t x43;
  uint64_t x44;
  uint64_t x45;
  uint64_t x46;
  uint64_t x47;
  fiat_p256_uint1 x48;
  uint64_t x49;
  fiat_p256_uint1 x50;
  uint64_t x51;
  fiat_p256_uint1 x52;
  uint64_t x53;
  uint64_t x54;
  fiat_p256_uint1 x55;
  uint64_t x56;
  fiat_p256_uint1 x57;
  uint64_t x58;
  fiat_p256_uint1 x59;
  uint64_t x60;
  fiat_p256_uint1 x61;
  uint64_t x62;
  fiat_p256_uint1 x63;
  uint64_t x64;
  uint64_t x65;
  uint64_t x66;
  uint64_t x67;
  uint64_t x68;
  uint64_t x69;
  uint64_t x70;
  fiat_p256_uint1 x71;
  uint64_t x72;
  uint64_t x73;
  fiat_p256_uint1 x74;
  uint64_t x75;
  fiat_p256_uint1 x76;
  uint64_t x77;
  fiat_p256_uint1 x78;
  uint64_t x79;
  fiat_p256_uint1 x80;
  uint64_t x81;
  fiat_p256_uint1 x82;
  uint64_t x83;
  uint64_t x84;
  uint64_t x85;
  uint64_t x86;
  uint64_t x87;
  uint64_t x88;
  uint64_t x89;
  uint64_t x90;
  uint64_t x91;
  uint64_t x92;
  fiat_p256_uint1 x93;
  uint64_t x94;
  fiat_p256_uint1 x95;
  uint64_t x96;
  fiat_p256_uint1 x97;
  uint64_t x98;
  uint64_t x99;
  fiat_p256_uint1 x100;
  uint64_t x101;
  fiat_p256_uint1 x102;
  uint64_t x103;
  fiat_p256_uint1 x104;
  uint64_t x105;
  fiat_p256_uint1 x106;
  uint64_t x107;
  fiat_p256_uint1 x108;
  uint64_t x109;
  uint64_t x110;
  uint64_t x111;
  uint64_t x112;
  uint64_t x113;
  uint64_t x114;
  uint64_t x115;
  fiat_p256_uint1 x116;
  uint64_t x117;
  uint64_t x118;
  fiat_p256_uint1 x119;
  uint64_t x120;
  fiat_p256_uint1 x121;
  uint64_t x122;
  fiat_p256_uint1 x123;
  uint64_t x124;
  fiat_p256_uint1 x125;
  uint64_t x126;
  fiat_p256_uint1 x127;
  uint64_t x128;
  uint64_t x129;
  uint64_t x130;
  uint64_t x131;
  uint64_t x132;
  uint64_t x133;
  uint64_t x134;
  uint64_t x135;
  uint64_t x136;
  uint64_t x137;
  fiat_p256_uint1 x138;
  uint64_t x139;
  fiat_p256_uint1 x140;
  uint64_t x141;
  fiat_p256_uint1 x142;
  uint64_t x143;
  uint64_t x144;
  fiat_p256_uint1 x145;
  uint64_t x146;
  fiat_p256_uint1 x147;
  uint64_t x148;
  fiat_p256_uint1 x149;
  uint64_t x150;
  fiat_p256_uint1 x151;
  uint64_t x152;
  fiat_p256_uint1 x153;
  uint64_t x154;
  uint64_t x155;
  uint64_t x156;
  uint64_t x157;
  uint64_t x158;
  uint64_t x159;
  uint64_t x160;
  fiat_p256_uint1 x161;
  uint64_t x162;
  uint64_t x163;
  fiat_p256_uint1 x164;
  uint64_t x165;
  fiat_p256_uint1 x166;
  uint64_t x167;
  fiat_p256_uint1 x168;
  uint64_t x169;
  fiat_p256_uint1 x170;
  uint64_t x171;
  fiat_p256_uint1 x172;
  uint64_t x173;
  uint64_t x174;
  fiat_p256_uint1 x175;
  uint64_t x176;
  fiat_p256_uint1 x177;
  uint64_t x178;
  fiat_p256_uint1 x179;
  uint64_t x180;
  fiat_p256_uint1 x181;
  uint64_t x182;
  fiat_p256_uint1 x183;
  uint64_t x184;
  uint64_t x185;
  uint64_t x186;
  uint64_t x187;
  x1 = (arg1[1]);
  x2 = (arg1[2]);
  x3 = (arg1[3]);
  x4 = (arg1[0]);
  fiat_p256_mulx_u64(&x5, &x6, x4, (arg2[3]));
  fiat_p256_mulx_u64(&x7, &x8, x4, (arg2[2]));
  fiat_p256_mulx_u64(&x9, &x10, x4, (arg2[1]));
  fiat_p256_mulx_u64(&x11, &x12, x4, (arg2[0]));
  fiat_p256_addcarryx_u64(&x13, &x14, 0x0, x12, x9);
  fiat_p256_addcarryx_u64(&x15, &x16, x14, x10, x7);
  fiat_p256_addcarryx_u64(&x17, &x18, x16, x8, x5);
  x19 = (x18 + x6);
  fiat_p256_mulx_u64(&x20, &x21, x11, UINT64_C(0xffffffff00000001));
  fiat_p256_mulx_u64(&x22, &x23, x11, UINT32_C(0xffffffff));
  fiat_p256_mulx_u64(&x24, &x25, x11, UINT64_C(0xffffffffffffffff));
  fiat_p256_addcarryx_u64(&x26, &x27, 0x0, x25, x22);
  x28 = (x27 + x23);
  fiat_p256_addcarryx_u64(&x29, &x30, 0x0, x11, x24);
  fiat_p256_addcarryx_u64(&x31, &x32, x30, x13, x26);
  fiat_p256_addcarryx_u64(&x33, &x34, x32, x15, x28);
  fiat_p256_addcarryx_u64(&x35, &x36, x34, x17, x20);
  fiat_p256_addcarryx_u64(&x37, &x38, x36, x19, x21);
  fiat_p256_mulx_u64(&x39, &x40, x1, (arg2[3]));
  fiat_p256_mulx_u64(&x41, &x42, x1, (arg2[2]));
  fiat_p256_mulx_u64(&x43, &x44, x1, (arg2[1]));
  fiat_p256_mulx_u64(&x45, &x46, x1, (arg2[0]));
  fiat_p256_addcarryx_u64(&x47, &x48, 0x0, x46, x43);
  fiat_p256_addcarryx_u64(&x49, &x50, x48, x44, x41);
  fiat_p256_addcarryx_u64(&x51, &x52, x50, x42, x39);
  x53 = (x52 + x40);
  fiat_p256_addcarryx_u64(&x54, &x55, 0x0, x31, x45);
  fiat_p256_addcarryx_u64(&x56, &x57, x55, x33, x47);
  fiat_p256_addcarryx_u64(&x58, &x59, x57, x35, x49);
  fiat_p256_addcarryx_u64(&x60, &x61, x59, x37, x51);
  fiat_p256_addcarryx_u64(&x62, &x63, x61, x38, x53);
  fiat_p256_mulx_u64(&x64, &x65, x54, UINT64_C(0xffffffff00000001));
  fiat_p256_mulx_u64(&x66, &x67, x54, UINT32_C(0xffffffff));
  fiat_p256_mulx_u64(&x68, &x69, x54, UINT64_C(0xffffffffffffffff));
  fiat_p256_addcarryx_u64(&x70, &x71, 0x0, x69, x66);
  x72 = (x71 + x67);
  fiat_p256_addcarryx_u64(&x73, &x74, 0x0, x54, x68);
  fiat_p256_addcarryx_u64(&x75, &x76, x74, x56, x70);
  fiat_p256_addcarryx_u64(&x77, &x78, x76, x58, x72);
  fiat_p256_addcarryx_u64(&x79, &x80, x78, x60, x64);
  fiat_p256_addcarryx_u64(&x81, &x82, x80, x62, x65);
  x83 = ((uint64_t)x82 + x63);
  fiat_p256_mulx_u64(&x84, &x85, x2, (arg2[3]));
  fiat_p256_mulx_u64(&x86, &x87, x2, (arg2[2]));
  fiat_p256_mulx_u64(&x88, &x89, x2, (arg2[1]));
  fiat_p256_mulx_u64(&x90, &x91, x2, (arg2[0]));
  fiat_p256_addcarryx_u64(&x92, &x93, 0x0, x91, x88);
  fiat_p256_addcarryx_u64(&x94, &x95, x93, x89, x86);
  fiat_p256_addcarryx_u64(&x96, &x97, x95, x87, x84);
  x98 = (x97 + x85);
  fiat_p256_addcarryx_u64(&x99, &x100, 0x0, x75, x90);
  fiat_p256_addcarryx_u64(&x101, &x102, x100, x77, x92);
  fiat_p256_addcarryx_u64(&x103, &x104, x102, x79, x94);
  fiat_p256_addcarryx_u64(&x105, &x106, x104, x81, x96);
  fiat_p256_addcarryx_u64(&x107, &x108, x106, x83, x98);
  fiat_p256_mulx_u64(&x109, &x110, x99, UINT64_C(0xffffffff00000001));
  fiat_p256_mulx_u64(&x111, &x112, x99, UINT32_C(0xffffffff));
  fiat_p256_mulx_u64(&x113, &x114, x99, UINT64_C(0xffffffffffffffff));
  fiat_p256_addcarryx_u64(&x115, &x116, 0x0, x114, x111);
  x117 = (x116 + x112);
  fiat_p256_addcarryx_u64(&x118, &x119, 0x0, x99, x113);
  fiat_p256_addcarryx_u64(&x120, &x121, x119, x101, x115);
  fiat_p256_addcarryx_u64(&x122, &x123, x121, x103, x117);
  fiat_p256_addcarryx_u64(&x124, &x125, x123, x105, x109);
  fiat_p256_addcarryx_u64(&x126, &x127, x125, x107, x110);
  x128 = ((uint64_t)x127 + x108);
  fiat_p256_mulx_u64(&x129, &x130, x3, (arg2[3]));
  fiat_p256_mulx_u64(&x131, &x132, x3, (arg2[2]));
  fiat_p256_mulx_u64(&x133, &x134, x3, (arg2[1]));
  fiat_p256_mulx_u64(&x135, &x136, x3, (arg2[0]));
  fiat_p256_addcarryx_u64(&x137, &x138, 0x0, x136, x133);
  fiat_p256_addcarryx_u64(&x139, &x140, x138, x134, x131);
  fiat_p256_addcarryx_u64(&x141, &x142, x140, x132, x129);
  x143 = (x142 + x130);
  fiat_p256_addcarryx_u64(&x144, &x145, 0x0, x120, x135);
  fiat_p256_addcarryx_u64(&x146, &x147, x145, x122, x137);
  fiat_p256_addcarryx_u64(&x148, &x149, x147, x124, x139);
  fiat_p256_addcarryx_u64(&x150, &x151, x149, x126, x141);
  fiat_p256_addcarryx_u64(&x152, &x153, x151, x128, x143);
  fiat_p256_mulx_u64(&x154, &x155, x144, UINT64_C(0xffffffff00000001));
  fiat_p256_mulx_u64(&x156, &x157, x144, UINT32_C(0xffffffff));
  fiat_p256_mulx_u64(&x158, &x159, x144, UINT64_C(0xffffffffffffffff));
  fiat_p256_addcarryx_u64(&x160, &x161, 0x0, x159, x156);
  x162 = (x161 + x157);
  fiat_p256_addcarryx_u64(&x163, &x164, 0x0, x144, x158);
  fiat_p256_addcarryx_u64(&x165, &x166, x164, x146, x160);
  fiat_p256_addcarryx_u64(&x167, &x168, x166, x148, x162);
  fiat_p256_addcarryx_u64(&x169, &x170, x168, x150, x154);
  fiat_p256_addcarryx_u64(&x171, &x172, x170, x152, x155);
  x173 = ((uint64_t)x172 + x153);
  fiat_p256_subborrowx_u64(&x174, &x175, 0x0, x165,
                           UINT64_C(0xffffffffffffffff));
  fiat_p256_subborrowx_u64(&x176, &x177, x175, x167, UINT32_C(0xffffffff));
  fiat_p256_subborrowx_u64(&x178, &x179, x177, x169, 0x0);
  fiat_p256_subborrowx_u64(&x180, &x181, x179, x171,
                           UINT64_C(0xffffffff00000001));
  fiat_p256_subborrowx_u64(&x182, &x183, x181, x173, 0x0);
  fiat_p256_cmovznz_u64(&x184, x183, x174, x165);
  fiat_p256_cmovznz_u64(&x185, x183, x176, x167);
  fiat_p256_cmovznz_u64(&x186, x183, x178, x169);
  fiat_p256_cmovznz_u64(&x187, x183, x180, x171);
  out1[0] = x184;
  out1[1] = x185;
  out1[2] = x186;
  out1[3] = x187;
}

/*
 * The function fiat_p256_square squares a field element in the Montgomery
 * domain. Preconditions: 0 ≤ eval arg1 < m Postconditions: eval
 * (from_montgomery out1) mod m = (eval (from_montgomery arg1) * eval
 * (from_montgomery arg1)) mod m 0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]] Output Bounds: out1: [[0x0
 * ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
void fiat_p256_square(uint64_t out1[4], const uint64_t arg1[4]) {
  uint64_t x1;
  uint64_t x2;
  uint64_t x3;
  uint64_t x4;
  uint64_t x5;
  uint64_t x6;
  uint64_t x7;
  uint64_t x8;
  uint64_t x9;
  uint64_t x10;
  uint64_t x11;
  uint64_t x12;
  uint64_t x13;
  fiat_p256_uint1 x14;
  uint64_t x15;
  fiat_p256_uint1 x16;
  uint64_t x17;
  fiat_p256_uint1 x18;
  uint64_t x19;
  uint64_t x20;
  uint64_t x21;
  uint64_t x22;
  uint64_t x23;
  uint64_t x24;
  uint64_t x25;
  uint64_t x26;
  fiat_p256_uint1 x27;
  uint64_t x28;
  uint64_t x29;
  fiat_p256_uint1 x30;
  uint64_t x31;
  fiat_p256_uint1 x32;
  uint64_t x33;
  fiat_p256_uint1 x34;
  uint64_t x35;
  fiat_p256_uint1 x36;
  uint64_t x37;
  fiat_p256_uint1 x38;
  uint64_t x39;
  uint64_t x40;
  uint64_t x41;
  uint64_t x42;
  uint64_t x43;
  uint64_t x44;
  uint64_t x45;
  uint64_t x46;
  uint64_t x47;
  fiat_p256_uint1 x48;
  uint64_t x49;
  fiat_p256_uint1 x50;
  uint64_t x51;
  fiat_p256_uint1 x52;
  uint64_t x53;
  uint64_t x54;
  fiat_p256_uint1 x55;
  uint64_t x56;
  fiat_p256_uint1 x57;
  uint64_t x58;
  fiat_p256_uint1 x59;
  uint64_t x60;
  fiat_p256_uint1 x61;
  uint64_t x62;
  fiat_p256_uint1 x63;
  uint64_t x64;
  uint64_t x65;
  uint64_t x66;
  uint64_t x67;
  uint64_t x68;
  uint64_t x69;
  uint64_t x70;
  fiat_p256_uint1 x71;
  uint64_t x72;
  uint64_t x73;
  fiat_p256_uint1 x74;
  uint64_t x75;
  fiat_p256_uint1 x76;
  uint64_t x77;
  fiat_p256_uint1 x78;
  uint64_t x79;
  fiat_p256_uint1 x80;
  uint64_t x81;
  fiat_p256_uint1 x82;
  uint64_t x83;
  uint64_t x84;
  uint64_t x85;
  uint64_t x86;
  uint64_t x87;
  uint64_t x88;
  uint64_t x89;
  uint64_t x90;
  uint64_t x91;
  uint64_t x92;
  fiat_p256_uint1 x93;
  uint64_t x94;
  fiat_p256_uint1 x95;
  uint64_t x96;
  fiat_p256_uint1 x97;
  uint64_t x98;
  uint64_t x99;
  fiat_p256_uint1 x100;
  uint64_t x101;
  fiat_p256_uint1 x102;
  uint64_t x103;
  fiat_p256_uint1 x104;
  uint64_t x105;
  fiat_p256_uint1 x106;
  uint64_t x107;
  fiat_p256_uint1 x108;
  uint64_t x109;
  uint64_t x110;
  uint64_t x111;
  uint64_t x112;
  uint64_t x113;
  uint64_t x114;
  uint64_t x115;
  fiat_p256_uint1 x116;
  uint64_t x117;
  uint64_t x118;
  fiat_p256_uint1 x119;
  uint64_t x120;
  fiat_p256_uint1 x121;
  uint64_t x122;
  fiat_p256_uint1 x123;
  uint64_t x124;
  fiat_p256_uint1 x125;
  uint64_t x126;
  fiat_p256_uint1 x127;
  uint64_t x128;
  uint64_t x129;
  uint64_t x130;
  uint64_t x131;
  uint64_t x132;
  uint64_t x133;
  uint64_t x134;
  uint64_t x135;
  uint64_t x136;
  uint64_t x137;
  fiat_p256_uint1 x138;
  uint64_t x139;
  fiat_p256_uint1 x140;
  uint64_t x141;
  fiat_p256_uint1 x142;
  uint64_t x143;
  uint64_t x144;
  fiat_p256_uint1 x145;
  uint64_t x146;
  fiat_p256_uint1 x147;
  uint64_t x148;
  fiat_p256_uint1 x149;
  uint64_t x150;
  fiat_p256_uint1 x151;
  uint64_t x152;
  fiat_p256_uint1 x153;
  uint64_t x154;
  uint64_t x155;
  uint64_t x156;
  uint64_t x157;
  uint64_t x158;
  uint64_t x159;
  uint64_t x160;
  fiat_p256_uint1 x161;
  uint64_t x162;
  uint64_t x163;
  fiat_p256_uint1 x164;
  uint64_t x165;
  fiat_p256_uint1 x166;
  uint64_t x167;
  fiat_p256_uint1 x168;
  uint64_t x169;
  fiat_p256_uint1 x170;
  uint64_t x171;
  fiat_p256_uint1 x172;
  uint64_t x173;
  uint64_t x174;
  fiat_p256_uint1 x175;
  uint64_t x176;
  fiat_p256_uint1 x177;
  uint64_t x178;
  fiat_p256_uint1 x179;
  uint64_t x180;
  fiat_p256_uint1 x181;
  uint64_t x182;
  fiat_p256_uint1 x183;
  uint64_t x184;
  uint64_t x185;
  uint64_t x186;
  uint64_t x187;
  x1 = (arg1[1]);
  x2 = (arg1[2]);
  x3 = (arg1[3]);
  x4 = (arg1[0]);
  fiat_p256_mulx_u64(&x5, &x6, x4, (arg1[3]));
  fiat_p256_mulx_u64(&x7, &x8, x4, (arg1[2]));
  fiat_p256_mulx_u64(&x9, &x10, x4, (arg1[1]));
  fiat_p256_mulx_u64(&x11, &x12, x4, (arg1[0]));
  fiat_p256_addcarryx_u64(&x13, &x14, 0x0, x12, x9);
  fiat_p256_addcarryx_u64(&x15, &x16, x14, x10, x7);
  fiat_p256_addcarryx_u64(&x17, &x18, x16, x8, x5);
  x19 = (x18 + x6);
  fiat_p256_mulx_u64(&x20, &x21, x11, UINT64_C(0xffffffff00000001));
  fiat_p256_mulx_u64(&x22, &x23, x11, UINT32_C(0xffffffff));
  fiat_p256_mulx_u64(&x24, &x25, x11, UINT64_C(0xffffffffffffffff));
  fiat_p256_addcarryx_u64(&x26, &x27, 0x0, x25, x22);
  x28 = (x27 + x23);
  fiat_p256_addcarryx_u64(&x29, &x30, 0x0, x11, x24);
  fiat_p256_addcarryx_u64(&x31, &x32, x30, x13, x26);
  fiat_p256_addcarryx_u64(&x33, &x34, x32, x15, x28);
  fiat_p256_addcarryx_u64(&x35, &x36, x34, x17, x20);
  fiat_p256_addcarryx_u64(&x37, &x38, x36, x19, x21);
  fiat_p256_mulx_u64(&x39, &x40, x1, (arg1[3]));
  fiat_p256_mulx_u64(&x41, &x42, x1, (arg1[2]));
  fiat_p256_mulx_u64(&x43, &x44, x1, (arg1[1]));
  fiat_p256_mulx_u64(&x45, &x46, x1, (arg1[0]));
  fiat_p256_addcarryx_u64(&x47, &x48, 0x0, x46, x43);
  fiat_p256_addcarryx_u64(&x49, &x50, x48, x44, x41);
  fiat_p256_addcarryx_u64(&x51, &x52, x50, x42, x39);
  x53 = (x52 + x40);
  fiat_p256_addcarryx_u64(&x54, &x55, 0x0, x31, x45);
  fiat_p256_addcarryx_u64(&x56, &x57, x55, x33, x47);
  fiat_p256_addcarryx_u64(&x58, &x59, x57, x35, x49);
  fiat_p256_addcarryx_u64(&x60, &x61, x59, x37, x51);
  fiat_p256_addcarryx_u64(&x62, &x63, x61, x38, x53);
  fiat_p256_mulx_u64(&x64, &x65, x54, UINT64_C(0xffffffff00000001));
  fiat_p256_mulx_u64(&x66, &x67, x54, UINT32_C(0xffffffff));
  fiat_p256_mulx_u64(&x68, &x69, x54, UINT64_C(0xffffffffffffffff));
  fiat_p256_addcarryx_u64(&x70, &x71, 0x0, x69, x66);
  x72 = (x71 + x67);
  fiat_p256_addcarryx_u64(&x73, &x74, 0x0, x54, x68);
  fiat_p256_addcarryx_u64(&x75, &x76, x74, x56, x70);
  fiat_p256_addcarryx_u64(&x77, &x78, x76, x58, x72);
  fiat_p256_addcarryx_u64(&x79, &x80, x78, x60, x64);
  fiat_p256_addcarryx_u64(&x81, &x82, x80, x62, x65);
  x83 = ((uint64_t)x82 + x63);
  fiat_p256_mulx_u64(&x84, &x85, x2, (arg1[3]));
  fiat_p256_mulx_u64(&x86, &x87, x2, (arg1[2]));
  fiat_p256_mulx_u64(&x88, &x89, x2, (arg1[1]));
  fiat_p256_mulx_u64(&x90, &x91, x2, (arg1[0]));
  fiat_p256_addcarryx_u64(&x92, &x93, 0x0, x91, x88);
  fiat_p256_addcarryx_u64(&x94, &x95, x93, x89, x86);
  fiat_p256_addcarryx_u64(&x96, &x97, x95, x87, x84);
  x98 = (x97 + x85);
  fiat_p256_addcarryx_u64(&x99, &x100, 0x0, x75, x90);
  fiat_p256_addcarryx_u64(&x101, &x102, x100, x77, x92);
  fiat_p256_addcarryx_u64(&x103, &x104, x102, x79, x94);
  fiat_p256_addcarryx_u64(&x105, &x106, x104, x81, x96);
  fiat_p256_addcarryx_u64(&x107, &x108, x106, x83, x98);
  fiat_p256_mulx_u64(&x109, &x110, x99, UINT64_C(0xffffffff00000001));
  fiat_p256_mulx_u64(&x111, &x112, x99, UINT32_C(0xffffffff));
  fiat_p256_mulx_u64(&x113, &x114, x99, UINT64_C(0xffffffffffffffff));
  fiat_p256_addcarryx_u64(&x115, &x116, 0x0, x114, x111);
  x117 = (x116 + x112);
  fiat_p256_addcarryx_u64(&x118, &x119, 0x0, x99, x113);
  fiat_p256_addcarryx_u64(&x120, &x121, x119, x101, x115);
  fiat_p256_addcarryx_u64(&x122, &x123, x121, x103, x117);
  fiat_p256_addcarryx_u64(&x124, &x125, x123, x105, x109);
  fiat_p256_addcarryx_u64(&x126, &x127, x125, x107, x110);
  x128 = ((uint64_t)x127 + x108);
  fiat_p256_mulx_u64(&x129, &x130, x3, (arg1[3]));
  fiat_p256_mulx_u64(&x131, &x132, x3, (arg1[2]));
  fiat_p256_mulx_u64(&x133, &x134, x3, (arg1[1]));
  fiat_p256_mulx_u64(&x135, &x136, x3, (arg1[0]));
  fiat_p256_addcarryx_u64(&x137, &x138, 0x0, x136, x133);
  fiat_p256_addcarryx_u64(&x139, &x140, x138, x134, x131);
  fiat_p256_addcarryx_u64(&x141, &x142, x140, x132, x129);
  x143 = (x142 + x130);
  fiat_p256_addcarryx_u64(&x144, &x145, 0x0, x120, x135);
  fiat_p256_addcarryx_u64(&x146, &x147, x145, x122, x137);
  fiat_p256_addcarryx_u64(&x148, &x149, x147, x124, x139);
  fiat_p256_addcarryx_u64(&x150, &x151, x149, x126, x141);
  fiat_p256_addcarryx_u64(&x152, &x153, x151, x128, x143);
  fiat_p256_mulx_u64(&x154, &x155, x144, UINT64_C(0xffffffff00000001));
  fiat_p256_mulx_u64(&x156, &x157, x144, UINT32_C(0xffffffff));
  fiat_p256_mulx_u64(&x158, &x159, x144, UINT64_C(0xffffffffffffffff));
  fiat_p256_addcarryx_u64(&x160, &x161, 0x0, x159, x156);
  x162 = (x161 + x157);
  fiat_p256_addcarryx_u64(&x163, &x164, 0x0, x144, x158);
  fiat_p256_addcarryx_u64(&x165, &x166, x164, x146, x160);
  fiat_p256_addcarryx_u64(&x167, &x168, x166, x148, x162);
  fiat_p256_addcarryx_u64(&x169, &x170, x168, x150, x154);
  fiat_p256_addcarryx_u64(&x171, &x172, x170, x152, x155);
  x173 = ((uint64_t)x172 + x153);
  fiat_p256_subborrowx_u64(&x174, &x175, 0x0, x165,
                           UINT64_C(0xffffffffffffffff));
  fiat_p256_subborrowx_u64(&x176, &x177, x175, x167, UINT32_C(0xffffffff));
  fiat_p256_subborrowx_u64(&x178, &x179, x177, x169, 0x0);
  fiat_p256_subborrowx_u64(&x180, &x181, x179, x171,
                           UINT64_C(0xffffffff00000001));
  fiat_p256_subborrowx_u64(&x182, &x183, x181, x173, 0x0);
  fiat_p256_cmovznz_u64(&x184, x183, x174, x165);
  fiat_p256_cmovznz_u64(&x185, x183, x176, x167);
  fiat_p256_cmovznz_u64(&x186, x183, x178, x169);
  fiat_p256_cmovznz_u64(&x187, x183, x180, x171);
  out1[0] = x184;
  out1[1] = x185;
  out1[2] = x186;
  out1[3] = x187;
}

/* curve description: p384 */
/* machine_wordsize = 64 (from "64") */
/* requested operations: mul, square */
/* m =
 * 0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffeffffffff0000000000000000ffffffff
 * (from "2^384 - 2^128 - 2^96 + 2^32 - 1") */
/*                                                                    */
/* NOTE: In addition to the bounds specified above each function, all */
/*   functions synthesized for this Montgomery arithmetic require the */
/*   input to be strictly less than the prime modulus (m), and also   */
/*   require the input to be in the unique saturated representation.  */
/*   All functions also ensure that these two properties are true of  */
/*   return values.                                                   */
/*  */
/* Computed values: */
/* eval z = z[0] + (z[1] << 64) + (z[2] << 128) + (z[3] << 192) + (z[4] << 256)
 * + (z[5] << 0x140) */
/* bytes_eval z = z[0] + (z[1] << 8) + (z[2] << 16) + (z[3] << 24) + (z[4] <<
 * 32) + (z[5] << 40) + (z[6] << 48) + (z[7] << 56) + (z[8] << 64) + (z[9] <<
 * 72) + (z[10] << 80) + (z[11] << 88) + (z[12] << 96) + (z[13] << 104) + (z[14]
 * << 112) + (z[15] << 120) + (z[16] << 128) + (z[17] << 136) + (z[18] << 144) +
 * (z[19] << 152) + (z[20] << 160) + (z[21] << 168) + (z[22] << 176) + (z[23] <<
 * 184) + (z[24] << 192) + (z[25] << 200) + (z[26] << 208) + (z[27] << 216) +
 * (z[28] << 224) + (z[29] << 232) + (z[30] << 240) + (z[31] << 248) + (z[32] <<
 * 256) + (z[33] << 0x108) + (z[34] << 0x110) + (z[35] << 0x118) + (z[36] <<
 * 0x120) + (z[37] << 0x128) + (z[38] << 0x130) + (z[39] << 0x138) + (z[40] <<
 * 0x140) + (z[41] << 0x148) + (z[42] << 0x150) + (z[43] << 0x158) + (z[44] <<
 * 0x160) + (z[45] << 0x168) + (z[46] << 0x170) + (z[47] << 0x178) */

#include <stdint.h>
typedef unsigned char fiat_p384_uint1;
typedef signed char fiat_p384_int1;
typedef signed __int128 fiat_p384_int128;
typedef unsigned __int128 fiat_p384_uint128;

#if (-1 & 3) != 3
#error "This code only works on a two's complement system"
#endif

/*
 * The function fiat_p384_addcarryx_u64 is an addition with carry.
 * Postconditions:
 *   out1 = (arg1 + arg2 + arg3) mod 2^64
 *   out2 = ⌊(arg1 + arg2 + arg3) / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0x1]
 */
void fiat_p384_addcarryx_u64(uint64_t *out1, fiat_p384_uint1 *out2,
                             fiat_p384_uint1 arg1, uint64_t arg2,
                             uint64_t arg3) {
  fiat_p384_uint128 x1;
  uint64_t x2;
  fiat_p384_uint1 x3;
  x1 = ((arg1 + (fiat_p384_uint128)arg2) + arg3);
  x2 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  x3 = (fiat_p384_uint1)(x1 >> 64);
  *out1 = x2;
  *out2 = x3;
}

/*
 * The function fiat_p384_subborrowx_u64 is a subtraction with borrow.
 * Postconditions:
 *   out1 = (-arg1 + arg2 + -arg3) mod 2^64
 *   out2 = -⌊(-arg1 + arg2 + -arg3) / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0x1]
 */
void fiat_p384_subborrowx_u64(uint64_t *out1, fiat_p384_uint1 *out2,
                              fiat_p384_uint1 arg1, uint64_t arg2,
                              uint64_t arg3) {
  fiat_p384_int128 x1;
  fiat_p384_int1 x2;
  uint64_t x3;
  x1 = ((arg2 - (fiat_p384_int128)arg1) - arg3);
  x2 = (fiat_p384_int1)(x1 >> 64);
  x3 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  *out1 = x3;
  *out2 = (fiat_p384_uint1)(0x0 - x2);
}

/*
 * The function fiat_p384_mulx_u64 is a multiplication, returning the full
 * double-width result. Postconditions: out1 = (arg1 * arg2) mod 2^64 out2 =
 * ⌊arg1 * arg2 / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0xffffffffffffffff]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0xffffffffffffffff]
 */
void fiat_p384_mulx_u64(uint64_t *out1, uint64_t *out2, uint64_t arg1,
                        uint64_t arg2) {
  fiat_p384_uint128 x1;
  uint64_t x2;
  uint64_t x3;
  x1 = ((fiat_p384_uint128)arg1 * arg2);
  x2 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  x3 = (uint64_t)(x1 >> 64);
  *out1 = x2;
  *out2 = x3;
}

/*
 * The function fiat_p384_cmovznz_u64 is a single-word conditional move.
 * Postconditions:
 *   out1 = (if arg1 = 0 then arg2 else arg3)
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 */
void fiat_p384_cmovznz_u64(uint64_t *out1, fiat_p384_uint1 arg1, uint64_t arg2,
                           uint64_t arg3) {
  fiat_p384_uint1 x1;
  uint64_t x2;
  uint64_t x3;
  x1 = (!(!arg1));
  x2 = ((fiat_p384_int1)(0x0 - x1) & UINT64_C(0xffffffffffffffff));
  x3 = ((x2 & arg3) | ((~x2) & arg2));
  *out1 = x3;
}

/*
 * The function fiat_p384_mul multiplies two field elements in the Montgomery
 * domain. Preconditions: 0 ≤ eval arg1 < m 0 ≤ eval arg2 < m Postconditions:
 *   eval (from_montgomery out1) mod m = (eval (from_montgomery arg1) * eval
 * (from_montgomery arg2)) mod m 0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]] arg2: [[0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]] Output Bounds: out1: [[0x0
 * ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
void fiat_p384_mul(uint64_t out1[6], const uint64_t arg1[6],
                   const uint64_t arg2[6]) {
  uint64_t x1;
  uint64_t x2;
  uint64_t x3;
  uint64_t x4;
  uint64_t x5;
  uint64_t x6;
  uint64_t x7;
  uint64_t x8;
  uint64_t x9;
  uint64_t x10;
  uint64_t x11;
  uint64_t x12;
  uint64_t x13;
  uint64_t x14;
  uint64_t x15;
  uint64_t x16;
  uint64_t x17;
  uint64_t x18;
  uint64_t x19;
  fiat_p384_uint1 x20;
  uint64_t x21;
  fiat_p384_uint1 x22;
  uint64_t x23;
  fiat_p384_uint1 x24;
  uint64_t x25;
  fiat_p384_uint1 x26;
  uint64_t x27;
  fiat_p384_uint1 x28;
  uint64_t x29;
  uint64_t x30;
  uint64_t x31;
  uint64_t x32;
  uint64_t x33;
  uint64_t x34;
  uint64_t x35;
  uint64_t x36;
  uint64_t x37;
  uint64_t x38;
  uint64_t x39;
  uint64_t x40;
  uint64_t x41;
  uint64_t x42;
  uint64_t x43;
  uint64_t x44;
  fiat_p384_uint1 x45;
  uint64_t x46;
  fiat_p384_uint1 x47;
  uint64_t x48;
  fiat_p384_uint1 x49;
  uint64_t x50;
  fiat_p384_uint1 x51;
  uint64_t x52;
  fiat_p384_uint1 x53;
  uint64_t x54;
  uint64_t x55;
  fiat_p384_uint1 x56;
  uint64_t x57;
  fiat_p384_uint1 x58;
  uint64_t x59;
  fiat_p384_uint1 x60;
  uint64_t x61;
  fiat_p384_uint1 x62;
  uint64_t x63;
  fiat_p384_uint1 x64;
  uint64_t x65;
  fiat_p384_uint1 x66;
  uint64_t x67;
  fiat_p384_uint1 x68;
  uint64_t x69;
  uint64_t x70;
  uint64_t x71;
  uint64_t x72;
  uint64_t x73;
  uint64_t x74;
  uint64_t x75;
  uint64_t x76;
  uint64_t x77;
  uint64_t x78;
  uint64_t x79;
  uint64_t x80;
  uint64_t x81;
  fiat_p384_uint1 x82;
  uint64_t x83;
  fiat_p384_uint1 x84;
  uint64_t x85;
  fiat_p384_uint1 x86;
  uint64_t x87;
  fiat_p384_uint1 x88;
  uint64_t x89;
  fiat_p384_uint1 x90;
  uint64_t x91;
  uint64_t x92;
  fiat_p384_uint1 x93;
  uint64_t x94;
  fiat_p384_uint1 x95;
  uint64_t x96;
  fiat_p384_uint1 x97;
  uint64_t x98;
  fiat_p384_uint1 x99;
  uint64_t x100;
  fiat_p384_uint1 x101;
  uint64_t x102;
  fiat_p384_uint1 x103;
  uint64_t x104;
  fiat_p384_uint1 x105;
  uint64_t x106;
  uint64_t x107;
  uint64_t x108;
  uint64_t x109;
  uint64_t x110;
  uint64_t x111;
  uint64_t x112;
  uint64_t x113;
  uint64_t x114;
  uint64_t x115;
  uint64_t x116;
  uint64_t x117;
  uint64_t x118;
  uint64_t x119;
  uint64_t x120;
  fiat_p384_uint1 x121;
  uint64_t x122;
  fiat_p384_uint1 x123;
  uint64_t x124;
  fiat_p384_uint1 x125;
  uint64_t x126;
  fiat_p384_uint1 x127;
  uint64_t x128;
  fiat_p384_uint1 x129;
  uint64_t x130;
  uint64_t x131;
  fiat_p384_uint1 x132;
  uint64_t x133;
  fiat_p384_uint1 x134;
  uint64_t x135;
  fiat_p384_uint1 x136;
  uint64_t x137;
  fiat_p384_uint1 x138;
  uint64_t x139;
  fiat_p384_uint1 x140;
  uint64_t x141;
  fiat_p384_uint1 x142;
  uint64_t x143;
  fiat_p384_uint1 x144;
  uint64_t x145;
  uint64_t x146;
  uint64_t x147;
  uint64_t x148;
  uint64_t x149;
  uint64_t x150;
  uint64_t x151;
  uint64_t x152;
  uint64_t x153;
  uint64_t x154;
  uint64_t x155;
  uint64_t x156;
  uint64_t x157;
  uint64_t x158;
  fiat_p384_uint1 x159;
  uint64_t x160;
  fiat_p384_uint1 x161;
  uint64_t x162;
  fiat_p384_uint1 x163;
  uint64_t x164;
  fiat_p384_uint1 x165;
  uint64_t x166;
  fiat_p384_uint1 x167;
  uint64_t x168;
  uint64_t x169;
  fiat_p384_uint1 x170;
  uint64_t x171;
  fiat_p384_uint1 x172;
  uint64_t x173;
  fiat_p384_uint1 x174;
  uint64_t x175;
  fiat_p384_uint1 x176;
  uint64_t x177;
  fiat_p384_uint1 x178;
  uint64_t x179;
  fiat_p384_uint1 x180;
  uint64_t x181;
  fiat_p384_uint1 x182;
  uint64_t x183;
  uint64_t x184;
  uint64_t x185;
  uint64_t x186;
  uint64_t x187;
  uint64_t x188;
  uint64_t x189;
  uint64_t x190;
  uint64_t x191;
  uint64_t x192;
  uint64_t x193;
  uint64_t x194;
  uint64_t x195;
  uint64_t x196;
  uint64_t x197;
  fiat_p384_uint1 x198;
  uint64_t x199;
  fiat_p384_uint1 x200;
  uint64_t x201;
  fiat_p384_uint1 x202;
  uint64_t x203;
  fiat_p384_uint1 x204;
  uint64_t x205;
  fiat_p384_uint1 x206;
  uint64_t x207;
  uint64_t x208;
  fiat_p384_uint1 x209;
  uint64_t x210;
  fiat_p384_uint1 x211;
  uint64_t x212;
  fiat_p384_uint1 x213;
  uint64_t x214;
  fiat_p384_uint1 x215;
  uint64_t x216;
  fiat_p384_uint1 x217;
  uint64_t x218;
  fiat_p384_uint1 x219;
  uint64_t x220;
  fiat_p384_uint1 x221;
  uint64_t x222;
  uint64_t x223;
  uint64_t x224;
  uint64_t x225;
  uint64_t x226;
  uint64_t x227;
  uint64_t x228;
  uint64_t x229;
  uint64_t x230;
  uint64_t x231;
  uint64_t x232;
  uint64_t x233;
  uint64_t x234;
  uint64_t x235;
  fiat_p384_uint1 x236;
  uint64_t x237;
  fiat_p384_uint1 x238;
  uint64_t x239;
  fiat_p384_uint1 x240;
  uint64_t x241;
  fiat_p384_uint1 x242;
  uint64_t x243;
  fiat_p384_uint1 x244;
  uint64_t x245;
  uint64_t x246;
  fiat_p384_uint1 x247;
  uint64_t x248;
  fiat_p384_uint1 x249;
  uint64_t x250;
  fiat_p384_uint1 x251;
  uint64_t x252;
  fiat_p384_uint1 x253;
  uint64_t x254;
  fiat_p384_uint1 x255;
  uint64_t x256;
  fiat_p384_uint1 x257;
  uint64_t x258;
  fiat_p384_uint1 x259;
  uint64_t x260;
  uint64_t x261;
  uint64_t x262;
  uint64_t x263;
  uint64_t x264;
  uint64_t x265;
  uint64_t x266;
  uint64_t x267;
  uint64_t x268;
  uint64_t x269;
  uint64_t x270;
  uint64_t x271;
  uint64_t x272;
  uint64_t x273;
  uint64_t x274;
  fiat_p384_uint1 x275;
  uint64_t x276;
  fiat_p384_uint1 x277;
  uint64_t x278;
  fiat_p384_uint1 x279;
  uint64_t x280;
  fiat_p384_uint1 x281;
  uint64_t x282;
  fiat_p384_uint1 x283;
  uint64_t x284;
  uint64_t x285;
  fiat_p384_uint1 x286;
  uint64_t x287;
  fiat_p384_uint1 x288;
  uint64_t x289;
  fiat_p384_uint1 x290;
  uint64_t x291;
  fiat_p384_uint1 x292;
  uint64_t x293;
  fiat_p384_uint1 x294;
  uint64_t x295;
  fiat_p384_uint1 x296;
  uint64_t x297;
  fiat_p384_uint1 x298;
  uint64_t x299;
  uint64_t x300;
  uint64_t x301;
  uint64_t x302;
  uint64_t x303;
  uint64_t x304;
  uint64_t x305;
  uint64_t x306;
  uint64_t x307;
  uint64_t x308;
  uint64_t x309;
  uint64_t x310;
  uint64_t x311;
  uint64_t x312;
  fiat_p384_uint1 x313;
  uint64_t x314;
  fiat_p384_uint1 x315;
  uint64_t x316;
  fiat_p384_uint1 x317;
  uint64_t x318;
  fiat_p384_uint1 x319;
  uint64_t x320;
  fiat_p384_uint1 x321;
  uint64_t x322;
  uint64_t x323;
  fiat_p384_uint1 x324;
  uint64_t x325;
  fiat_p384_uint1 x326;
  uint64_t x327;
  fiat_p384_uint1 x328;
  uint64_t x329;
  fiat_p384_uint1 x330;
  uint64_t x331;
  fiat_p384_uint1 x332;
  uint64_t x333;
  fiat_p384_uint1 x334;
  uint64_t x335;
  fiat_p384_uint1 x336;
  uint64_t x337;
  uint64_t x338;
  uint64_t x339;
  uint64_t x340;
  uint64_t x341;
  uint64_t x342;
  uint64_t x343;
  uint64_t x344;
  uint64_t x345;
  uint64_t x346;
  uint64_t x347;
  uint64_t x348;
  uint64_t x349;
  uint64_t x350;
  uint64_t x351;
  fiat_p384_uint1 x352;
  uint64_t x353;
  fiat_p384_uint1 x354;
  uint64_t x355;
  fiat_p384_uint1 x356;
  uint64_t x357;
  fiat_p384_uint1 x358;
  uint64_t x359;
  fiat_p384_uint1 x360;
  uint64_t x361;
  uint64_t x362;
  fiat_p384_uint1 x363;
  uint64_t x364;
  fiat_p384_uint1 x365;
  uint64_t x366;
  fiat_p384_uint1 x367;
  uint64_t x368;
  fiat_p384_uint1 x369;
  uint64_t x370;
  fiat_p384_uint1 x371;
  uint64_t x372;
  fiat_p384_uint1 x373;
  uint64_t x374;
  fiat_p384_uint1 x375;
  uint64_t x376;
  uint64_t x377;
  uint64_t x378;
  uint64_t x379;
  uint64_t x380;
  uint64_t x381;
  uint64_t x382;
  uint64_t x383;
  uint64_t x384;
  uint64_t x385;
  uint64_t x386;
  uint64_t x387;
  uint64_t x388;
  uint64_t x389;
  fiat_p384_uint1 x390;
  uint64_t x391;
  fiat_p384_uint1 x392;
  uint64_t x393;
  fiat_p384_uint1 x394;
  uint64_t x395;
  fiat_p384_uint1 x396;
  uint64_t x397;
  fiat_p384_uint1 x398;
  uint64_t x399;
  uint64_t x400;
  fiat_p384_uint1 x401;
  uint64_t x402;
  fiat_p384_uint1 x403;
  uint64_t x404;
  fiat_p384_uint1 x405;
  uint64_t x406;
  fiat_p384_uint1 x407;
  uint64_t x408;
  fiat_p384_uint1 x409;
  uint64_t x410;
  fiat_p384_uint1 x411;
  uint64_t x412;
  fiat_p384_uint1 x413;
  uint64_t x414;
  uint64_t x415;
  uint64_t x416;
  uint64_t x417;
  uint64_t x418;
  uint64_t x419;
  uint64_t x420;
  uint64_t x421;
  uint64_t x422;
  uint64_t x423;
  uint64_t x424;
  uint64_t x425;
  uint64_t x426;
  uint64_t x427;
  uint64_t x428;
  fiat_p384_uint1 x429;
  uint64_t x430;
  fiat_p384_uint1 x431;
  uint64_t x432;
  fiat_p384_uint1 x433;
  uint64_t x434;
  fiat_p384_uint1 x435;
  uint64_t x436;
  fiat_p384_uint1 x437;
  uint64_t x438;
  uint64_t x439;
  fiat_p384_uint1 x440;
  uint64_t x441;
  fiat_p384_uint1 x442;
  uint64_t x443;
  fiat_p384_uint1 x444;
  uint64_t x445;
  fiat_p384_uint1 x446;
  uint64_t x447;
  fiat_p384_uint1 x448;
  uint64_t x449;
  fiat_p384_uint1 x450;
  uint64_t x451;
  fiat_p384_uint1 x452;
  uint64_t x453;
  uint64_t x454;
  fiat_p384_uint1 x455;
  uint64_t x456;
  fiat_p384_uint1 x457;
  uint64_t x458;
  fiat_p384_uint1 x459;
  uint64_t x460;
  fiat_p384_uint1 x461;
  uint64_t x462;
  fiat_p384_uint1 x463;
  uint64_t x464;
  fiat_p384_uint1 x465;
  uint64_t x466;
  fiat_p384_uint1 x467;
  uint64_t x468;
  uint64_t x469;
  uint64_t x470;
  uint64_t x471;
  uint64_t x472;
  uint64_t x473;
  x1 = (arg1[1]);
  x2 = (arg1[2]);
  x3 = (arg1[3]);
  x4 = (arg1[4]);
  x5 = (arg1[5]);
  x6 = (arg1[0]);
  fiat_p384_mulx_u64(&x7, &x8, x6, (arg2[5]));
  fiat_p384_mulx_u64(&x9, &x10, x6, (arg2[4]));
  fiat_p384_mulx_u64(&x11, &x12, x6, (arg2[3]));
  fiat_p384_mulx_u64(&x13, &x14, x6, (arg2[2]));
  fiat_p384_mulx_u64(&x15, &x16, x6, (arg2[1]));
  fiat_p384_mulx_u64(&x17, &x18, x6, (arg2[0]));
  fiat_p384_addcarryx_u64(&x19, &x20, 0x0, x18, x15);
  fiat_p384_addcarryx_u64(&x21, &x22, x20, x16, x13);
  fiat_p384_addcarryx_u64(&x23, &x24, x22, x14, x11);
  fiat_p384_addcarryx_u64(&x25, &x26, x24, x12, x9);
  fiat_p384_addcarryx_u64(&x27, &x28, x26, x10, x7);
  x29 = (x28 + x8);
  fiat_p384_mulx_u64(&x30, &x31, x17, UINT64_C(0x100000001));
  fiat_p384_mulx_u64(&x32, &x33, x30, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x34, &x35, x30, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x36, &x37, x30, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x38, &x39, x30, UINT64_C(0xfffffffffffffffe));
  fiat_p384_mulx_u64(&x40, &x41, x30, UINT64_C(0xffffffff00000000));
  fiat_p384_mulx_u64(&x42, &x43, x30, UINT32_C(0xffffffff));
  fiat_p384_addcarryx_u64(&x44, &x45, 0x0, x43, x40);
  fiat_p384_addcarryx_u64(&x46, &x47, x45, x41, x38);
  fiat_p384_addcarryx_u64(&x48, &x49, x47, x39, x36);
  fiat_p384_addcarryx_u64(&x50, &x51, x49, x37, x34);
  fiat_p384_addcarryx_u64(&x52, &x53, x51, x35, x32);
  x54 = (x53 + x33);
  fiat_p384_addcarryx_u64(&x55, &x56, 0x0, x17, x42);
  fiat_p384_addcarryx_u64(&x57, &x58, x56, x19, x44);
  fiat_p384_addcarryx_u64(&x59, &x60, x58, x21, x46);
  fiat_p384_addcarryx_u64(&x61, &x62, x60, x23, x48);
  fiat_p384_addcarryx_u64(&x63, &x64, x62, x25, x50);
  fiat_p384_addcarryx_u64(&x65, &x66, x64, x27, x52);
  fiat_p384_addcarryx_u64(&x67, &x68, x66, x29, x54);
  fiat_p384_mulx_u64(&x69, &x70, x1, (arg2[5]));
  fiat_p384_mulx_u64(&x71, &x72, x1, (arg2[4]));
  fiat_p384_mulx_u64(&x73, &x74, x1, (arg2[3]));
  fiat_p384_mulx_u64(&x75, &x76, x1, (arg2[2]));
  fiat_p384_mulx_u64(&x77, &x78, x1, (arg2[1]));
  fiat_p384_mulx_u64(&x79, &x80, x1, (arg2[0]));
  fiat_p384_addcarryx_u64(&x81, &x82, 0x0, x80, x77);
  fiat_p384_addcarryx_u64(&x83, &x84, x82, x78, x75);
  fiat_p384_addcarryx_u64(&x85, &x86, x84, x76, x73);
  fiat_p384_addcarryx_u64(&x87, &x88, x86, x74, x71);
  fiat_p384_addcarryx_u64(&x89, &x90, x88, x72, x69);
  x91 = (x90 + x70);
  fiat_p384_addcarryx_u64(&x92, &x93, 0x0, x57, x79);
  fiat_p384_addcarryx_u64(&x94, &x95, x93, x59, x81);
  fiat_p384_addcarryx_u64(&x96, &x97, x95, x61, x83);
  fiat_p384_addcarryx_u64(&x98, &x99, x97, x63, x85);
  fiat_p384_addcarryx_u64(&x100, &x101, x99, x65, x87);
  fiat_p384_addcarryx_u64(&x102, &x103, x101, x67, x89);
  fiat_p384_addcarryx_u64(&x104, &x105, x103, x68, x91);
  fiat_p384_mulx_u64(&x106, &x107, x92, UINT64_C(0x100000001));
  fiat_p384_mulx_u64(&x108, &x109, x106, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x110, &x111, x106, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x112, &x113, x106, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x114, &x115, x106, UINT64_C(0xfffffffffffffffe));
  fiat_p384_mulx_u64(&x116, &x117, x106, UINT64_C(0xffffffff00000000));
  fiat_p384_mulx_u64(&x118, &x119, x106, UINT32_C(0xffffffff));
  fiat_p384_addcarryx_u64(&x120, &x121, 0x0, x119, x116);
  fiat_p384_addcarryx_u64(&x122, &x123, x121, x117, x114);
  fiat_p384_addcarryx_u64(&x124, &x125, x123, x115, x112);
  fiat_p384_addcarryx_u64(&x126, &x127, x125, x113, x110);
  fiat_p384_addcarryx_u64(&x128, &x129, x127, x111, x108);
  x130 = (x129 + x109);
  fiat_p384_addcarryx_u64(&x131, &x132, 0x0, x92, x118);
  fiat_p384_addcarryx_u64(&x133, &x134, x132, x94, x120);
  fiat_p384_addcarryx_u64(&x135, &x136, x134, x96, x122);
  fiat_p384_addcarryx_u64(&x137, &x138, x136, x98, x124);
  fiat_p384_addcarryx_u64(&x139, &x140, x138, x100, x126);
  fiat_p384_addcarryx_u64(&x141, &x142, x140, x102, x128);
  fiat_p384_addcarryx_u64(&x143, &x144, x142, x104, x130);
  x145 = ((uint64_t)x144 + x105);
  fiat_p384_mulx_u64(&x146, &x147, x2, (arg2[5]));
  fiat_p384_mulx_u64(&x148, &x149, x2, (arg2[4]));
  fiat_p384_mulx_u64(&x150, &x151, x2, (arg2[3]));
  fiat_p384_mulx_u64(&x152, &x153, x2, (arg2[2]));
  fiat_p384_mulx_u64(&x154, &x155, x2, (arg2[1]));
  fiat_p384_mulx_u64(&x156, &x157, x2, (arg2[0]));
  fiat_p384_addcarryx_u64(&x158, &x159, 0x0, x157, x154);
  fiat_p384_addcarryx_u64(&x160, &x161, x159, x155, x152);
  fiat_p384_addcarryx_u64(&x162, &x163, x161, x153, x150);
  fiat_p384_addcarryx_u64(&x164, &x165, x163, x151, x148);
  fiat_p384_addcarryx_u64(&x166, &x167, x165, x149, x146);
  x168 = (x167 + x147);
  fiat_p384_addcarryx_u64(&x169, &x170, 0x0, x133, x156);
  fiat_p384_addcarryx_u64(&x171, &x172, x170, x135, x158);
  fiat_p384_addcarryx_u64(&x173, &x174, x172, x137, x160);
  fiat_p384_addcarryx_u64(&x175, &x176, x174, x139, x162);
  fiat_p384_addcarryx_u64(&x177, &x178, x176, x141, x164);
  fiat_p384_addcarryx_u64(&x179, &x180, x178, x143, x166);
  fiat_p384_addcarryx_u64(&x181, &x182, x180, x145, x168);
  fiat_p384_mulx_u64(&x183, &x184, x169, UINT64_C(0x100000001));
  fiat_p384_mulx_u64(&x185, &x186, x183, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x187, &x188, x183, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x189, &x190, x183, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x191, &x192, x183, UINT64_C(0xfffffffffffffffe));
  fiat_p384_mulx_u64(&x193, &x194, x183, UINT64_C(0xffffffff00000000));
  fiat_p384_mulx_u64(&x195, &x196, x183, UINT32_C(0xffffffff));
  fiat_p384_addcarryx_u64(&x197, &x198, 0x0, x196, x193);
  fiat_p384_addcarryx_u64(&x199, &x200, x198, x194, x191);
  fiat_p384_addcarryx_u64(&x201, &x202, x200, x192, x189);
  fiat_p384_addcarryx_u64(&x203, &x204, x202, x190, x187);
  fiat_p384_addcarryx_u64(&x205, &x206, x204, x188, x185);
  x207 = (x206 + x186);
  fiat_p384_addcarryx_u64(&x208, &x209, 0x0, x169, x195);
  fiat_p384_addcarryx_u64(&x210, &x211, x209, x171, x197);
  fiat_p384_addcarryx_u64(&x212, &x213, x211, x173, x199);
  fiat_p384_addcarryx_u64(&x214, &x215, x213, x175, x201);
  fiat_p384_addcarryx_u64(&x216, &x217, x215, x177, x203);
  fiat_p384_addcarryx_u64(&x218, &x219, x217, x179, x205);
  fiat_p384_addcarryx_u64(&x220, &x221, x219, x181, x207);
  x222 = ((uint64_t)x221 + x182);
  fiat_p384_mulx_u64(&x223, &x224, x3, (arg2[5]));
  fiat_p384_mulx_u64(&x225, &x226, x3, (arg2[4]));
  fiat_p384_mulx_u64(&x227, &x228, x3, (arg2[3]));
  fiat_p384_mulx_u64(&x229, &x230, x3, (arg2[2]));
  fiat_p384_mulx_u64(&x231, &x232, x3, (arg2[1]));
  fiat_p384_mulx_u64(&x233, &x234, x3, (arg2[0]));
  fiat_p384_addcarryx_u64(&x235, &x236, 0x0, x234, x231);
  fiat_p384_addcarryx_u64(&x237, &x238, x236, x232, x229);
  fiat_p384_addcarryx_u64(&x239, &x240, x238, x230, x227);
  fiat_p384_addcarryx_u64(&x241, &x242, x240, x228, x225);
  fiat_p384_addcarryx_u64(&x243, &x244, x242, x226, x223);
  x245 = (x244 + x224);
  fiat_p384_addcarryx_u64(&x246, &x247, 0x0, x210, x233);
  fiat_p384_addcarryx_u64(&x248, &x249, x247, x212, x235);
  fiat_p384_addcarryx_u64(&x250, &x251, x249, x214, x237);
  fiat_p384_addcarryx_u64(&x252, &x253, x251, x216, x239);
  fiat_p384_addcarryx_u64(&x254, &x255, x253, x218, x241);
  fiat_p384_addcarryx_u64(&x256, &x257, x255, x220, x243);
  fiat_p384_addcarryx_u64(&x258, &x259, x257, x222, x245);
  fiat_p384_mulx_u64(&x260, &x261, x246, UINT64_C(0x100000001));
  fiat_p384_mulx_u64(&x262, &x263, x260, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x264, &x265, x260, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x266, &x267, x260, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x268, &x269, x260, UINT64_C(0xfffffffffffffffe));
  fiat_p384_mulx_u64(&x270, &x271, x260, UINT64_C(0xffffffff00000000));
  fiat_p384_mulx_u64(&x272, &x273, x260, UINT32_C(0xffffffff));
  fiat_p384_addcarryx_u64(&x274, &x275, 0x0, x273, x270);
  fiat_p384_addcarryx_u64(&x276, &x277, x275, x271, x268);
  fiat_p384_addcarryx_u64(&x278, &x279, x277, x269, x266);
  fiat_p384_addcarryx_u64(&x280, &x281, x279, x267, x264);
  fiat_p384_addcarryx_u64(&x282, &x283, x281, x265, x262);
  x284 = (x283 + x263);
  fiat_p384_addcarryx_u64(&x285, &x286, 0x0, x246, x272);
  fiat_p384_addcarryx_u64(&x287, &x288, x286, x248, x274);
  fiat_p384_addcarryx_u64(&x289, &x290, x288, x250, x276);
  fiat_p384_addcarryx_u64(&x291, &x292, x290, x252, x278);
  fiat_p384_addcarryx_u64(&x293, &x294, x292, x254, x280);
  fiat_p384_addcarryx_u64(&x295, &x296, x294, x256, x282);
  fiat_p384_addcarryx_u64(&x297, &x298, x296, x258, x284);
  x299 = ((uint64_t)x298 + x259);
  fiat_p384_mulx_u64(&x300, &x301, x4, (arg2[5]));
  fiat_p384_mulx_u64(&x302, &x303, x4, (arg2[4]));
  fiat_p384_mulx_u64(&x304, &x305, x4, (arg2[3]));
  fiat_p384_mulx_u64(&x306, &x307, x4, (arg2[2]));
  fiat_p384_mulx_u64(&x308, &x309, x4, (arg2[1]));
  fiat_p384_mulx_u64(&x310, &x311, x4, (arg2[0]));
  fiat_p384_addcarryx_u64(&x312, &x313, 0x0, x311, x308);
  fiat_p384_addcarryx_u64(&x314, &x315, x313, x309, x306);
  fiat_p384_addcarryx_u64(&x316, &x317, x315, x307, x304);
  fiat_p384_addcarryx_u64(&x318, &x319, x317, x305, x302);
  fiat_p384_addcarryx_u64(&x320, &x321, x319, x303, x300);
  x322 = (x321 + x301);
  fiat_p384_addcarryx_u64(&x323, &x324, 0x0, x287, x310);
  fiat_p384_addcarryx_u64(&x325, &x326, x324, x289, x312);
  fiat_p384_addcarryx_u64(&x327, &x328, x326, x291, x314);
  fiat_p384_addcarryx_u64(&x329, &x330, x328, x293, x316);
  fiat_p384_addcarryx_u64(&x331, &x332, x330, x295, x318);
  fiat_p384_addcarryx_u64(&x333, &x334, x332, x297, x320);
  fiat_p384_addcarryx_u64(&x335, &x336, x334, x299, x322);
  fiat_p384_mulx_u64(&x337, &x338, x323, UINT64_C(0x100000001));
  fiat_p384_mulx_u64(&x339, &x340, x337, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x341, &x342, x337, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x343, &x344, x337, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x345, &x346, x337, UINT64_C(0xfffffffffffffffe));
  fiat_p384_mulx_u64(&x347, &x348, x337, UINT64_C(0xffffffff00000000));
  fiat_p384_mulx_u64(&x349, &x350, x337, UINT32_C(0xffffffff));
  fiat_p384_addcarryx_u64(&x351, &x352, 0x0, x350, x347);
  fiat_p384_addcarryx_u64(&x353, &x354, x352, x348, x345);
  fiat_p384_addcarryx_u64(&x355, &x356, x354, x346, x343);
  fiat_p384_addcarryx_u64(&x357, &x358, x356, x344, x341);
  fiat_p384_addcarryx_u64(&x359, &x360, x358, x342, x339);
  x361 = (x360 + x340);
  fiat_p384_addcarryx_u64(&x362, &x363, 0x0, x323, x349);
  fiat_p384_addcarryx_u64(&x364, &x365, x363, x325, x351);
  fiat_p384_addcarryx_u64(&x366, &x367, x365, x327, x353);
  fiat_p384_addcarryx_u64(&x368, &x369, x367, x329, x355);
  fiat_p384_addcarryx_u64(&x370, &x371, x369, x331, x357);
  fiat_p384_addcarryx_u64(&x372, &x373, x371, x333, x359);
  fiat_p384_addcarryx_u64(&x374, &x375, x373, x335, x361);
  x376 = ((uint64_t)x375 + x336);
  fiat_p384_mulx_u64(&x377, &x378, x5, (arg2[5]));
  fiat_p384_mulx_u64(&x379, &x380, x5, (arg2[4]));
  fiat_p384_mulx_u64(&x381, &x382, x5, (arg2[3]));
  fiat_p384_mulx_u64(&x383, &x384, x5, (arg2[2]));
  fiat_p384_mulx_u64(&x385, &x386, x5, (arg2[1]));
  fiat_p384_mulx_u64(&x387, &x388, x5, (arg2[0]));
  fiat_p384_addcarryx_u64(&x389, &x390, 0x0, x388, x385);
  fiat_p384_addcarryx_u64(&x391, &x392, x390, x386, x383);
  fiat_p384_addcarryx_u64(&x393, &x394, x392, x384, x381);
  fiat_p384_addcarryx_u64(&x395, &x396, x394, x382, x379);
  fiat_p384_addcarryx_u64(&x397, &x398, x396, x380, x377);
  x399 = (x398 + x378);
  fiat_p384_addcarryx_u64(&x400, &x401, 0x0, x364, x387);
  fiat_p384_addcarryx_u64(&x402, &x403, x401, x366, x389);
  fiat_p384_addcarryx_u64(&x404, &x405, x403, x368, x391);
  fiat_p384_addcarryx_u64(&x406, &x407, x405, x370, x393);
  fiat_p384_addcarryx_u64(&x408, &x409, x407, x372, x395);
  fiat_p384_addcarryx_u64(&x410, &x411, x409, x374, x397);
  fiat_p384_addcarryx_u64(&x412, &x413, x411, x376, x399);
  fiat_p384_mulx_u64(&x414, &x415, x400, UINT64_C(0x100000001));
  fiat_p384_mulx_u64(&x416, &x417, x414, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x418, &x419, x414, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x420, &x421, x414, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x422, &x423, x414, UINT64_C(0xfffffffffffffffe));
  fiat_p384_mulx_u64(&x424, &x425, x414, UINT64_C(0xffffffff00000000));
  fiat_p384_mulx_u64(&x426, &x427, x414, UINT32_C(0xffffffff));
  fiat_p384_addcarryx_u64(&x428, &x429, 0x0, x427, x424);
  fiat_p384_addcarryx_u64(&x430, &x431, x429, x425, x422);
  fiat_p384_addcarryx_u64(&x432, &x433, x431, x423, x420);
  fiat_p384_addcarryx_u64(&x434, &x435, x433, x421, x418);
  fiat_p384_addcarryx_u64(&x436, &x437, x435, x419, x416);
  x438 = (x437 + x417);
  fiat_p384_addcarryx_u64(&x439, &x440, 0x0, x400, x426);
  fiat_p384_addcarryx_u64(&x441, &x442, x440, x402, x428);
  fiat_p384_addcarryx_u64(&x443, &x444, x442, x404, x430);
  fiat_p384_addcarryx_u64(&x445, &x446, x444, x406, x432);
  fiat_p384_addcarryx_u64(&x447, &x448, x446, x408, x434);
  fiat_p384_addcarryx_u64(&x449, &x450, x448, x410, x436);
  fiat_p384_addcarryx_u64(&x451, &x452, x450, x412, x438);
  x453 = ((uint64_t)x452 + x413);
  fiat_p384_subborrowx_u64(&x454, &x455, 0x0, x441, UINT32_C(0xffffffff));
  fiat_p384_subborrowx_u64(&x456, &x457, x455, x443,
                           UINT64_C(0xffffffff00000000));
  fiat_p384_subborrowx_u64(&x458, &x459, x457, x445,
                           UINT64_C(0xfffffffffffffffe));
  fiat_p384_subborrowx_u64(&x460, &x461, x459, x447,
                           UINT64_C(0xffffffffffffffff));
  fiat_p384_subborrowx_u64(&x462, &x463, x461, x449,
                           UINT64_C(0xffffffffffffffff));
  fiat_p384_subborrowx_u64(&x464, &x465, x463, x451,
                           UINT64_C(0xffffffffffffffff));
  fiat_p384_subborrowx_u64(&x466, &x467, x465, x453, 0x0);
  fiat_p384_cmovznz_u64(&x468, x467, x454, x441);
  fiat_p384_cmovznz_u64(&x469, x467, x456, x443);
  fiat_p384_cmovznz_u64(&x470, x467, x458, x445);
  fiat_p384_cmovznz_u64(&x471, x467, x460, x447);
  fiat_p384_cmovznz_u64(&x472, x467, x462, x449);
  fiat_p384_cmovznz_u64(&x473, x467, x464, x451);
  out1[0] = x468;
  out1[1] = x469;
  out1[2] = x470;
  out1[3] = x471;
  out1[4] = x472;
  out1[5] = x473;
}

/*
 * The function fiat_p384_square squares a field element in the Montgomery
 * domain. Preconditions: 0 ≤ eval arg1 < m Postconditions: eval
 * (from_montgomery out1) mod m = (eval (from_montgomery arg1) * eval
 * (from_montgomery arg1)) mod m 0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]] Output Bounds: out1: [[0x0
 * ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
void fiat_p384_square(uint64_t out1[6], const uint64_t arg1[6]) {
  uint64_t x1;
  uint64_t x2;
  uint64_t x3;
  uint64_t x4;
  uint64_t x5;
  uint64_t x6;
  uint64_t x7;
  uint64_t x8;
  uint64_t x9;
  uint64_t x10;
  uint64_t x11;
  uint64_t x12;
  uint64_t x13;
  uint64_t x14;
  uint64_t x15;
  uint64_t x16;
  uint64_t x17;
  uint64_t x18;
  uint64_t x19;
  fiat_p384_uint1 x20;
  uint64_t x21;
  fiat_p384_uint1 x22;
  uint64_t x23;
  fiat_p384_uint1 x24;
  uint64_t x25;
  fiat_p384_uint1 x26;
  uint64_t x27;
  fiat_p384_uint1 x28;
  uint64_t x29;
  uint64_t x30;
  uint64_t x31;
  uint64_t x32;
  uint64_t x33;
  uint64_t x34;
  uint64_t x35;
  uint64_t x36;
  uint64_t x37;
  uint64_t x38;
  uint64_t x39;
  uint64_t x40;
  uint64_t x41;
  uint64_t x42;
  uint64_t x43;
  uint64_t x44;
  fiat_p384_uint1 x45;
  uint64_t x46;
  fiat_p384_uint1 x47;
  uint64_t x48;
  fiat_p384_uint1 x49;
  uint64_t x50;
  fiat_p384_uint1 x51;
  uint64_t x52;
  fiat_p384_uint1 x53;
  uint64_t x54;
  uint64_t x55;
  fiat_p384_uint1 x56;
  uint64_t x57;
  fiat_p384_uint1 x58;
  uint64_t x59;
  fiat_p384_uint1 x60;
  uint64_t x61;
  fiat_p384_uint1 x62;
  uint64_t x63;
  fiat_p384_uint1 x64;
  uint64_t x65;
  fiat_p384_uint1 x66;
  uint64_t x67;
  fiat_p384_uint1 x68;
  uint64_t x69;
  uint64_t x70;
  uint64_t x71;
  uint64_t x72;
  uint64_t x73;
  uint64_t x74;
  uint64_t x75;
  uint64_t x76;
  uint64_t x77;
  uint64_t x78;
  uint64_t x79;
  uint64_t x80;
  uint64_t x81;
  fiat_p384_uint1 x82;
  uint64_t x83;
  fiat_p384_uint1 x84;
  uint64_t x85;
  fiat_p384_uint1 x86;
  uint64_t x87;
  fiat_p384_uint1 x88;
  uint64_t x89;
  fiat_p384_uint1 x90;
  uint64_t x91;
  uint64_t x92;
  fiat_p384_uint1 x93;
  uint64_t x94;
  fiat_p384_uint1 x95;
  uint64_t x96;
  fiat_p384_uint1 x97;
  uint64_t x98;
  fiat_p384_uint1 x99;
  uint64_t x100;
  fiat_p384_uint1 x101;
  uint64_t x102;
  fiat_p384_uint1 x103;
  uint64_t x104;
  fiat_p384_uint1 x105;
  uint64_t x106;
  uint64_t x107;
  uint64_t x108;
  uint64_t x109;
  uint64_t x110;
  uint64_t x111;
  uint64_t x112;
  uint64_t x113;
  uint64_t x114;
  uint64_t x115;
  uint64_t x116;
  uint64_t x117;
  uint64_t x118;
  uint64_t x119;
  uint64_t x120;
  fiat_p384_uint1 x121;
  uint64_t x122;
  fiat_p384_uint1 x123;
  uint64_t x124;
  fiat_p384_uint1 x125;
  uint64_t x126;
  fiat_p384_uint1 x127;
  uint64_t x128;
  fiat_p384_uint1 x129;
  uint64_t x130;
  uint64_t x131;
  fiat_p384_uint1 x132;
  uint64_t x133;
  fiat_p384_uint1 x134;
  uint64_t x135;
  fiat_p384_uint1 x136;
  uint64_t x137;
  fiat_p384_uint1 x138;
  uint64_t x139;
  fiat_p384_uint1 x140;
  uint64_t x141;
  fiat_p384_uint1 x142;
  uint64_t x143;
  fiat_p384_uint1 x144;
  uint64_t x145;
  uint64_t x146;
  uint64_t x147;
  uint64_t x148;
  uint64_t x149;
  uint64_t x150;
  uint64_t x151;
  uint64_t x152;
  uint64_t x153;
  uint64_t x154;
  uint64_t x155;
  uint64_t x156;
  uint64_t x157;
  uint64_t x158;
  fiat_p384_uint1 x159;
  uint64_t x160;
  fiat_p384_uint1 x161;
  uint64_t x162;
  fiat_p384_uint1 x163;
  uint64_t x164;
  fiat_p384_uint1 x165;
  uint64_t x166;
  fiat_p384_uint1 x167;
  uint64_t x168;
  uint64_t x169;
  fiat_p384_uint1 x170;
  uint64_t x171;
  fiat_p384_uint1 x172;
  uint64_t x173;
  fiat_p384_uint1 x174;
  uint64_t x175;
  fiat_p384_uint1 x176;
  uint64_t x177;
  fiat_p384_uint1 x178;
  uint64_t x179;
  fiat_p384_uint1 x180;
  uint64_t x181;
  fiat_p384_uint1 x182;
  uint64_t x183;
  uint64_t x184;
  uint64_t x185;
  uint64_t x186;
  uint64_t x187;
  uint64_t x188;
  uint64_t x189;
  uint64_t x190;
  uint64_t x191;
  uint64_t x192;
  uint64_t x193;
  uint64_t x194;
  uint64_t x195;
  uint64_t x196;
  uint64_t x197;
  fiat_p384_uint1 x198;
  uint64_t x199;
  fiat_p384_uint1 x200;
  uint64_t x201;
  fiat_p384_uint1 x202;
  uint64_t x203;
  fiat_p384_uint1 x204;
  uint64_t x205;
  fiat_p384_uint1 x206;
  uint64_t x207;
  uint64_t x208;
  fiat_p384_uint1 x209;
  uint64_t x210;
  fiat_p384_uint1 x211;
  uint64_t x212;
  fiat_p384_uint1 x213;
  uint64_t x214;
  fiat_p384_uint1 x215;
  uint64_t x216;
  fiat_p384_uint1 x217;
  uint64_t x218;
  fiat_p384_uint1 x219;
  uint64_t x220;
  fiat_p384_uint1 x221;
  uint64_t x222;
  uint64_t x223;
  uint64_t x224;
  uint64_t x225;
  uint64_t x226;
  uint64_t x227;
  uint64_t x228;
  uint64_t x229;
  uint64_t x230;
  uint64_t x231;
  uint64_t x232;
  uint64_t x233;
  uint64_t x234;
  uint64_t x235;
  fiat_p384_uint1 x236;
  uint64_t x237;
  fiat_p384_uint1 x238;
  uint64_t x239;
  fiat_p384_uint1 x240;
  uint64_t x241;
  fiat_p384_uint1 x242;
  uint64_t x243;
  fiat_p384_uint1 x244;
  uint64_t x245;
  uint64_t x246;
  fiat_p384_uint1 x247;
  uint64_t x248;
  fiat_p384_uint1 x249;
  uint64_t x250;
  fiat_p384_uint1 x251;
  uint64_t x252;
  fiat_p384_uint1 x253;
  uint64_t x254;
  fiat_p384_uint1 x255;
  uint64_t x256;
  fiat_p384_uint1 x257;
  uint64_t x258;
  fiat_p384_uint1 x259;
  uint64_t x260;
  uint64_t x261;
  uint64_t x262;
  uint64_t x263;
  uint64_t x264;
  uint64_t x265;
  uint64_t x266;
  uint64_t x267;
  uint64_t x268;
  uint64_t x269;
  uint64_t x270;
  uint64_t x271;
  uint64_t x272;
  uint64_t x273;
  uint64_t x274;
  fiat_p384_uint1 x275;
  uint64_t x276;
  fiat_p384_uint1 x277;
  uint64_t x278;
  fiat_p384_uint1 x279;
  uint64_t x280;
  fiat_p384_uint1 x281;
  uint64_t x282;
  fiat_p384_uint1 x283;
  uint64_t x284;
  uint64_t x285;
  fiat_p384_uint1 x286;
  uint64_t x287;
  fiat_p384_uint1 x288;
  uint64_t x289;
  fiat_p384_uint1 x290;
  uint64_t x291;
  fiat_p384_uint1 x292;
  uint64_t x293;
  fiat_p384_uint1 x294;
  uint64_t x295;
  fiat_p384_uint1 x296;
  uint64_t x297;
  fiat_p384_uint1 x298;
  uint64_t x299;
  uint64_t x300;
  uint64_t x301;
  uint64_t x302;
  uint64_t x303;
  uint64_t x304;
  uint64_t x305;
  uint64_t x306;
  uint64_t x307;
  uint64_t x308;
  uint64_t x309;
  uint64_t x310;
  uint64_t x311;
  uint64_t x312;
  fiat_p384_uint1 x313;
  uint64_t x314;
  fiat_p384_uint1 x315;
  uint64_t x316;
  fiat_p384_uint1 x317;
  uint64_t x318;
  fiat_p384_uint1 x319;
  uint64_t x320;
  fiat_p384_uint1 x321;
  uint64_t x322;
  uint64_t x323;
  fiat_p384_uint1 x324;
  uint64_t x325;
  fiat_p384_uint1 x326;
  uint64_t x327;
  fiat_p384_uint1 x328;
  uint64_t x329;
  fiat_p384_uint1 x330;
  uint64_t x331;
  fiat_p384_uint1 x332;
  uint64_t x333;
  fiat_p384_uint1 x334;
  uint64_t x335;
  fiat_p384_uint1 x336;
  uint64_t x337;
  uint64_t x338;
  uint64_t x339;
  uint64_t x340;
  uint64_t x341;
  uint64_t x342;
  uint64_t x343;
  uint64_t x344;
  uint64_t x345;
  uint64_t x346;
  uint64_t x347;
  uint64_t x348;
  uint64_t x349;
  uint64_t x350;
  uint64_t x351;
  fiat_p384_uint1 x352;
  uint64_t x353;
  fiat_p384_uint1 x354;
  uint64_t x355;
  fiat_p384_uint1 x356;
  uint64_t x357;
  fiat_p384_uint1 x358;
  uint64_t x359;
  fiat_p384_uint1 x360;
  uint64_t x361;
  uint64_t x362;
  fiat_p384_uint1 x363;
  uint64_t x364;
  fiat_p384_uint1 x365;
  uint64_t x366;
  fiat_p384_uint1 x367;
  uint64_t x368;
  fiat_p384_uint1 x369;
  uint64_t x370;
  fiat_p384_uint1 x371;
  uint64_t x372;
  fiat_p384_uint1 x373;
  uint64_t x374;
  fiat_p384_uint1 x375;
  uint64_t x376;
  uint64_t x377;
  uint64_t x378;
  uint64_t x379;
  uint64_t x380;
  uint64_t x381;
  uint64_t x382;
  uint64_t x383;
  uint64_t x384;
  uint64_t x385;
  uint64_t x386;
  uint64_t x387;
  uint64_t x388;
  uint64_t x389;
  fiat_p384_uint1 x390;
  uint64_t x391;
  fiat_p384_uint1 x392;
  uint64_t x393;
  fiat_p384_uint1 x394;
  uint64_t x395;
  fiat_p384_uint1 x396;
  uint64_t x397;
  fiat_p384_uint1 x398;
  uint64_t x399;
  uint64_t x400;
  fiat_p384_uint1 x401;
  uint64_t x402;
  fiat_p384_uint1 x403;
  uint64_t x404;
  fiat_p384_uint1 x405;
  uint64_t x406;
  fiat_p384_uint1 x407;
  uint64_t x408;
  fiat_p384_uint1 x409;
  uint64_t x410;
  fiat_p384_uint1 x411;
  uint64_t x412;
  fiat_p384_uint1 x413;
  uint64_t x414;
  uint64_t x415;
  uint64_t x416;
  uint64_t x417;
  uint64_t x418;
  uint64_t x419;
  uint64_t x420;
  uint64_t x421;
  uint64_t x422;
  uint64_t x423;
  uint64_t x424;
  uint64_t x425;
  uint64_t x426;
  uint64_t x427;
  uint64_t x428;
  fiat_p384_uint1 x429;
  uint64_t x430;
  fiat_p384_uint1 x431;
  uint64_t x432;
  fiat_p384_uint1 x433;
  uint64_t x434;
  fiat_p384_uint1 x435;
  uint64_t x436;
  fiat_p384_uint1 x437;
  uint64_t x438;
  uint64_t x439;
  fiat_p384_uint1 x440;
  uint64_t x441;
  fiat_p384_uint1 x442;
  uint64_t x443;
  fiat_p384_uint1 x444;
  uint64_t x445;
  fiat_p384_uint1 x446;
  uint64_t x447;
  fiat_p384_uint1 x448;
  uint64_t x449;
  fiat_p384_uint1 x450;
  uint64_t x451;
  fiat_p384_uint1 x452;
  uint64_t x453;
  uint64_t x454;
  fiat_p384_uint1 x455;
  uint64_t x456;
  fiat_p384_uint1 x457;
  uint64_t x458;
  fiat_p384_uint1 x459;
  uint64_t x460;
  fiat_p384_uint1 x461;
  uint64_t x462;
  fiat_p384_uint1 x463;
  uint64_t x464;
  fiat_p384_uint1 x465;
  uint64_t x466;
  fiat_p384_uint1 x467;
  uint64_t x468;
  uint64_t x469;
  uint64_t x470;
  uint64_t x471;
  uint64_t x472;
  uint64_t x473;
  x1 = (arg1[1]);
  x2 = (arg1[2]);
  x3 = (arg1[3]);
  x4 = (arg1[4]);
  x5 = (arg1[5]);
  x6 = (arg1[0]);
  fiat_p384_mulx_u64(&x7, &x8, x6, (arg1[5]));
  fiat_p384_mulx_u64(&x9, &x10, x6, (arg1[4]));
  fiat_p384_mulx_u64(&x11, &x12, x6, (arg1[3]));
  fiat_p384_mulx_u64(&x13, &x14, x6, (arg1[2]));
  fiat_p384_mulx_u64(&x15, &x16, x6, (arg1[1]));
  fiat_p384_mulx_u64(&x17, &x18, x6, (arg1[0]));
  fiat_p384_addcarryx_u64(&x19, &x20, 0x0, x18, x15);
  fiat_p384_addcarryx_u64(&x21, &x22, x20, x16, x13);
  fiat_p384_addcarryx_u64(&x23, &x24, x22, x14, x11);
  fiat_p384_addcarryx_u64(&x25, &x26, x24, x12, x9);
  fiat_p384_addcarryx_u64(&x27, &x28, x26, x10, x7);
  x29 = (x28 + x8);
  fiat_p384_mulx_u64(&x30, &x31, x17, UINT64_C(0x100000001));
  fiat_p384_mulx_u64(&x32, &x33, x30, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x34, &x35, x30, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x36, &x37, x30, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x38, &x39, x30, UINT64_C(0xfffffffffffffffe));
  fiat_p384_mulx_u64(&x40, &x41, x30, UINT64_C(0xffffffff00000000));
  fiat_p384_mulx_u64(&x42, &x43, x30, UINT32_C(0xffffffff));
  fiat_p384_addcarryx_u64(&x44, &x45, 0x0, x43, x40);
  fiat_p384_addcarryx_u64(&x46, &x47, x45, x41, x38);
  fiat_p384_addcarryx_u64(&x48, &x49, x47, x39, x36);
  fiat_p384_addcarryx_u64(&x50, &x51, x49, x37, x34);
  fiat_p384_addcarryx_u64(&x52, &x53, x51, x35, x32);
  x54 = (x53 + x33);
  fiat_p384_addcarryx_u64(&x55, &x56, 0x0, x17, x42);
  fiat_p384_addcarryx_u64(&x57, &x58, x56, x19, x44);
  fiat_p384_addcarryx_u64(&x59, &x60, x58, x21, x46);
  fiat_p384_addcarryx_u64(&x61, &x62, x60, x23, x48);
  fiat_p384_addcarryx_u64(&x63, &x64, x62, x25, x50);
  fiat_p384_addcarryx_u64(&x65, &x66, x64, x27, x52);
  fiat_p384_addcarryx_u64(&x67, &x68, x66, x29, x54);
  fiat_p384_mulx_u64(&x69, &x70, x1, (arg1[5]));
  fiat_p384_mulx_u64(&x71, &x72, x1, (arg1[4]));
  fiat_p384_mulx_u64(&x73, &x74, x1, (arg1[3]));
  fiat_p384_mulx_u64(&x75, &x76, x1, (arg1[2]));
  fiat_p384_mulx_u64(&x77, &x78, x1, (arg1[1]));
  fiat_p384_mulx_u64(&x79, &x80, x1, (arg1[0]));
  fiat_p384_addcarryx_u64(&x81, &x82, 0x0, x80, x77);
  fiat_p384_addcarryx_u64(&x83, &x84, x82, x78, x75);
  fiat_p384_addcarryx_u64(&x85, &x86, x84, x76, x73);
  fiat_p384_addcarryx_u64(&x87, &x88, x86, x74, x71);
  fiat_p384_addcarryx_u64(&x89, &x90, x88, x72, x69);
  x91 = (x90 + x70);
  fiat_p384_addcarryx_u64(&x92, &x93, 0x0, x57, x79);
  fiat_p384_addcarryx_u64(&x94, &x95, x93, x59, x81);
  fiat_p384_addcarryx_u64(&x96, &x97, x95, x61, x83);
  fiat_p384_addcarryx_u64(&x98, &x99, x97, x63, x85);
  fiat_p384_addcarryx_u64(&x100, &x101, x99, x65, x87);
  fiat_p384_addcarryx_u64(&x102, &x103, x101, x67, x89);
  fiat_p384_addcarryx_u64(&x104, &x105, x103, x68, x91);
  fiat_p384_mulx_u64(&x106, &x107, x92, UINT64_C(0x100000001));
  fiat_p384_mulx_u64(&x108, &x109, x106, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x110, &x111, x106, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x112, &x113, x106, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x114, &x115, x106, UINT64_C(0xfffffffffffffffe));
  fiat_p384_mulx_u64(&x116, &x117, x106, UINT64_C(0xffffffff00000000));
  fiat_p384_mulx_u64(&x118, &x119, x106, UINT32_C(0xffffffff));
  fiat_p384_addcarryx_u64(&x120, &x121, 0x0, x119, x116);
  fiat_p384_addcarryx_u64(&x122, &x123, x121, x117, x114);
  fiat_p384_addcarryx_u64(&x124, &x125, x123, x115, x112);
  fiat_p384_addcarryx_u64(&x126, &x127, x125, x113, x110);
  fiat_p384_addcarryx_u64(&x128, &x129, x127, x111, x108);
  x130 = (x129 + x109);
  fiat_p384_addcarryx_u64(&x131, &x132, 0x0, x92, x118);
  fiat_p384_addcarryx_u64(&x133, &x134, x132, x94, x120);
  fiat_p384_addcarryx_u64(&x135, &x136, x134, x96, x122);
  fiat_p384_addcarryx_u64(&x137, &x138, x136, x98, x124);
  fiat_p384_addcarryx_u64(&x139, &x140, x138, x100, x126);
  fiat_p384_addcarryx_u64(&x141, &x142, x140, x102, x128);
  fiat_p384_addcarryx_u64(&x143, &x144, x142, x104, x130);
  x145 = ((uint64_t)x144 + x105);
  fiat_p384_mulx_u64(&x146, &x147, x2, (arg1[5]));
  fiat_p384_mulx_u64(&x148, &x149, x2, (arg1[4]));
  fiat_p384_mulx_u64(&x150, &x151, x2, (arg1[3]));
  fiat_p384_mulx_u64(&x152, &x153, x2, (arg1[2]));
  fiat_p384_mulx_u64(&x154, &x155, x2, (arg1[1]));
  fiat_p384_mulx_u64(&x156, &x157, x2, (arg1[0]));
  fiat_p384_addcarryx_u64(&x158, &x159, 0x0, x157, x154);
  fiat_p384_addcarryx_u64(&x160, &x161, x159, x155, x152);
  fiat_p384_addcarryx_u64(&x162, &x163, x161, x153, x150);
  fiat_p384_addcarryx_u64(&x164, &x165, x163, x151, x148);
  fiat_p384_addcarryx_u64(&x166, &x167, x165, x149, x146);
  x168 = (x167 + x147);
  fiat_p384_addcarryx_u64(&x169, &x170, 0x0, x133, x156);
  fiat_p384_addcarryx_u64(&x171, &x172, x170, x135, x158);
  fiat_p384_addcarryx_u64(&x173, &x174, x172, x137, x160);
  fiat_p384_addcarryx_u64(&x175, &x176, x174, x139, x162);
  fiat_p384_addcarryx_u64(&x177, &x178, x176, x141, x164);
  fiat_p384_addcarryx_u64(&x179, &x180, x178, x143, x166);
  fiat_p384_addcarryx_u64(&x181, &x182, x180, x145, x168);
  fiat_p384_mulx_u64(&x183, &x184, x169, UINT64_C(0x100000001));
  fiat_p384_mulx_u64(&x185, &x186, x183, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x187, &x188, x183, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x189, &x190, x183, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x191, &x192, x183, UINT64_C(0xfffffffffffffffe));
  fiat_p384_mulx_u64(&x193, &x194, x183, UINT64_C(0xffffffff00000000));
  fiat_p384_mulx_u64(&x195, &x196, x183, UINT32_C(0xffffffff));
  fiat_p384_addcarryx_u64(&x197, &x198, 0x0, x196, x193);
  fiat_p384_addcarryx_u64(&x199, &x200, x198, x194, x191);
  fiat_p384_addcarryx_u64(&x201, &x202, x200, x192, x189);
  fiat_p384_addcarryx_u64(&x203, &x204, x202, x190, x187);
  fiat_p384_addcarryx_u64(&x205, &x206, x204, x188, x185);
  x207 = (x206 + x186);
  fiat_p384_addcarryx_u64(&x208, &x209, 0x0, x169, x195);
  fiat_p384_addcarryx_u64(&x210, &x211, x209, x171, x197);
  fiat_p384_addcarryx_u64(&x212, &x213, x211, x173, x199);
  fiat_p384_addcarryx_u64(&x214, &x215, x213, x175, x201);
  fiat_p384_addcarryx_u64(&x216, &x217, x215, x177, x203);
  fiat_p384_addcarryx_u64(&x218, &x219, x217, x179, x205);
  fiat_p384_addcarryx_u64(&x220, &x221, x219, x181, x207);
  x222 = ((uint64_t)x221 + x182);
  fiat_p384_mulx_u64(&x223, &x224, x3, (arg1[5]));
  fiat_p384_mulx_u64(&x225, &x226, x3, (arg1[4]));
  fiat_p384_mulx_u64(&x227, &x228, x3, (arg1[3]));
  fiat_p384_mulx_u64(&x229, &x230, x3, (arg1[2]));
  fiat_p384_mulx_u64(&x231, &x232, x3, (arg1[1]));
  fiat_p384_mulx_u64(&x233, &x234, x3, (arg1[0]));
  fiat_p384_addcarryx_u64(&x235, &x236, 0x0, x234, x231);
  fiat_p384_addcarryx_u64(&x237, &x238, x236, x232, x229);
  fiat_p384_addcarryx_u64(&x239, &x240, x238, x230, x227);
  fiat_p384_addcarryx_u64(&x241, &x242, x240, x228, x225);
  fiat_p384_addcarryx_u64(&x243, &x244, x242, x226, x223);
  x245 = (x244 + x224);
  fiat_p384_addcarryx_u64(&x246, &x247, 0x0, x210, x233);
  fiat_p384_addcarryx_u64(&x248, &x249, x247, x212, x235);
  fiat_p384_addcarryx_u64(&x250, &x251, x249, x214, x237);
  fiat_p384_addcarryx_u64(&x252, &x253, x251, x216, x239);
  fiat_p384_addcarryx_u64(&x254, &x255, x253, x218, x241);
  fiat_p384_addcarryx_u64(&x256, &x257, x255, x220, x243);
  fiat_p384_addcarryx_u64(&x258, &x259, x257, x222, x245);
  fiat_p384_mulx_u64(&x260, &x261, x246, UINT64_C(0x100000001));
  fiat_p384_mulx_u64(&x262, &x263, x260, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x264, &x265, x260, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x266, &x267, x260, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x268, &x269, x260, UINT64_C(0xfffffffffffffffe));
  fiat_p384_mulx_u64(&x270, &x271, x260, UINT64_C(0xffffffff00000000));
  fiat_p384_mulx_u64(&x272, &x273, x260, UINT32_C(0xffffffff));
  fiat_p384_addcarryx_u64(&x274, &x275, 0x0, x273, x270);
  fiat_p384_addcarryx_u64(&x276, &x277, x275, x271, x268);
  fiat_p384_addcarryx_u64(&x278, &x279, x277, x269, x266);
  fiat_p384_addcarryx_u64(&x280, &x281, x279, x267, x264);
  fiat_p384_addcarryx_u64(&x282, &x283, x281, x265, x262);
  x284 = (x283 + x263);
  fiat_p384_addcarryx_u64(&x285, &x286, 0x0, x246, x272);
  fiat_p384_addcarryx_u64(&x287, &x288, x286, x248, x274);
  fiat_p384_addcarryx_u64(&x289, &x290, x288, x250, x276);
  fiat_p384_addcarryx_u64(&x291, &x292, x290, x252, x278);
  fiat_p384_addcarryx_u64(&x293, &x294, x292, x254, x280);
  fiat_p384_addcarryx_u64(&x295, &x296, x294, x256, x282);
  fiat_p384_addcarryx_u64(&x297, &x298, x296, x258, x284);
  x299 = ((uint64_t)x298 + x259);
  fiat_p384_mulx_u64(&x300, &x301, x4, (arg1[5]));
  fiat_p384_mulx_u64(&x302, &x303, x4, (arg1[4]));
  fiat_p384_mulx_u64(&x304, &x305, x4, (arg1[3]));
  fiat_p384_mulx_u64(&x306, &x307, x4, (arg1[2]));
  fiat_p384_mulx_u64(&x308, &x309, x4, (arg1[1]));
  fiat_p384_mulx_u64(&x310, &x311, x4, (arg1[0]));
  fiat_p384_addcarryx_u64(&x312, &x313, 0x0, x311, x308);
  fiat_p384_addcarryx_u64(&x314, &x315, x313, x309, x306);
  fiat_p384_addcarryx_u64(&x316, &x317, x315, x307, x304);
  fiat_p384_addcarryx_u64(&x318, &x319, x317, x305, x302);
  fiat_p384_addcarryx_u64(&x320, &x321, x319, x303, x300);
  x322 = (x321 + x301);
  fiat_p384_addcarryx_u64(&x323, &x324, 0x0, x287, x310);
  fiat_p384_addcarryx_u64(&x325, &x326, x324, x289, x312);
  fiat_p384_addcarryx_u64(&x327, &x328, x326, x291, x314);
  fiat_p384_addcarryx_u64(&x329, &x330, x328, x293, x316);
  fiat_p384_addcarryx_u64(&x331, &x332, x330, x295, x318);
  fiat_p384_addcarryx_u64(&x333, &x334, x332, x297, x320);
  fiat_p384_addcarryx_u64(&x335, &x336, x334, x299, x322);
  fiat_p384_mulx_u64(&x337, &x338, x323, UINT64_C(0x100000001));
  fiat_p384_mulx_u64(&x339, &x340, x337, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x341, &x342, x337, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x343, &x344, x337, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x345, &x346, x337, UINT64_C(0xfffffffffffffffe));
  fiat_p384_mulx_u64(&x347, &x348, x337, UINT64_C(0xffffffff00000000));
  fiat_p384_mulx_u64(&x349, &x350, x337, UINT32_C(0xffffffff));
  fiat_p384_addcarryx_u64(&x351, &x352, 0x0, x350, x347);
  fiat_p384_addcarryx_u64(&x353, &x354, x352, x348, x345);
  fiat_p384_addcarryx_u64(&x355, &x356, x354, x346, x343);
  fiat_p384_addcarryx_u64(&x357, &x358, x356, x344, x341);
  fiat_p384_addcarryx_u64(&x359, &x360, x358, x342, x339);
  x361 = (x360 + x340);
  fiat_p384_addcarryx_u64(&x362, &x363, 0x0, x323, x349);
  fiat_p384_addcarryx_u64(&x364, &x365, x363, x325, x351);
  fiat_p384_addcarryx_u64(&x366, &x367, x365, x327, x353);
  fiat_p384_addcarryx_u64(&x368, &x369, x367, x329, x355);
  fiat_p384_addcarryx_u64(&x370, &x371, x369, x331, x357);
  fiat_p384_addcarryx_u64(&x372, &x373, x371, x333, x359);
  fiat_p384_addcarryx_u64(&x374, &x375, x373, x335, x361);
  x376 = ((uint64_t)x375 + x336);
  fiat_p384_mulx_u64(&x377, &x378, x5, (arg1[5]));
  fiat_p384_mulx_u64(&x379, &x380, x5, (arg1[4]));
  fiat_p384_mulx_u64(&x381, &x382, x5, (arg1[3]));
  fiat_p384_mulx_u64(&x383, &x384, x5, (arg1[2]));
  fiat_p384_mulx_u64(&x385, &x386, x5, (arg1[1]));
  fiat_p384_mulx_u64(&x387, &x388, x5, (arg1[0]));
  fiat_p384_addcarryx_u64(&x389, &x390, 0x0, x388, x385);
  fiat_p384_addcarryx_u64(&x391, &x392, x390, x386, x383);
  fiat_p384_addcarryx_u64(&x393, &x394, x392, x384, x381);
  fiat_p384_addcarryx_u64(&x395, &x396, x394, x382, x379);
  fiat_p384_addcarryx_u64(&x397, &x398, x396, x380, x377);
  x399 = (x398 + x378);
  fiat_p384_addcarryx_u64(&x400, &x401, 0x0, x364, x387);
  fiat_p384_addcarryx_u64(&x402, &x403, x401, x366, x389);
  fiat_p384_addcarryx_u64(&x404, &x405, x403, x368, x391);
  fiat_p384_addcarryx_u64(&x406, &x407, x405, x370, x393);
  fiat_p384_addcarryx_u64(&x408, &x409, x407, x372, x395);
  fiat_p384_addcarryx_u64(&x410, &x411, x409, x374, x397);
  fiat_p384_addcarryx_u64(&x412, &x413, x411, x376, x399);
  fiat_p384_mulx_u64(&x414, &x415, x400, UINT64_C(0x100000001));
  fiat_p384_mulx_u64(&x416, &x417, x414, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x418, &x419, x414, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x420, &x421, x414, UINT64_C(0xffffffffffffffff));
  fiat_p384_mulx_u64(&x422, &x423, x414, UINT64_C(0xfffffffffffffffe));
  fiat_p384_mulx_u64(&x424, &x425, x414, UINT64_C(0xffffffff00000000));
  fiat_p384_mulx_u64(&x426, &x427, x414, UINT32_C(0xffffffff));
  fiat_p384_addcarryx_u64(&x428, &x429, 0x0, x427, x424);
  fiat_p384_addcarryx_u64(&x430, &x431, x429, x425, x422);
  fiat_p384_addcarryx_u64(&x432, &x433, x431, x423, x420);
  fiat_p384_addcarryx_u64(&x434, &x435, x433, x421, x418);
  fiat_p384_addcarryx_u64(&x436, &x437, x435, x419, x416);
  x438 = (x437 + x417);
  fiat_p384_addcarryx_u64(&x439, &x440, 0x0, x400, x426);
  fiat_p384_addcarryx_u64(&x441, &x442, x440, x402, x428);
  fiat_p384_addcarryx_u64(&x443, &x444, x442, x404, x430);
  fiat_p384_addcarryx_u64(&x445, &x446, x444, x406, x432);
  fiat_p384_addcarryx_u64(&x447, &x448, x446, x408, x434);
  fiat_p384_addcarryx_u64(&x449, &x450, x448, x410, x436);
  fiat_p384_addcarryx_u64(&x451, &x452, x450, x412, x438);
  x453 = ((uint64_t)x452 + x413);
  fiat_p384_subborrowx_u64(&x454, &x455, 0x0, x441, UINT32_C(0xffffffff));
  fiat_p384_subborrowx_u64(&x456, &x457, x455, x443,
                           UINT64_C(0xffffffff00000000));
  fiat_p384_subborrowx_u64(&x458, &x459, x457, x445,
                           UINT64_C(0xfffffffffffffffe));
  fiat_p384_subborrowx_u64(&x460, &x461, x459, x447,
                           UINT64_C(0xffffffffffffffff));
  fiat_p384_subborrowx_u64(&x462, &x463, x461, x449,
                           UINT64_C(0xffffffffffffffff));
  fiat_p384_subborrowx_u64(&x464, &x465, x463, x451,
                           UINT64_C(0xffffffffffffffff));
  fiat_p384_subborrowx_u64(&x466, &x467, x465, x453, 0x0);
  fiat_p384_cmovznz_u64(&x468, x467, x454, x441);
  fiat_p384_cmovznz_u64(&x469, x467, x456, x443);
  fiat_p384_cmovznz_u64(&x470, x467, x458, x445);
  fiat_p384_cmovznz_u64(&x471, x467, x460, x447);
  fiat_p384_cmovznz_u64(&x472, x467, x462, x449);
  fiat_p384_cmovznz_u64(&x473, x467, x464, x451);
  out1[0] = x468;
  out1[1] = x469;
  out1[2] = x470;
  out1[3] = x471;
  out1[4] = x472;
  out1[5] = x473;
}

/* curve description: p434 */
/* machine_wordsize = 64 (from "64") */
/* requested operations: mul, square */
/* m =
 * 0x2341f271773446cfc5fd681c520567bc65c783158aea3fdc1767ae2ffffffffffffffffffffffffffffffffffffffffffffffffffffff
 * (from "2^216 * 3^137 - 1") */
/*                                                                    */
/* NOTE: In addition to the bounds specified above each function, all */
/*   functions synthesized for this Montgomery arithmetic require the */
/*   input to be strictly less than the prime modulus (m), and also   */
/*   require the input to be in the unique saturated representation.  */
/*   All functions also ensure that these two properties are true of  */
/*   return values.                                                   */
/*  */
/* Computed values: */
/* eval z = z[0] + (z[1] << 64) + (z[2] << 128) + (z[3] << 192) + (z[4] << 256)
 * + (z[5] << 0x140) + (z[6] << 0x180) */
/* bytes_eval z = z[0] + (z[1] << 8) + (z[2] << 16) + (z[3] << 24) + (z[4] <<
 * 32) + (z[5] << 40) + (z[6] << 48) + (z[7] << 56) + (z[8] << 64) + (z[9] <<
 * 72) + (z[10] << 80) + (z[11] << 88) + (z[12] << 96) + (z[13] << 104) + (z[14]
 * << 112) + (z[15] << 120) + (z[16] << 128) + (z[17] << 136) + (z[18] << 144) +
 * (z[19] << 152) + (z[20] << 160) + (z[21] << 168) + (z[22] << 176) + (z[23] <<
 * 184) + (z[24] << 192) + (z[25] << 200) + (z[26] << 208) + (z[27] << 216) +
 * (z[28] << 224) + (z[29] << 232) + (z[30] << 240) + (z[31] << 248) + (z[32] <<
 * 256) + (z[33] << 0x108) + (z[34] << 0x110) + (z[35] << 0x118) + (z[36] <<
 * 0x120) + (z[37] << 0x128) + (z[38] << 0x130) + (z[39] << 0x138) + (z[40] <<
 * 0x140) + (z[41] << 0x148) + (z[42] << 0x150) + (z[43] << 0x158) + (z[44] <<
 * 0x160) + (z[45] << 0x168) + (z[46] << 0x170) + (z[47] << 0x178) + (z[48] <<
 * 0x180) + (z[49] << 0x188) + (z[50] << 0x190) + (z[51] << 0x198) + (z[52] <<
 * 0x1a0) + (z[53] << 0x1a8) + (z[54] << 0x1b0) */

#include <stdint.h>
typedef unsigned char fiat_p434_uint1;
typedef signed char fiat_p434_int1;
typedef signed __int128 fiat_p434_int128;
typedef unsigned __int128 fiat_p434_uint128;

#if (-1 & 3) != 3
#error "This code only works on a two's complement system"
#endif

/*
 * The function fiat_p434_addcarryx_u64 is an addition with carry.
 * Postconditions:
 *   out1 = (arg1 + arg2 + arg3) mod 2^64
 *   out2 = ⌊(arg1 + arg2 + arg3) / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0x1]
 */
void fiat_p434_addcarryx_u64(uint64_t *out1, fiat_p434_uint1 *out2,
                             fiat_p434_uint1 arg1, uint64_t arg2,
                             uint64_t arg3) {
  fiat_p434_uint128 x1;
  uint64_t x2;
  fiat_p434_uint1 x3;
  x1 = ((arg1 + (fiat_p434_uint128)arg2) + arg3);
  x2 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  x3 = (fiat_p434_uint1)(x1 >> 64);
  *out1 = x2;
  *out2 = x3;
}

/*
 * The function fiat_p434_subborrowx_u64 is a subtraction with borrow.
 * Postconditions:
 *   out1 = (-arg1 + arg2 + -arg3) mod 2^64
 *   out2 = -⌊(-arg1 + arg2 + -arg3) / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0x1]
 */
void fiat_p434_subborrowx_u64(uint64_t *out1, fiat_p434_uint1 *out2,
                              fiat_p434_uint1 arg1, uint64_t arg2,
                              uint64_t arg3) {
  fiat_p434_int128 x1;
  fiat_p434_int1 x2;
  uint64_t x3;
  x1 = ((arg2 - (fiat_p434_int128)arg1) - arg3);
  x2 = (fiat_p434_int1)(x1 >> 64);
  x3 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  *out1 = x3;
  *out2 = (fiat_p434_uint1)(0x0 - x2);
}

/*
 * The function fiat_p434_mulx_u64 is a multiplication, returning the full
 * double-width result. Postconditions: out1 = (arg1 * arg2) mod 2^64 out2 =
 * ⌊arg1 * arg2 / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0xffffffffffffffff]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0xffffffffffffffff]
 */
void fiat_p434_mulx_u64(uint64_t *out1, uint64_t *out2, uint64_t arg1,
                        uint64_t arg2) {
  fiat_p434_uint128 x1;
  uint64_t x2;
  uint64_t x3;
  x1 = ((fiat_p434_uint128)arg1 * arg2);
  x2 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  x3 = (uint64_t)(x1 >> 64);
  *out1 = x2;
  *out2 = x3;
}

/*
 * The function fiat_p434_cmovznz_u64 is a single-word conditional move.
 * Postconditions:
 *   out1 = (if arg1 = 0 then arg2 else arg3)
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 */
void fiat_p434_cmovznz_u64(uint64_t *out1, fiat_p434_uint1 arg1, uint64_t arg2,
                           uint64_t arg3) {
  fiat_p434_uint1 x1;
  uint64_t x2;
  uint64_t x3;
  x1 = (!(!arg1));
  x2 = ((fiat_p434_int1)(0x0 - x1) & UINT64_C(0xffffffffffffffff));
  x3 = ((x2 & arg3) | ((~x2) & arg2));
  *out1 = x3;
}

/*
 * The function fiat_p434_mul multiplies two field elements in the Montgomery
 * domain. Preconditions: 0 ≤ eval arg1 < m 0 ≤ eval arg2 < m Postconditions:
 *   eval (from_montgomery out1) mod m = (eval (from_montgomery arg1) * eval
 * (from_montgomery arg2)) mod m 0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff]] arg2: [[0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]] Output Bounds: out1: [[0x0
 * ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff]]
 */
void fiat_p434_mul(uint64_t out1[7], const uint64_t arg1[7],
                   const uint64_t arg2[7]) {
  uint64_t x1;
  uint64_t x2;
  uint64_t x3;
  uint64_t x4;
  uint64_t x5;
  uint64_t x6;
  uint64_t x7;
  uint64_t x8;
  uint64_t x9;
  uint64_t x10;
  uint64_t x11;
  uint64_t x12;
  uint64_t x13;
  uint64_t x14;
  uint64_t x15;
  uint64_t x16;
  uint64_t x17;
  uint64_t x18;
  uint64_t x19;
  uint64_t x20;
  uint64_t x21;
  uint64_t x22;
  fiat_p434_uint1 x23;
  uint64_t x24;
  fiat_p434_uint1 x25;
  uint64_t x26;
  fiat_p434_uint1 x27;
  uint64_t x28;
  fiat_p434_uint1 x29;
  uint64_t x30;
  fiat_p434_uint1 x31;
  uint64_t x32;
  fiat_p434_uint1 x33;
  uint64_t x34;
  uint64_t x35;
  uint64_t x36;
  uint64_t x37;
  uint64_t x38;
  uint64_t x39;
  uint64_t x40;
  uint64_t x41;
  uint64_t x42;
  uint64_t x43;
  uint64_t x44;
  uint64_t x45;
  uint64_t x46;
  uint64_t x47;
  uint64_t x48;
  uint64_t x49;
  fiat_p434_uint1 x50;
  uint64_t x51;
  fiat_p434_uint1 x52;
  uint64_t x53;
  fiat_p434_uint1 x54;
  uint64_t x55;
  fiat_p434_uint1 x56;
  uint64_t x57;
  fiat_p434_uint1 x58;
  uint64_t x59;
  fiat_p434_uint1 x60;
  uint64_t x61;
  uint64_t x62;
  fiat_p434_uint1 x63;
  uint64_t x64;
  fiat_p434_uint1 x65;
  uint64_t x66;
  fiat_p434_uint1 x67;
  uint64_t x68;
  fiat_p434_uint1 x69;
  uint64_t x70;
  fiat_p434_uint1 x71;
  uint64_t x72;
  fiat_p434_uint1 x73;
  uint64_t x74;
  fiat_p434_uint1 x75;
  uint64_t x76;
  fiat_p434_uint1 x77;
  uint64_t x78;
  uint64_t x79;
  uint64_t x80;
  uint64_t x81;
  uint64_t x82;
  uint64_t x83;
  uint64_t x84;
  uint64_t x85;
  uint64_t x86;
  uint64_t x87;
  uint64_t x88;
  uint64_t x89;
  uint64_t x90;
  uint64_t x91;
  uint64_t x92;
  fiat_p434_uint1 x93;
  uint64_t x94;
  fiat_p434_uint1 x95;
  uint64_t x96;
  fiat_p434_uint1 x97;
  uint64_t x98;
  fiat_p434_uint1 x99;
  uint64_t x100;
  fiat_p434_uint1 x101;
  uint64_t x102;
  fiat_p434_uint1 x103;
  uint64_t x104;
  uint64_t x105;
  fiat_p434_uint1 x106;
  uint64_t x107;
  fiat_p434_uint1 x108;
  uint64_t x109;
  fiat_p434_uint1 x110;
  uint64_t x111;
  fiat_p434_uint1 x112;
  uint64_t x113;
  fiat_p434_uint1 x114;
  uint64_t x115;
  fiat_p434_uint1 x116;
  uint64_t x117;
  fiat_p434_uint1 x118;
  uint64_t x119;
  fiat_p434_uint1 x120;
  uint64_t x121;
  uint64_t x122;
  uint64_t x123;
  uint64_t x124;
  uint64_t x125;
  uint64_t x126;
  uint64_t x127;
  uint64_t x128;
  uint64_t x129;
  uint64_t x130;
  uint64_t x131;
  uint64_t x132;
  uint64_t x133;
  uint64_t x134;
  uint64_t x135;
  fiat_p434_uint1 x136;
  uint64_t x137;
  fiat_p434_uint1 x138;
  uint64_t x139;
  fiat_p434_uint1 x140;
  uint64_t x141;
  fiat_p434_uint1 x142;
  uint64_t x143;
  fiat_p434_uint1 x144;
  uint64_t x145;
  fiat_p434_uint1 x146;
  uint64_t x147;
  uint64_t x148;
  fiat_p434_uint1 x149;
  uint64_t x150;
  fiat_p434_uint1 x151;
  uint64_t x152;
  fiat_p434_uint1 x153;
  uint64_t x154;
  fiat_p434_uint1 x155;
  uint64_t x156;
  fiat_p434_uint1 x157;
  uint64_t x158;
  fiat_p434_uint1 x159;
  uint64_t x160;
  fiat_p434_uint1 x161;
  uint64_t x162;
  fiat_p434_uint1 x163;
  uint64_t x164;
  uint64_t x165;
  uint64_t x166;
  uint64_t x167;
  uint64_t x168;
  uint64_t x169;
  uint64_t x170;
  uint64_t x171;
  uint64_t x172;
  uint64_t x173;
  uint64_t x174;
  uint64_t x175;
  uint64_t x176;
  uint64_t x177;
  uint64_t x178;
  uint64_t x179;
  fiat_p434_uint1 x180;
  uint64_t x181;
  fiat_p434_uint1 x182;
  uint64_t x183;
  fiat_p434_uint1 x184;
  uint64_t x185;
  fiat_p434_uint1 x186;
  uint64_t x187;
  fiat_p434_uint1 x188;
  uint64_t x189;
  fiat_p434_uint1 x190;
  uint64_t x191;
  uint64_t x192;
  fiat_p434_uint1 x193;
  uint64_t x194;
  fiat_p434_uint1 x195;
  uint64_t x196;
  fiat_p434_uint1 x197;
  uint64_t x198;
  fiat_p434_uint1 x199;
  uint64_t x200;
  fiat_p434_uint1 x201;
  uint64_t x202;
  fiat_p434_uint1 x203;
  uint64_t x204;
  fiat_p434_uint1 x205;
  uint64_t x206;
  fiat_p434_uint1 x207;
  uint64_t x208;
  uint64_t x209;
  uint64_t x210;
  uint64_t x211;
  uint64_t x212;
  uint64_t x213;
  uint64_t x214;
  uint64_t x215;
  uint64_t x216;
  uint64_t x217;
  uint64_t x218;
  uint64_t x219;
  uint64_t x220;
  uint64_t x221;
  uint64_t x222;
  fiat_p434_uint1 x223;
  uint64_t x224;
  fiat_p434_uint1 x225;
  uint64_t x226;
  fiat_p434_uint1 x227;
  uint64_t x228;
  fiat_p434_uint1 x229;
  uint64_t x230;
  fiat_p434_uint1 x231;
  uint64_t x232;
  fiat_p434_uint1 x233;
  uint64_t x234;
  uint64_t x235;
  fiat_p434_uint1 x236;
  uint64_t x237;
  fiat_p434_uint1 x238;
  uint64_t x239;
  fiat_p434_uint1 x240;
  uint64_t x241;
  fiat_p434_uint1 x242;
  uint64_t x243;
  fiat_p434_uint1 x244;
  uint64_t x245;
  fiat_p434_uint1 x246;
  uint64_t x247;
  fiat_p434_uint1 x248;
  uint64_t x249;
  fiat_p434_uint1 x250;
  uint64_t x251;
  uint64_t x252;
  uint64_t x253;
  uint64_t x254;
  uint64_t x255;
  uint64_t x256;
  uint64_t x257;
  uint64_t x258;
  uint64_t x259;
  uint64_t x260;
  uint64_t x261;
  uint64_t x262;
  uint64_t x263;
  uint64_t x264;
  uint64_t x265;
  uint64_t x266;
  fiat_p434_uint1 x267;
  uint64_t x268;
  fiat_p434_uint1 x269;
  uint64_t x270;
  fiat_p434_uint1 x271;
  uint64_t x272;
  fiat_p434_uint1 x273;
  uint64_t x274;
  fiat_p434_uint1 x275;
  uint64_t x276;
  fiat_p434_uint1 x277;
  uint64_t x278;
  uint64_t x279;
  fiat_p434_uint1 x280;
  uint64_t x281;
  fiat_p434_uint1 x282;
  uint64_t x283;
  fiat_p434_uint1 x284;
  uint64_t x285;
  fiat_p434_uint1 x286;
  uint64_t x287;
  fiat_p434_uint1 x288;
  uint64_t x289;
  fiat_p434_uint1 x290;
  uint64_t x291;
  fiat_p434_uint1 x292;
  uint64_t x293;
  fiat_p434_uint1 x294;
  uint64_t x295;
  uint64_t x296;
  uint64_t x297;
  uint64_t x298;
  uint64_t x299;
  uint64_t x300;
  uint64_t x301;
  uint64_t x302;
  uint64_t x303;
  uint64_t x304;
  uint64_t x305;
  uint64_t x306;
  uint64_t x307;
  uint64_t x308;
  uint64_t x309;
  fiat_p434_uint1 x310;
  uint64_t x311;
  fiat_p434_uint1 x312;
  uint64_t x313;
  fiat_p434_uint1 x314;
  uint64_t x315;
  fiat_p434_uint1 x316;
  uint64_t x317;
  fiat_p434_uint1 x318;
  uint64_t x319;
  fiat_p434_uint1 x320;
  uint64_t x321;
  uint64_t x322;
  fiat_p434_uint1 x323;
  uint64_t x324;
  fiat_p434_uint1 x325;
  uint64_t x326;
  fiat_p434_uint1 x327;
  uint64_t x328;
  fiat_p434_uint1 x329;
  uint64_t x330;
  fiat_p434_uint1 x331;
  uint64_t x332;
  fiat_p434_uint1 x333;
  uint64_t x334;
  fiat_p434_uint1 x335;
  uint64_t x336;
  fiat_p434_uint1 x337;
  uint64_t x338;
  uint64_t x339;
  uint64_t x340;
  uint64_t x341;
  uint64_t x342;
  uint64_t x343;
  uint64_t x344;
  uint64_t x345;
  uint64_t x346;
  uint64_t x347;
  uint64_t x348;
  uint64_t x349;
  uint64_t x350;
  uint64_t x351;
  uint64_t x352;
  uint64_t x353;
  fiat_p434_uint1 x354;
  uint64_t x355;
  fiat_p434_uint1 x356;
  uint64_t x357;
  fiat_p434_uint1 x358;
  uint64_t x359;
  fiat_p434_uint1 x360;
  uint64_t x361;
  fiat_p434_uint1 x362;
  uint64_t x363;
  fiat_p434_uint1 x364;
  uint64_t x365;
  uint64_t x366;
  fiat_p434_uint1 x367;
  uint64_t x368;
  fiat_p434_uint1 x369;
  uint64_t x370;
  fiat_p434_uint1 x371;
  uint64_t x372;
  fiat_p434_uint1 x373;
  uint64_t x374;
  fiat_p434_uint1 x375;
  uint64_t x376;
  fiat_p434_uint1 x377;
  uint64_t x378;
  fiat_p434_uint1 x379;
  uint64_t x380;
  fiat_p434_uint1 x381;
  uint64_t x382;
  uint64_t x383;
  uint64_t x384;
  uint64_t x385;
  uint64_t x386;
  uint64_t x387;
  uint64_t x388;
  uint64_t x389;
  uint64_t x390;
  uint64_t x391;
  uint64_t x392;
  uint64_t x393;
  uint64_t x394;
  uint64_t x395;
  uint64_t x396;
  fiat_p434_uint1 x397;
  uint64_t x398;
  fiat_p434_uint1 x399;
  uint64_t x400;
  fiat_p434_uint1 x401;
  uint64_t x402;
  fiat_p434_uint1 x403;
  uint64_t x404;
  fiat_p434_uint1 x405;
  uint64_t x406;
  fiat_p434_uint1 x407;
  uint64_t x408;
  uint64_t x409;
  fiat_p434_uint1 x410;
  uint64_t x411;
  fiat_p434_uint1 x412;
  uint64_t x413;
  fiat_p434_uint1 x414;
  uint64_t x415;
  fiat_p434_uint1 x416;
  uint64_t x417;
  fiat_p434_uint1 x418;
  uint64_t x419;
  fiat_p434_uint1 x420;
  uint64_t x421;
  fiat_p434_uint1 x422;
  uint64_t x423;
  fiat_p434_uint1 x424;
  uint64_t x425;
  uint64_t x426;
  uint64_t x427;
  uint64_t x428;
  uint64_t x429;
  uint64_t x430;
  uint64_t x431;
  uint64_t x432;
  uint64_t x433;
  uint64_t x434;
  uint64_t x435;
  uint64_t x436;
  uint64_t x437;
  uint64_t x438;
  uint64_t x439;
  uint64_t x440;
  fiat_p434_uint1 x441;
  uint64_t x442;
  fiat_p434_uint1 x443;
  uint64_t x444;
  fiat_p434_uint1 x445;
  uint64_t x446;
  fiat_p434_uint1 x447;
  uint64_t x448;
  fiat_p434_uint1 x449;
  uint64_t x450;
  fiat_p434_uint1 x451;
  uint64_t x452;
  uint64_t x453;
  fiat_p434_uint1 x454;
  uint64_t x455;
  fiat_p434_uint1 x456;
  uint64_t x457;
  fiat_p434_uint1 x458;
  uint64_t x459;
  fiat_p434_uint1 x460;
  uint64_t x461;
  fiat_p434_uint1 x462;
  uint64_t x463;
  fiat_p434_uint1 x464;
  uint64_t x465;
  fiat_p434_uint1 x466;
  uint64_t x467;
  fiat_p434_uint1 x468;
  uint64_t x469;
  uint64_t x470;
  uint64_t x471;
  uint64_t x472;
  uint64_t x473;
  uint64_t x474;
  uint64_t x475;
  uint64_t x476;
  uint64_t x477;
  uint64_t x478;
  uint64_t x479;
  uint64_t x480;
  uint64_t x481;
  uint64_t x482;
  uint64_t x483;
  fiat_p434_uint1 x484;
  uint64_t x485;
  fiat_p434_uint1 x486;
  uint64_t x487;
  fiat_p434_uint1 x488;
  uint64_t x489;
  fiat_p434_uint1 x490;
  uint64_t x491;
  fiat_p434_uint1 x492;
  uint64_t x493;
  fiat_p434_uint1 x494;
  uint64_t x495;
  uint64_t x496;
  fiat_p434_uint1 x497;
  uint64_t x498;
  fiat_p434_uint1 x499;
  uint64_t x500;
  fiat_p434_uint1 x501;
  uint64_t x502;
  fiat_p434_uint1 x503;
  uint64_t x504;
  fiat_p434_uint1 x505;
  uint64_t x506;
  fiat_p434_uint1 x507;
  uint64_t x508;
  fiat_p434_uint1 x509;
  uint64_t x510;
  fiat_p434_uint1 x511;
  uint64_t x512;
  uint64_t x513;
  uint64_t x514;
  uint64_t x515;
  uint64_t x516;
  uint64_t x517;
  uint64_t x518;
  uint64_t x519;
  uint64_t x520;
  uint64_t x521;
  uint64_t x522;
  uint64_t x523;
  uint64_t x524;
  uint64_t x525;
  uint64_t x526;
  uint64_t x527;
  fiat_p434_uint1 x528;
  uint64_t x529;
  fiat_p434_uint1 x530;
  uint64_t x531;
  fiat_p434_uint1 x532;
  uint64_t x533;
  fiat_p434_uint1 x534;
  uint64_t x535;
  fiat_p434_uint1 x536;
  uint64_t x537;
  fiat_p434_uint1 x538;
  uint64_t x539;
  uint64_t x540;
  fiat_p434_uint1 x541;
  uint64_t x542;
  fiat_p434_uint1 x543;
  uint64_t x544;
  fiat_p434_uint1 x545;
  uint64_t x546;
  fiat_p434_uint1 x547;
  uint64_t x548;
  fiat_p434_uint1 x549;
  uint64_t x550;
  fiat_p434_uint1 x551;
  uint64_t x552;
  fiat_p434_uint1 x553;
  uint64_t x554;
  fiat_p434_uint1 x555;
  uint64_t x556;
  uint64_t x557;
  uint64_t x558;
  uint64_t x559;
  uint64_t x560;
  uint64_t x561;
  uint64_t x562;
  uint64_t x563;
  uint64_t x564;
  uint64_t x565;
  uint64_t x566;
  uint64_t x567;
  uint64_t x568;
  uint64_t x569;
  uint64_t x570;
  fiat_p434_uint1 x571;
  uint64_t x572;
  fiat_p434_uint1 x573;
  uint64_t x574;
  fiat_p434_uint1 x575;
  uint64_t x576;
  fiat_p434_uint1 x577;
  uint64_t x578;
  fiat_p434_uint1 x579;
  uint64_t x580;
  fiat_p434_uint1 x581;
  uint64_t x582;
  uint64_t x583;
  fiat_p434_uint1 x584;
  uint64_t x585;
  fiat_p434_uint1 x586;
  uint64_t x587;
  fiat_p434_uint1 x588;
  uint64_t x589;
  fiat_p434_uint1 x590;
  uint64_t x591;
  fiat_p434_uint1 x592;
  uint64_t x593;
  fiat_p434_uint1 x594;
  uint64_t x595;
  fiat_p434_uint1 x596;
  uint64_t x597;
  fiat_p434_uint1 x598;
  uint64_t x599;
  uint64_t x600;
  fiat_p434_uint1 x601;
  uint64_t x602;
  fiat_p434_uint1 x603;
  uint64_t x604;
  fiat_p434_uint1 x605;
  uint64_t x606;
  fiat_p434_uint1 x607;
  uint64_t x608;
  fiat_p434_uint1 x609;
  uint64_t x610;
  fiat_p434_uint1 x611;
  uint64_t x612;
  fiat_p434_uint1 x613;
  uint64_t x614;
  fiat_p434_uint1 x615;
  uint64_t x616;
  uint64_t x617;
  uint64_t x618;
  uint64_t x619;
  uint64_t x620;
  uint64_t x621;
  uint64_t x622;
  x1 = (arg1[1]);
  x2 = (arg1[2]);
  x3 = (arg1[3]);
  x4 = (arg1[4]);
  x5 = (arg1[5]);
  x6 = (arg1[6]);
  x7 = (arg1[0]);
  fiat_p434_mulx_u64(&x8, &x9, x7, (arg2[6]));
  fiat_p434_mulx_u64(&x10, &x11, x7, (arg2[5]));
  fiat_p434_mulx_u64(&x12, &x13, x7, (arg2[4]));
  fiat_p434_mulx_u64(&x14, &x15, x7, (arg2[3]));
  fiat_p434_mulx_u64(&x16, &x17, x7, (arg2[2]));
  fiat_p434_mulx_u64(&x18, &x19, x7, (arg2[1]));
  fiat_p434_mulx_u64(&x20, &x21, x7, (arg2[0]));
  fiat_p434_addcarryx_u64(&x22, &x23, 0x0, x21, x18);
  fiat_p434_addcarryx_u64(&x24, &x25, x23, x19, x16);
  fiat_p434_addcarryx_u64(&x26, &x27, x25, x17, x14);
  fiat_p434_addcarryx_u64(&x28, &x29, x27, x15, x12);
  fiat_p434_addcarryx_u64(&x30, &x31, x29, x13, x10);
  fiat_p434_addcarryx_u64(&x32, &x33, x31, x11, x8);
  x34 = (x33 + x9);
  fiat_p434_mulx_u64(&x35, &x36, x20, UINT64_C(0x2341f27177344));
  fiat_p434_mulx_u64(&x37, &x38, x20, UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_mulx_u64(&x39, &x40, x20, UINT64_C(0x7bc65c783158aea3));
  fiat_p434_mulx_u64(&x41, &x42, x20, UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_mulx_u64(&x43, &x44, x20, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x45, &x46, x20, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x47, &x48, x20, UINT64_C(0xffffffffffffffff));
  fiat_p434_addcarryx_u64(&x49, &x50, 0x0, x48, x45);
  fiat_p434_addcarryx_u64(&x51, &x52, x50, x46, x43);
  fiat_p434_addcarryx_u64(&x53, &x54, x52, x44, x41);
  fiat_p434_addcarryx_u64(&x55, &x56, x54, x42, x39);
  fiat_p434_addcarryx_u64(&x57, &x58, x56, x40, x37);
  fiat_p434_addcarryx_u64(&x59, &x60, x58, x38, x35);
  x61 = (x60 + x36);
  fiat_p434_addcarryx_u64(&x62, &x63, 0x0, x20, x47);
  fiat_p434_addcarryx_u64(&x64, &x65, x63, x22, x49);
  fiat_p434_addcarryx_u64(&x66, &x67, x65, x24, x51);
  fiat_p434_addcarryx_u64(&x68, &x69, x67, x26, x53);
  fiat_p434_addcarryx_u64(&x70, &x71, x69, x28, x55);
  fiat_p434_addcarryx_u64(&x72, &x73, x71, x30, x57);
  fiat_p434_addcarryx_u64(&x74, &x75, x73, x32, x59);
  fiat_p434_addcarryx_u64(&x76, &x77, x75, x34, x61);
  fiat_p434_mulx_u64(&x78, &x79, x1, (arg2[6]));
  fiat_p434_mulx_u64(&x80, &x81, x1, (arg2[5]));
  fiat_p434_mulx_u64(&x82, &x83, x1, (arg2[4]));
  fiat_p434_mulx_u64(&x84, &x85, x1, (arg2[3]));
  fiat_p434_mulx_u64(&x86, &x87, x1, (arg2[2]));
  fiat_p434_mulx_u64(&x88, &x89, x1, (arg2[1]));
  fiat_p434_mulx_u64(&x90, &x91, x1, (arg2[0]));
  fiat_p434_addcarryx_u64(&x92, &x93, 0x0, x91, x88);
  fiat_p434_addcarryx_u64(&x94, &x95, x93, x89, x86);
  fiat_p434_addcarryx_u64(&x96, &x97, x95, x87, x84);
  fiat_p434_addcarryx_u64(&x98, &x99, x97, x85, x82);
  fiat_p434_addcarryx_u64(&x100, &x101, x99, x83, x80);
  fiat_p434_addcarryx_u64(&x102, &x103, x101, x81, x78);
  x104 = (x103 + x79);
  fiat_p434_addcarryx_u64(&x105, &x106, 0x0, x64, x90);
  fiat_p434_addcarryx_u64(&x107, &x108, x106, x66, x92);
  fiat_p434_addcarryx_u64(&x109, &x110, x108, x68, x94);
  fiat_p434_addcarryx_u64(&x111, &x112, x110, x70, x96);
  fiat_p434_addcarryx_u64(&x113, &x114, x112, x72, x98);
  fiat_p434_addcarryx_u64(&x115, &x116, x114, x74, x100);
  fiat_p434_addcarryx_u64(&x117, &x118, x116, x76, x102);
  fiat_p434_addcarryx_u64(&x119, &x120, x118, x77, x104);
  fiat_p434_mulx_u64(&x121, &x122, x105, UINT64_C(0x2341f27177344));
  fiat_p434_mulx_u64(&x123, &x124, x105, UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_mulx_u64(&x125, &x126, x105, UINT64_C(0x7bc65c783158aea3));
  fiat_p434_mulx_u64(&x127, &x128, x105, UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_mulx_u64(&x129, &x130, x105, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x131, &x132, x105, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x133, &x134, x105, UINT64_C(0xffffffffffffffff));
  fiat_p434_addcarryx_u64(&x135, &x136, 0x0, x134, x131);
  fiat_p434_addcarryx_u64(&x137, &x138, x136, x132, x129);
  fiat_p434_addcarryx_u64(&x139, &x140, x138, x130, x127);
  fiat_p434_addcarryx_u64(&x141, &x142, x140, x128, x125);
  fiat_p434_addcarryx_u64(&x143, &x144, x142, x126, x123);
  fiat_p434_addcarryx_u64(&x145, &x146, x144, x124, x121);
  x147 = (x146 + x122);
  fiat_p434_addcarryx_u64(&x148, &x149, 0x0, x105, x133);
  fiat_p434_addcarryx_u64(&x150, &x151, x149, x107, x135);
  fiat_p434_addcarryx_u64(&x152, &x153, x151, x109, x137);
  fiat_p434_addcarryx_u64(&x154, &x155, x153, x111, x139);
  fiat_p434_addcarryx_u64(&x156, &x157, x155, x113, x141);
  fiat_p434_addcarryx_u64(&x158, &x159, x157, x115, x143);
  fiat_p434_addcarryx_u64(&x160, &x161, x159, x117, x145);
  fiat_p434_addcarryx_u64(&x162, &x163, x161, x119, x147);
  x164 = ((uint64_t)x163 + x120);
  fiat_p434_mulx_u64(&x165, &x166, x2, (arg2[6]));
  fiat_p434_mulx_u64(&x167, &x168, x2, (arg2[5]));
  fiat_p434_mulx_u64(&x169, &x170, x2, (arg2[4]));
  fiat_p434_mulx_u64(&x171, &x172, x2, (arg2[3]));
  fiat_p434_mulx_u64(&x173, &x174, x2, (arg2[2]));
  fiat_p434_mulx_u64(&x175, &x176, x2, (arg2[1]));
  fiat_p434_mulx_u64(&x177, &x178, x2, (arg2[0]));
  fiat_p434_addcarryx_u64(&x179, &x180, 0x0, x178, x175);
  fiat_p434_addcarryx_u64(&x181, &x182, x180, x176, x173);
  fiat_p434_addcarryx_u64(&x183, &x184, x182, x174, x171);
  fiat_p434_addcarryx_u64(&x185, &x186, x184, x172, x169);
  fiat_p434_addcarryx_u64(&x187, &x188, x186, x170, x167);
  fiat_p434_addcarryx_u64(&x189, &x190, x188, x168, x165);
  x191 = (x190 + x166);
  fiat_p434_addcarryx_u64(&x192, &x193, 0x0, x150, x177);
  fiat_p434_addcarryx_u64(&x194, &x195, x193, x152, x179);
  fiat_p434_addcarryx_u64(&x196, &x197, x195, x154, x181);
  fiat_p434_addcarryx_u64(&x198, &x199, x197, x156, x183);
  fiat_p434_addcarryx_u64(&x200, &x201, x199, x158, x185);
  fiat_p434_addcarryx_u64(&x202, &x203, x201, x160, x187);
  fiat_p434_addcarryx_u64(&x204, &x205, x203, x162, x189);
  fiat_p434_addcarryx_u64(&x206, &x207, x205, x164, x191);
  fiat_p434_mulx_u64(&x208, &x209, x192, UINT64_C(0x2341f27177344));
  fiat_p434_mulx_u64(&x210, &x211, x192, UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_mulx_u64(&x212, &x213, x192, UINT64_C(0x7bc65c783158aea3));
  fiat_p434_mulx_u64(&x214, &x215, x192, UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_mulx_u64(&x216, &x217, x192, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x218, &x219, x192, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x220, &x221, x192, UINT64_C(0xffffffffffffffff));
  fiat_p434_addcarryx_u64(&x222, &x223, 0x0, x221, x218);
  fiat_p434_addcarryx_u64(&x224, &x225, x223, x219, x216);
  fiat_p434_addcarryx_u64(&x226, &x227, x225, x217, x214);
  fiat_p434_addcarryx_u64(&x228, &x229, x227, x215, x212);
  fiat_p434_addcarryx_u64(&x230, &x231, x229, x213, x210);
  fiat_p434_addcarryx_u64(&x232, &x233, x231, x211, x208);
  x234 = (x233 + x209);
  fiat_p434_addcarryx_u64(&x235, &x236, 0x0, x192, x220);
  fiat_p434_addcarryx_u64(&x237, &x238, x236, x194, x222);
  fiat_p434_addcarryx_u64(&x239, &x240, x238, x196, x224);
  fiat_p434_addcarryx_u64(&x241, &x242, x240, x198, x226);
  fiat_p434_addcarryx_u64(&x243, &x244, x242, x200, x228);
  fiat_p434_addcarryx_u64(&x245, &x246, x244, x202, x230);
  fiat_p434_addcarryx_u64(&x247, &x248, x246, x204, x232);
  fiat_p434_addcarryx_u64(&x249, &x250, x248, x206, x234);
  x251 = ((uint64_t)x250 + x207);
  fiat_p434_mulx_u64(&x252, &x253, x3, (arg2[6]));
  fiat_p434_mulx_u64(&x254, &x255, x3, (arg2[5]));
  fiat_p434_mulx_u64(&x256, &x257, x3, (arg2[4]));
  fiat_p434_mulx_u64(&x258, &x259, x3, (arg2[3]));
  fiat_p434_mulx_u64(&x260, &x261, x3, (arg2[2]));
  fiat_p434_mulx_u64(&x262, &x263, x3, (arg2[1]));
  fiat_p434_mulx_u64(&x264, &x265, x3, (arg2[0]));
  fiat_p434_addcarryx_u64(&x266, &x267, 0x0, x265, x262);
  fiat_p434_addcarryx_u64(&x268, &x269, x267, x263, x260);
  fiat_p434_addcarryx_u64(&x270, &x271, x269, x261, x258);
  fiat_p434_addcarryx_u64(&x272, &x273, x271, x259, x256);
  fiat_p434_addcarryx_u64(&x274, &x275, x273, x257, x254);
  fiat_p434_addcarryx_u64(&x276, &x277, x275, x255, x252);
  x278 = (x277 + x253);
  fiat_p434_addcarryx_u64(&x279, &x280, 0x0, x237, x264);
  fiat_p434_addcarryx_u64(&x281, &x282, x280, x239, x266);
  fiat_p434_addcarryx_u64(&x283, &x284, x282, x241, x268);
  fiat_p434_addcarryx_u64(&x285, &x286, x284, x243, x270);
  fiat_p434_addcarryx_u64(&x287, &x288, x286, x245, x272);
  fiat_p434_addcarryx_u64(&x289, &x290, x288, x247, x274);
  fiat_p434_addcarryx_u64(&x291, &x292, x290, x249, x276);
  fiat_p434_addcarryx_u64(&x293, &x294, x292, x251, x278);
  fiat_p434_mulx_u64(&x295, &x296, x279, UINT64_C(0x2341f27177344));
  fiat_p434_mulx_u64(&x297, &x298, x279, UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_mulx_u64(&x299, &x300, x279, UINT64_C(0x7bc65c783158aea3));
  fiat_p434_mulx_u64(&x301, &x302, x279, UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_mulx_u64(&x303, &x304, x279, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x305, &x306, x279, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x307, &x308, x279, UINT64_C(0xffffffffffffffff));
  fiat_p434_addcarryx_u64(&x309, &x310, 0x0, x308, x305);
  fiat_p434_addcarryx_u64(&x311, &x312, x310, x306, x303);
  fiat_p434_addcarryx_u64(&x313, &x314, x312, x304, x301);
  fiat_p434_addcarryx_u64(&x315, &x316, x314, x302, x299);
  fiat_p434_addcarryx_u64(&x317, &x318, x316, x300, x297);
  fiat_p434_addcarryx_u64(&x319, &x320, x318, x298, x295);
  x321 = (x320 + x296);
  fiat_p434_addcarryx_u64(&x322, &x323, 0x0, x279, x307);
  fiat_p434_addcarryx_u64(&x324, &x325, x323, x281, x309);
  fiat_p434_addcarryx_u64(&x326, &x327, x325, x283, x311);
  fiat_p434_addcarryx_u64(&x328, &x329, x327, x285, x313);
  fiat_p434_addcarryx_u64(&x330, &x331, x329, x287, x315);
  fiat_p434_addcarryx_u64(&x332, &x333, x331, x289, x317);
  fiat_p434_addcarryx_u64(&x334, &x335, x333, x291, x319);
  fiat_p434_addcarryx_u64(&x336, &x337, x335, x293, x321);
  x338 = ((uint64_t)x337 + x294);
  fiat_p434_mulx_u64(&x339, &x340, x4, (arg2[6]));
  fiat_p434_mulx_u64(&x341, &x342, x4, (arg2[5]));
  fiat_p434_mulx_u64(&x343, &x344, x4, (arg2[4]));
  fiat_p434_mulx_u64(&x345, &x346, x4, (arg2[3]));
  fiat_p434_mulx_u64(&x347, &x348, x4, (arg2[2]));
  fiat_p434_mulx_u64(&x349, &x350, x4, (arg2[1]));
  fiat_p434_mulx_u64(&x351, &x352, x4, (arg2[0]));
  fiat_p434_addcarryx_u64(&x353, &x354, 0x0, x352, x349);
  fiat_p434_addcarryx_u64(&x355, &x356, x354, x350, x347);
  fiat_p434_addcarryx_u64(&x357, &x358, x356, x348, x345);
  fiat_p434_addcarryx_u64(&x359, &x360, x358, x346, x343);
  fiat_p434_addcarryx_u64(&x361, &x362, x360, x344, x341);
  fiat_p434_addcarryx_u64(&x363, &x364, x362, x342, x339);
  x365 = (x364 + x340);
  fiat_p434_addcarryx_u64(&x366, &x367, 0x0, x324, x351);
  fiat_p434_addcarryx_u64(&x368, &x369, x367, x326, x353);
  fiat_p434_addcarryx_u64(&x370, &x371, x369, x328, x355);
  fiat_p434_addcarryx_u64(&x372, &x373, x371, x330, x357);
  fiat_p434_addcarryx_u64(&x374, &x375, x373, x332, x359);
  fiat_p434_addcarryx_u64(&x376, &x377, x375, x334, x361);
  fiat_p434_addcarryx_u64(&x378, &x379, x377, x336, x363);
  fiat_p434_addcarryx_u64(&x380, &x381, x379, x338, x365);
  fiat_p434_mulx_u64(&x382, &x383, x366, UINT64_C(0x2341f27177344));
  fiat_p434_mulx_u64(&x384, &x385, x366, UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_mulx_u64(&x386, &x387, x366, UINT64_C(0x7bc65c783158aea3));
  fiat_p434_mulx_u64(&x388, &x389, x366, UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_mulx_u64(&x390, &x391, x366, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x392, &x393, x366, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x394, &x395, x366, UINT64_C(0xffffffffffffffff));
  fiat_p434_addcarryx_u64(&x396, &x397, 0x0, x395, x392);
  fiat_p434_addcarryx_u64(&x398, &x399, x397, x393, x390);
  fiat_p434_addcarryx_u64(&x400, &x401, x399, x391, x388);
  fiat_p434_addcarryx_u64(&x402, &x403, x401, x389, x386);
  fiat_p434_addcarryx_u64(&x404, &x405, x403, x387, x384);
  fiat_p434_addcarryx_u64(&x406, &x407, x405, x385, x382);
  x408 = (x407 + x383);
  fiat_p434_addcarryx_u64(&x409, &x410, 0x0, x366, x394);
  fiat_p434_addcarryx_u64(&x411, &x412, x410, x368, x396);
  fiat_p434_addcarryx_u64(&x413, &x414, x412, x370, x398);
  fiat_p434_addcarryx_u64(&x415, &x416, x414, x372, x400);
  fiat_p434_addcarryx_u64(&x417, &x418, x416, x374, x402);
  fiat_p434_addcarryx_u64(&x419, &x420, x418, x376, x404);
  fiat_p434_addcarryx_u64(&x421, &x422, x420, x378, x406);
  fiat_p434_addcarryx_u64(&x423, &x424, x422, x380, x408);
  x425 = ((uint64_t)x424 + x381);
  fiat_p434_mulx_u64(&x426, &x427, x5, (arg2[6]));
  fiat_p434_mulx_u64(&x428, &x429, x5, (arg2[5]));
  fiat_p434_mulx_u64(&x430, &x431, x5, (arg2[4]));
  fiat_p434_mulx_u64(&x432, &x433, x5, (arg2[3]));
  fiat_p434_mulx_u64(&x434, &x435, x5, (arg2[2]));
  fiat_p434_mulx_u64(&x436, &x437, x5, (arg2[1]));
  fiat_p434_mulx_u64(&x438, &x439, x5, (arg2[0]));
  fiat_p434_addcarryx_u64(&x440, &x441, 0x0, x439, x436);
  fiat_p434_addcarryx_u64(&x442, &x443, x441, x437, x434);
  fiat_p434_addcarryx_u64(&x444, &x445, x443, x435, x432);
  fiat_p434_addcarryx_u64(&x446, &x447, x445, x433, x430);
  fiat_p434_addcarryx_u64(&x448, &x449, x447, x431, x428);
  fiat_p434_addcarryx_u64(&x450, &x451, x449, x429, x426);
  x452 = (x451 + x427);
  fiat_p434_addcarryx_u64(&x453, &x454, 0x0, x411, x438);
  fiat_p434_addcarryx_u64(&x455, &x456, x454, x413, x440);
  fiat_p434_addcarryx_u64(&x457, &x458, x456, x415, x442);
  fiat_p434_addcarryx_u64(&x459, &x460, x458, x417, x444);
  fiat_p434_addcarryx_u64(&x461, &x462, x460, x419, x446);
  fiat_p434_addcarryx_u64(&x463, &x464, x462, x421, x448);
  fiat_p434_addcarryx_u64(&x465, &x466, x464, x423, x450);
  fiat_p434_addcarryx_u64(&x467, &x468, x466, x425, x452);
  fiat_p434_mulx_u64(&x469, &x470, x453, UINT64_C(0x2341f27177344));
  fiat_p434_mulx_u64(&x471, &x472, x453, UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_mulx_u64(&x473, &x474, x453, UINT64_C(0x7bc65c783158aea3));
  fiat_p434_mulx_u64(&x475, &x476, x453, UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_mulx_u64(&x477, &x478, x453, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x479, &x480, x453, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x481, &x482, x453, UINT64_C(0xffffffffffffffff));
  fiat_p434_addcarryx_u64(&x483, &x484, 0x0, x482, x479);
  fiat_p434_addcarryx_u64(&x485, &x486, x484, x480, x477);
  fiat_p434_addcarryx_u64(&x487, &x488, x486, x478, x475);
  fiat_p434_addcarryx_u64(&x489, &x490, x488, x476, x473);
  fiat_p434_addcarryx_u64(&x491, &x492, x490, x474, x471);
  fiat_p434_addcarryx_u64(&x493, &x494, x492, x472, x469);
  x495 = (x494 + x470);
  fiat_p434_addcarryx_u64(&x496, &x497, 0x0, x453, x481);
  fiat_p434_addcarryx_u64(&x498, &x499, x497, x455, x483);
  fiat_p434_addcarryx_u64(&x500, &x501, x499, x457, x485);
  fiat_p434_addcarryx_u64(&x502, &x503, x501, x459, x487);
  fiat_p434_addcarryx_u64(&x504, &x505, x503, x461, x489);
  fiat_p434_addcarryx_u64(&x506, &x507, x505, x463, x491);
  fiat_p434_addcarryx_u64(&x508, &x509, x507, x465, x493);
  fiat_p434_addcarryx_u64(&x510, &x511, x509, x467, x495);
  x512 = ((uint64_t)x511 + x468);
  fiat_p434_mulx_u64(&x513, &x514, x6, (arg2[6]));
  fiat_p434_mulx_u64(&x515, &x516, x6, (arg2[5]));
  fiat_p434_mulx_u64(&x517, &x518, x6, (arg2[4]));
  fiat_p434_mulx_u64(&x519, &x520, x6, (arg2[3]));
  fiat_p434_mulx_u64(&x521, &x522, x6, (arg2[2]));
  fiat_p434_mulx_u64(&x523, &x524, x6, (arg2[1]));
  fiat_p434_mulx_u64(&x525, &x526, x6, (arg2[0]));
  fiat_p434_addcarryx_u64(&x527, &x528, 0x0, x526, x523);
  fiat_p434_addcarryx_u64(&x529, &x530, x528, x524, x521);
  fiat_p434_addcarryx_u64(&x531, &x532, x530, x522, x519);
  fiat_p434_addcarryx_u64(&x533, &x534, x532, x520, x517);
  fiat_p434_addcarryx_u64(&x535, &x536, x534, x518, x515);
  fiat_p434_addcarryx_u64(&x537, &x538, x536, x516, x513);
  x539 = (x538 + x514);
  fiat_p434_addcarryx_u64(&x540, &x541, 0x0, x498, x525);
  fiat_p434_addcarryx_u64(&x542, &x543, x541, x500, x527);
  fiat_p434_addcarryx_u64(&x544, &x545, x543, x502, x529);
  fiat_p434_addcarryx_u64(&x546, &x547, x545, x504, x531);
  fiat_p434_addcarryx_u64(&x548, &x549, x547, x506, x533);
  fiat_p434_addcarryx_u64(&x550, &x551, x549, x508, x535);
  fiat_p434_addcarryx_u64(&x552, &x553, x551, x510, x537);
  fiat_p434_addcarryx_u64(&x554, &x555, x553, x512, x539);
  fiat_p434_mulx_u64(&x556, &x557, x540, UINT64_C(0x2341f27177344));
  fiat_p434_mulx_u64(&x558, &x559, x540, UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_mulx_u64(&x560, &x561, x540, UINT64_C(0x7bc65c783158aea3));
  fiat_p434_mulx_u64(&x562, &x563, x540, UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_mulx_u64(&x564, &x565, x540, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x566, &x567, x540, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x568, &x569, x540, UINT64_C(0xffffffffffffffff));
  fiat_p434_addcarryx_u64(&x570, &x571, 0x0, x569, x566);
  fiat_p434_addcarryx_u64(&x572, &x573, x571, x567, x564);
  fiat_p434_addcarryx_u64(&x574, &x575, x573, x565, x562);
  fiat_p434_addcarryx_u64(&x576, &x577, x575, x563, x560);
  fiat_p434_addcarryx_u64(&x578, &x579, x577, x561, x558);
  fiat_p434_addcarryx_u64(&x580, &x581, x579, x559, x556);
  x582 = (x581 + x557);
  fiat_p434_addcarryx_u64(&x583, &x584, 0x0, x540, x568);
  fiat_p434_addcarryx_u64(&x585, &x586, x584, x542, x570);
  fiat_p434_addcarryx_u64(&x587, &x588, x586, x544, x572);
  fiat_p434_addcarryx_u64(&x589, &x590, x588, x546, x574);
  fiat_p434_addcarryx_u64(&x591, &x592, x590, x548, x576);
  fiat_p434_addcarryx_u64(&x593, &x594, x592, x550, x578);
  fiat_p434_addcarryx_u64(&x595, &x596, x594, x552, x580);
  fiat_p434_addcarryx_u64(&x597, &x598, x596, x554, x582);
  x599 = ((uint64_t)x598 + x555);
  fiat_p434_subborrowx_u64(&x600, &x601, 0x0, x585,
                           UINT64_C(0xffffffffffffffff));
  fiat_p434_subborrowx_u64(&x602, &x603, x601, x587,
                           UINT64_C(0xffffffffffffffff));
  fiat_p434_subborrowx_u64(&x604, &x605, x603, x589,
                           UINT64_C(0xffffffffffffffff));
  fiat_p434_subborrowx_u64(&x606, &x607, x605, x591,
                           UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_subborrowx_u64(&x608, &x609, x607, x593,
                           UINT64_C(0x7bc65c783158aea3));
  fiat_p434_subborrowx_u64(&x610, &x611, x609, x595,
                           UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_subborrowx_u64(&x612, &x613, x611, x597, UINT64_C(0x2341f27177344));
  fiat_p434_subborrowx_u64(&x614, &x615, x613, x599, 0x0);
  fiat_p434_cmovznz_u64(&x616, x615, x600, x585);
  fiat_p434_cmovznz_u64(&x617, x615, x602, x587);
  fiat_p434_cmovznz_u64(&x618, x615, x604, x589);
  fiat_p434_cmovznz_u64(&x619, x615, x606, x591);
  fiat_p434_cmovznz_u64(&x620, x615, x608, x593);
  fiat_p434_cmovznz_u64(&x621, x615, x610, x595);
  fiat_p434_cmovznz_u64(&x622, x615, x612, x597);
  out1[0] = x616;
  out1[1] = x617;
  out1[2] = x618;
  out1[3] = x619;
  out1[4] = x620;
  out1[5] = x621;
  out1[6] = x622;
}

/*
 * The function fiat_p434_square squares a field element in the Montgomery
 * domain. Preconditions: 0 ≤ eval arg1 < m Postconditions: eval
 * (from_montgomery out1) mod m = (eval (from_montgomery arg1) * eval
 * (from_montgomery arg1)) mod m 0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff]] Output Bounds: out1: [[0x0 ~> 0xffffffffffffffff], [0x0
 * ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
void fiat_p434_square(uint64_t out1[7], const uint64_t arg1[7]) {
  uint64_t x1;
  uint64_t x2;
  uint64_t x3;
  uint64_t x4;
  uint64_t x5;
  uint64_t x6;
  uint64_t x7;
  uint64_t x8;
  uint64_t x9;
  uint64_t x10;
  uint64_t x11;
  uint64_t x12;
  uint64_t x13;
  uint64_t x14;
  uint64_t x15;
  uint64_t x16;
  uint64_t x17;
  uint64_t x18;
  uint64_t x19;
  uint64_t x20;
  uint64_t x21;
  uint64_t x22;
  fiat_p434_uint1 x23;
  uint64_t x24;
  fiat_p434_uint1 x25;
  uint64_t x26;
  fiat_p434_uint1 x27;
  uint64_t x28;
  fiat_p434_uint1 x29;
  uint64_t x30;
  fiat_p434_uint1 x31;
  uint64_t x32;
  fiat_p434_uint1 x33;
  uint64_t x34;
  uint64_t x35;
  uint64_t x36;
  uint64_t x37;
  uint64_t x38;
  uint64_t x39;
  uint64_t x40;
  uint64_t x41;
  uint64_t x42;
  uint64_t x43;
  uint64_t x44;
  uint64_t x45;
  uint64_t x46;
  uint64_t x47;
  uint64_t x48;
  uint64_t x49;
  fiat_p434_uint1 x50;
  uint64_t x51;
  fiat_p434_uint1 x52;
  uint64_t x53;
  fiat_p434_uint1 x54;
  uint64_t x55;
  fiat_p434_uint1 x56;
  uint64_t x57;
  fiat_p434_uint1 x58;
  uint64_t x59;
  fiat_p434_uint1 x60;
  uint64_t x61;
  uint64_t x62;
  fiat_p434_uint1 x63;
  uint64_t x64;
  fiat_p434_uint1 x65;
  uint64_t x66;
  fiat_p434_uint1 x67;
  uint64_t x68;
  fiat_p434_uint1 x69;
  uint64_t x70;
  fiat_p434_uint1 x71;
  uint64_t x72;
  fiat_p434_uint1 x73;
  uint64_t x74;
  fiat_p434_uint1 x75;
  uint64_t x76;
  fiat_p434_uint1 x77;
  uint64_t x78;
  uint64_t x79;
  uint64_t x80;
  uint64_t x81;
  uint64_t x82;
  uint64_t x83;
  uint64_t x84;
  uint64_t x85;
  uint64_t x86;
  uint64_t x87;
  uint64_t x88;
  uint64_t x89;
  uint64_t x90;
  uint64_t x91;
  uint64_t x92;
  fiat_p434_uint1 x93;
  uint64_t x94;
  fiat_p434_uint1 x95;
  uint64_t x96;
  fiat_p434_uint1 x97;
  uint64_t x98;
  fiat_p434_uint1 x99;
  uint64_t x100;
  fiat_p434_uint1 x101;
  uint64_t x102;
  fiat_p434_uint1 x103;
  uint64_t x104;
  uint64_t x105;
  fiat_p434_uint1 x106;
  uint64_t x107;
  fiat_p434_uint1 x108;
  uint64_t x109;
  fiat_p434_uint1 x110;
  uint64_t x111;
  fiat_p434_uint1 x112;
  uint64_t x113;
  fiat_p434_uint1 x114;
  uint64_t x115;
  fiat_p434_uint1 x116;
  uint64_t x117;
  fiat_p434_uint1 x118;
  uint64_t x119;
  fiat_p434_uint1 x120;
  uint64_t x121;
  uint64_t x122;
  uint64_t x123;
  uint64_t x124;
  uint64_t x125;
  uint64_t x126;
  uint64_t x127;
  uint64_t x128;
  uint64_t x129;
  uint64_t x130;
  uint64_t x131;
  uint64_t x132;
  uint64_t x133;
  uint64_t x134;
  uint64_t x135;
  fiat_p434_uint1 x136;
  uint64_t x137;
  fiat_p434_uint1 x138;
  uint64_t x139;
  fiat_p434_uint1 x140;
  uint64_t x141;
  fiat_p434_uint1 x142;
  uint64_t x143;
  fiat_p434_uint1 x144;
  uint64_t x145;
  fiat_p434_uint1 x146;
  uint64_t x147;
  uint64_t x148;
  fiat_p434_uint1 x149;
  uint64_t x150;
  fiat_p434_uint1 x151;
  uint64_t x152;
  fiat_p434_uint1 x153;
  uint64_t x154;
  fiat_p434_uint1 x155;
  uint64_t x156;
  fiat_p434_uint1 x157;
  uint64_t x158;
  fiat_p434_uint1 x159;
  uint64_t x160;
  fiat_p434_uint1 x161;
  uint64_t x162;
  fiat_p434_uint1 x163;
  uint64_t x164;
  uint64_t x165;
  uint64_t x166;
  uint64_t x167;
  uint64_t x168;
  uint64_t x169;
  uint64_t x170;
  uint64_t x171;
  uint64_t x172;
  uint64_t x173;
  uint64_t x174;
  uint64_t x175;
  uint64_t x176;
  uint64_t x177;
  uint64_t x178;
  uint64_t x179;
  fiat_p434_uint1 x180;
  uint64_t x181;
  fiat_p434_uint1 x182;
  uint64_t x183;
  fiat_p434_uint1 x184;
  uint64_t x185;
  fiat_p434_uint1 x186;
  uint64_t x187;
  fiat_p434_uint1 x188;
  uint64_t x189;
  fiat_p434_uint1 x190;
  uint64_t x191;
  uint64_t x192;
  fiat_p434_uint1 x193;
  uint64_t x194;
  fiat_p434_uint1 x195;
  uint64_t x196;
  fiat_p434_uint1 x197;
  uint64_t x198;
  fiat_p434_uint1 x199;
  uint64_t x200;
  fiat_p434_uint1 x201;
  uint64_t x202;
  fiat_p434_uint1 x203;
  uint64_t x204;
  fiat_p434_uint1 x205;
  uint64_t x206;
  fiat_p434_uint1 x207;
  uint64_t x208;
  uint64_t x209;
  uint64_t x210;
  uint64_t x211;
  uint64_t x212;
  uint64_t x213;
  uint64_t x214;
  uint64_t x215;
  uint64_t x216;
  uint64_t x217;
  uint64_t x218;
  uint64_t x219;
  uint64_t x220;
  uint64_t x221;
  uint64_t x222;
  fiat_p434_uint1 x223;
  uint64_t x224;
  fiat_p434_uint1 x225;
  uint64_t x226;
  fiat_p434_uint1 x227;
  uint64_t x228;
  fiat_p434_uint1 x229;
  uint64_t x230;
  fiat_p434_uint1 x231;
  uint64_t x232;
  fiat_p434_uint1 x233;
  uint64_t x234;
  uint64_t x235;
  fiat_p434_uint1 x236;
  uint64_t x237;
  fiat_p434_uint1 x238;
  uint64_t x239;
  fiat_p434_uint1 x240;
  uint64_t x241;
  fiat_p434_uint1 x242;
  uint64_t x243;
  fiat_p434_uint1 x244;
  uint64_t x245;
  fiat_p434_uint1 x246;
  uint64_t x247;
  fiat_p434_uint1 x248;
  uint64_t x249;
  fiat_p434_uint1 x250;
  uint64_t x251;
  uint64_t x252;
  uint64_t x253;
  uint64_t x254;
  uint64_t x255;
  uint64_t x256;
  uint64_t x257;
  uint64_t x258;
  uint64_t x259;
  uint64_t x260;
  uint64_t x261;
  uint64_t x262;
  uint64_t x263;
  uint64_t x264;
  uint64_t x265;
  uint64_t x266;
  fiat_p434_uint1 x267;
  uint64_t x268;
  fiat_p434_uint1 x269;
  uint64_t x270;
  fiat_p434_uint1 x271;
  uint64_t x272;
  fiat_p434_uint1 x273;
  uint64_t x274;
  fiat_p434_uint1 x275;
  uint64_t x276;
  fiat_p434_uint1 x277;
  uint64_t x278;
  uint64_t x279;
  fiat_p434_uint1 x280;
  uint64_t x281;
  fiat_p434_uint1 x282;
  uint64_t x283;
  fiat_p434_uint1 x284;
  uint64_t x285;
  fiat_p434_uint1 x286;
  uint64_t x287;
  fiat_p434_uint1 x288;
  uint64_t x289;
  fiat_p434_uint1 x290;
  uint64_t x291;
  fiat_p434_uint1 x292;
  uint64_t x293;
  fiat_p434_uint1 x294;
  uint64_t x295;
  uint64_t x296;
  uint64_t x297;
  uint64_t x298;
  uint64_t x299;
  uint64_t x300;
  uint64_t x301;
  uint64_t x302;
  uint64_t x303;
  uint64_t x304;
  uint64_t x305;
  uint64_t x306;
  uint64_t x307;
  uint64_t x308;
  uint64_t x309;
  fiat_p434_uint1 x310;
  uint64_t x311;
  fiat_p434_uint1 x312;
  uint64_t x313;
  fiat_p434_uint1 x314;
  uint64_t x315;
  fiat_p434_uint1 x316;
  uint64_t x317;
  fiat_p434_uint1 x318;
  uint64_t x319;
  fiat_p434_uint1 x320;
  uint64_t x321;
  uint64_t x322;
  fiat_p434_uint1 x323;
  uint64_t x324;
  fiat_p434_uint1 x325;
  uint64_t x326;
  fiat_p434_uint1 x327;
  uint64_t x328;
  fiat_p434_uint1 x329;
  uint64_t x330;
  fiat_p434_uint1 x331;
  uint64_t x332;
  fiat_p434_uint1 x333;
  uint64_t x334;
  fiat_p434_uint1 x335;
  uint64_t x336;
  fiat_p434_uint1 x337;
  uint64_t x338;
  uint64_t x339;
  uint64_t x340;
  uint64_t x341;
  uint64_t x342;
  uint64_t x343;
  uint64_t x344;
  uint64_t x345;
  uint64_t x346;
  uint64_t x347;
  uint64_t x348;
  uint64_t x349;
  uint64_t x350;
  uint64_t x351;
  uint64_t x352;
  uint64_t x353;
  fiat_p434_uint1 x354;
  uint64_t x355;
  fiat_p434_uint1 x356;
  uint64_t x357;
  fiat_p434_uint1 x358;
  uint64_t x359;
  fiat_p434_uint1 x360;
  uint64_t x361;
  fiat_p434_uint1 x362;
  uint64_t x363;
  fiat_p434_uint1 x364;
  uint64_t x365;
  uint64_t x366;
  fiat_p434_uint1 x367;
  uint64_t x368;
  fiat_p434_uint1 x369;
  uint64_t x370;
  fiat_p434_uint1 x371;
  uint64_t x372;
  fiat_p434_uint1 x373;
  uint64_t x374;
  fiat_p434_uint1 x375;
  uint64_t x376;
  fiat_p434_uint1 x377;
  uint64_t x378;
  fiat_p434_uint1 x379;
  uint64_t x380;
  fiat_p434_uint1 x381;
  uint64_t x382;
  uint64_t x383;
  uint64_t x384;
  uint64_t x385;
  uint64_t x386;
  uint64_t x387;
  uint64_t x388;
  uint64_t x389;
  uint64_t x390;
  uint64_t x391;
  uint64_t x392;
  uint64_t x393;
  uint64_t x394;
  uint64_t x395;
  uint64_t x396;
  fiat_p434_uint1 x397;
  uint64_t x398;
  fiat_p434_uint1 x399;
  uint64_t x400;
  fiat_p434_uint1 x401;
  uint64_t x402;
  fiat_p434_uint1 x403;
  uint64_t x404;
  fiat_p434_uint1 x405;
  uint64_t x406;
  fiat_p434_uint1 x407;
  uint64_t x408;
  uint64_t x409;
  fiat_p434_uint1 x410;
  uint64_t x411;
  fiat_p434_uint1 x412;
  uint64_t x413;
  fiat_p434_uint1 x414;
  uint64_t x415;
  fiat_p434_uint1 x416;
  uint64_t x417;
  fiat_p434_uint1 x418;
  uint64_t x419;
  fiat_p434_uint1 x420;
  uint64_t x421;
  fiat_p434_uint1 x422;
  uint64_t x423;
  fiat_p434_uint1 x424;
  uint64_t x425;
  uint64_t x426;
  uint64_t x427;
  uint64_t x428;
  uint64_t x429;
  uint64_t x430;
  uint64_t x431;
  uint64_t x432;
  uint64_t x433;
  uint64_t x434;
  uint64_t x435;
  uint64_t x436;
  uint64_t x437;
  uint64_t x438;
  uint64_t x439;
  uint64_t x440;
  fiat_p434_uint1 x441;
  uint64_t x442;
  fiat_p434_uint1 x443;
  uint64_t x444;
  fiat_p434_uint1 x445;
  uint64_t x446;
  fiat_p434_uint1 x447;
  uint64_t x448;
  fiat_p434_uint1 x449;
  uint64_t x450;
  fiat_p434_uint1 x451;
  uint64_t x452;
  uint64_t x453;
  fiat_p434_uint1 x454;
  uint64_t x455;
  fiat_p434_uint1 x456;
  uint64_t x457;
  fiat_p434_uint1 x458;
  uint64_t x459;
  fiat_p434_uint1 x460;
  uint64_t x461;
  fiat_p434_uint1 x462;
  uint64_t x463;
  fiat_p434_uint1 x464;
  uint64_t x465;
  fiat_p434_uint1 x466;
  uint64_t x467;
  fiat_p434_uint1 x468;
  uint64_t x469;
  uint64_t x470;
  uint64_t x471;
  uint64_t x472;
  uint64_t x473;
  uint64_t x474;
  uint64_t x475;
  uint64_t x476;
  uint64_t x477;
  uint64_t x478;
  uint64_t x479;
  uint64_t x480;
  uint64_t x481;
  uint64_t x482;
  uint64_t x483;
  fiat_p434_uint1 x484;
  uint64_t x485;
  fiat_p434_uint1 x486;
  uint64_t x487;
  fiat_p434_uint1 x488;
  uint64_t x489;
  fiat_p434_uint1 x490;
  uint64_t x491;
  fiat_p434_uint1 x492;
  uint64_t x493;
  fiat_p434_uint1 x494;
  uint64_t x495;
  uint64_t x496;
  fiat_p434_uint1 x497;
  uint64_t x498;
  fiat_p434_uint1 x499;
  uint64_t x500;
  fiat_p434_uint1 x501;
  uint64_t x502;
  fiat_p434_uint1 x503;
  uint64_t x504;
  fiat_p434_uint1 x505;
  uint64_t x506;
  fiat_p434_uint1 x507;
  uint64_t x508;
  fiat_p434_uint1 x509;
  uint64_t x510;
  fiat_p434_uint1 x511;
  uint64_t x512;
  uint64_t x513;
  uint64_t x514;
  uint64_t x515;
  uint64_t x516;
  uint64_t x517;
  uint64_t x518;
  uint64_t x519;
  uint64_t x520;
  uint64_t x521;
  uint64_t x522;
  uint64_t x523;
  uint64_t x524;
  uint64_t x525;
  uint64_t x526;
  uint64_t x527;
  fiat_p434_uint1 x528;
  uint64_t x529;
  fiat_p434_uint1 x530;
  uint64_t x531;
  fiat_p434_uint1 x532;
  uint64_t x533;
  fiat_p434_uint1 x534;
  uint64_t x535;
  fiat_p434_uint1 x536;
  uint64_t x537;
  fiat_p434_uint1 x538;
  uint64_t x539;
  uint64_t x540;
  fiat_p434_uint1 x541;
  uint64_t x542;
  fiat_p434_uint1 x543;
  uint64_t x544;
  fiat_p434_uint1 x545;
  uint64_t x546;
  fiat_p434_uint1 x547;
  uint64_t x548;
  fiat_p434_uint1 x549;
  uint64_t x550;
  fiat_p434_uint1 x551;
  uint64_t x552;
  fiat_p434_uint1 x553;
  uint64_t x554;
  fiat_p434_uint1 x555;
  uint64_t x556;
  uint64_t x557;
  uint64_t x558;
  uint64_t x559;
  uint64_t x560;
  uint64_t x561;
  uint64_t x562;
  uint64_t x563;
  uint64_t x564;
  uint64_t x565;
  uint64_t x566;
  uint64_t x567;
  uint64_t x568;
  uint64_t x569;
  uint64_t x570;
  fiat_p434_uint1 x571;
  uint64_t x572;
  fiat_p434_uint1 x573;
  uint64_t x574;
  fiat_p434_uint1 x575;
  uint64_t x576;
  fiat_p434_uint1 x577;
  uint64_t x578;
  fiat_p434_uint1 x579;
  uint64_t x580;
  fiat_p434_uint1 x581;
  uint64_t x582;
  uint64_t x583;
  fiat_p434_uint1 x584;
  uint64_t x585;
  fiat_p434_uint1 x586;
  uint64_t x587;
  fiat_p434_uint1 x588;
  uint64_t x589;
  fiat_p434_uint1 x590;
  uint64_t x591;
  fiat_p434_uint1 x592;
  uint64_t x593;
  fiat_p434_uint1 x594;
  uint64_t x595;
  fiat_p434_uint1 x596;
  uint64_t x597;
  fiat_p434_uint1 x598;
  uint64_t x599;
  uint64_t x600;
  fiat_p434_uint1 x601;
  uint64_t x602;
  fiat_p434_uint1 x603;
  uint64_t x604;
  fiat_p434_uint1 x605;
  uint64_t x606;
  fiat_p434_uint1 x607;
  uint64_t x608;
  fiat_p434_uint1 x609;
  uint64_t x610;
  fiat_p434_uint1 x611;
  uint64_t x612;
  fiat_p434_uint1 x613;
  uint64_t x614;
  fiat_p434_uint1 x615;
  uint64_t x616;
  uint64_t x617;
  uint64_t x618;
  uint64_t x619;
  uint64_t x620;
  uint64_t x621;
  uint64_t x622;
  x1 = (arg1[1]);
  x2 = (arg1[2]);
  x3 = (arg1[3]);
  x4 = (arg1[4]);
  x5 = (arg1[5]);
  x6 = (arg1[6]);
  x7 = (arg1[0]);
  fiat_p434_mulx_u64(&x8, &x9, x7, (arg1[6]));
  fiat_p434_mulx_u64(&x10, &x11, x7, (arg1[5]));
  fiat_p434_mulx_u64(&x12, &x13, x7, (arg1[4]));
  fiat_p434_mulx_u64(&x14, &x15, x7, (arg1[3]));
  fiat_p434_mulx_u64(&x16, &x17, x7, (arg1[2]));
  fiat_p434_mulx_u64(&x18, &x19, x7, (arg1[1]));
  fiat_p434_mulx_u64(&x20, &x21, x7, (arg1[0]));
  fiat_p434_addcarryx_u64(&x22, &x23, 0x0, x21, x18);
  fiat_p434_addcarryx_u64(&x24, &x25, x23, x19, x16);
  fiat_p434_addcarryx_u64(&x26, &x27, x25, x17, x14);
  fiat_p434_addcarryx_u64(&x28, &x29, x27, x15, x12);
  fiat_p434_addcarryx_u64(&x30, &x31, x29, x13, x10);
  fiat_p434_addcarryx_u64(&x32, &x33, x31, x11, x8);
  x34 = (x33 + x9);
  fiat_p434_mulx_u64(&x35, &x36, x20, UINT64_C(0x2341f27177344));
  fiat_p434_mulx_u64(&x37, &x38, x20, UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_mulx_u64(&x39, &x40, x20, UINT64_C(0x7bc65c783158aea3));
  fiat_p434_mulx_u64(&x41, &x42, x20, UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_mulx_u64(&x43, &x44, x20, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x45, &x46, x20, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x47, &x48, x20, UINT64_C(0xffffffffffffffff));
  fiat_p434_addcarryx_u64(&x49, &x50, 0x0, x48, x45);
  fiat_p434_addcarryx_u64(&x51, &x52, x50, x46, x43);
  fiat_p434_addcarryx_u64(&x53, &x54, x52, x44, x41);
  fiat_p434_addcarryx_u64(&x55, &x56, x54, x42, x39);
  fiat_p434_addcarryx_u64(&x57, &x58, x56, x40, x37);
  fiat_p434_addcarryx_u64(&x59, &x60, x58, x38, x35);
  x61 = (x60 + x36);
  fiat_p434_addcarryx_u64(&x62, &x63, 0x0, x20, x47);
  fiat_p434_addcarryx_u64(&x64, &x65, x63, x22, x49);
  fiat_p434_addcarryx_u64(&x66, &x67, x65, x24, x51);
  fiat_p434_addcarryx_u64(&x68, &x69, x67, x26, x53);
  fiat_p434_addcarryx_u64(&x70, &x71, x69, x28, x55);
  fiat_p434_addcarryx_u64(&x72, &x73, x71, x30, x57);
  fiat_p434_addcarryx_u64(&x74, &x75, x73, x32, x59);
  fiat_p434_addcarryx_u64(&x76, &x77, x75, x34, x61);
  fiat_p434_mulx_u64(&x78, &x79, x1, (arg1[6]));
  fiat_p434_mulx_u64(&x80, &x81, x1, (arg1[5]));
  fiat_p434_mulx_u64(&x82, &x83, x1, (arg1[4]));
  fiat_p434_mulx_u64(&x84, &x85, x1, (arg1[3]));
  fiat_p434_mulx_u64(&x86, &x87, x1, (arg1[2]));
  fiat_p434_mulx_u64(&x88, &x89, x1, (arg1[1]));
  fiat_p434_mulx_u64(&x90, &x91, x1, (arg1[0]));
  fiat_p434_addcarryx_u64(&x92, &x93, 0x0, x91, x88);
  fiat_p434_addcarryx_u64(&x94, &x95, x93, x89, x86);
  fiat_p434_addcarryx_u64(&x96, &x97, x95, x87, x84);
  fiat_p434_addcarryx_u64(&x98, &x99, x97, x85, x82);
  fiat_p434_addcarryx_u64(&x100, &x101, x99, x83, x80);
  fiat_p434_addcarryx_u64(&x102, &x103, x101, x81, x78);
  x104 = (x103 + x79);
  fiat_p434_addcarryx_u64(&x105, &x106, 0x0, x64, x90);
  fiat_p434_addcarryx_u64(&x107, &x108, x106, x66, x92);
  fiat_p434_addcarryx_u64(&x109, &x110, x108, x68, x94);
  fiat_p434_addcarryx_u64(&x111, &x112, x110, x70, x96);
  fiat_p434_addcarryx_u64(&x113, &x114, x112, x72, x98);
  fiat_p434_addcarryx_u64(&x115, &x116, x114, x74, x100);
  fiat_p434_addcarryx_u64(&x117, &x118, x116, x76, x102);
  fiat_p434_addcarryx_u64(&x119, &x120, x118, x77, x104);
  fiat_p434_mulx_u64(&x121, &x122, x105, UINT64_C(0x2341f27177344));
  fiat_p434_mulx_u64(&x123, &x124, x105, UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_mulx_u64(&x125, &x126, x105, UINT64_C(0x7bc65c783158aea3));
  fiat_p434_mulx_u64(&x127, &x128, x105, UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_mulx_u64(&x129, &x130, x105, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x131, &x132, x105, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x133, &x134, x105, UINT64_C(0xffffffffffffffff));
  fiat_p434_addcarryx_u64(&x135, &x136, 0x0, x134, x131);
  fiat_p434_addcarryx_u64(&x137, &x138, x136, x132, x129);
  fiat_p434_addcarryx_u64(&x139, &x140, x138, x130, x127);
  fiat_p434_addcarryx_u64(&x141, &x142, x140, x128, x125);
  fiat_p434_addcarryx_u64(&x143, &x144, x142, x126, x123);
  fiat_p434_addcarryx_u64(&x145, &x146, x144, x124, x121);
  x147 = (x146 + x122);
  fiat_p434_addcarryx_u64(&x148, &x149, 0x0, x105, x133);
  fiat_p434_addcarryx_u64(&x150, &x151, x149, x107, x135);
  fiat_p434_addcarryx_u64(&x152, &x153, x151, x109, x137);
  fiat_p434_addcarryx_u64(&x154, &x155, x153, x111, x139);
  fiat_p434_addcarryx_u64(&x156, &x157, x155, x113, x141);
  fiat_p434_addcarryx_u64(&x158, &x159, x157, x115, x143);
  fiat_p434_addcarryx_u64(&x160, &x161, x159, x117, x145);
  fiat_p434_addcarryx_u64(&x162, &x163, x161, x119, x147);
  x164 = ((uint64_t)x163 + x120);
  fiat_p434_mulx_u64(&x165, &x166, x2, (arg1[6]));
  fiat_p434_mulx_u64(&x167, &x168, x2, (arg1[5]));
  fiat_p434_mulx_u64(&x169, &x170, x2, (arg1[4]));
  fiat_p434_mulx_u64(&x171, &x172, x2, (arg1[3]));
  fiat_p434_mulx_u64(&x173, &x174, x2, (arg1[2]));
  fiat_p434_mulx_u64(&x175, &x176, x2, (arg1[1]));
  fiat_p434_mulx_u64(&x177, &x178, x2, (arg1[0]));
  fiat_p434_addcarryx_u64(&x179, &x180, 0x0, x178, x175);
  fiat_p434_addcarryx_u64(&x181, &x182, x180, x176, x173);
  fiat_p434_addcarryx_u64(&x183, &x184, x182, x174, x171);
  fiat_p434_addcarryx_u64(&x185, &x186, x184, x172, x169);
  fiat_p434_addcarryx_u64(&x187, &x188, x186, x170, x167);
  fiat_p434_addcarryx_u64(&x189, &x190, x188, x168, x165);
  x191 = (x190 + x166);
  fiat_p434_addcarryx_u64(&x192, &x193, 0x0, x150, x177);
  fiat_p434_addcarryx_u64(&x194, &x195, x193, x152, x179);
  fiat_p434_addcarryx_u64(&x196, &x197, x195, x154, x181);
  fiat_p434_addcarryx_u64(&x198, &x199, x197, x156, x183);
  fiat_p434_addcarryx_u64(&x200, &x201, x199, x158, x185);
  fiat_p434_addcarryx_u64(&x202, &x203, x201, x160, x187);
  fiat_p434_addcarryx_u64(&x204, &x205, x203, x162, x189);
  fiat_p434_addcarryx_u64(&x206, &x207, x205, x164, x191);
  fiat_p434_mulx_u64(&x208, &x209, x192, UINT64_C(0x2341f27177344));
  fiat_p434_mulx_u64(&x210, &x211, x192, UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_mulx_u64(&x212, &x213, x192, UINT64_C(0x7bc65c783158aea3));
  fiat_p434_mulx_u64(&x214, &x215, x192, UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_mulx_u64(&x216, &x217, x192, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x218, &x219, x192, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x220, &x221, x192, UINT64_C(0xffffffffffffffff));
  fiat_p434_addcarryx_u64(&x222, &x223, 0x0, x221, x218);
  fiat_p434_addcarryx_u64(&x224, &x225, x223, x219, x216);
  fiat_p434_addcarryx_u64(&x226, &x227, x225, x217, x214);
  fiat_p434_addcarryx_u64(&x228, &x229, x227, x215, x212);
  fiat_p434_addcarryx_u64(&x230, &x231, x229, x213, x210);
  fiat_p434_addcarryx_u64(&x232, &x233, x231, x211, x208);
  x234 = (x233 + x209);
  fiat_p434_addcarryx_u64(&x235, &x236, 0x0, x192, x220);
  fiat_p434_addcarryx_u64(&x237, &x238, x236, x194, x222);
  fiat_p434_addcarryx_u64(&x239, &x240, x238, x196, x224);
  fiat_p434_addcarryx_u64(&x241, &x242, x240, x198, x226);
  fiat_p434_addcarryx_u64(&x243, &x244, x242, x200, x228);
  fiat_p434_addcarryx_u64(&x245, &x246, x244, x202, x230);
  fiat_p434_addcarryx_u64(&x247, &x248, x246, x204, x232);
  fiat_p434_addcarryx_u64(&x249, &x250, x248, x206, x234);
  x251 = ((uint64_t)x250 + x207);
  fiat_p434_mulx_u64(&x252, &x253, x3, (arg1[6]));
  fiat_p434_mulx_u64(&x254, &x255, x3, (arg1[5]));
  fiat_p434_mulx_u64(&x256, &x257, x3, (arg1[4]));
  fiat_p434_mulx_u64(&x258, &x259, x3, (arg1[3]));
  fiat_p434_mulx_u64(&x260, &x261, x3, (arg1[2]));
  fiat_p434_mulx_u64(&x262, &x263, x3, (arg1[1]));
  fiat_p434_mulx_u64(&x264, &x265, x3, (arg1[0]));
  fiat_p434_addcarryx_u64(&x266, &x267, 0x0, x265, x262);
  fiat_p434_addcarryx_u64(&x268, &x269, x267, x263, x260);
  fiat_p434_addcarryx_u64(&x270, &x271, x269, x261, x258);
  fiat_p434_addcarryx_u64(&x272, &x273, x271, x259, x256);
  fiat_p434_addcarryx_u64(&x274, &x275, x273, x257, x254);
  fiat_p434_addcarryx_u64(&x276, &x277, x275, x255, x252);
  x278 = (x277 + x253);
  fiat_p434_addcarryx_u64(&x279, &x280, 0x0, x237, x264);
  fiat_p434_addcarryx_u64(&x281, &x282, x280, x239, x266);
  fiat_p434_addcarryx_u64(&x283, &x284, x282, x241, x268);
  fiat_p434_addcarryx_u64(&x285, &x286, x284, x243, x270);
  fiat_p434_addcarryx_u64(&x287, &x288, x286, x245, x272);
  fiat_p434_addcarryx_u64(&x289, &x290, x288, x247, x274);
  fiat_p434_addcarryx_u64(&x291, &x292, x290, x249, x276);
  fiat_p434_addcarryx_u64(&x293, &x294, x292, x251, x278);
  fiat_p434_mulx_u64(&x295, &x296, x279, UINT64_C(0x2341f27177344));
  fiat_p434_mulx_u64(&x297, &x298, x279, UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_mulx_u64(&x299, &x300, x279, UINT64_C(0x7bc65c783158aea3));
  fiat_p434_mulx_u64(&x301, &x302, x279, UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_mulx_u64(&x303, &x304, x279, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x305, &x306, x279, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x307, &x308, x279, UINT64_C(0xffffffffffffffff));
  fiat_p434_addcarryx_u64(&x309, &x310, 0x0, x308, x305);
  fiat_p434_addcarryx_u64(&x311, &x312, x310, x306, x303);
  fiat_p434_addcarryx_u64(&x313, &x314, x312, x304, x301);
  fiat_p434_addcarryx_u64(&x315, &x316, x314, x302, x299);
  fiat_p434_addcarryx_u64(&x317, &x318, x316, x300, x297);
  fiat_p434_addcarryx_u64(&x319, &x320, x318, x298, x295);
  x321 = (x320 + x296);
  fiat_p434_addcarryx_u64(&x322, &x323, 0x0, x279, x307);
  fiat_p434_addcarryx_u64(&x324, &x325, x323, x281, x309);
  fiat_p434_addcarryx_u64(&x326, &x327, x325, x283, x311);
  fiat_p434_addcarryx_u64(&x328, &x329, x327, x285, x313);
  fiat_p434_addcarryx_u64(&x330, &x331, x329, x287, x315);
  fiat_p434_addcarryx_u64(&x332, &x333, x331, x289, x317);
  fiat_p434_addcarryx_u64(&x334, &x335, x333, x291, x319);
  fiat_p434_addcarryx_u64(&x336, &x337, x335, x293, x321);
  x338 = ((uint64_t)x337 + x294);
  fiat_p434_mulx_u64(&x339, &x340, x4, (arg1[6]));
  fiat_p434_mulx_u64(&x341, &x342, x4, (arg1[5]));
  fiat_p434_mulx_u64(&x343, &x344, x4, (arg1[4]));
  fiat_p434_mulx_u64(&x345, &x346, x4, (arg1[3]));
  fiat_p434_mulx_u64(&x347, &x348, x4, (arg1[2]));
  fiat_p434_mulx_u64(&x349, &x350, x4, (arg1[1]));
  fiat_p434_mulx_u64(&x351, &x352, x4, (arg1[0]));
  fiat_p434_addcarryx_u64(&x353, &x354, 0x0, x352, x349);
  fiat_p434_addcarryx_u64(&x355, &x356, x354, x350, x347);
  fiat_p434_addcarryx_u64(&x357, &x358, x356, x348, x345);
  fiat_p434_addcarryx_u64(&x359, &x360, x358, x346, x343);
  fiat_p434_addcarryx_u64(&x361, &x362, x360, x344, x341);
  fiat_p434_addcarryx_u64(&x363, &x364, x362, x342, x339);
  x365 = (x364 + x340);
  fiat_p434_addcarryx_u64(&x366, &x367, 0x0, x324, x351);
  fiat_p434_addcarryx_u64(&x368, &x369, x367, x326, x353);
  fiat_p434_addcarryx_u64(&x370, &x371, x369, x328, x355);
  fiat_p434_addcarryx_u64(&x372, &x373, x371, x330, x357);
  fiat_p434_addcarryx_u64(&x374, &x375, x373, x332, x359);
  fiat_p434_addcarryx_u64(&x376, &x377, x375, x334, x361);
  fiat_p434_addcarryx_u64(&x378, &x379, x377, x336, x363);
  fiat_p434_addcarryx_u64(&x380, &x381, x379, x338, x365);
  fiat_p434_mulx_u64(&x382, &x383, x366, UINT64_C(0x2341f27177344));
  fiat_p434_mulx_u64(&x384, &x385, x366, UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_mulx_u64(&x386, &x387, x366, UINT64_C(0x7bc65c783158aea3));
  fiat_p434_mulx_u64(&x388, &x389, x366, UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_mulx_u64(&x390, &x391, x366, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x392, &x393, x366, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x394, &x395, x366, UINT64_C(0xffffffffffffffff));
  fiat_p434_addcarryx_u64(&x396, &x397, 0x0, x395, x392);
  fiat_p434_addcarryx_u64(&x398, &x399, x397, x393, x390);
  fiat_p434_addcarryx_u64(&x400, &x401, x399, x391, x388);
  fiat_p434_addcarryx_u64(&x402, &x403, x401, x389, x386);
  fiat_p434_addcarryx_u64(&x404, &x405, x403, x387, x384);
  fiat_p434_addcarryx_u64(&x406, &x407, x405, x385, x382);
  x408 = (x407 + x383);
  fiat_p434_addcarryx_u64(&x409, &x410, 0x0, x366, x394);
  fiat_p434_addcarryx_u64(&x411, &x412, x410, x368, x396);
  fiat_p434_addcarryx_u64(&x413, &x414, x412, x370, x398);
  fiat_p434_addcarryx_u64(&x415, &x416, x414, x372, x400);
  fiat_p434_addcarryx_u64(&x417, &x418, x416, x374, x402);
  fiat_p434_addcarryx_u64(&x419, &x420, x418, x376, x404);
  fiat_p434_addcarryx_u64(&x421, &x422, x420, x378, x406);
  fiat_p434_addcarryx_u64(&x423, &x424, x422, x380, x408);
  x425 = ((uint64_t)x424 + x381);
  fiat_p434_mulx_u64(&x426, &x427, x5, (arg1[6]));
  fiat_p434_mulx_u64(&x428, &x429, x5, (arg1[5]));
  fiat_p434_mulx_u64(&x430, &x431, x5, (arg1[4]));
  fiat_p434_mulx_u64(&x432, &x433, x5, (arg1[3]));
  fiat_p434_mulx_u64(&x434, &x435, x5, (arg1[2]));
  fiat_p434_mulx_u64(&x436, &x437, x5, (arg1[1]));
  fiat_p434_mulx_u64(&x438, &x439, x5, (arg1[0]));
  fiat_p434_addcarryx_u64(&x440, &x441, 0x0, x439, x436);
  fiat_p434_addcarryx_u64(&x442, &x443, x441, x437, x434);
  fiat_p434_addcarryx_u64(&x444, &x445, x443, x435, x432);
  fiat_p434_addcarryx_u64(&x446, &x447, x445, x433, x430);
  fiat_p434_addcarryx_u64(&x448, &x449, x447, x431, x428);
  fiat_p434_addcarryx_u64(&x450, &x451, x449, x429, x426);
  x452 = (x451 + x427);
  fiat_p434_addcarryx_u64(&x453, &x454, 0x0, x411, x438);
  fiat_p434_addcarryx_u64(&x455, &x456, x454, x413, x440);
  fiat_p434_addcarryx_u64(&x457, &x458, x456, x415, x442);
  fiat_p434_addcarryx_u64(&x459, &x460, x458, x417, x444);
  fiat_p434_addcarryx_u64(&x461, &x462, x460, x419, x446);
  fiat_p434_addcarryx_u64(&x463, &x464, x462, x421, x448);
  fiat_p434_addcarryx_u64(&x465, &x466, x464, x423, x450);
  fiat_p434_addcarryx_u64(&x467, &x468, x466, x425, x452);
  fiat_p434_mulx_u64(&x469, &x470, x453, UINT64_C(0x2341f27177344));
  fiat_p434_mulx_u64(&x471, &x472, x453, UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_mulx_u64(&x473, &x474, x453, UINT64_C(0x7bc65c783158aea3));
  fiat_p434_mulx_u64(&x475, &x476, x453, UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_mulx_u64(&x477, &x478, x453, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x479, &x480, x453, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x481, &x482, x453, UINT64_C(0xffffffffffffffff));
  fiat_p434_addcarryx_u64(&x483, &x484, 0x0, x482, x479);
  fiat_p434_addcarryx_u64(&x485, &x486, x484, x480, x477);
  fiat_p434_addcarryx_u64(&x487, &x488, x486, x478, x475);
  fiat_p434_addcarryx_u64(&x489, &x490, x488, x476, x473);
  fiat_p434_addcarryx_u64(&x491, &x492, x490, x474, x471);
  fiat_p434_addcarryx_u64(&x493, &x494, x492, x472, x469);
  x495 = (x494 + x470);
  fiat_p434_addcarryx_u64(&x496, &x497, 0x0, x453, x481);
  fiat_p434_addcarryx_u64(&x498, &x499, x497, x455, x483);
  fiat_p434_addcarryx_u64(&x500, &x501, x499, x457, x485);
  fiat_p434_addcarryx_u64(&x502, &x503, x501, x459, x487);
  fiat_p434_addcarryx_u64(&x504, &x505, x503, x461, x489);
  fiat_p434_addcarryx_u64(&x506, &x507, x505, x463, x491);
  fiat_p434_addcarryx_u64(&x508, &x509, x507, x465, x493);
  fiat_p434_addcarryx_u64(&x510, &x511, x509, x467, x495);
  x512 = ((uint64_t)x511 + x468);
  fiat_p434_mulx_u64(&x513, &x514, x6, (arg1[6]));
  fiat_p434_mulx_u64(&x515, &x516, x6, (arg1[5]));
  fiat_p434_mulx_u64(&x517, &x518, x6, (arg1[4]));
  fiat_p434_mulx_u64(&x519, &x520, x6, (arg1[3]));
  fiat_p434_mulx_u64(&x521, &x522, x6, (arg1[2]));
  fiat_p434_mulx_u64(&x523, &x524, x6, (arg1[1]));
  fiat_p434_mulx_u64(&x525, &x526, x6, (arg1[0]));
  fiat_p434_addcarryx_u64(&x527, &x528, 0x0, x526, x523);
  fiat_p434_addcarryx_u64(&x529, &x530, x528, x524, x521);
  fiat_p434_addcarryx_u64(&x531, &x532, x530, x522, x519);
  fiat_p434_addcarryx_u64(&x533, &x534, x532, x520, x517);
  fiat_p434_addcarryx_u64(&x535, &x536, x534, x518, x515);
  fiat_p434_addcarryx_u64(&x537, &x538, x536, x516, x513);
  x539 = (x538 + x514);
  fiat_p434_addcarryx_u64(&x540, &x541, 0x0, x498, x525);
  fiat_p434_addcarryx_u64(&x542, &x543, x541, x500, x527);
  fiat_p434_addcarryx_u64(&x544, &x545, x543, x502, x529);
  fiat_p434_addcarryx_u64(&x546, &x547, x545, x504, x531);
  fiat_p434_addcarryx_u64(&x548, &x549, x547, x506, x533);
  fiat_p434_addcarryx_u64(&x550, &x551, x549, x508, x535);
  fiat_p434_addcarryx_u64(&x552, &x553, x551, x510, x537);
  fiat_p434_addcarryx_u64(&x554, &x555, x553, x512, x539);
  fiat_p434_mulx_u64(&x556, &x557, x540, UINT64_C(0x2341f27177344));
  fiat_p434_mulx_u64(&x558, &x559, x540, UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_mulx_u64(&x560, &x561, x540, UINT64_C(0x7bc65c783158aea3));
  fiat_p434_mulx_u64(&x562, &x563, x540, UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_mulx_u64(&x564, &x565, x540, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x566, &x567, x540, UINT64_C(0xffffffffffffffff));
  fiat_p434_mulx_u64(&x568, &x569, x540, UINT64_C(0xffffffffffffffff));
  fiat_p434_addcarryx_u64(&x570, &x571, 0x0, x569, x566);
  fiat_p434_addcarryx_u64(&x572, &x573, x571, x567, x564);
  fiat_p434_addcarryx_u64(&x574, &x575, x573, x565, x562);
  fiat_p434_addcarryx_u64(&x576, &x577, x575, x563, x560);
  fiat_p434_addcarryx_u64(&x578, &x579, x577, x561, x558);
  fiat_p434_addcarryx_u64(&x580, &x581, x579, x559, x556);
  x582 = (x581 + x557);
  fiat_p434_addcarryx_u64(&x583, &x584, 0x0, x540, x568);
  fiat_p434_addcarryx_u64(&x585, &x586, x584, x542, x570);
  fiat_p434_addcarryx_u64(&x587, &x588, x586, x544, x572);
  fiat_p434_addcarryx_u64(&x589, &x590, x588, x546, x574);
  fiat_p434_addcarryx_u64(&x591, &x592, x590, x548, x576);
  fiat_p434_addcarryx_u64(&x593, &x594, x592, x550, x578);
  fiat_p434_addcarryx_u64(&x595, &x596, x594, x552, x580);
  fiat_p434_addcarryx_u64(&x597, &x598, x596, x554, x582);
  x599 = ((uint64_t)x598 + x555);
  fiat_p434_subborrowx_u64(&x600, &x601, 0x0, x585,
                           UINT64_C(0xffffffffffffffff));
  fiat_p434_subborrowx_u64(&x602, &x603, x601, x587,
                           UINT64_C(0xffffffffffffffff));
  fiat_p434_subborrowx_u64(&x604, &x605, x603, x589,
                           UINT64_C(0xffffffffffffffff));
  fiat_p434_subborrowx_u64(&x606, &x607, x605, x591,
                           UINT64_C(0xfdc1767ae2ffffff));
  fiat_p434_subborrowx_u64(&x608, &x609, x607, x593,
                           UINT64_C(0x7bc65c783158aea3));
  fiat_p434_subborrowx_u64(&x610, &x611, x609, x595,
                           UINT64_C(0x6cfc5fd681c52056));
  fiat_p434_subborrowx_u64(&x612, &x613, x611, x597, UINT64_C(0x2341f27177344));
  fiat_p434_subborrowx_u64(&x614, &x615, x613, x599, 0x0);
  fiat_p434_cmovznz_u64(&x616, x615, x600, x585);
  fiat_p434_cmovznz_u64(&x617, x615, x602, x587);
  fiat_p434_cmovznz_u64(&x618, x615, x604, x589);
  fiat_p434_cmovznz_u64(&x619, x615, x606, x591);
  fiat_p434_cmovznz_u64(&x620, x615, x608, x593);
  fiat_p434_cmovznz_u64(&x621, x615, x610, x595);
  fiat_p434_cmovznz_u64(&x622, x615, x612, x597);
  out1[0] = x616;
  out1[1] = x617;
  out1[2] = x618;
  out1[3] = x619;
  out1[4] = x620;
  out1[5] = x621;
  out1[6] = x622;
}

/* curve description: p448_solinas */
/* machine_wordsize = 64 (from "64") */
/* requested operations: carry_mul, carry_square */
/* n = 8 (from "8") */
/* s-c = 2^448 - [(2^224, 1), (1, 1)] (from "2^448 - 2^224 - 1") */
/* tight_bounds_multiplier = 1 (from "") */
/*  */
/* Computed values: */
/* carry_chain = [3, 7, 4, 0, 5, 1, 6, 2, 7, 3, 4, 0] */
/* eval z = z[0] + (z[1] << 56) + (z[2] << 112) + (z[3] << 168) + (z[4] << 224)
 * + (z[5] << 0x118) + (z[6] << 0x150) + (z[7] << 0x188) */
/* bytes_eval z = z[0] + (z[1] << 8) + (z[2] << 16) + (z[3] << 24) + (z[4] <<
 * 32) + (z[5] << 40) + (z[6] << 48) + (z[7] << 56) + (z[8] << 64) + (z[9] <<
 * 72) + (z[10] << 80) + (z[11] << 88) + (z[12] << 96) + (z[13] << 104) + (z[14]
 * << 112) + (z[15] << 120) + (z[16] << 128) + (z[17] << 136) + (z[18] << 144) +
 * (z[19] << 152) + (z[20] << 160) + (z[21] << 168) + (z[22] << 176) + (z[23] <<
 * 184) + (z[24] << 192) + (z[25] << 200) + (z[26] << 208) + (z[27] << 216) +
 * (z[28] << 224) + (z[29] << 232) + (z[30] << 240) + (z[31] << 248) + (z[32] <<
 * 256) + (z[33] << 0x108) + (z[34] << 0x110) + (z[35] << 0x118) + (z[36] <<
 * 0x120) + (z[37] << 0x128) + (z[38] << 0x130) + (z[39] << 0x138) + (z[40] <<
 * 0x140) + (z[41] << 0x148) + (z[42] << 0x150) + (z[43] << 0x158) + (z[44] <<
 * 0x160) + (z[45] << 0x168) + (z[46] << 0x170) + (z[47] << 0x178) + (z[48] <<
 * 0x180) + (z[49] << 0x188) + (z[50] << 0x190) + (z[51] << 0x198) + (z[52] <<
 * 0x1a0) + (z[53] << 0x1a8) + (z[54] << 0x1b0) + (z[55] << 0x1b8) */
/* balance = [0x1fffffffffffffe, 0x1fffffffffffffe, 0x1fffffffffffffe,
 * 0x1fffffffffffffe, 0x1fffffffffffffc, 0x1fffffffffffffe, 0x1fffffffffffffe,
 * 0x1fffffffffffffe] */

#include <stdint.h>
typedef unsigned char fiat_p448_solinas_uint1;
typedef signed char fiat_p448_solinas_int1;
typedef signed __int128 fiat_p448_solinas_int128;
typedef unsigned __int128 fiat_p448_solinas_uint128;

#if (-1 & 3) != 3
#error "This code only works on a two's complement system"
#endif

/*
 * The function fiat_p448_solinas_carry_mul multiplies two field elements and
 * reduces the result. Postconditions: eval out1 mod m = (eval arg1 * eval arg2)
 * mod m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0x300000000000000], [0x0 ~> 0x300000000000000], [0x0 ~>
 * 0x300000000000000], [0x0 ~> 0x300000000000000], [0x0 ~> 0x300000000000000],
 * [0x0 ~> 0x300000000000000], [0x0 ~> 0x300000000000000], [0x0 ~>
 * 0x300000000000000]] arg2: [[0x0 ~> 0x300000000000000], [0x0 ~>
 * 0x300000000000000], [0x0 ~> 0x300000000000000], [0x0 ~> 0x300000000000000],
 * [0x0 ~> 0x300000000000000], [0x0 ~> 0x300000000000000], [0x0 ~>
 * 0x300000000000000], [0x0 ~> 0x300000000000000]] Output Bounds: out1: [[0x0 ~>
 * 0x100000000000000], [0x0 ~> 0x100000000000000], [0x0 ~> 0x100000000000000],
 * [0x0 ~> 0x100000000000000], [0x0 ~> 0x100000000000000], [0x0 ~>
 * 0x100000000000000], [0x0 ~> 0x100000000000000], [0x0 ~> 0x100000000000000]]
 */
void fiat_p448_solinas_carry_mul(uint64_t out1[8], const uint64_t arg1[8],
                                 const uint64_t arg2[8]) {
  fiat_p448_solinas_uint128 x1;
  fiat_p448_solinas_uint128 x2;
  fiat_p448_solinas_uint128 x3;
  fiat_p448_solinas_uint128 x4;
  fiat_p448_solinas_uint128 x5;
  fiat_p448_solinas_uint128 x6;
  fiat_p448_solinas_uint128 x7;
  fiat_p448_solinas_uint128 x8;
  fiat_p448_solinas_uint128 x9;
  fiat_p448_solinas_uint128 x10;
  fiat_p448_solinas_uint128 x11;
  fiat_p448_solinas_uint128 x12;
  fiat_p448_solinas_uint128 x13;
  fiat_p448_solinas_uint128 x14;
  fiat_p448_solinas_uint128 x15;
  fiat_p448_solinas_uint128 x16;
  fiat_p448_solinas_uint128 x17;
  fiat_p448_solinas_uint128 x18;
  fiat_p448_solinas_uint128 x19;
  fiat_p448_solinas_uint128 x20;
  fiat_p448_solinas_uint128 x21;
  fiat_p448_solinas_uint128 x22;
  fiat_p448_solinas_uint128 x23;
  fiat_p448_solinas_uint128 x24;
  fiat_p448_solinas_uint128 x25;
  fiat_p448_solinas_uint128 x26;
  fiat_p448_solinas_uint128 x27;
  fiat_p448_solinas_uint128 x28;
  fiat_p448_solinas_uint128 x29;
  fiat_p448_solinas_uint128 x30;
  fiat_p448_solinas_uint128 x31;
  fiat_p448_solinas_uint128 x32;
  fiat_p448_solinas_uint128 x33;
  fiat_p448_solinas_uint128 x34;
  fiat_p448_solinas_uint128 x35;
  fiat_p448_solinas_uint128 x36;
  fiat_p448_solinas_uint128 x37;
  fiat_p448_solinas_uint128 x38;
  fiat_p448_solinas_uint128 x39;
  fiat_p448_solinas_uint128 x40;
  fiat_p448_solinas_uint128 x41;
  fiat_p448_solinas_uint128 x42;
  fiat_p448_solinas_uint128 x43;
  fiat_p448_solinas_uint128 x44;
  fiat_p448_solinas_uint128 x45;
  fiat_p448_solinas_uint128 x46;
  fiat_p448_solinas_uint128 x47;
  fiat_p448_solinas_uint128 x48;
  fiat_p448_solinas_uint128 x49;
  fiat_p448_solinas_uint128 x50;
  fiat_p448_solinas_uint128 x51;
  fiat_p448_solinas_uint128 x52;
  fiat_p448_solinas_uint128 x53;
  fiat_p448_solinas_uint128 x54;
  fiat_p448_solinas_uint128 x55;
  fiat_p448_solinas_uint128 x56;
  fiat_p448_solinas_uint128 x57;
  fiat_p448_solinas_uint128 x58;
  fiat_p448_solinas_uint128 x59;
  fiat_p448_solinas_uint128 x60;
  fiat_p448_solinas_uint128 x61;
  fiat_p448_solinas_uint128 x62;
  fiat_p448_solinas_uint128 x63;
  fiat_p448_solinas_uint128 x64;
  fiat_p448_solinas_uint128 x65;
  fiat_p448_solinas_uint128 x66;
  fiat_p448_solinas_uint128 x67;
  fiat_p448_solinas_uint128 x68;
  fiat_p448_solinas_uint128 x69;
  fiat_p448_solinas_uint128 x70;
  fiat_p448_solinas_uint128 x71;
  fiat_p448_solinas_uint128 x72;
  fiat_p448_solinas_uint128 x73;
  fiat_p448_solinas_uint128 x74;
  fiat_p448_solinas_uint128 x75;
  fiat_p448_solinas_uint128 x76;
  fiat_p448_solinas_uint128 x77;
  fiat_p448_solinas_uint128 x78;
  fiat_p448_solinas_uint128 x79;
  fiat_p448_solinas_uint128 x80;
  fiat_p448_solinas_uint128 x81;
  fiat_p448_solinas_uint128 x82;
  fiat_p448_solinas_uint128 x83;
  fiat_p448_solinas_uint128 x84;
  fiat_p448_solinas_uint128 x85;
  fiat_p448_solinas_uint128 x86;
  fiat_p448_solinas_uint128 x87;
  fiat_p448_solinas_uint128 x88;
  fiat_p448_solinas_uint128 x89;
  fiat_p448_solinas_uint128 x90;
  fiat_p448_solinas_uint128 x91;
  fiat_p448_solinas_uint128 x92;
  fiat_p448_solinas_uint128 x93;
  fiat_p448_solinas_uint128 x94;
  fiat_p448_solinas_uint128 x95;
  fiat_p448_solinas_uint128 x96;
  fiat_p448_solinas_uint128 x97;
  fiat_p448_solinas_uint128 x98;
  fiat_p448_solinas_uint128 x99;
  uint64_t x100;
  uint64_t x101;
  fiat_p448_solinas_uint128 x102;
  fiat_p448_solinas_uint128 x103;
  fiat_p448_solinas_uint128 x104;
  fiat_p448_solinas_uint128 x105;
  fiat_p448_solinas_uint128 x106;
  fiat_p448_solinas_uint128 x107;
  fiat_p448_solinas_uint128 x108;
  fiat_p448_solinas_uint128 x109;
  uint64_t x110;
  uint64_t x111;
  fiat_p448_solinas_uint128 x112;
  uint64_t x113;
  uint64_t x114;
  fiat_p448_solinas_uint128 x115;
  fiat_p448_solinas_uint128 x116;
  uint64_t x117;
  uint64_t x118;
  fiat_p448_solinas_uint128 x119;
  uint64_t x120;
  uint64_t x121;
  fiat_p448_solinas_uint128 x122;
  uint64_t x123;
  uint64_t x124;
  fiat_p448_solinas_uint128 x125;
  uint64_t x126;
  uint64_t x127;
  uint64_t x128;
  uint64_t x129;
  uint64_t x130;
  uint64_t x131;
  uint64_t x132;
  uint64_t x133;
  uint64_t x134;
  uint64_t x135;
  uint64_t x136;
  uint64_t x137;
  uint64_t x138;
  fiat_p448_solinas_uint1 x139;
  uint64_t x140;
  uint64_t x141;
  fiat_p448_solinas_uint1 x142;
  uint64_t x143;
  uint64_t x144;
  x1 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[7]));
  x2 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[6]));
  x3 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[5]));
  x4 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[7]));
  x5 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[6]));
  x6 = ((fiat_p448_solinas_uint128)(arg1[5]) * (arg2[7]));
  x7 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[7]));
  x8 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[6]));
  x9 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[5]));
  x10 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[7]));
  x11 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[6]));
  x12 = ((fiat_p448_solinas_uint128)(arg1[5]) * (arg2[7]));
  x13 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[7]));
  x14 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[6]));
  x15 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[5]));
  x16 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[4]));
  x17 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[3]));
  x18 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[2]));
  x19 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[1]));
  x20 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[7]));
  x21 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[6]));
  x22 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[5]));
  x23 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[4]));
  x24 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[3]));
  x25 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[2]));
  x26 = ((fiat_p448_solinas_uint128)(arg1[5]) * (arg2[7]));
  x27 = ((fiat_p448_solinas_uint128)(arg1[5]) * (arg2[6]));
  x28 = ((fiat_p448_solinas_uint128)(arg1[5]) * (arg2[5]));
  x29 = ((fiat_p448_solinas_uint128)(arg1[5]) * (arg2[4]));
  x30 = ((fiat_p448_solinas_uint128)(arg1[5]) * (arg2[3]));
  x31 = ((fiat_p448_solinas_uint128)(arg1[4]) * (arg2[7]));
  x32 = ((fiat_p448_solinas_uint128)(arg1[4]) * (arg2[6]));
  x33 = ((fiat_p448_solinas_uint128)(arg1[4]) * (arg2[5]));
  x34 = ((fiat_p448_solinas_uint128)(arg1[4]) * (arg2[4]));
  x35 = ((fiat_p448_solinas_uint128)(arg1[3]) * (arg2[7]));
  x36 = ((fiat_p448_solinas_uint128)(arg1[3]) * (arg2[6]));
  x37 = ((fiat_p448_solinas_uint128)(arg1[3]) * (arg2[5]));
  x38 = ((fiat_p448_solinas_uint128)(arg1[2]) * (arg2[7]));
  x39 = ((fiat_p448_solinas_uint128)(arg1[2]) * (arg2[6]));
  x40 = ((fiat_p448_solinas_uint128)(arg1[1]) * (arg2[7]));
  x41 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[4]));
  x42 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[3]));
  x43 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[2]));
  x44 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[1]));
  x45 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[5]));
  x46 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[4]));
  x47 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[3]));
  x48 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[2]));
  x49 = ((fiat_p448_solinas_uint128)(arg1[5]) * (arg2[6]));
  x50 = ((fiat_p448_solinas_uint128)(arg1[5]) * (arg2[5]));
  x51 = ((fiat_p448_solinas_uint128)(arg1[5]) * (arg2[4]));
  x52 = ((fiat_p448_solinas_uint128)(arg1[5]) * (arg2[3]));
  x53 = ((fiat_p448_solinas_uint128)(arg1[4]) * (arg2[7]));
  x54 = ((fiat_p448_solinas_uint128)(arg1[4]) * (arg2[6]));
  x55 = ((fiat_p448_solinas_uint128)(arg1[4]) * (arg2[5]));
  x56 = ((fiat_p448_solinas_uint128)(arg1[4]) * (arg2[4]));
  x57 = ((fiat_p448_solinas_uint128)(arg1[3]) * (arg2[7]));
  x58 = ((fiat_p448_solinas_uint128)(arg1[3]) * (arg2[6]));
  x59 = ((fiat_p448_solinas_uint128)(arg1[3]) * (arg2[5]));
  x60 = ((fiat_p448_solinas_uint128)(arg1[2]) * (arg2[7]));
  x61 = ((fiat_p448_solinas_uint128)(arg1[2]) * (arg2[6]));
  x62 = ((fiat_p448_solinas_uint128)(arg1[1]) * (arg2[7]));
  x63 = ((fiat_p448_solinas_uint128)(arg1[7]) * (arg2[0]));
  x64 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[1]));
  x65 = ((fiat_p448_solinas_uint128)(arg1[6]) * (arg2[0]));
  x66 = ((fiat_p448_solinas_uint128)(arg1[5]) * (arg2[2]));
  x67 = ((fiat_p448_solinas_uint128)(arg1[5]) * (arg2[1]));
  x68 = ((fiat_p448_solinas_uint128)(arg1[5]) * (arg2[0]));
  x69 = ((fiat_p448_solinas_uint128)(arg1[4]) * (arg2[3]));
  x70 = ((fiat_p448_solinas_uint128)(arg1[4]) * (arg2[2]));
  x71 = ((fiat_p448_solinas_uint128)(arg1[4]) * (arg2[1]));
  x72 = ((fiat_p448_solinas_uint128)(arg1[4]) * (arg2[0]));
  x73 = ((fiat_p448_solinas_uint128)(arg1[3]) * (arg2[4]));
  x74 = ((fiat_p448_solinas_uint128)(arg1[3]) * (arg2[3]));
  x75 = ((fiat_p448_solinas_uint128)(arg1[3]) * (arg2[2]));
  x76 = ((fiat_p448_solinas_uint128)(arg1[3]) * (arg2[1]));
  x77 = ((fiat_p448_solinas_uint128)(arg1[3]) * (arg2[0]));
  x78 = ((fiat_p448_solinas_uint128)(arg1[2]) * (arg2[5]));
  x79 = ((fiat_p448_solinas_uint128)(arg1[2]) * (arg2[4]));
  x80 = ((fiat_p448_solinas_uint128)(arg1[2]) * (arg2[3]));
  x81 = ((fiat_p448_solinas_uint128)(arg1[2]) * (arg2[2]));
  x82 = ((fiat_p448_solinas_uint128)(arg1[2]) * (arg2[1]));
  x83 = ((fiat_p448_solinas_uint128)(arg1[2]) * (arg2[0]));
  x84 = ((fiat_p448_solinas_uint128)(arg1[1]) * (arg2[6]));
  x85 = ((fiat_p448_solinas_uint128)(arg1[1]) * (arg2[5]));
  x86 = ((fiat_p448_solinas_uint128)(arg1[1]) * (arg2[4]));
  x87 = ((fiat_p448_solinas_uint128)(arg1[1]) * (arg2[3]));
  x88 = ((fiat_p448_solinas_uint128)(arg1[1]) * (arg2[2]));
  x89 = ((fiat_p448_solinas_uint128)(arg1[1]) * (arg2[1]));
  x90 = ((fiat_p448_solinas_uint128)(arg1[1]) * (arg2[0]));
  x91 = ((fiat_p448_solinas_uint128)(arg1[0]) * (arg2[7]));
  x92 = ((fiat_p448_solinas_uint128)(arg1[0]) * (arg2[6]));
  x93 = ((fiat_p448_solinas_uint128)(arg1[0]) * (arg2[5]));
  x94 = ((fiat_p448_solinas_uint128)(arg1[0]) * (arg2[4]));
  x95 = ((fiat_p448_solinas_uint128)(arg1[0]) * (arg2[3]));
  x96 = ((fiat_p448_solinas_uint128)(arg1[0]) * (arg2[2]));
  x97 = ((fiat_p448_solinas_uint128)(arg1[0]) * (arg2[1]));
  x98 = ((fiat_p448_solinas_uint128)(arg1[0]) * (arg2[0]));
  x99 = (x95 + (x88 + (x82 + (x77 + (x31 + (x27 + (x22 + x16)))))));
  x100 = (uint64_t)(x99 >> 56);
  x101 = (uint64_t)(x99 & UINT64_C(0xffffffffffffff));
  x102 =
      (x91 +
       (x84 +
        (x78 +
         (x73 + (x69 + (x66 + (x64 + (x63 + (x53 + (x49 + (x45 + x41)))))))))));
  x103 = (x92 +
          (x85 +
           (x79 +
            (x74 +
             (x70 +
              (x67 +
               (x65 + (x57 + (x54 + (x50 + (x46 + (x42 + (x13 + x7)))))))))))));
  x104 = (x93 +
          (x86 +
           (x80 +
            (x75 +
             (x71 +
              (x68 +
               (x60 +
                (x58 +
                 (x55 +
                  (x51 + (x47 + (x43 + (x20 + (x14 + (x10 + x8)))))))))))))));
  x105 =
      (x94 +
       (x87 +
        (x81 +
         (x76 +
          (x72 +
           (x62 +
            (x61 +
             (x59 +
              (x56 +
               (x52 +
                (x48 +
                 (x44 + (x26 + (x21 + (x15 + (x12 + (x11 + x9)))))))))))))))));
  x106 = (x96 + (x89 + (x83 + (x35 + (x32 + (x28 + (x23 + (x17 + x1))))))));
  x107 =
      (x97 + (x90 + (x38 + (x36 + (x33 + (x29 + (x24 + (x18 + (x4 + x2)))))))));
  x108 = (x98 +
          (x40 +
           (x39 + (x37 + (x34 + (x30 + (x25 + (x19 + (x6 + (x5 + x3))))))))));
  x109 = (x100 + x105);
  x110 = (uint64_t)(x102 >> 56);
  x111 = (uint64_t)(x102 & UINT64_C(0xffffffffffffff));
  x112 = (x109 + x110);
  x113 = (uint64_t)(x112 >> 56);
  x114 = (uint64_t)(x112 & UINT64_C(0xffffffffffffff));
  x115 = (x108 + x110);
  x116 = (x113 + x104);
  x117 = (uint64_t)(x115 >> 56);
  x118 = (uint64_t)(x115 & UINT64_C(0xffffffffffffff));
  x119 = (x117 + x107);
  x120 = (uint64_t)(x116 >> 56);
  x121 = (uint64_t)(x116 & UINT64_C(0xffffffffffffff));
  x122 = (x120 + x103);
  x123 = (uint64_t)(x119 >> 56);
  x124 = (uint64_t)(x119 & UINT64_C(0xffffffffffffff));
  x125 = (x123 + x106);
  x126 = (uint64_t)(x122 >> 56);
  x127 = (uint64_t)(x122 & UINT64_C(0xffffffffffffff));
  x128 = (x126 + x111);
  x129 = (uint64_t)(x125 >> 56);
  x130 = (uint64_t)(x125 & UINT64_C(0xffffffffffffff));
  x131 = (x129 + x101);
  x132 = (x128 >> 56);
  x133 = (x128 & UINT64_C(0xffffffffffffff));
  x134 = (x131 >> 56);
  x135 = (x131 & UINT64_C(0xffffffffffffff));
  x136 = (x114 + x132);
  x137 = (x118 + x132);
  x138 = (x134 + x136);
  x139 = (fiat_p448_solinas_uint1)(x138 >> 56);
  x140 = (x138 & UINT64_C(0xffffffffffffff));
  x141 = (x139 + x121);
  x142 = (fiat_p448_solinas_uint1)(x137 >> 56);
  x143 = (x137 & UINT64_C(0xffffffffffffff));
  x144 = (x142 + x124);
  out1[0] = x143;
  out1[1] = x144;
  out1[2] = x130;
  out1[3] = x135;
  out1[4] = x140;
  out1[5] = x141;
  out1[6] = x127;
  out1[7] = x133;
}

/*
 * The function fiat_p448_solinas_carry_square squares a field element and
 * reduces the result. Postconditions: eval out1 mod m = (eval arg1 * eval arg1)
 * mod m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0x300000000000000], [0x0 ~> 0x300000000000000], [0x0 ~>
 * 0x300000000000000], [0x0 ~> 0x300000000000000], [0x0 ~> 0x300000000000000],
 * [0x0 ~> 0x300000000000000], [0x0 ~> 0x300000000000000], [0x0 ~>
 * 0x300000000000000]] Output Bounds: out1: [[0x0 ~> 0x100000000000000], [0x0 ~>
 * 0x100000000000000], [0x0 ~> 0x100000000000000], [0x0 ~> 0x100000000000000],
 * [0x0 ~> 0x100000000000000], [0x0 ~> 0x100000000000000], [0x0 ~>
 * 0x100000000000000], [0x0 ~> 0x100000000000000]]
 */
void fiat_p448_solinas_carry_square(uint64_t out1[8], const uint64_t arg1[8]) {
  uint64_t x1;
  uint64_t x2;
  uint64_t x3;
  uint64_t x4;
  uint64_t x5;
  uint64_t x6;
  uint64_t x7;
  uint64_t x8;
  uint64_t x9;
  uint64_t x10;
  uint64_t x11;
  uint64_t x12;
  uint64_t x13;
  uint64_t x14;
  uint64_t x15;
  uint64_t x16;
  uint64_t x17;
  uint64_t x18;
  uint64_t x19;
  uint64_t x20;
  uint64_t x21;
  fiat_p448_solinas_uint128 x22;
  fiat_p448_solinas_uint128 x23;
  fiat_p448_solinas_uint128 x24;
  fiat_p448_solinas_uint128 x25;
  fiat_p448_solinas_uint128 x26;
  fiat_p448_solinas_uint128 x27;
  fiat_p448_solinas_uint128 x28;
  fiat_p448_solinas_uint128 x29;
  fiat_p448_solinas_uint128 x30;
  fiat_p448_solinas_uint128 x31;
  fiat_p448_solinas_uint128 x32;
  fiat_p448_solinas_uint128 x33;
  fiat_p448_solinas_uint128 x34;
  fiat_p448_solinas_uint128 x35;
  fiat_p448_solinas_uint128 x36;
  fiat_p448_solinas_uint128 x37;
  fiat_p448_solinas_uint128 x38;
  fiat_p448_solinas_uint128 x39;
  fiat_p448_solinas_uint128 x40;
  fiat_p448_solinas_uint128 x41;
  fiat_p448_solinas_uint128 x42;
  fiat_p448_solinas_uint128 x43;
  fiat_p448_solinas_uint128 x44;
  fiat_p448_solinas_uint128 x45;
  fiat_p448_solinas_uint128 x46;
  fiat_p448_solinas_uint128 x47;
  fiat_p448_solinas_uint128 x48;
  fiat_p448_solinas_uint128 x49;
  fiat_p448_solinas_uint128 x50;
  fiat_p448_solinas_uint128 x51;
  fiat_p448_solinas_uint128 x52;
  fiat_p448_solinas_uint128 x53;
  fiat_p448_solinas_uint128 x54;
  fiat_p448_solinas_uint128 x55;
  fiat_p448_solinas_uint128 x56;
  fiat_p448_solinas_uint128 x57;
  fiat_p448_solinas_uint128 x58;
  fiat_p448_solinas_uint128 x59;
  fiat_p448_solinas_uint128 x60;
  fiat_p448_solinas_uint128 x61;
  fiat_p448_solinas_uint128 x62;
  fiat_p448_solinas_uint128 x63;
  fiat_p448_solinas_uint128 x64;
  fiat_p448_solinas_uint128 x65;
  fiat_p448_solinas_uint128 x66;
  fiat_p448_solinas_uint128 x67;
  fiat_p448_solinas_uint128 x68;
  fiat_p448_solinas_uint128 x69;
  fiat_p448_solinas_uint128 x70;
  fiat_p448_solinas_uint128 x71;
  fiat_p448_solinas_uint128 x72;
  fiat_p448_solinas_uint128 x73;
  fiat_p448_solinas_uint128 x74;
  fiat_p448_solinas_uint128 x75;
  fiat_p448_solinas_uint128 x76;
  fiat_p448_solinas_uint128 x77;
  fiat_p448_solinas_uint128 x78;
  uint64_t x79;
  uint64_t x80;
  fiat_p448_solinas_uint128 x81;
  fiat_p448_solinas_uint128 x82;
  fiat_p448_solinas_uint128 x83;
  fiat_p448_solinas_uint128 x84;
  fiat_p448_solinas_uint128 x85;
  fiat_p448_solinas_uint128 x86;
  fiat_p448_solinas_uint128 x87;
  fiat_p448_solinas_uint128 x88;
  uint64_t x89;
  uint64_t x90;
  fiat_p448_solinas_uint128 x91;
  uint64_t x92;
  uint64_t x93;
  fiat_p448_solinas_uint128 x94;
  fiat_p448_solinas_uint128 x95;
  uint64_t x96;
  uint64_t x97;
  fiat_p448_solinas_uint128 x98;
  uint64_t x99;
  uint64_t x100;
  fiat_p448_solinas_uint128 x101;
  uint64_t x102;
  uint64_t x103;
  fiat_p448_solinas_uint128 x104;
  uint64_t x105;
  uint64_t x106;
  uint64_t x107;
  uint64_t x108;
  uint64_t x109;
  uint64_t x110;
  uint64_t x111;
  uint64_t x112;
  uint64_t x113;
  uint64_t x114;
  uint64_t x115;
  uint64_t x116;
  uint64_t x117;
  fiat_p448_solinas_uint1 x118;
  uint64_t x119;
  uint64_t x120;
  fiat_p448_solinas_uint1 x121;
  uint64_t x122;
  uint64_t x123;
  x1 = (arg1[7]);
  x2 = (arg1[7]);
  x3 = (x1 * 0x2);
  x4 = (x2 * 0x2);
  x5 = ((arg1[7]) * 0x2);
  x6 = (arg1[6]);
  x7 = (arg1[6]);
  x8 = (x6 * 0x2);
  x9 = (x7 * 0x2);
  x10 = ((arg1[6]) * 0x2);
  x11 = (arg1[5]);
  x12 = (arg1[5]);
  x13 = (x11 * 0x2);
  x14 = (x12 * 0x2);
  x15 = ((arg1[5]) * 0x2);
  x16 = (arg1[4]);
  x17 = (arg1[4]);
  x18 = ((arg1[4]) * 0x2);
  x19 = ((arg1[3]) * 0x2);
  x20 = ((arg1[2]) * 0x2);
  x21 = ((arg1[1]) * 0x2);
  x22 = ((fiat_p448_solinas_uint128)(arg1[7]) * x1);
  x23 = ((fiat_p448_solinas_uint128)(arg1[6]) * x3);
  x24 = ((fiat_p448_solinas_uint128)(arg1[6]) * x6);
  x25 = ((fiat_p448_solinas_uint128)(arg1[5]) * x3);
  x26 = ((fiat_p448_solinas_uint128)(arg1[7]) * x1);
  x27 = ((fiat_p448_solinas_uint128)(arg1[6]) * x3);
  x28 = ((fiat_p448_solinas_uint128)(arg1[6]) * x6);
  x29 = ((fiat_p448_solinas_uint128)(arg1[5]) * x3);
  x30 = ((fiat_p448_solinas_uint128)(arg1[7]) * x2);
  x31 = ((fiat_p448_solinas_uint128)(arg1[6]) * x4);
  x32 = ((fiat_p448_solinas_uint128)(arg1[6]) * x7);
  x33 = ((fiat_p448_solinas_uint128)(arg1[5]) * x4);
  x34 = ((fiat_p448_solinas_uint128)(arg1[5]) * x9);
  x35 = ((fiat_p448_solinas_uint128)(arg1[5]) * x8);
  x36 = ((fiat_p448_solinas_uint128)(arg1[5]) * x12);
  x37 = ((fiat_p448_solinas_uint128)(arg1[5]) * x11);
  x38 = ((fiat_p448_solinas_uint128)(arg1[4]) * x4);
  x39 = ((fiat_p448_solinas_uint128)(arg1[4]) * x3);
  x40 = ((fiat_p448_solinas_uint128)(arg1[4]) * x9);
  x41 = ((fiat_p448_solinas_uint128)(arg1[4]) * x8);
  x42 = ((fiat_p448_solinas_uint128)(arg1[4]) * x14);
  x43 = ((fiat_p448_solinas_uint128)(arg1[4]) * x13);
  x44 = ((fiat_p448_solinas_uint128)(arg1[4]) * x17);
  x45 = ((fiat_p448_solinas_uint128)(arg1[4]) * x16);
  x46 = ((fiat_p448_solinas_uint128)(arg1[3]) * x4);
  x47 = ((fiat_p448_solinas_uint128)(arg1[3]) * x3);
  x48 = ((fiat_p448_solinas_uint128)(arg1[3]) * x9);
  x49 = ((fiat_p448_solinas_uint128)(arg1[3]) * x8);
  x50 = ((fiat_p448_solinas_uint128)(arg1[3]) * x14);
  x51 = ((fiat_p448_solinas_uint128)(arg1[3]) * x13);
  x52 = ((fiat_p448_solinas_uint128)(arg1[3]) * x18);
  x53 = ((fiat_p448_solinas_uint128)(arg1[3]) * (arg1[3]));
  x54 = ((fiat_p448_solinas_uint128)(arg1[2]) * x4);
  x55 = ((fiat_p448_solinas_uint128)(arg1[2]) * x3);
  x56 = ((fiat_p448_solinas_uint128)(arg1[2]) * x9);
  x57 = ((fiat_p448_solinas_uint128)(arg1[2]) * x8);
  x58 = ((fiat_p448_solinas_uint128)(arg1[2]) * x15);
  x59 = ((fiat_p448_solinas_uint128)(arg1[2]) * x18);
  x60 = ((fiat_p448_solinas_uint128)(arg1[2]) * x19);
  x61 = ((fiat_p448_solinas_uint128)(arg1[2]) * (arg1[2]));
  x62 = ((fiat_p448_solinas_uint128)(arg1[1]) * x4);
  x63 = ((fiat_p448_solinas_uint128)(arg1[1]) * x3);
  x64 = ((fiat_p448_solinas_uint128)(arg1[1]) * x10);
  x65 = ((fiat_p448_solinas_uint128)(arg1[1]) * x15);
  x66 = ((fiat_p448_solinas_uint128)(arg1[1]) * x18);
  x67 = ((fiat_p448_solinas_uint128)(arg1[1]) * x19);
  x68 = ((fiat_p448_solinas_uint128)(arg1[1]) * x20);
  x69 = ((fiat_p448_solinas_uint128)(arg1[1]) * (arg1[1]));
  x70 = ((fiat_p448_solinas_uint128)(arg1[0]) * x5);
  x71 = ((fiat_p448_solinas_uint128)(arg1[0]) * x10);
  x72 = ((fiat_p448_solinas_uint128)(arg1[0]) * x15);
  x73 = ((fiat_p448_solinas_uint128)(arg1[0]) * x18);
  x74 = ((fiat_p448_solinas_uint128)(arg1[0]) * x19);
  x75 = ((fiat_p448_solinas_uint128)(arg1[0]) * x20);
  x76 = ((fiat_p448_solinas_uint128)(arg1[0]) * x21);
  x77 = ((fiat_p448_solinas_uint128)(arg1[0]) * (arg1[0]));
  x78 = (x74 + (x68 + (x38 + x34)));
  x79 = (uint64_t)(x78 >> 56);
  x80 = (uint64_t)(x78 & UINT64_C(0xffffffffffffff));
  x81 = (x70 + (x64 + (x58 + (x52 + (x39 + x35)))));
  x82 = (x71 + (x65 + (x59 + (x53 + (x47 + (x41 + (x37 + (x30 + x26))))))));
  x83 = (x72 + (x66 + (x60 + (x55 + (x49 + (x43 + (x31 + x27)))))));
  x84 = (x73 +
         (x67 +
          (x63 + (x61 + (x57 + (x51 + (x45 + (x33 + (x32 + (x29 + x28))))))))));
  x85 = (x75 + (x69 + (x46 + (x40 + (x36 + x22)))));
  x86 = (x76 + (x54 + (x48 + (x42 + x23))));
  x87 = (x77 + (x62 + (x56 + (x50 + (x44 + (x25 + x24))))));
  x88 = (x79 + x84);
  x89 = (uint64_t)(x81 >> 56);
  x90 = (uint64_t)(x81 & UINT64_C(0xffffffffffffff));
  x91 = (x88 + x89);
  x92 = (uint64_t)(x91 >> 56);
  x93 = (uint64_t)(x91 & UINT64_C(0xffffffffffffff));
  x94 = (x87 + x89);
  x95 = (x92 + x83);
  x96 = (uint64_t)(x94 >> 56);
  x97 = (uint64_t)(x94 & UINT64_C(0xffffffffffffff));
  x98 = (x96 + x86);
  x99 = (uint64_t)(x95 >> 56);
  x100 = (uint64_t)(x95 & UINT64_C(0xffffffffffffff));
  x101 = (x99 + x82);
  x102 = (uint64_t)(x98 >> 56);
  x103 = (uint64_t)(x98 & UINT64_C(0xffffffffffffff));
  x104 = (x102 + x85);
  x105 = (uint64_t)(x101 >> 56);
  x106 = (uint64_t)(x101 & UINT64_C(0xffffffffffffff));
  x107 = (x105 + x90);
  x108 = (uint64_t)(x104 >> 56);
  x109 = (uint64_t)(x104 & UINT64_C(0xffffffffffffff));
  x110 = (x108 + x80);
  x111 = (x107 >> 56);
  x112 = (x107 & UINT64_C(0xffffffffffffff));
  x113 = (x110 >> 56);
  x114 = (x110 & UINT64_C(0xffffffffffffff));
  x115 = (x93 + x111);
  x116 = (x97 + x111);
  x117 = (x113 + x115);
  x118 = (fiat_p448_solinas_uint1)(x117 >> 56);
  x119 = (x117 & UINT64_C(0xffffffffffffff));
  x120 = (x118 + x100);
  x121 = (fiat_p448_solinas_uint1)(x116 >> 56);
  x122 = (x116 & UINT64_C(0xffffffffffffff));
  x123 = (x121 + x103);
  out1[0] = x122;
  out1[1] = x123;
  out1[2] = x109;
  out1[3] = x114;
  out1[4] = x119;
  out1[5] = x120;
  out1[6] = x106;
  out1[7] = x112;
}

/* curve description: p521 */
/* machine_wordsize = 64 (from "64") */
/* requested operations: carry_mul, carry_square */
/* n = 9 (from "9") */
/* s-c = 2^521 - [(1, 1)] (from "2^521 - 1") */
/* tight_bounds_multiplier = 1 (from "") */
/*  */
/* Computed values: */
/* carry_chain = [0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 1] */
/* eval z = z[0] + (z[1] << 58) + (z[2] << 116) + (z[3] << 174) + (z[4] << 232)
 * + (z[5] << 0x122) + (z[6] << 0x15c) + (z[7] << 0x196) + (z[8] << 0x1d0) */
/* bytes_eval z = z[0] + (z[1] << 8) + (z[2] << 16) + (z[3] << 24) + (z[4] <<
 * 32) + (z[5] << 40) + (z[6] << 48) + (z[7] << 56) + (z[8] << 64) + (z[9] <<
 * 72) + (z[10] << 80) + (z[11] << 88) + (z[12] << 96) + (z[13] << 104) + (z[14]
 * << 112) + (z[15] << 120) + (z[16] << 128) + (z[17] << 136) + (z[18] << 144) +
 * (z[19] << 152) + (z[20] << 160) + (z[21] << 168) + (z[22] << 176) + (z[23] <<
 * 184) + (z[24] << 192) + (z[25] << 200) + (z[26] << 208) + (z[27] << 216) +
 * (z[28] << 224) + (z[29] << 232) + (z[30] << 240) + (z[31] << 248) + (z[32] <<
 * 256) + (z[33] << 0x108) + (z[34] << 0x110) + (z[35] << 0x118) + (z[36] <<
 * 0x120) + (z[37] << 0x128) + (z[38] << 0x130) + (z[39] << 0x138) + (z[40] <<
 * 0x140) + (z[41] << 0x148) + (z[42] << 0x150) + (z[43] << 0x158) + (z[44] <<
 * 0x160) + (z[45] << 0x168) + (z[46] << 0x170) + (z[47] << 0x178) + (z[48] <<
 * 0x180) + (z[49] << 0x188) + (z[50] << 0x190) + (z[51] << 0x198) + (z[52] <<
 * 0x1a0) + (z[53] << 0x1a8) + (z[54] << 0x1b0) + (z[55] << 0x1b8) + (z[56] <<
 * 0x1c0) + (z[57] << 0x1c8) + (z[58] << 0x1d0) + (z[59] << 0x1d8) + (z[60] <<
 * 0x1e0) + (z[61] << 0x1e8) + (z[62] << 0x1f0) + (z[63] << 0x1f8) + (z[64] <<
 * 2^9) + (z[65] << 0x208) */
/* balance = [0x7fffffffffffffe, 0x7fffffffffffffe, 0x7fffffffffffffe,
 * 0x7fffffffffffffe, 0x7fffffffffffffe, 0x7fffffffffffffe, 0x7fffffffffffffe,
 * 0x7fffffffffffffe, 0x3fffffffffffffe] */

#include <stdint.h>
typedef unsigned char fiat_p521_uint1;
typedef signed char fiat_p521_int1;
typedef signed __int128 fiat_p521_int128;
typedef unsigned __int128 fiat_p521_uint128;

#if (-1 & 3) != 3
#error "This code only works on a two's complement system"
#endif

/*
 * The function fiat_p521_carry_mul multiplies two field elements and reduces
 * the result. Postconditions: eval out1 mod m = (eval arg1 * eval arg2) mod m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xc00000000000000], [0x0 ~> 0xc00000000000000], [0x0 ~>
 * 0xc00000000000000], [0x0 ~> 0xc00000000000000], [0x0 ~> 0xc00000000000000],
 * [0x0 ~> 0xc00000000000000], [0x0 ~> 0xc00000000000000], [0x0 ~>
 * 0xc00000000000000], [0x0 ~> 0x600000000000000]] arg2: [[0x0 ~>
 * 0xc00000000000000], [0x0 ~> 0xc00000000000000], [0x0 ~> 0xc00000000000000],
 * [0x0 ~> 0xc00000000000000], [0x0 ~> 0xc00000000000000], [0x0 ~>
 * 0xc00000000000000], [0x0 ~> 0xc00000000000000], [0x0 ~> 0xc00000000000000],
 * [0x0 ~> 0x600000000000000]] Output Bounds: out1: [[0x0 ~> 0x400000000000000],
 * [0x0 ~> 0x400000000000000], [0x0 ~> 0x400000000000000], [0x0 ~>
 * 0x400000000000000], [0x0 ~> 0x400000000000000], [0x0 ~> 0x400000000000000],
 * [0x0 ~> 0x400000000000000], [0x0 ~> 0x400000000000000], [0x0 ~>
 * 0x200000000000000]]
 */
void fiat_p521_carry_mul(uint64_t out1[9], const uint64_t arg1[9],
                         const uint64_t arg2[9]) {
  fiat_p521_uint128 x1;
  fiat_p521_uint128 x2;
  fiat_p521_uint128 x3;
  fiat_p521_uint128 x4;
  fiat_p521_uint128 x5;
  fiat_p521_uint128 x6;
  fiat_p521_uint128 x7;
  fiat_p521_uint128 x8;
  fiat_p521_uint128 x9;
  fiat_p521_uint128 x10;
  fiat_p521_uint128 x11;
  fiat_p521_uint128 x12;
  fiat_p521_uint128 x13;
  fiat_p521_uint128 x14;
  fiat_p521_uint128 x15;
  fiat_p521_uint128 x16;
  fiat_p521_uint128 x17;
  fiat_p521_uint128 x18;
  fiat_p521_uint128 x19;
  fiat_p521_uint128 x20;
  fiat_p521_uint128 x21;
  fiat_p521_uint128 x22;
  fiat_p521_uint128 x23;
  fiat_p521_uint128 x24;
  fiat_p521_uint128 x25;
  fiat_p521_uint128 x26;
  fiat_p521_uint128 x27;
  fiat_p521_uint128 x28;
  fiat_p521_uint128 x29;
  fiat_p521_uint128 x30;
  fiat_p521_uint128 x31;
  fiat_p521_uint128 x32;
  fiat_p521_uint128 x33;
  fiat_p521_uint128 x34;
  fiat_p521_uint128 x35;
  fiat_p521_uint128 x36;
  fiat_p521_uint128 x37;
  fiat_p521_uint128 x38;
  fiat_p521_uint128 x39;
  fiat_p521_uint128 x40;
  fiat_p521_uint128 x41;
  fiat_p521_uint128 x42;
  fiat_p521_uint128 x43;
  fiat_p521_uint128 x44;
  fiat_p521_uint128 x45;
  fiat_p521_uint128 x46;
  fiat_p521_uint128 x47;
  fiat_p521_uint128 x48;
  fiat_p521_uint128 x49;
  fiat_p521_uint128 x50;
  fiat_p521_uint128 x51;
  fiat_p521_uint128 x52;
  fiat_p521_uint128 x53;
  fiat_p521_uint128 x54;
  fiat_p521_uint128 x55;
  fiat_p521_uint128 x56;
  fiat_p521_uint128 x57;
  fiat_p521_uint128 x58;
  fiat_p521_uint128 x59;
  fiat_p521_uint128 x60;
  fiat_p521_uint128 x61;
  fiat_p521_uint128 x62;
  fiat_p521_uint128 x63;
  fiat_p521_uint128 x64;
  fiat_p521_uint128 x65;
  fiat_p521_uint128 x66;
  fiat_p521_uint128 x67;
  fiat_p521_uint128 x68;
  fiat_p521_uint128 x69;
  fiat_p521_uint128 x70;
  fiat_p521_uint128 x71;
  fiat_p521_uint128 x72;
  fiat_p521_uint128 x73;
  fiat_p521_uint128 x74;
  fiat_p521_uint128 x75;
  fiat_p521_uint128 x76;
  fiat_p521_uint128 x77;
  fiat_p521_uint128 x78;
  fiat_p521_uint128 x79;
  fiat_p521_uint128 x80;
  fiat_p521_uint128 x81;
  fiat_p521_uint128 x82;
  fiat_p521_uint128 x83;
  uint64_t x84;
  fiat_p521_uint128 x85;
  fiat_p521_uint128 x86;
  fiat_p521_uint128 x87;
  fiat_p521_uint128 x88;
  fiat_p521_uint128 x89;
  fiat_p521_uint128 x90;
  fiat_p521_uint128 x91;
  fiat_p521_uint128 x92;
  fiat_p521_uint128 x93;
  fiat_p521_uint128 x94;
  uint64_t x95;
  fiat_p521_uint128 x96;
  fiat_p521_uint128 x97;
  uint64_t x98;
  fiat_p521_uint128 x99;
  fiat_p521_uint128 x100;
  uint64_t x101;
  fiat_p521_uint128 x102;
  fiat_p521_uint128 x103;
  uint64_t x104;
  fiat_p521_uint128 x105;
  fiat_p521_uint128 x106;
  uint64_t x107;
  fiat_p521_uint128 x108;
  fiat_p521_uint128 x109;
  uint64_t x110;
  fiat_p521_uint128 x111;
  fiat_p521_uint128 x112;
  uint64_t x113;
  fiat_p521_uint128 x114;
  fiat_p521_uint128 x115;
  uint64_t x116;
  fiat_p521_uint128 x117;
  uint64_t x118;
  uint64_t x119;
  uint64_t x120;
  fiat_p521_uint1 x121;
  uint64_t x122;
  uint64_t x123;
  x1 = ((fiat_p521_uint128)(arg1[8]) * ((arg2[8]) * 0x2));
  x2 = ((fiat_p521_uint128)(arg1[8]) * ((arg2[7]) * 0x2));
  x3 = ((fiat_p521_uint128)(arg1[8]) * ((arg2[6]) * 0x2));
  x4 = ((fiat_p521_uint128)(arg1[8]) * ((arg2[5]) * 0x2));
  x5 = ((fiat_p521_uint128)(arg1[8]) * ((arg2[4]) * 0x2));
  x6 = ((fiat_p521_uint128)(arg1[8]) * ((arg2[3]) * 0x2));
  x7 = ((fiat_p521_uint128)(arg1[8]) * ((arg2[2]) * 0x2));
  x8 = ((fiat_p521_uint128)(arg1[8]) * ((arg2[1]) * 0x2));
  x9 = ((fiat_p521_uint128)(arg1[7]) * ((arg2[8]) * 0x2));
  x10 = ((fiat_p521_uint128)(arg1[7]) * ((arg2[7]) * 0x2));
  x11 = ((fiat_p521_uint128)(arg1[7]) * ((arg2[6]) * 0x2));
  x12 = ((fiat_p521_uint128)(arg1[7]) * ((arg2[5]) * 0x2));
  x13 = ((fiat_p521_uint128)(arg1[7]) * ((arg2[4]) * 0x2));
  x14 = ((fiat_p521_uint128)(arg1[7]) * ((arg2[3]) * 0x2));
  x15 = ((fiat_p521_uint128)(arg1[7]) * ((arg2[2]) * 0x2));
  x16 = ((fiat_p521_uint128)(arg1[6]) * ((arg2[8]) * 0x2));
  x17 = ((fiat_p521_uint128)(arg1[6]) * ((arg2[7]) * 0x2));
  x18 = ((fiat_p521_uint128)(arg1[6]) * ((arg2[6]) * 0x2));
  x19 = ((fiat_p521_uint128)(arg1[6]) * ((arg2[5]) * 0x2));
  x20 = ((fiat_p521_uint128)(arg1[6]) * ((arg2[4]) * 0x2));
  x21 = ((fiat_p521_uint128)(arg1[6]) * ((arg2[3]) * 0x2));
  x22 = ((fiat_p521_uint128)(arg1[5]) * ((arg2[8]) * 0x2));
  x23 = ((fiat_p521_uint128)(arg1[5]) * ((arg2[7]) * 0x2));
  x24 = ((fiat_p521_uint128)(arg1[5]) * ((arg2[6]) * 0x2));
  x25 = ((fiat_p521_uint128)(arg1[5]) * ((arg2[5]) * 0x2));
  x26 = ((fiat_p521_uint128)(arg1[5]) * ((arg2[4]) * 0x2));
  x27 = ((fiat_p521_uint128)(arg1[4]) * ((arg2[8]) * 0x2));
  x28 = ((fiat_p521_uint128)(arg1[4]) * ((arg2[7]) * 0x2));
  x29 = ((fiat_p521_uint128)(arg1[4]) * ((arg2[6]) * 0x2));
  x30 = ((fiat_p521_uint128)(arg1[4]) * ((arg2[5]) * 0x2));
  x31 = ((fiat_p521_uint128)(arg1[3]) * ((arg2[8]) * 0x2));
  x32 = ((fiat_p521_uint128)(arg1[3]) * ((arg2[7]) * 0x2));
  x33 = ((fiat_p521_uint128)(arg1[3]) * ((arg2[6]) * 0x2));
  x34 = ((fiat_p521_uint128)(arg1[2]) * ((arg2[8]) * 0x2));
  x35 = ((fiat_p521_uint128)(arg1[2]) * ((arg2[7]) * 0x2));
  x36 = ((fiat_p521_uint128)(arg1[1]) * ((arg2[8]) * 0x2));
  x37 = ((fiat_p521_uint128)(arg1[8]) * (arg2[0]));
  x38 = ((fiat_p521_uint128)(arg1[7]) * (arg2[1]));
  x39 = ((fiat_p521_uint128)(arg1[7]) * (arg2[0]));
  x40 = ((fiat_p521_uint128)(arg1[6]) * (arg2[2]));
  x41 = ((fiat_p521_uint128)(arg1[6]) * (arg2[1]));
  x42 = ((fiat_p521_uint128)(arg1[6]) * (arg2[0]));
  x43 = ((fiat_p521_uint128)(arg1[5]) * (arg2[3]));
  x44 = ((fiat_p521_uint128)(arg1[5]) * (arg2[2]));
  x45 = ((fiat_p521_uint128)(arg1[5]) * (arg2[1]));
  x46 = ((fiat_p521_uint128)(arg1[5]) * (arg2[0]));
  x47 = ((fiat_p521_uint128)(arg1[4]) * (arg2[4]));
  x48 = ((fiat_p521_uint128)(arg1[4]) * (arg2[3]));
  x49 = ((fiat_p521_uint128)(arg1[4]) * (arg2[2]));
  x50 = ((fiat_p521_uint128)(arg1[4]) * (arg2[1]));
  x51 = ((fiat_p521_uint128)(arg1[4]) * (arg2[0]));
  x52 = ((fiat_p521_uint128)(arg1[3]) * (arg2[5]));
  x53 = ((fiat_p521_uint128)(arg1[3]) * (arg2[4]));
  x54 = ((fiat_p521_uint128)(arg1[3]) * (arg2[3]));
  x55 = ((fiat_p521_uint128)(arg1[3]) * (arg2[2]));
  x56 = ((fiat_p521_uint128)(arg1[3]) * (arg2[1]));
  x57 = ((fiat_p521_uint128)(arg1[3]) * (arg2[0]));
  x58 = ((fiat_p521_uint128)(arg1[2]) * (arg2[6]));
  x59 = ((fiat_p521_uint128)(arg1[2]) * (arg2[5]));
  x60 = ((fiat_p521_uint128)(arg1[2]) * (arg2[4]));
  x61 = ((fiat_p521_uint128)(arg1[2]) * (arg2[3]));
  x62 = ((fiat_p521_uint128)(arg1[2]) * (arg2[2]));
  x63 = ((fiat_p521_uint128)(arg1[2]) * (arg2[1]));
  x64 = ((fiat_p521_uint128)(arg1[2]) * (arg2[0]));
  x65 = ((fiat_p521_uint128)(arg1[1]) * (arg2[7]));
  x66 = ((fiat_p521_uint128)(arg1[1]) * (arg2[6]));
  x67 = ((fiat_p521_uint128)(arg1[1]) * (arg2[5]));
  x68 = ((fiat_p521_uint128)(arg1[1]) * (arg2[4]));
  x69 = ((fiat_p521_uint128)(arg1[1]) * (arg2[3]));
  x70 = ((fiat_p521_uint128)(arg1[1]) * (arg2[2]));
  x71 = ((fiat_p521_uint128)(arg1[1]) * (arg2[1]));
  x72 = ((fiat_p521_uint128)(arg1[1]) * (arg2[0]));
  x73 = ((fiat_p521_uint128)(arg1[0]) * (arg2[8]));
  x74 = ((fiat_p521_uint128)(arg1[0]) * (arg2[7]));
  x75 = ((fiat_p521_uint128)(arg1[0]) * (arg2[6]));
  x76 = ((fiat_p521_uint128)(arg1[0]) * (arg2[5]));
  x77 = ((fiat_p521_uint128)(arg1[0]) * (arg2[4]));
  x78 = ((fiat_p521_uint128)(arg1[0]) * (arg2[3]));
  x79 = ((fiat_p521_uint128)(arg1[0]) * (arg2[2]));
  x80 = ((fiat_p521_uint128)(arg1[0]) * (arg2[1]));
  x81 = ((fiat_p521_uint128)(arg1[0]) * (arg2[0]));
  x82 = (x81 + (x36 + (x35 + (x33 + (x30 + (x26 + (x21 + (x15 + x8))))))));
  x83 = (x82 >> 58);
  x84 = (uint64_t)(x82 & UINT64_C(0x3ffffffffffffff));
  x85 = (x73 + (x65 + (x58 + (x52 + (x47 + (x43 + (x40 + (x38 + x37))))))));
  x86 = (x74 + (x66 + (x59 + (x53 + (x48 + (x44 + (x41 + (x39 + x1))))))));
  x87 = (x75 + (x67 + (x60 + (x54 + (x49 + (x45 + (x42 + (x9 + x2))))))));
  x88 = (x76 + (x68 + (x61 + (x55 + (x50 + (x46 + (x16 + (x10 + x3))))))));
  x89 = (x77 + (x69 + (x62 + (x56 + (x51 + (x22 + (x17 + (x11 + x4))))))));
  x90 = (x78 + (x70 + (x63 + (x57 + (x27 + (x23 + (x18 + (x12 + x5))))))));
  x91 = (x79 + (x71 + (x64 + (x31 + (x28 + (x24 + (x19 + (x13 + x6))))))));
  x92 = (x80 + (x72 + (x34 + (x32 + (x29 + (x25 + (x20 + (x14 + x7))))))));
  x93 = (x83 + x92);
  x94 = (x93 >> 58);
  x95 = (uint64_t)(x93 & UINT64_C(0x3ffffffffffffff));
  x96 = (x94 + x91);
  x97 = (x96 >> 58);
  x98 = (uint64_t)(x96 & UINT64_C(0x3ffffffffffffff));
  x99 = (x97 + x90);
  x100 = (x99 >> 58);
  x101 = (uint64_t)(x99 & UINT64_C(0x3ffffffffffffff));
  x102 = (x100 + x89);
  x103 = (x102 >> 58);
  x104 = (uint64_t)(x102 & UINT64_C(0x3ffffffffffffff));
  x105 = (x103 + x88);
  x106 = (x105 >> 58);
  x107 = (uint64_t)(x105 & UINT64_C(0x3ffffffffffffff));
  x108 = (x106 + x87);
  x109 = (x108 >> 58);
  x110 = (uint64_t)(x108 & UINT64_C(0x3ffffffffffffff));
  x111 = (x109 + x86);
  x112 = (x111 >> 58);
  x113 = (uint64_t)(x111 & UINT64_C(0x3ffffffffffffff));
  x114 = (x112 + x85);
  x115 = (x114 >> 57);
  x116 = (uint64_t)(x114 & UINT64_C(0x1ffffffffffffff));
  x117 = (x84 + x115);
  x118 = (uint64_t)(x117 >> 58);
  x119 = (uint64_t)(x117 & UINT64_C(0x3ffffffffffffff));
  x120 = (x118 + x95);
  x121 = (fiat_p521_uint1)(x120 >> 58);
  x122 = (x120 & UINT64_C(0x3ffffffffffffff));
  x123 = (x121 + x98);
  out1[0] = x119;
  out1[1] = x122;
  out1[2] = x123;
  out1[3] = x101;
  out1[4] = x104;
  out1[5] = x107;
  out1[6] = x110;
  out1[7] = x113;
  out1[8] = x116;
}

/*
 * The function fiat_p521_carry_square squares a field element and reduces the
 * result. Postconditions: eval out1 mod m = (eval arg1 * eval arg1) mod m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xc00000000000000], [0x0 ~> 0xc00000000000000], [0x0 ~>
 * 0xc00000000000000], [0x0 ~> 0xc00000000000000], [0x0 ~> 0xc00000000000000],
 * [0x0 ~> 0xc00000000000000], [0x0 ~> 0xc00000000000000], [0x0 ~>
 * 0xc00000000000000], [0x0 ~> 0x600000000000000]] Output Bounds: out1: [[0x0 ~>
 * 0x400000000000000], [0x0 ~> 0x400000000000000], [0x0 ~> 0x400000000000000],
 * [0x0 ~> 0x400000000000000], [0x0 ~> 0x400000000000000], [0x0 ~>
 * 0x400000000000000], [0x0 ~> 0x400000000000000], [0x0 ~> 0x400000000000000],
 * [0x0 ~> 0x200000000000000]]
 */
void fiat_p521_carry_square(uint64_t out1[9], const uint64_t arg1[9]) {
  uint64_t x1;
  uint64_t x2;
  uint64_t x3;
  uint64_t x4;
  uint64_t x5;
  uint64_t x6;
  uint64_t x7;
  uint64_t x8;
  uint64_t x9;
  uint64_t x10;
  uint64_t x11;
  uint64_t x12;
  uint64_t x13;
  uint64_t x14;
  uint64_t x15;
  uint64_t x16;
  fiat_p521_uint128 x17;
  fiat_p521_uint128 x18;
  fiat_p521_uint128 x19;
  fiat_p521_uint128 x20;
  fiat_p521_uint128 x21;
  fiat_p521_uint128 x22;
  fiat_p521_uint128 x23;
  fiat_p521_uint128 x24;
  fiat_p521_uint128 x25;
  fiat_p521_uint128 x26;
  fiat_p521_uint128 x27;
  fiat_p521_uint128 x28;
  fiat_p521_uint128 x29;
  fiat_p521_uint128 x30;
  fiat_p521_uint128 x31;
  fiat_p521_uint128 x32;
  fiat_p521_uint128 x33;
  fiat_p521_uint128 x34;
  fiat_p521_uint128 x35;
  fiat_p521_uint128 x36;
  fiat_p521_uint128 x37;
  fiat_p521_uint128 x38;
  fiat_p521_uint128 x39;
  fiat_p521_uint128 x40;
  fiat_p521_uint128 x41;
  fiat_p521_uint128 x42;
  fiat_p521_uint128 x43;
  fiat_p521_uint128 x44;
  fiat_p521_uint128 x45;
  fiat_p521_uint128 x46;
  fiat_p521_uint128 x47;
  fiat_p521_uint128 x48;
  fiat_p521_uint128 x49;
  fiat_p521_uint128 x50;
  fiat_p521_uint128 x51;
  fiat_p521_uint128 x52;
  fiat_p521_uint128 x53;
  fiat_p521_uint128 x54;
  fiat_p521_uint128 x55;
  fiat_p521_uint128 x56;
  fiat_p521_uint128 x57;
  fiat_p521_uint128 x58;
  fiat_p521_uint128 x59;
  fiat_p521_uint128 x60;
  fiat_p521_uint128 x61;
  fiat_p521_uint128 x62;
  fiat_p521_uint128 x63;
  uint64_t x64;
  fiat_p521_uint128 x65;
  fiat_p521_uint128 x66;
  fiat_p521_uint128 x67;
  fiat_p521_uint128 x68;
  fiat_p521_uint128 x69;
  fiat_p521_uint128 x70;
  fiat_p521_uint128 x71;
  fiat_p521_uint128 x72;
  fiat_p521_uint128 x73;
  fiat_p521_uint128 x74;
  uint64_t x75;
  fiat_p521_uint128 x76;
  fiat_p521_uint128 x77;
  uint64_t x78;
  fiat_p521_uint128 x79;
  fiat_p521_uint128 x80;
  uint64_t x81;
  fiat_p521_uint128 x82;
  fiat_p521_uint128 x83;
  uint64_t x84;
  fiat_p521_uint128 x85;
  fiat_p521_uint128 x86;
  uint64_t x87;
  fiat_p521_uint128 x88;
  fiat_p521_uint128 x89;
  uint64_t x90;
  fiat_p521_uint128 x91;
  fiat_p521_uint128 x92;
  uint64_t x93;
  fiat_p521_uint128 x94;
  fiat_p521_uint128 x95;
  uint64_t x96;
  fiat_p521_uint128 x97;
  uint64_t x98;
  uint64_t x99;
  uint64_t x100;
  fiat_p521_uint1 x101;
  uint64_t x102;
  uint64_t x103;
  x1 = (arg1[8]);
  x2 = (x1 * 0x2);
  x3 = ((arg1[8]) * 0x2);
  x4 = (arg1[7]);
  x5 = (x4 * 0x2);
  x6 = ((arg1[7]) * 0x2);
  x7 = (arg1[6]);
  x8 = (x7 * 0x2);
  x9 = ((arg1[6]) * 0x2);
  x10 = (arg1[5]);
  x11 = (x10 * 0x2);
  x12 = ((arg1[5]) * 0x2);
  x13 = ((arg1[4]) * 0x2);
  x14 = ((arg1[3]) * 0x2);
  x15 = ((arg1[2]) * 0x2);
  x16 = ((arg1[1]) * 0x2);
  x17 = ((fiat_p521_uint128)(arg1[8]) * (x1 * 0x2));
  x18 = ((fiat_p521_uint128)(arg1[7]) * (x2 * 0x2));
  x19 = ((fiat_p521_uint128)(arg1[7]) * (x4 * 0x2));
  x20 = ((fiat_p521_uint128)(arg1[6]) * (x2 * 0x2));
  x21 = ((fiat_p521_uint128)(arg1[6]) * (x5 * 0x2));
  x22 = ((fiat_p521_uint128)(arg1[6]) * (x7 * 0x2));
  x23 = ((fiat_p521_uint128)(arg1[5]) * (x2 * 0x2));
  x24 = ((fiat_p521_uint128)(arg1[5]) * (x5 * 0x2));
  x25 = ((fiat_p521_uint128)(arg1[5]) * (x8 * 0x2));
  x26 = ((fiat_p521_uint128)(arg1[5]) * (x10 * 0x2));
  x27 = ((fiat_p521_uint128)(arg1[4]) * (x2 * 0x2));
  x28 = ((fiat_p521_uint128)(arg1[4]) * (x5 * 0x2));
  x29 = ((fiat_p521_uint128)(arg1[4]) * (x8 * 0x2));
  x30 = ((fiat_p521_uint128)(arg1[4]) * (x11 * 0x2));
  x31 = ((fiat_p521_uint128)(arg1[4]) * (arg1[4]));
  x32 = ((fiat_p521_uint128)(arg1[3]) * (x2 * 0x2));
  x33 = ((fiat_p521_uint128)(arg1[3]) * (x5 * 0x2));
  x34 = ((fiat_p521_uint128)(arg1[3]) * (x8 * 0x2));
  x35 = ((fiat_p521_uint128)(arg1[3]) * x12);
  x36 = ((fiat_p521_uint128)(arg1[3]) * x13);
  x37 = ((fiat_p521_uint128)(arg1[3]) * (arg1[3]));
  x38 = ((fiat_p521_uint128)(arg1[2]) * (x2 * 0x2));
  x39 = ((fiat_p521_uint128)(arg1[2]) * (x5 * 0x2));
  x40 = ((fiat_p521_uint128)(arg1[2]) * x9);
  x41 = ((fiat_p521_uint128)(arg1[2]) * x12);
  x42 = ((fiat_p521_uint128)(arg1[2]) * x13);
  x43 = ((fiat_p521_uint128)(arg1[2]) * x14);
  x44 = ((fiat_p521_uint128)(arg1[2]) * (arg1[2]));
  x45 = ((fiat_p521_uint128)(arg1[1]) * (x2 * 0x2));
  x46 = ((fiat_p521_uint128)(arg1[1]) * x6);
  x47 = ((fiat_p521_uint128)(arg1[1]) * x9);
  x48 = ((fiat_p521_uint128)(arg1[1]) * x12);
  x49 = ((fiat_p521_uint128)(arg1[1]) * x13);
  x50 = ((fiat_p521_uint128)(arg1[1]) * x14);
  x51 = ((fiat_p521_uint128)(arg1[1]) * x15);
  x52 = ((fiat_p521_uint128)(arg1[1]) * (arg1[1]));
  x53 = ((fiat_p521_uint128)(arg1[0]) * x3);
  x54 = ((fiat_p521_uint128)(arg1[0]) * x6);
  x55 = ((fiat_p521_uint128)(arg1[0]) * x9);
  x56 = ((fiat_p521_uint128)(arg1[0]) * x12);
  x57 = ((fiat_p521_uint128)(arg1[0]) * x13);
  x58 = ((fiat_p521_uint128)(arg1[0]) * x14);
  x59 = ((fiat_p521_uint128)(arg1[0]) * x15);
  x60 = ((fiat_p521_uint128)(arg1[0]) * x16);
  x61 = ((fiat_p521_uint128)(arg1[0]) * (arg1[0]));
  x62 = (x61 + (x45 + (x39 + (x34 + x30))));
  x63 = (x62 >> 58);
  x64 = (uint64_t)(x62 & UINT64_C(0x3ffffffffffffff));
  x65 = (x53 + (x46 + (x40 + (x35 + x31))));
  x66 = (x54 + (x47 + (x41 + (x36 + x17))));
  x67 = (x55 + (x48 + (x42 + (x37 + x18))));
  x68 = (x56 + (x49 + (x43 + (x20 + x19))));
  x69 = (x57 + (x50 + (x44 + (x23 + x21))));
  x70 = (x58 + (x51 + (x27 + (x24 + x22))));
  x71 = (x59 + (x52 + (x32 + (x28 + x25))));
  x72 = (x60 + (x38 + (x33 + (x29 + x26))));
  x73 = (x63 + x72);
  x74 = (x73 >> 58);
  x75 = (uint64_t)(x73 & UINT64_C(0x3ffffffffffffff));
  x76 = (x74 + x71);
  x77 = (x76 >> 58);
  x78 = (uint64_t)(x76 & UINT64_C(0x3ffffffffffffff));
  x79 = (x77 + x70);
  x80 = (x79 >> 58);
  x81 = (uint64_t)(x79 & UINT64_C(0x3ffffffffffffff));
  x82 = (x80 + x69);
  x83 = (x82 >> 58);
  x84 = (uint64_t)(x82 & UINT64_C(0x3ffffffffffffff));
  x85 = (x83 + x68);
  x86 = (x85 >> 58);
  x87 = (uint64_t)(x85 & UINT64_C(0x3ffffffffffffff));
  x88 = (x86 + x67);
  x89 = (x88 >> 58);
  x90 = (uint64_t)(x88 & UINT64_C(0x3ffffffffffffff));
  x91 = (x89 + x66);
  x92 = (x91 >> 58);
  x93 = (uint64_t)(x91 & UINT64_C(0x3ffffffffffffff));
  x94 = (x92 + x65);
  x95 = (x94 >> 57);
  x96 = (uint64_t)(x94 & UINT64_C(0x1ffffffffffffff));
  x97 = (x64 + x95);
  x98 = (uint64_t)(x97 >> 58);
  x99 = (uint64_t)(x97 & UINT64_C(0x3ffffffffffffff));
  x100 = (x98 + x75);
  x101 = (fiat_p521_uint1)(x100 >> 58);
  x102 = (x100 & UINT64_C(0x3ffffffffffffff));
  x103 = (x101 + x78);
  out1[0] = x99;
  out1[1] = x102;
  out1[2] = x103;
  out1[3] = x81;
  out1[4] = x84;
  out1[5] = x87;
  out1[6] = x90;
  out1[7] = x93;
  out1[8] = x96;
}

/* curve description: poly1305 */
/* machine_wordsize = 64 (from "64") */
/* requested operations: carry_mul, carry_square */
/* n = 3 (from "3") */
/* s-c = 2^130 - [(1, 5)] (from "2^130 - 5") */
/* tight_bounds_multiplier = 1 (from "") */
/*  */
/* Computed values: */
/* carry_chain = [0, 1, 2, 0, 1] */
/* eval z = z[0] + (z[1] << 44) + (z[2] << 87) */
/* bytes_eval z = z[0] + (z[1] << 8) + (z[2] << 16) + (z[3] << 24) + (z[4] <<
 * 32) + (z[5] << 40) + (z[6] << 48) + (z[7] << 56) + (z[8] << 64) + (z[9] <<
 * 72) + (z[10] << 80) + (z[11] << 88) + (z[12] << 96) + (z[13] << 104) + (z[14]
 * << 112) + (z[15] << 120) + (z[16] << 128) */
/* balance = [0x1ffffffffff6, 0xffffffffffe, 0xffffffffffe] */

#include <stdint.h>
typedef unsigned char fiat_poly1305_uint1;
typedef signed char fiat_poly1305_int1;
typedef signed __int128 fiat_poly1305_int128;
typedef unsigned __int128 fiat_poly1305_uint128;

#if (-1 & 3) != 3
#error "This code only works on a two's complement system"
#endif

/*
 * The function fiat_poly1305_carry_mul multiplies two field elements and
 * reduces the result. Postconditions: eval out1 mod m = (eval arg1 * eval arg2)
 * mod m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0x300000000000], [0x0 ~> 0x180000000000], [0x0 ~>
 * 0x180000000000]] arg2: [[0x0 ~> 0x300000000000], [0x0 ~> 0x180000000000],
 * [0x0 ~> 0x180000000000]] Output Bounds: out1: [[0x0 ~> 0x100000000000], [0x0
 * ~> 0x80000000000], [0x0 ~> 0x80000000000]]
 */
void fiat_poly1305_carry_mul(uint64_t out1[3], const uint64_t arg1[3],
                             const uint64_t arg2[3]) {
  fiat_poly1305_uint128 x1;
  fiat_poly1305_uint128 x2;
  fiat_poly1305_uint128 x3;
  fiat_poly1305_uint128 x4;
  fiat_poly1305_uint128 x5;
  fiat_poly1305_uint128 x6;
  fiat_poly1305_uint128 x7;
  fiat_poly1305_uint128 x8;
  fiat_poly1305_uint128 x9;
  fiat_poly1305_uint128 x10;
  uint64_t x11;
  uint64_t x12;
  fiat_poly1305_uint128 x13;
  fiat_poly1305_uint128 x14;
  fiat_poly1305_uint128 x15;
  uint64_t x16;
  uint64_t x17;
  fiat_poly1305_uint128 x18;
  uint64_t x19;
  uint64_t x20;
  uint64_t x21;
  uint64_t x22;
  uint64_t x23;
  uint64_t x24;
  uint64_t x25;
  fiat_poly1305_uint1 x26;
  uint64_t x27;
  uint64_t x28;
  x1 = ((fiat_poly1305_uint128)(arg1[2]) * ((arg2[2]) * 0x5));
  x2 = ((fiat_poly1305_uint128)(arg1[2]) * ((arg2[1]) * 0xa));
  x3 = ((fiat_poly1305_uint128)(arg1[1]) * ((arg2[2]) * 0xa));
  x4 = ((fiat_poly1305_uint128)(arg1[2]) * (arg2[0]));
  x5 = ((fiat_poly1305_uint128)(arg1[1]) * ((arg2[1]) * 0x2));
  x6 = ((fiat_poly1305_uint128)(arg1[1]) * (arg2[0]));
  x7 = ((fiat_poly1305_uint128)(arg1[0]) * (arg2[2]));
  x8 = ((fiat_poly1305_uint128)(arg1[0]) * (arg2[1]));
  x9 = ((fiat_poly1305_uint128)(arg1[0]) * (arg2[0]));
  x10 = (x9 + (x3 + x2));
  x11 = (uint64_t)(x10 >> 44);
  x12 = (uint64_t)(x10 & UINT64_C(0xfffffffffff));
  x13 = (x7 + (x5 + x4));
  x14 = (x8 + (x6 + x1));
  x15 = (x11 + x14);
  x16 = (uint64_t)(x15 >> 43);
  x17 = (uint64_t)(x15 & UINT64_C(0x7ffffffffff));
  x18 = (x16 + x13);
  x19 = (uint64_t)(x18 >> 43);
  x20 = (uint64_t)(x18 & UINT64_C(0x7ffffffffff));
  x21 = (x19 * 0x5);
  x22 = (x12 + x21);
  x23 = (x22 >> 44);
  x24 = (x22 & UINT64_C(0xfffffffffff));
  x25 = (x23 + x17);
  x26 = (fiat_poly1305_uint1)(x25 >> 43);
  x27 = (x25 & UINT64_C(0x7ffffffffff));
  x28 = (x26 + x20);
  out1[0] = x24;
  out1[1] = x27;
  out1[2] = x28;
}

/*
 * The function fiat_poly1305_carry_square squares a field element and reduces
 * the result. Postconditions: eval out1 mod m = (eval arg1 * eval arg1) mod m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0x300000000000], [0x0 ~> 0x180000000000], [0x0 ~>
 * 0x180000000000]] Output Bounds: out1: [[0x0 ~> 0x100000000000], [0x0 ~>
 * 0x80000000000], [0x0 ~> 0x80000000000]]
 */
void fiat_poly1305_carry_square(uint64_t out1[3], const uint64_t arg1[3]) {
  uint64_t x1;
  uint64_t x2;
  uint64_t x3;
  uint64_t x4;
  fiat_poly1305_uint128 x5;
  fiat_poly1305_uint128 x6;
  fiat_poly1305_uint128 x7;
  fiat_poly1305_uint128 x8;
  fiat_poly1305_uint128 x9;
  fiat_poly1305_uint128 x10;
  fiat_poly1305_uint128 x11;
  uint64_t x12;
  uint64_t x13;
  fiat_poly1305_uint128 x14;
  fiat_poly1305_uint128 x15;
  fiat_poly1305_uint128 x16;
  uint64_t x17;
  uint64_t x18;
  fiat_poly1305_uint128 x19;
  uint64_t x20;
  uint64_t x21;
  uint64_t x22;
  uint64_t x23;
  uint64_t x24;
  uint64_t x25;
  uint64_t x26;
  fiat_poly1305_uint1 x27;
  uint64_t x28;
  uint64_t x29;
  x1 = ((arg1[2]) * 0x5);
  x2 = (x1 * 0x2);
  x3 = ((arg1[2]) * 0x2);
  x4 = ((arg1[1]) * 0x2);
  x5 = ((fiat_poly1305_uint128)(arg1[2]) * x1);
  x6 = ((fiat_poly1305_uint128)(arg1[1]) * (x2 * 0x2));
  x7 = ((fiat_poly1305_uint128)(arg1[1]) * ((arg1[1]) * 0x2));
  x8 = ((fiat_poly1305_uint128)(arg1[0]) * x3);
  x9 = ((fiat_poly1305_uint128)(arg1[0]) * x4);
  x10 = ((fiat_poly1305_uint128)(arg1[0]) * (arg1[0]));
  x11 = (x10 + x6);
  x12 = (uint64_t)(x11 >> 44);
  x13 = (uint64_t)(x11 & UINT64_C(0xfffffffffff));
  x14 = (x8 + x7);
  x15 = (x9 + x5);
  x16 = (x12 + x15);
  x17 = (uint64_t)(x16 >> 43);
  x18 = (uint64_t)(x16 & UINT64_C(0x7ffffffffff));
  x19 = (x17 + x14);
  x20 = (uint64_t)(x19 >> 43);
  x21 = (uint64_t)(x19 & UINT64_C(0x7ffffffffff));
  x22 = (x20 * 0x5);
  x23 = (x13 + x22);
  x24 = (x23 >> 44);
  x25 = (x23 & UINT64_C(0xfffffffffff));
  x26 = (x24 + x18);
  x27 = (fiat_poly1305_uint1)(x26 >> 43);
  x28 = (x26 & UINT64_C(0x7ffffffffff));
  x29 = (x27 + x21);
  out1[0] = x25;
  out1[1] = x28;
  out1[2] = x29;
}

/* curve description: secp256k1 */
/* machine_wordsize = 64 (from "64") */
/* requested operations: mul, square */
/* m = 0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f (from
 * "2^256 - 2^32 - 977") */
/*                                                                    */
/* NOTE: In addition to the bounds specified above each function, all */
/*   functions synthesized for this Montgomery arithmetic require the */
/*   input to be strictly less than the prime modulus (m), and also   */
/*   require the input to be in the unique saturated representation.  */
/*   All functions also ensure that these two properties are true of  */
/*   return values.                                                   */
/*  */
/* Computed values: */
/* eval z = z[0] + (z[1] << 64) + (z[2] << 128) + (z[3] << 192) */
/* bytes_eval z = z[0] + (z[1] << 8) + (z[2] << 16) + (z[3] << 24) + (z[4] <<
 * 32) + (z[5] << 40) + (z[6] << 48) + (z[7] << 56) + (z[8] << 64) + (z[9] <<
 * 72) + (z[10] << 80) + (z[11] << 88) + (z[12] << 96) + (z[13] << 104) + (z[14]
 * << 112) + (z[15] << 120) + (z[16] << 128) + (z[17] << 136) + (z[18] << 144) +
 * (z[19] << 152) + (z[20] << 160) + (z[21] << 168) + (z[22] << 176) + (z[23] <<
 * 184) + (z[24] << 192) + (z[25] << 200) + (z[26] << 208) + (z[27] << 216) +
 * (z[28] << 224) + (z[29] << 232) + (z[30] << 240) + (z[31] << 248) */

#include <stdint.h>
typedef unsigned char fiat_secp256k1_uint1;
typedef signed char fiat_secp256k1_int1;
typedef signed __int128 fiat_secp256k1_int128;
typedef unsigned __int128 fiat_secp256k1_uint128;

#if (-1 & 3) != 3
#error "This code only works on a two's complement system"
#endif

/*
 * The function fiat_secp256k1_addcarryx_u64 is an addition with carry.
 * Postconditions:
 *   out1 = (arg1 + arg2 + arg3) mod 2^64
 *   out2 = ⌊(arg1 + arg2 + arg3) / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0x1]
 */
void fiat_secp256k1_addcarryx_u64(uint64_t *out1, fiat_secp256k1_uint1 *out2,
                                  fiat_secp256k1_uint1 arg1, uint64_t arg2,
                                  uint64_t arg3) {
  fiat_secp256k1_uint128 x1;
  uint64_t x2;
  fiat_secp256k1_uint1 x3;
  x1 = ((arg1 + (fiat_secp256k1_uint128)arg2) + arg3);
  x2 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  x3 = (fiat_secp256k1_uint1)(x1 >> 64);
  *out1 = x2;
  *out2 = x3;
}

/*
 * The function fiat_secp256k1_subborrowx_u64 is a subtraction with borrow.
 * Postconditions:
 *   out1 = (-arg1 + arg2 + -arg3) mod 2^64
 *   out2 = -⌊(-arg1 + arg2 + -arg3) / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0x1]
 */
void fiat_secp256k1_subborrowx_u64(uint64_t *out1, fiat_secp256k1_uint1 *out2,
                                   fiat_secp256k1_uint1 arg1, uint64_t arg2,
                                   uint64_t arg3) {
  fiat_secp256k1_int128 x1;
  fiat_secp256k1_int1 x2;
  uint64_t x3;
  x1 = ((arg2 - (fiat_secp256k1_int128)arg1) - arg3);
  x2 = (fiat_secp256k1_int1)(x1 >> 64);
  x3 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  *out1 = x3;
  *out2 = (fiat_secp256k1_uint1)(0x0 - x2);
}

/*
 * The function fiat_secp256k1_mulx_u64 is a multiplication, returning the full
 * double-width result. Postconditions: out1 = (arg1 * arg2) mod 2^64 out2 =
 * ⌊arg1 * arg2 / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0xffffffffffffffff]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0xffffffffffffffff]
 */
void fiat_secp256k1_mulx_u64(uint64_t *out1, uint64_t *out2, uint64_t arg1,
                             uint64_t arg2) {
  fiat_secp256k1_uint128 x1;
  uint64_t x2;
  uint64_t x3;
  x1 = ((fiat_secp256k1_uint128)arg1 * arg2);
  x2 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  x3 = (uint64_t)(x1 >> 64);
  *out1 = x2;
  *out2 = x3;
}

/*
 * The function fiat_secp256k1_cmovznz_u64 is a single-word conditional move.
 * Postconditions:
 *   out1 = (if arg1 = 0 then arg2 else arg3)
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 */
void fiat_secp256k1_cmovznz_u64(uint64_t *out1, fiat_secp256k1_uint1 arg1,
                                uint64_t arg2, uint64_t arg3) {
  fiat_secp256k1_uint1 x1;
  uint64_t x2;
  uint64_t x3;
  x1 = (!(!arg1));
  x2 = ((fiat_secp256k1_int1)(0x0 - x1) & UINT64_C(0xffffffffffffffff));
  x3 = ((x2 & arg3) | ((~x2) & arg2));
  *out1 = x3;
}

/*
 * The function fiat_secp256k1_mul multiplies two field elements in the
 * Montgomery domain. Preconditions: 0 ≤ eval arg1 < m 0 ≤ eval arg2 < m
 * Postconditions:
 *   eval (from_montgomery out1) mod m = (eval (from_montgomery arg1) * eval
 * (from_montgomery arg2)) mod m 0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]] arg2: [[0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]] Output Bounds: out1: [[0x0
 * ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
void fiat_secp256k1_mul(uint64_t out1[4], const uint64_t arg1[4],
                        const uint64_t arg2[4]) {
  uint64_t x1;
  uint64_t x2;
  uint64_t x3;
  uint64_t x4;
  uint64_t x5;
  uint64_t x6;
  uint64_t x7;
  uint64_t x8;
  uint64_t x9;
  uint64_t x10;
  uint64_t x11;
  uint64_t x12;
  uint64_t x13;
  fiat_secp256k1_uint1 x14;
  uint64_t x15;
  fiat_secp256k1_uint1 x16;
  uint64_t x17;
  fiat_secp256k1_uint1 x18;
  uint64_t x19;
  uint64_t x20;
  uint64_t x21;
  uint64_t x22;
  uint64_t x23;
  uint64_t x24;
  uint64_t x25;
  uint64_t x26;
  uint64_t x27;
  uint64_t x28;
  uint64_t x29;
  uint64_t x30;
  fiat_secp256k1_uint1 x31;
  uint64_t x32;
  fiat_secp256k1_uint1 x33;
  uint64_t x34;
  fiat_secp256k1_uint1 x35;
  uint64_t x36;
  uint64_t x37;
  fiat_secp256k1_uint1 x38;
  uint64_t x39;
  fiat_secp256k1_uint1 x40;
  uint64_t x41;
  fiat_secp256k1_uint1 x42;
  uint64_t x43;
  fiat_secp256k1_uint1 x44;
  uint64_t x45;
  fiat_secp256k1_uint1 x46;
  uint64_t x47;
  uint64_t x48;
  uint64_t x49;
  uint64_t x50;
  uint64_t x51;
  uint64_t x52;
  uint64_t x53;
  uint64_t x54;
  uint64_t x55;
  fiat_secp256k1_uint1 x56;
  uint64_t x57;
  fiat_secp256k1_uint1 x58;
  uint64_t x59;
  fiat_secp256k1_uint1 x60;
  uint64_t x61;
  uint64_t x62;
  fiat_secp256k1_uint1 x63;
  uint64_t x64;
  fiat_secp256k1_uint1 x65;
  uint64_t x66;
  fiat_secp256k1_uint1 x67;
  uint64_t x68;
  fiat_secp256k1_uint1 x69;
  uint64_t x70;
  fiat_secp256k1_uint1 x71;
  uint64_t x72;
  uint64_t x73;
  uint64_t x74;
  uint64_t x75;
  uint64_t x76;
  uint64_t x77;
  uint64_t x78;
  uint64_t x79;
  uint64_t x80;
  uint64_t x81;
  uint64_t x82;
  fiat_secp256k1_uint1 x83;
  uint64_t x84;
  fiat_secp256k1_uint1 x85;
  uint64_t x86;
  fiat_secp256k1_uint1 x87;
  uint64_t x88;
  uint64_t x89;
  fiat_secp256k1_uint1 x90;
  uint64_t x91;
  fiat_secp256k1_uint1 x92;
  uint64_t x93;
  fiat_secp256k1_uint1 x94;
  uint64_t x95;
  fiat_secp256k1_uint1 x96;
  uint64_t x97;
  fiat_secp256k1_uint1 x98;
  uint64_t x99;
  uint64_t x100;
  uint64_t x101;
  uint64_t x102;
  uint64_t x103;
  uint64_t x104;
  uint64_t x105;
  uint64_t x106;
  uint64_t x107;
  uint64_t x108;
  fiat_secp256k1_uint1 x109;
  uint64_t x110;
  fiat_secp256k1_uint1 x111;
  uint64_t x112;
  fiat_secp256k1_uint1 x113;
  uint64_t x114;
  uint64_t x115;
  fiat_secp256k1_uint1 x116;
  uint64_t x117;
  fiat_secp256k1_uint1 x118;
  uint64_t x119;
  fiat_secp256k1_uint1 x120;
  uint64_t x121;
  fiat_secp256k1_uint1 x122;
  uint64_t x123;
  fiat_secp256k1_uint1 x124;
  uint64_t x125;
  uint64_t x126;
  uint64_t x127;
  uint64_t x128;
  uint64_t x129;
  uint64_t x130;
  uint64_t x131;
  uint64_t x132;
  uint64_t x133;
  uint64_t x134;
  uint64_t x135;
  fiat_secp256k1_uint1 x136;
  uint64_t x137;
  fiat_secp256k1_uint1 x138;
  uint64_t x139;
  fiat_secp256k1_uint1 x140;
  uint64_t x141;
  uint64_t x142;
  fiat_secp256k1_uint1 x143;
  uint64_t x144;
  fiat_secp256k1_uint1 x145;
  uint64_t x146;
  fiat_secp256k1_uint1 x147;
  uint64_t x148;
  fiat_secp256k1_uint1 x149;
  uint64_t x150;
  fiat_secp256k1_uint1 x151;
  uint64_t x152;
  uint64_t x153;
  uint64_t x154;
  uint64_t x155;
  uint64_t x156;
  uint64_t x157;
  uint64_t x158;
  uint64_t x159;
  uint64_t x160;
  uint64_t x161;
  fiat_secp256k1_uint1 x162;
  uint64_t x163;
  fiat_secp256k1_uint1 x164;
  uint64_t x165;
  fiat_secp256k1_uint1 x166;
  uint64_t x167;
  uint64_t x168;
  fiat_secp256k1_uint1 x169;
  uint64_t x170;
  fiat_secp256k1_uint1 x171;
  uint64_t x172;
  fiat_secp256k1_uint1 x173;
  uint64_t x174;
  fiat_secp256k1_uint1 x175;
  uint64_t x176;
  fiat_secp256k1_uint1 x177;
  uint64_t x178;
  uint64_t x179;
  uint64_t x180;
  uint64_t x181;
  uint64_t x182;
  uint64_t x183;
  uint64_t x184;
  uint64_t x185;
  uint64_t x186;
  uint64_t x187;
  uint64_t x188;
  fiat_secp256k1_uint1 x189;
  uint64_t x190;
  fiat_secp256k1_uint1 x191;
  uint64_t x192;
  fiat_secp256k1_uint1 x193;
  uint64_t x194;
  uint64_t x195;
  fiat_secp256k1_uint1 x196;
  uint64_t x197;
  fiat_secp256k1_uint1 x198;
  uint64_t x199;
  fiat_secp256k1_uint1 x200;
  uint64_t x201;
  fiat_secp256k1_uint1 x202;
  uint64_t x203;
  fiat_secp256k1_uint1 x204;
  uint64_t x205;
  uint64_t x206;
  fiat_secp256k1_uint1 x207;
  uint64_t x208;
  fiat_secp256k1_uint1 x209;
  uint64_t x210;
  fiat_secp256k1_uint1 x211;
  uint64_t x212;
  fiat_secp256k1_uint1 x213;
  uint64_t x214;
  fiat_secp256k1_uint1 x215;
  uint64_t x216;
  uint64_t x217;
  uint64_t x218;
  uint64_t x219;
  x1 = (arg1[1]);
  x2 = (arg1[2]);
  x3 = (arg1[3]);
  x4 = (arg1[0]);
  fiat_secp256k1_mulx_u64(&x5, &x6, x4, (arg2[3]));
  fiat_secp256k1_mulx_u64(&x7, &x8, x4, (arg2[2]));
  fiat_secp256k1_mulx_u64(&x9, &x10, x4, (arg2[1]));
  fiat_secp256k1_mulx_u64(&x11, &x12, x4, (arg2[0]));
  fiat_secp256k1_addcarryx_u64(&x13, &x14, 0x0, x12, x9);
  fiat_secp256k1_addcarryx_u64(&x15, &x16, x14, x10, x7);
  fiat_secp256k1_addcarryx_u64(&x17, &x18, x16, x8, x5);
  x19 = (x18 + x6);
  fiat_secp256k1_mulx_u64(&x20, &x21, x11, UINT64_C(0xd838091dd2253531));
  fiat_secp256k1_mulx_u64(&x22, &x23, x20, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x24, &x25, x20, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x26, &x27, x20, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x28, &x29, x20, UINT64_C(0xfffffffefffffc2f));
  fiat_secp256k1_addcarryx_u64(&x30, &x31, 0x0, x29, x26);
  fiat_secp256k1_addcarryx_u64(&x32, &x33, x31, x27, x24);
  fiat_secp256k1_addcarryx_u64(&x34, &x35, x33, x25, x22);
  x36 = (x35 + x23);
  fiat_secp256k1_addcarryx_u64(&x37, &x38, 0x0, x11, x28);
  fiat_secp256k1_addcarryx_u64(&x39, &x40, x38, x13, x30);
  fiat_secp256k1_addcarryx_u64(&x41, &x42, x40, x15, x32);
  fiat_secp256k1_addcarryx_u64(&x43, &x44, x42, x17, x34);
  fiat_secp256k1_addcarryx_u64(&x45, &x46, x44, x19, x36);
  fiat_secp256k1_mulx_u64(&x47, &x48, x1, (arg2[3]));
  fiat_secp256k1_mulx_u64(&x49, &x50, x1, (arg2[2]));
  fiat_secp256k1_mulx_u64(&x51, &x52, x1, (arg2[1]));
  fiat_secp256k1_mulx_u64(&x53, &x54, x1, (arg2[0]));
  fiat_secp256k1_addcarryx_u64(&x55, &x56, 0x0, x54, x51);
  fiat_secp256k1_addcarryx_u64(&x57, &x58, x56, x52, x49);
  fiat_secp256k1_addcarryx_u64(&x59, &x60, x58, x50, x47);
  x61 = (x60 + x48);
  fiat_secp256k1_addcarryx_u64(&x62, &x63, 0x0, x39, x53);
  fiat_secp256k1_addcarryx_u64(&x64, &x65, x63, x41, x55);
  fiat_secp256k1_addcarryx_u64(&x66, &x67, x65, x43, x57);
  fiat_secp256k1_addcarryx_u64(&x68, &x69, x67, x45, x59);
  fiat_secp256k1_addcarryx_u64(&x70, &x71, x69, x46, x61);
  fiat_secp256k1_mulx_u64(&x72, &x73, x62, UINT64_C(0xd838091dd2253531));
  fiat_secp256k1_mulx_u64(&x74, &x75, x72, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x76, &x77, x72, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x78, &x79, x72, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x80, &x81, x72, UINT64_C(0xfffffffefffffc2f));
  fiat_secp256k1_addcarryx_u64(&x82, &x83, 0x0, x81, x78);
  fiat_secp256k1_addcarryx_u64(&x84, &x85, x83, x79, x76);
  fiat_secp256k1_addcarryx_u64(&x86, &x87, x85, x77, x74);
  x88 = (x87 + x75);
  fiat_secp256k1_addcarryx_u64(&x89, &x90, 0x0, x62, x80);
  fiat_secp256k1_addcarryx_u64(&x91, &x92, x90, x64, x82);
  fiat_secp256k1_addcarryx_u64(&x93, &x94, x92, x66, x84);
  fiat_secp256k1_addcarryx_u64(&x95, &x96, x94, x68, x86);
  fiat_secp256k1_addcarryx_u64(&x97, &x98, x96, x70, x88);
  x99 = ((uint64_t)x98 + x71);
  fiat_secp256k1_mulx_u64(&x100, &x101, x2, (arg2[3]));
  fiat_secp256k1_mulx_u64(&x102, &x103, x2, (arg2[2]));
  fiat_secp256k1_mulx_u64(&x104, &x105, x2, (arg2[1]));
  fiat_secp256k1_mulx_u64(&x106, &x107, x2, (arg2[0]));
  fiat_secp256k1_addcarryx_u64(&x108, &x109, 0x0, x107, x104);
  fiat_secp256k1_addcarryx_u64(&x110, &x111, x109, x105, x102);
  fiat_secp256k1_addcarryx_u64(&x112, &x113, x111, x103, x100);
  x114 = (x113 + x101);
  fiat_secp256k1_addcarryx_u64(&x115, &x116, 0x0, x91, x106);
  fiat_secp256k1_addcarryx_u64(&x117, &x118, x116, x93, x108);
  fiat_secp256k1_addcarryx_u64(&x119, &x120, x118, x95, x110);
  fiat_secp256k1_addcarryx_u64(&x121, &x122, x120, x97, x112);
  fiat_secp256k1_addcarryx_u64(&x123, &x124, x122, x99, x114);
  fiat_secp256k1_mulx_u64(&x125, &x126, x115, UINT64_C(0xd838091dd2253531));
  fiat_secp256k1_mulx_u64(&x127, &x128, x125, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x129, &x130, x125, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x131, &x132, x125, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x133, &x134, x125, UINT64_C(0xfffffffefffffc2f));
  fiat_secp256k1_addcarryx_u64(&x135, &x136, 0x0, x134, x131);
  fiat_secp256k1_addcarryx_u64(&x137, &x138, x136, x132, x129);
  fiat_secp256k1_addcarryx_u64(&x139, &x140, x138, x130, x127);
  x141 = (x140 + x128);
  fiat_secp256k1_addcarryx_u64(&x142, &x143, 0x0, x115, x133);
  fiat_secp256k1_addcarryx_u64(&x144, &x145, x143, x117, x135);
  fiat_secp256k1_addcarryx_u64(&x146, &x147, x145, x119, x137);
  fiat_secp256k1_addcarryx_u64(&x148, &x149, x147, x121, x139);
  fiat_secp256k1_addcarryx_u64(&x150, &x151, x149, x123, x141);
  x152 = ((uint64_t)x151 + x124);
  fiat_secp256k1_mulx_u64(&x153, &x154, x3, (arg2[3]));
  fiat_secp256k1_mulx_u64(&x155, &x156, x3, (arg2[2]));
  fiat_secp256k1_mulx_u64(&x157, &x158, x3, (arg2[1]));
  fiat_secp256k1_mulx_u64(&x159, &x160, x3, (arg2[0]));
  fiat_secp256k1_addcarryx_u64(&x161, &x162, 0x0, x160, x157);
  fiat_secp256k1_addcarryx_u64(&x163, &x164, x162, x158, x155);
  fiat_secp256k1_addcarryx_u64(&x165, &x166, x164, x156, x153);
  x167 = (x166 + x154);
  fiat_secp256k1_addcarryx_u64(&x168, &x169, 0x0, x144, x159);
  fiat_secp256k1_addcarryx_u64(&x170, &x171, x169, x146, x161);
  fiat_secp256k1_addcarryx_u64(&x172, &x173, x171, x148, x163);
  fiat_secp256k1_addcarryx_u64(&x174, &x175, x173, x150, x165);
  fiat_secp256k1_addcarryx_u64(&x176, &x177, x175, x152, x167);
  fiat_secp256k1_mulx_u64(&x178, &x179, x168, UINT64_C(0xd838091dd2253531));
  fiat_secp256k1_mulx_u64(&x180, &x181, x178, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x182, &x183, x178, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x184, &x185, x178, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x186, &x187, x178, UINT64_C(0xfffffffefffffc2f));
  fiat_secp256k1_addcarryx_u64(&x188, &x189, 0x0, x187, x184);
  fiat_secp256k1_addcarryx_u64(&x190, &x191, x189, x185, x182);
  fiat_secp256k1_addcarryx_u64(&x192, &x193, x191, x183, x180);
  x194 = (x193 + x181);
  fiat_secp256k1_addcarryx_u64(&x195, &x196, 0x0, x168, x186);
  fiat_secp256k1_addcarryx_u64(&x197, &x198, x196, x170, x188);
  fiat_secp256k1_addcarryx_u64(&x199, &x200, x198, x172, x190);
  fiat_secp256k1_addcarryx_u64(&x201, &x202, x200, x174, x192);
  fiat_secp256k1_addcarryx_u64(&x203, &x204, x202, x176, x194);
  x205 = ((uint64_t)x204 + x177);
  fiat_secp256k1_subborrowx_u64(&x206, &x207, 0x0, x197,
                                UINT64_C(0xfffffffefffffc2f));
  fiat_secp256k1_subborrowx_u64(&x208, &x209, x207, x199,
                                UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_subborrowx_u64(&x210, &x211, x209, x201,
                                UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_subborrowx_u64(&x212, &x213, x211, x203,
                                UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_subborrowx_u64(&x214, &x215, x213, x205, 0x0);
  fiat_secp256k1_cmovznz_u64(&x216, x215, x206, x197);
  fiat_secp256k1_cmovznz_u64(&x217, x215, x208, x199);
  fiat_secp256k1_cmovznz_u64(&x218, x215, x210, x201);
  fiat_secp256k1_cmovznz_u64(&x219, x215, x212, x203);
  out1[0] = x216;
  out1[1] = x217;
  out1[2] = x218;
  out1[3] = x219;
}

/*
 * The function fiat_secp256k1_square squares a field element in the Montgomery
 * domain. Preconditions: 0 ≤ eval arg1 < m Postconditions: eval
 * (from_montgomery out1) mod m = (eval (from_montgomery arg1) * eval
 * (from_montgomery arg1)) mod m 0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]] Output Bounds: out1: [[0x0
 * ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~>
 * 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
void fiat_secp256k1_square(uint64_t out1[4], const uint64_t arg1[4]) {
  uint64_t x1;
  uint64_t x2;
  uint64_t x3;
  uint64_t x4;
  uint64_t x5;
  uint64_t x6;
  uint64_t x7;
  uint64_t x8;
  uint64_t x9;
  uint64_t x10;
  uint64_t x11;
  uint64_t x12;
  uint64_t x13;
  fiat_secp256k1_uint1 x14;
  uint64_t x15;
  fiat_secp256k1_uint1 x16;
  uint64_t x17;
  fiat_secp256k1_uint1 x18;
  uint64_t x19;
  uint64_t x20;
  uint64_t x21;
  uint64_t x22;
  uint64_t x23;
  uint64_t x24;
  uint64_t x25;
  uint64_t x26;
  uint64_t x27;
  uint64_t x28;
  uint64_t x29;
  uint64_t x30;
  fiat_secp256k1_uint1 x31;
  uint64_t x32;
  fiat_secp256k1_uint1 x33;
  uint64_t x34;
  fiat_secp256k1_uint1 x35;
  uint64_t x36;
  uint64_t x37;
  fiat_secp256k1_uint1 x38;
  uint64_t x39;
  fiat_secp256k1_uint1 x40;
  uint64_t x41;
  fiat_secp256k1_uint1 x42;
  uint64_t x43;
  fiat_secp256k1_uint1 x44;
  uint64_t x45;
  fiat_secp256k1_uint1 x46;
  uint64_t x47;
  uint64_t x48;
  uint64_t x49;
  uint64_t x50;
  uint64_t x51;
  uint64_t x52;
  uint64_t x53;
  uint64_t x54;
  uint64_t x55;
  fiat_secp256k1_uint1 x56;
  uint64_t x57;
  fiat_secp256k1_uint1 x58;
  uint64_t x59;
  fiat_secp256k1_uint1 x60;
  uint64_t x61;
  uint64_t x62;
  fiat_secp256k1_uint1 x63;
  uint64_t x64;
  fiat_secp256k1_uint1 x65;
  uint64_t x66;
  fiat_secp256k1_uint1 x67;
  uint64_t x68;
  fiat_secp256k1_uint1 x69;
  uint64_t x70;
  fiat_secp256k1_uint1 x71;
  uint64_t x72;
  uint64_t x73;
  uint64_t x74;
  uint64_t x75;
  uint64_t x76;
  uint64_t x77;
  uint64_t x78;
  uint64_t x79;
  uint64_t x80;
  uint64_t x81;
  uint64_t x82;
  fiat_secp256k1_uint1 x83;
  uint64_t x84;
  fiat_secp256k1_uint1 x85;
  uint64_t x86;
  fiat_secp256k1_uint1 x87;
  uint64_t x88;
  uint64_t x89;
  fiat_secp256k1_uint1 x90;
  uint64_t x91;
  fiat_secp256k1_uint1 x92;
  uint64_t x93;
  fiat_secp256k1_uint1 x94;
  uint64_t x95;
  fiat_secp256k1_uint1 x96;
  uint64_t x97;
  fiat_secp256k1_uint1 x98;
  uint64_t x99;
  uint64_t x100;
  uint64_t x101;
  uint64_t x102;
  uint64_t x103;
  uint64_t x104;
  uint64_t x105;
  uint64_t x106;
  uint64_t x107;
  uint64_t x108;
  fiat_secp256k1_uint1 x109;
  uint64_t x110;
  fiat_secp256k1_uint1 x111;
  uint64_t x112;
  fiat_secp256k1_uint1 x113;
  uint64_t x114;
  uint64_t x115;
  fiat_secp256k1_uint1 x116;
  uint64_t x117;
  fiat_secp256k1_uint1 x118;
  uint64_t x119;
  fiat_secp256k1_uint1 x120;
  uint64_t x121;
  fiat_secp256k1_uint1 x122;
  uint64_t x123;
  fiat_secp256k1_uint1 x124;
  uint64_t x125;
  uint64_t x126;
  uint64_t x127;
  uint64_t x128;
  uint64_t x129;
  uint64_t x130;
  uint64_t x131;
  uint64_t x132;
  uint64_t x133;
  uint64_t x134;
  uint64_t x135;
  fiat_secp256k1_uint1 x136;
  uint64_t x137;
  fiat_secp256k1_uint1 x138;
  uint64_t x139;
  fiat_secp256k1_uint1 x140;
  uint64_t x141;
  uint64_t x142;
  fiat_secp256k1_uint1 x143;
  uint64_t x144;
  fiat_secp256k1_uint1 x145;
  uint64_t x146;
  fiat_secp256k1_uint1 x147;
  uint64_t x148;
  fiat_secp256k1_uint1 x149;
  uint64_t x150;
  fiat_secp256k1_uint1 x151;
  uint64_t x152;
  uint64_t x153;
  uint64_t x154;
  uint64_t x155;
  uint64_t x156;
  uint64_t x157;
  uint64_t x158;
  uint64_t x159;
  uint64_t x160;
  uint64_t x161;
  fiat_secp256k1_uint1 x162;
  uint64_t x163;
  fiat_secp256k1_uint1 x164;
  uint64_t x165;
  fiat_secp256k1_uint1 x166;
  uint64_t x167;
  uint64_t x168;
  fiat_secp256k1_uint1 x169;
  uint64_t x170;
  fiat_secp256k1_uint1 x171;
  uint64_t x172;
  fiat_secp256k1_uint1 x173;
  uint64_t x174;
  fiat_secp256k1_uint1 x175;
  uint64_t x176;
  fiat_secp256k1_uint1 x177;
  uint64_t x178;
  uint64_t x179;
  uint64_t x180;
  uint64_t x181;
  uint64_t x182;
  uint64_t x183;
  uint64_t x184;
  uint64_t x185;
  uint64_t x186;
  uint64_t x187;
  uint64_t x188;
  fiat_secp256k1_uint1 x189;
  uint64_t x190;
  fiat_secp256k1_uint1 x191;
  uint64_t x192;
  fiat_secp256k1_uint1 x193;
  uint64_t x194;
  uint64_t x195;
  fiat_secp256k1_uint1 x196;
  uint64_t x197;
  fiat_secp256k1_uint1 x198;
  uint64_t x199;
  fiat_secp256k1_uint1 x200;
  uint64_t x201;
  fiat_secp256k1_uint1 x202;
  uint64_t x203;
  fiat_secp256k1_uint1 x204;
  uint64_t x205;
  uint64_t x206;
  fiat_secp256k1_uint1 x207;
  uint64_t x208;
  fiat_secp256k1_uint1 x209;
  uint64_t x210;
  fiat_secp256k1_uint1 x211;
  uint64_t x212;
  fiat_secp256k1_uint1 x213;
  uint64_t x214;
  fiat_secp256k1_uint1 x215;
  uint64_t x216;
  uint64_t x217;
  uint64_t x218;
  uint64_t x219;
  x1 = (arg1[1]);
  x2 = (arg1[2]);
  x3 = (arg1[3]);
  x4 = (arg1[0]);
  fiat_secp256k1_mulx_u64(&x5, &x6, x4, (arg1[3]));
  fiat_secp256k1_mulx_u64(&x7, &x8, x4, (arg1[2]));
  fiat_secp256k1_mulx_u64(&x9, &x10, x4, (arg1[1]));
  fiat_secp256k1_mulx_u64(&x11, &x12, x4, (arg1[0]));
  fiat_secp256k1_addcarryx_u64(&x13, &x14, 0x0, x12, x9);
  fiat_secp256k1_addcarryx_u64(&x15, &x16, x14, x10, x7);
  fiat_secp256k1_addcarryx_u64(&x17, &x18, x16, x8, x5);
  x19 = (x18 + x6);
  fiat_secp256k1_mulx_u64(&x20, &x21, x11, UINT64_C(0xd838091dd2253531));
  fiat_secp256k1_mulx_u64(&x22, &x23, x20, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x24, &x25, x20, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x26, &x27, x20, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x28, &x29, x20, UINT64_C(0xfffffffefffffc2f));
  fiat_secp256k1_addcarryx_u64(&x30, &x31, 0x0, x29, x26);
  fiat_secp256k1_addcarryx_u64(&x32, &x33, x31, x27, x24);
  fiat_secp256k1_addcarryx_u64(&x34, &x35, x33, x25, x22);
  x36 = (x35 + x23);
  fiat_secp256k1_addcarryx_u64(&x37, &x38, 0x0, x11, x28);
  fiat_secp256k1_addcarryx_u64(&x39, &x40, x38, x13, x30);
  fiat_secp256k1_addcarryx_u64(&x41, &x42, x40, x15, x32);
  fiat_secp256k1_addcarryx_u64(&x43, &x44, x42, x17, x34);
  fiat_secp256k1_addcarryx_u64(&x45, &x46, x44, x19, x36);
  fiat_secp256k1_mulx_u64(&x47, &x48, x1, (arg1[3]));
  fiat_secp256k1_mulx_u64(&x49, &x50, x1, (arg1[2]));
  fiat_secp256k1_mulx_u64(&x51, &x52, x1, (arg1[1]));
  fiat_secp256k1_mulx_u64(&x53, &x54, x1, (arg1[0]));
  fiat_secp256k1_addcarryx_u64(&x55, &x56, 0x0, x54, x51);
  fiat_secp256k1_addcarryx_u64(&x57, &x58, x56, x52, x49);
  fiat_secp256k1_addcarryx_u64(&x59, &x60, x58, x50, x47);
  x61 = (x60 + x48);
  fiat_secp256k1_addcarryx_u64(&x62, &x63, 0x0, x39, x53);
  fiat_secp256k1_addcarryx_u64(&x64, &x65, x63, x41, x55);
  fiat_secp256k1_addcarryx_u64(&x66, &x67, x65, x43, x57);
  fiat_secp256k1_addcarryx_u64(&x68, &x69, x67, x45, x59);
  fiat_secp256k1_addcarryx_u64(&x70, &x71, x69, x46, x61);
  fiat_secp256k1_mulx_u64(&x72, &x73, x62, UINT64_C(0xd838091dd2253531));
  fiat_secp256k1_mulx_u64(&x74, &x75, x72, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x76, &x77, x72, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x78, &x79, x72, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x80, &x81, x72, UINT64_C(0xfffffffefffffc2f));
  fiat_secp256k1_addcarryx_u64(&x82, &x83, 0x0, x81, x78);
  fiat_secp256k1_addcarryx_u64(&x84, &x85, x83, x79, x76);
  fiat_secp256k1_addcarryx_u64(&x86, &x87, x85, x77, x74);
  x88 = (x87 + x75);
  fiat_secp256k1_addcarryx_u64(&x89, &x90, 0x0, x62, x80);
  fiat_secp256k1_addcarryx_u64(&x91, &x92, x90, x64, x82);
  fiat_secp256k1_addcarryx_u64(&x93, &x94, x92, x66, x84);
  fiat_secp256k1_addcarryx_u64(&x95, &x96, x94, x68, x86);
  fiat_secp256k1_addcarryx_u64(&x97, &x98, x96, x70, x88);
  x99 = ((uint64_t)x98 + x71);
  fiat_secp256k1_mulx_u64(&x100, &x101, x2, (arg1[3]));
  fiat_secp256k1_mulx_u64(&x102, &x103, x2, (arg1[2]));
  fiat_secp256k1_mulx_u64(&x104, &x105, x2, (arg1[1]));
  fiat_secp256k1_mulx_u64(&x106, &x107, x2, (arg1[0]));
  fiat_secp256k1_addcarryx_u64(&x108, &x109, 0x0, x107, x104);
  fiat_secp256k1_addcarryx_u64(&x110, &x111, x109, x105, x102);
  fiat_secp256k1_addcarryx_u64(&x112, &x113, x111, x103, x100);
  x114 = (x113 + x101);
  fiat_secp256k1_addcarryx_u64(&x115, &x116, 0x0, x91, x106);
  fiat_secp256k1_addcarryx_u64(&x117, &x118, x116, x93, x108);
  fiat_secp256k1_addcarryx_u64(&x119, &x120, x118, x95, x110);
  fiat_secp256k1_addcarryx_u64(&x121, &x122, x120, x97, x112);
  fiat_secp256k1_addcarryx_u64(&x123, &x124, x122, x99, x114);
  fiat_secp256k1_mulx_u64(&x125, &x126, x115, UINT64_C(0xd838091dd2253531));
  fiat_secp256k1_mulx_u64(&x127, &x128, x125, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x129, &x130, x125, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x131, &x132, x125, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x133, &x134, x125, UINT64_C(0xfffffffefffffc2f));
  fiat_secp256k1_addcarryx_u64(&x135, &x136, 0x0, x134, x131);
  fiat_secp256k1_addcarryx_u64(&x137, &x138, x136, x132, x129);
  fiat_secp256k1_addcarryx_u64(&x139, &x140, x138, x130, x127);
  x141 = (x140 + x128);
  fiat_secp256k1_addcarryx_u64(&x142, &x143, 0x0, x115, x133);
  fiat_secp256k1_addcarryx_u64(&x144, &x145, x143, x117, x135);
  fiat_secp256k1_addcarryx_u64(&x146, &x147, x145, x119, x137);
  fiat_secp256k1_addcarryx_u64(&x148, &x149, x147, x121, x139);
  fiat_secp256k1_addcarryx_u64(&x150, &x151, x149, x123, x141);
  x152 = ((uint64_t)x151 + x124);
  fiat_secp256k1_mulx_u64(&x153, &x154, x3, (arg1[3]));
  fiat_secp256k1_mulx_u64(&x155, &x156, x3, (arg1[2]));
  fiat_secp256k1_mulx_u64(&x157, &x158, x3, (arg1[1]));
  fiat_secp256k1_mulx_u64(&x159, &x160, x3, (arg1[0]));
  fiat_secp256k1_addcarryx_u64(&x161, &x162, 0x0, x160, x157);
  fiat_secp256k1_addcarryx_u64(&x163, &x164, x162, x158, x155);
  fiat_secp256k1_addcarryx_u64(&x165, &x166, x164, x156, x153);
  x167 = (x166 + x154);
  fiat_secp256k1_addcarryx_u64(&x168, &x169, 0x0, x144, x159);
  fiat_secp256k1_addcarryx_u64(&x170, &x171, x169, x146, x161);
  fiat_secp256k1_addcarryx_u64(&x172, &x173, x171, x148, x163);
  fiat_secp256k1_addcarryx_u64(&x174, &x175, x173, x150, x165);
  fiat_secp256k1_addcarryx_u64(&x176, &x177, x175, x152, x167);
  fiat_secp256k1_mulx_u64(&x178, &x179, x168, UINT64_C(0xd838091dd2253531));
  fiat_secp256k1_mulx_u64(&x180, &x181, x178, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x182, &x183, x178, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x184, &x185, x178, UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_mulx_u64(&x186, &x187, x178, UINT64_C(0xfffffffefffffc2f));
  fiat_secp256k1_addcarryx_u64(&x188, &x189, 0x0, x187, x184);
  fiat_secp256k1_addcarryx_u64(&x190, &x191, x189, x185, x182);
  fiat_secp256k1_addcarryx_u64(&x192, &x193, x191, x183, x180);
  x194 = (x193 + x181);
  fiat_secp256k1_addcarryx_u64(&x195, &x196, 0x0, x168, x186);
  fiat_secp256k1_addcarryx_u64(&x197, &x198, x196, x170, x188);
  fiat_secp256k1_addcarryx_u64(&x199, &x200, x198, x172, x190);
  fiat_secp256k1_addcarryx_u64(&x201, &x202, x200, x174, x192);
  fiat_secp256k1_addcarryx_u64(&x203, &x204, x202, x176, x194);
  x205 = ((uint64_t)x204 + x177);
  fiat_secp256k1_subborrowx_u64(&x206, &x207, 0x0, x197,
                                UINT64_C(0xfffffffefffffc2f));
  fiat_secp256k1_subborrowx_u64(&x208, &x209, x207, x199,
                                UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_subborrowx_u64(&x210, &x211, x209, x201,
                                UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_subborrowx_u64(&x212, &x213, x211, x203,
                                UINT64_C(0xffffffffffffffff));
  fiat_secp256k1_subborrowx_u64(&x214, &x215, x213, x205, 0x0);
  fiat_secp256k1_cmovznz_u64(&x216, x215, x206, x197);
  fiat_secp256k1_cmovznz_u64(&x217, x215, x208, x199);
  fiat_secp256k1_cmovznz_u64(&x218, x215, x210, x201);
  fiat_secp256k1_cmovznz_u64(&x219, x215, x212, x203);
  out1[0] = x216;
  out1[1] = x217;
  out1[2] = x218;
  out1[3] = x219;
}

// NOLINTEND
