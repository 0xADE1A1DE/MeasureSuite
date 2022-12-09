typedef __int128 uint128_t;
#define static
#define SECP256K1_INLINE
#define SECP256K1_RESTRICT restrict 
/***********************************************************************
 * Copyright (c) 2013, 2014 Pieter Wuille                              *
 * Distributed under the MIT software license, see the accompanying    *
 * file COPYING or https://www.opensource.org/licenses/mit-license.php.*
 ***********************************************************************/

#ifndef SECP256K1_FIELD_INNER5X52_IMPL_H
#define SECP256K1_FIELD_INNER5X52_IMPL_H

#include <stdint.h>

#ifdef VERIFY
#define VERIFY_BITS(x, n) VERIFY_CHECK(((x) >> (n)) == 0)
#else
#define VERIFY_BITS(x, n)                                                      \
  do {                                                                         \
  } while (0)
#endif

SECP256K1_INLINE static void
secp256k1_fe_mul_inner(uint64_t *r, const uint64_t *a,
                       const uint64_t *SECP256K1_RESTRICT b) {
  uint128_t c, d;
  uint64_t t3, t4, tx, u0;
  uint64_t a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4];
  const uint64_t M = 0xFFFFFFFFFFFFFULL, R = 0x1000003D10ULL;


  /*  [... a b c] is a shorthand for ... + a<<104 + b<<52 + c<<0 mod n.
   *  for 0 <= x <= 4, px is a shorthand for sum(a[i]*b[x-i], i=0..x).
   *  for 4 <= x <= 8, px is a shorthand for sum(a[i]*b[x-i], i=(x-4)..4)
   *  Note that [x 0 0 0 0 0] = [x*R].
   */

  d = (uint128_t)a0 * b[3] + (uint128_t)a1 * b[2] + (uint128_t)a2 * b[1] +
      (uint128_t)a3 * b[0];
  /* [d 0 0 0] = [p3 0 0 0] */
  c = (uint128_t)a4 * b[4];
  /* [c 0 0 0 0 d 0 0 0] = [p8 0 0 0 0 p3 0 0 0] */
  d += (uint128_t)R * (uint64_t)c;
  c >>= 64;
  /* [(c<<12) 0 0 0 0 0 d 0 0 0] = [p8 0 0 0 0 p3 0 0 0] */
  t3 = d & M;
  d >>= 52;
  /* [(c<<12) 0 0 0 0 d t3 0 0 0] = [p8 0 0 0 0 p3 0 0 0] */

  d += (uint128_t)a0 * b[4] + (uint128_t)a1 * b[3] + (uint128_t)a2 * b[2] +
       (uint128_t)a3 * b[1] + (uint128_t)a4 * b[0];
  /* [(c<<12) 0 0 0 0 d t3 0 0 0] = [p8 0 0 0 p4 p3 0 0 0] */
  d += (uint128_t)(R << 12) * (uint64_t)c;
  /* [d t3 0 0 0] = [p8 0 0 0 p4 p3 0 0 0] */
  t4 = d & M;
  d >>= 52;
  /* [d t4 t3 0 0 0] = [p8 0 0 0 p4 p3 0 0 0] */
  tx = (t4 >> 48);
  t4 &= (M >> 4);
  /* [d t4+(tx<<48) t3 0 0 0] = [p8 0 0 0 p4 p3 0 0 0] */

  c = (uint128_t)a0 * b[0];
  /* [d t4+(tx<<48) t3 0 0 c] = [p8 0 0 0 p4 p3 0 0 p0] */
  d += (uint128_t)a1 * b[4] + (uint128_t)a2 * b[3] + (uint128_t)a3 * b[2] +
       (uint128_t)a4 * b[1];
  /* [d t4+(tx<<48) t3 0 0 c] = [p8 0 0 p5 p4 p3 0 0 p0] */
  u0 = d & M;
  d >>= 52;
  /* [d u0 t4+(tx<<48) t3 0 0 c] = [p8 0 0 p5 p4 p3 0 0 p0] */
  /* [d 0 t4+(tx<<48)+(u0<<52) t3 0 0 c] = [p8 0 0 p5 p4 p3 0 0 p0] */
  u0 = (u0 << 4) | tx;
  /* [d 0 t4+(u0<<48) t3 0 0 c] = [p8 0 0 p5 p4 p3 0 0 p0] */
  c += (uint128_t)u0 * (R >> 4);
  /* [d 0 t4 t3 0 0 c] = [p8 0 0 p5 p4 p3 0 0 p0] */
  r[0] = c & M;
  c >>= 52;
  /* [d 0 t4 t3 0 c r0] = [p8 0 0 p5 p4 p3 0 0 p0] */

  c += (uint128_t)a0 * b[1] + (uint128_t)a1 * b[0];
  /* [d 0 t4 t3 0 c r0] = [p8 0 0 p5 p4 p3 0 p1 p0] */
  d += (uint128_t)a2 * b[4] + (uint128_t)a3 * b[3] + (uint128_t)a4 * b[2];
  /* [d 0 t4 t3 0 c r0] = [p8 0 p6 p5 p4 p3 0 p1 p0] */
  c += (d & M) * R;
  d >>= 52;
  /* [d 0 0 t4 t3 0 c r0] = [p8 0 p6 p5 p4 p3 0 p1 p0] */
  r[1] = c & M;
  c >>= 52;
  /* [d 0 0 t4 t3 c r1 r0] = [p8 0 p6 p5 p4 p3 0 p1 p0] */

  c += (uint128_t)a0 * b[2] + (uint128_t)a1 * b[1] + (uint128_t)a2 * b[0];
  /* [d 0 0 t4 t3 c r1 r0] = [p8 0 p6 p5 p4 p3 p2 p1 p0] */
  d += (uint128_t)a3 * b[4] + (uint128_t)a4 * b[3];
  /* [d 0 0 t4 t3 c t1 r0] = [p8 p7 p6 p5 p4 p3 p2 p1 p0] */
  c += (uint128_t)R * (uint64_t)d;
  d >>= 64;
  /* [(d<<12) 0 0 0 t4 t3 c r1 r0] = [p8 p7 p6 p5 p4 p3 p2 p1 p0] */

  r[2] = c & M;
  c >>= 52;
  /* [(d<<12) 0 0 0 t4 t3+c r2 r1 r0] = [p8 p7 p6 p5 p4 p3 p2 p1 p0] */
  c += (uint128_t)(R << 12) * (uint64_t)d + t3;
  /* [t4 c r2 r1 r0] = [p8 p7 p6 p5 p4 p3 p2 p1 p0] */
  r[3] = c & M;
  c >>= 52;
  /* [t4+c r3 r2 r1 r0] = [p8 p7 p6 p5 p4 p3 p2 p1 p0] */
  c += t4;
  /* [c r3 r2 r1 r0] = [p8 p7 p6 p5 p4 p3 p2 p1 p0] */
  r[4] = c;
  /* [r4 r3 r2 r1 r0] = [p8 p7 p6 p5 p4 p3 p2 p1 p0] */
}

SECP256K1_INLINE static void secp256k1_fe_sqr_inner(uint64_t *r,
                                                    const uint64_t *a) {
  uint128_t c, d;
  uint64_t a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4];
  int64_t t3, t4, tx, u0;
  const uint64_t M = 0xFFFFFFFFFFFFFULL, R = 0x1000003D10ULL;


  /**  [... a b c] is a shorthand for ... + a<<104 + b<<52 + c<<0 mod n.
   *  px is a shorthand for sum(a[i]*a[x-i], i=0..x).
   *  Note that [x 0 0 0 0 0] = [x*R].
   */

  d = (uint128_t)(a0 * 2) * a3 + (uint128_t)(a1 * 2) * a2;
  /* [d 0 0 0] = [p3 0 0 0] */
  c = (uint128_t)a4 * a4;
  /* [c 0 0 0 0 d 0 0 0] = [p8 0 0 0 0 p3 0 0 0] */
  d += (uint128_t)R * (uint64_t)c;
  c >>= 64;
  /* [(c<<12) 0 0 0 0 0 d 0 0 0] = [p8 0 0 0 0 p3 0 0 0] */
  t3 = d & M;
  d >>= 52;
  /* [(c<<12) 0 0 0 0 d t3 0 0 0] = [p8 0 0 0 0 p3 0 0 0] */

  a4 *= 2;
  d += (uint128_t)a0 * a4 + (uint128_t)(a1 * 2) * a3 + (uint128_t)a2 * a2;
  /* [(c<<12) 0 0 0 0 d t3 0 0 0] = [p8 0 0 0 p4 p3 0 0 0] */
  d += (uint128_t)(R << 12) * (uint64_t)c;
  /* [d t3 0 0 0] = [p8 0 0 0 p4 p3 0 0 0] */
  t4 = d & M;
  d >>= 52;
  /* [d t4 t3 0 0 0] = [p8 0 0 0 p4 p3 0 0 0] */
  tx = (t4 >> 48);
  t4 &= (M >> 4);
  /* [d t4+(tx<<48) t3 0 0 0] = [p8 0 0 0 p4 p3 0 0 0] */

  c = (uint128_t)a0 * a0;
  /* [d t4+(tx<<48) t3 0 0 c] = [p8 0 0 0 p4 p3 0 0 p0] */
  d += (uint128_t)a1 * a4 + (uint128_t)(a2 * 2) * a3;
  /* [d t4+(tx<<48) t3 0 0 c] = [p8 0 0 p5 p4 p3 0 0 p0] */
  u0 = d & M;
  d >>= 52;
  /* [d u0 t4+(tx<<48) t3 0 0 c] = [p8 0 0 p5 p4 p3 0 0 p0] */
  /* [d 0 t4+(tx<<48)+(u0<<52) t3 0 0 c] = [p8 0 0 p5 p4 p3 0 0 p0] */
  u0 = (u0 << 4) | tx;
  /* [d 0 t4+(u0<<48) t3 0 0 c] = [p8 0 0 p5 p4 p3 0 0 p0] */
  c += (uint128_t)u0 * (R >> 4);
  /* [d 0 t4 t3 0 0 c] = [p8 0 0 p5 p4 p3 0 0 p0] */
  r[0] = c & M;
  c >>= 52;
  /* [d 0 t4 t3 0 c r0] = [p8 0 0 p5 p4 p3 0 0 p0] */

  a0 *= 2;
  c += (uint128_t)a0 * a1;
  /* [d 0 t4 t3 0 c r0] = [p8 0 0 p5 p4 p3 0 p1 p0] */
  d += (uint128_t)a2 * a4 + (uint128_t)a3 * a3;
  /* [d 0 t4 t3 0 c r0] = [p8 0 p6 p5 p4 p3 0 p1 p0] */
  c += (d & M) * R;
  d >>= 52;
  /* [d 0 0 t4 t3 0 c r0] = [p8 0 p6 p5 p4 p3 0 p1 p0] */
  r[1] = c & M;
  c >>= 52;
  /* [d 0 0 t4 t3 c r1 r0] = [p8 0 p6 p5 p4 p3 0 p1 p0] */

  c += (uint128_t)a0 * a2 + (uint128_t)a1 * a1;
  /* [d 0 0 t4 t3 c r1 r0] = [p8 0 p6 p5 p4 p3 p2 p1 p0] */
  d += (uint128_t)a3 * a4;
  /* [d 0 0 t4 t3 c r1 r0] = [p8 p7 p6 p5 p4 p3 p2 p1 p0] */
  c += (uint128_t)R * (uint64_t)d;
  d >>= 64;
  /* [(d<<12) 0 0 0 t4 t3 c r1 r0] = [p8 p7 p6 p5 p4 p3 p2 p1 p0] */
  r[2] = c & M;
  c >>= 52;
  /* [(d<<12) 0 0 0 t4 t3+c r2 r1 r0] = [p8 p7 p6 p5 p4 p3 p2 p1 p0] */

  c += (uint128_t)(R << 12) * (uint64_t)d + t3;
  /* [t4 c r2 r1 r0] = [p8 p7 p6 p5 p4 p3 p2 p1 p0] */
  r[3] = c & M;
  c >>= 52;
  /* [t4+c r3 r2 r1 r0] = [p8 p7 p6 p5 p4 p3 p2 p1 p0] */
  c += t4;
  /* [c r3 r2 r1 r0] = [p8 p7 p6 p5 p4 p3 p2 p1 p0] */
  r[4] = c;
  /* [r4 r3 r2 r1 r0] = [p8 p7 p6 p5 p4 p3 p2 p1 p0] */
}

#endif /* SECP256K1_FIELD_INNER5X52_IMPL_H */
