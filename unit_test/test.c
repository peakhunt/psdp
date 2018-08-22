#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"

#include <stdlib.h>
#include <stdio.h>

#include "psdp.h"

int init_suite_success(void) { return 0; }
int init_suite_failure(void) { return -1; }
int clean_suite_success(void) { return 0; }
int clean_suite_failure(void) { return -1; }

static void
psdp_test_v(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;
  psdp_str*       t = &sdp.v;

  static const char*    sdp_msg1 = \
  "v=1" \
  ;

  static const char*    sdp_msg2 = \
  "v=" \
  ;

  static const char*    sdp_msg3 = \
  "v=0\r\n" \
  ;

  static const char*    sdp_msg4 = \
  "v=0\n" \
  "v=1\r\n" \
  "v=zolla" \
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(t->val_len == 1);
  CU_ASSERT(psdp_str_cmp(t, "1") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(t->val_len == 0);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(t->val_len == 1);
  CU_ASSERT(psdp_str_cmp(t, "0") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg4, strlen(sdp_msg4));
  CU_ASSERT(t->val_len == 5);
  CU_ASSERT(psdp_str_cmp(t, "zolla") == PSDP_TRUE);
}

static void
psdp_test_o(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;
  psdp_str*       t = &sdp.o;

  static const char*    sdp_msg1 = \
  "o=Hello World" \
  ;

  static const char*    sdp_msg2 = \
  "o=" \
  ;

  static const char*    sdp_msg3 = \
  "o= broken invalid \r\n" \
  ;

  static const char*    sdp_msg4 = \
  "o=ignored1\n" \
  "o=ignored2\r\n" \
  "o=accepted" \
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(t->val_len == 11);
  CU_ASSERT(psdp_str_cmp(t, "Hello World") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(t->val_len == 0);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(t->val_len == 16);
  CU_ASSERT(psdp_str_cmp(t, " broken invalid ") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg4, strlen(sdp_msg4));
  CU_ASSERT(t->val_len == 8);
  CU_ASSERT(psdp_str_cmp(t, "accepted") == PSDP_TRUE);
}

static void
psdp_test_s(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;
  psdp_str*       t = &sdp.s;

  static const char*    sdp_msg1 = \
  "s=12345678901234567890" \
  ;

  static const char*    sdp_msg2 = \
  "s=" \
  ;

  static const char*    sdp_msg3 = \
  "s= broken invalid \r\n" \
  ;

  static const char*    sdp_msg4 = \
  "s=ignored1\n" \
  "s=ignored2\r\n" \
  "s=accepted" \
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(t->val_len == 20);
  CU_ASSERT(psdp_str_cmp(t, "12345678901234567890") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(t->val_len == 0);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(t->val_len == 16);
  CU_ASSERT(psdp_str_cmp(t, " broken invalid ") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg4, strlen(sdp_msg4));
  CU_ASSERT(t->val_len == 8);
  CU_ASSERT(psdp_str_cmp(t, "accepted") == PSDP_TRUE);
}

static void
psdp_test_i(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;
  psdp_str*       t = &sdp.i;

  static const char*    sdp_msg1 = \
  "i=12345678901234567890" \
  ;

  static const char*    sdp_msg2 = \
  "i=" \
  ;

  static const char*    sdp_msg3 = \
  "i= broken invalid \r\n" \
  ;

  static const char*    sdp_msg4 = \
  "i=ignored1\n" \
  "i=ignored2\r\n" \
  "i=accepted" \
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(t->val_len == 20);
  CU_ASSERT(psdp_str_cmp(t, "12345678901234567890") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(t->val_len == 0);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(t->val_len == 16);
  CU_ASSERT(psdp_str_cmp(t, " broken invalid ") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg4, strlen(sdp_msg4));
  CU_ASSERT(t->val_len == 8);
  CU_ASSERT(psdp_str_cmp(t, "accepted") == PSDP_TRUE);
}

static void
psdp_test_u(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;
  psdp_str*       t = &sdp.u;

  static const char*    sdp_msg1 = \
  "u=12345678901234567890" \
  ;

  static const char*    sdp_msg2 = \
  "u=" \
  ;

  static const char*    sdp_msg3 = \
  "u= broken invalid \r\n" \
  ;

  static const char*    sdp_msg4 = \
  "u=ignored1\n" \
  "u=ignored2\r\n" \
  "u=accepted" \
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(t->val_len == 20);
  CU_ASSERT(psdp_str_cmp(t, "12345678901234567890") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(t->val_len == 0);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(t->val_len == 16);
  CU_ASSERT(psdp_str_cmp(t, " broken invalid ") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg4, strlen(sdp_msg4));
  CU_ASSERT(t->val_len == 8);
  CU_ASSERT(psdp_str_cmp(t, "accepted") == PSDP_TRUE);
}

static void
psdp_test_e(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;
  psdp_str*       t = &sdp.e;

  static const char*    sdp_msg1 = \
  "e=12345678901234567890" \
  ;

  static const char*    sdp_msg2 = \
  "e=" \
  ;

  static const char*    sdp_msg3 = \
  "e= broken invalid \r\n" \
  ;

  static const char*    sdp_msg4 = \
  "e=ignored1\n" \
  "e=ignored2\r\n" \
  "e=accepted" \
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(t->val_len == 20);
  CU_ASSERT(psdp_str_cmp(t, "12345678901234567890") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(t->val_len == 0);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(t->val_len == 16);
  CU_ASSERT(psdp_str_cmp(t, " broken invalid ") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg4, strlen(sdp_msg4));
  CU_ASSERT(t->val_len == 8);
  CU_ASSERT(psdp_str_cmp(t, "accepted") == PSDP_TRUE);
}

static void
psdp_test_p(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;
  psdp_str*       t = &sdp.p;

  static const char*    sdp_msg1 = \
  "p=12345678901234567890" \
  ;

  static const char*    sdp_msg2 = \
  "p=" \
  ;

  static const char*    sdp_msg3 = \
  "p= broken invalid \r\n" \
  ;

  static const char*    sdp_msg4 = \
  "p=ignored1\n" \
  "p=ignored2\r\n" \
  "p=accepted" \
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(t->val_len == 20);
  CU_ASSERT(psdp_str_cmp(t, "12345678901234567890") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(t->val_len == 0);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(t->val_len == 16);
  CU_ASSERT(psdp_str_cmp(t, " broken invalid ") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg4, strlen(sdp_msg4));
  CU_ASSERT(t->val_len == 8);
  CU_ASSERT(psdp_str_cmp(t, "accepted") == PSDP_TRUE);
}

static void
psdp_test_c(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;
  psdp_str*       t = &sdp.c;

  static const char*    sdp_msg1 = \
  "c=12345678901234567890" \
  ;

  static const char*    sdp_msg2 = \
  "c=" \
  ;

  static const char*    sdp_msg3 = \
  "c= broken invalid \r\n" \
  ;

  static const char*    sdp_msg4 = \
  "c=ignored1\n" \
  "c=ignored2\r\n" \
  "c=accepted" \
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(t->val_len == 20);
  CU_ASSERT(psdp_str_cmp(t, "12345678901234567890") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(t->val_len == 0);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(t->val_len == 16);
  CU_ASSERT(psdp_str_cmp(t, " broken invalid ") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg4, strlen(sdp_msg4));
  CU_ASSERT(t->val_len == 8);
  CU_ASSERT(psdp_str_cmp(t, "accepted") == PSDP_TRUE);
}

static void
psdp_test_b(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;

  static const char*    sdp_msg1 = \
  "b=12345678901234567890" \
  ;

  static const char*    sdp_msg2 = \
  "b=12345678901234567890\r\n" \
  "b=aaaaaaaaaaaaaaaaaaaa\r\n" \
  "b=cccccccccccccccccccc\r\n" \
  "b=dddddddddddddddddddd\r\n" \
  ;

  static const char*    sdp_msg3 = \
  "b=12345678901234567890\r\n" \
  "b=aaaaaaaaaaaaaaaaaaaa\r\n" \
  "b=cccccccccccccccccccc\r\n" \
  "b=dddddddddddddddddddd\r\n" \
  "b=not ignored\r\n" \
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(sdp.num_b == 1);
  CU_ASSERT(sdp.b[0].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.b[0], "12345678901234567890") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(sdp.num_b == 4);
  CU_ASSERT(sdp.b[0].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.b[0], "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.b[1].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.b[1], "aaaaaaaaaaaaaaaaaaaa") == PSDP_TRUE);
  CU_ASSERT(sdp.b[2].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.b[2], "cccccccccccccccccccc") == PSDP_TRUE);
  CU_ASSERT(sdp.b[3].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.b[3], "dddddddddddddddddddd") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(sdp.num_b == 5);
  CU_ASSERT(sdp.b[0].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.b[0], "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.b[1].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.b[1], "aaaaaaaaaaaaaaaaaaaa") == PSDP_TRUE);
  CU_ASSERT(sdp.b[2].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.b[2], "cccccccccccccccccccc") == PSDP_TRUE);
  CU_ASSERT(sdp.b[3].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.b[3], "dddddddddddddddddddd") == PSDP_TRUE);
  CU_ASSERT(sdp.b[4].val_len == 11);
  CU_ASSERT(psdp_str_cmp(&sdp.b[4], "not ignored") == PSDP_TRUE);
}

static void
psdp_test_z(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;
  psdp_str*       t = &sdp.z;

  static const char*    sdp_msg1 = \
  "z=12345678901234567890" \
  ;

  static const char*    sdp_msg2 = \
  "z=" \
  ;

  static const char*    sdp_msg3 = \
  "z= broken invalid \r\n" \
  ;

  static const char*    sdp_msg4 = \
  "z=ignored1\n" \
  "z=ignored2\r\n" \
  "z=accepted" \
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(t->val_len == 20);
  CU_ASSERT(psdp_str_cmp(t, "12345678901234567890") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(t->val_len == 0);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(t->val_len == 16);
  CU_ASSERT(psdp_str_cmp(t, " broken invalid ") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg4, strlen(sdp_msg4));
  CU_ASSERT(t->val_len == 8);
  CU_ASSERT(psdp_str_cmp(t, "accepted") == PSDP_TRUE);

}

static void
psdp_test_k(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;
  psdp_str*       t = &sdp.k;

  static const char*    sdp_msg1 = \
  "k=12345678901234567890" \
  ;

  static const char*    sdp_msg2 = \
  "k=" \
  ;

  static const char*    sdp_msg3 = \
  "k= broken invalid \r\n" \
  ;

  static const char*    sdp_msg4 = \
  "k=ignored1\n" \
  "k=ignored2\r\n" \
  "k=accepted" \
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(t->val_len == 20);
  CU_ASSERT(psdp_str_cmp(t, "12345678901234567890") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(t->val_len == 0);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(t->val_len == 16);
  CU_ASSERT(psdp_str_cmp(t, " broken invalid ") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg4, strlen(sdp_msg4));
  CU_ASSERT(t->val_len == 8);
  CU_ASSERT(psdp_str_cmp(t, "accepted") == PSDP_TRUE);

}

static void
psdp_test_a(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;

  static const char*    sdp_msg1 = \
  "a=12345678901234567890" \
  ;

  static const char*    sdp_msg2 = \
  "a=12345678901234567890\r\n" \
  "a=aaaaaaaaaaaaaaaaaaaa\r\n" \
  "a=cccccccccccccccccccc\r\n" \
  "a=dddddddddddddddddddd\r\n" \
  ;

  static const char*    sdp_msg3 = \
  "a=12345678901234567890\r\n" \
  "a=aaaaaaaaaaaaaaaaaaaa\r\n" \
  "a=cccccccccccccccccccc\r\n" \
  "a=dddddddddddddddddddd\r\n" \
  "a=not ignored\r\n" \
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(sdp.num_a == 1);
  CU_ASSERT(sdp.a[0].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.a[0], "12345678901234567890") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(sdp.num_a == 4);
  CU_ASSERT(sdp.a[0].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.a[0], "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.a[1].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.a[1], "aaaaaaaaaaaaaaaaaaaa") == PSDP_TRUE);
  CU_ASSERT(sdp.a[2].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.a[2], "cccccccccccccccccccc") == PSDP_TRUE);
  CU_ASSERT(sdp.a[3].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.a[3], "dddddddddddddddddddd") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(sdp.num_a == 5);
  CU_ASSERT(sdp.a[0].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.a[0], "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.a[1].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.a[1], "aaaaaaaaaaaaaaaaaaaa") == PSDP_TRUE);
  CU_ASSERT(sdp.a[2].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.a[2], "cccccccccccccccccccc") == PSDP_TRUE);
  CU_ASSERT(sdp.a[3].val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.a[3], "dddddddddddddddddddd") == PSDP_TRUE);
  CU_ASSERT(sdp.a[4].val_len == 11);
  CU_ASSERT(psdp_str_cmp(&sdp.a[4], "not ignored") == PSDP_TRUE);
}

static void
psdp_test_m(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;

  static const char*    sdp_msg1 = \
  "m=12345678901234567890" \
  ;

  static const char*    sdp_msg2 = \
  "m=12345678901234567890\r\n" \
  "m=aaaaaaaaaaaaaaaaaaaa\r\n" \
  "m=cccccccccccccccccccc\r\n" \
  "m=dddddddddddddddddddd\r\n" \
  ;

  static const char*    sdp_msg3 = \
  "m=12345678901234567890\r\n" \
  "m=aaaaaaaaaaaaaaaaaaaa\r\n" \
  "m=cccccccccccccccccccc\r\n" \
  "m=dddddddddddddddddddd\r\n" \
  "m=ignored\r\n" \
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(sdp.num_m == 1);
  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);

  //
  // XXX this test assumes that PSDP_MAX_BANDWIDTH_INFO is 4
  //
  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(sdp.num_m == 4);
  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[1].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].m, "aaaaaaaaaaaaaaaaaaaa") == PSDP_TRUE);
  CU_ASSERT(sdp.media[2].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].m, "cccccccccccccccccccc") == PSDP_TRUE);
  CU_ASSERT(sdp.media[3].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].m, "dddddddddddddddddddd") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(sdp.num_m == 4);
  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[1].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].m, "aaaaaaaaaaaaaaaaaaaa") == PSDP_TRUE);
  CU_ASSERT(sdp.media[2].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].m, "cccccccccccccccccccc") == PSDP_TRUE);
  CU_ASSERT(sdp.media[3].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].m, "dddddddddddddddddddd") == PSDP_TRUE);
}

static void
psdp_test_m_i(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;

  static const char*    sdp_msg1 = \
  "m=12345678901234567890\r\n" \
  "i=iiiiiiiiiiiiiiiiiiii"
  ;

  static const char*    sdp_msg2 = \
  "m=12345678901234567890\r\n" \
  "i=iiiiiiiiiiiiiiiiiiii\r\n" \
  "m=aaaaaaaaaaaaaaaaaaaa\r\n" \
  "i=aiaiaiaiaiaiaiaiaiai\r\n" \
  "m=cccccccccccccccccccc\r\n" \
  "i=77777777777777777777\r\n" \
  "m=dddddddddddddddddddd\r\n" \
  "i=overriden\r\n" \
  "i=88888888888888888888\r\n"
  ;

  static const char*    sdp_msg3 = \
  "m=12345678901234567890\r\n" \
  "i=iiiiiiiiiiiiiiiiiiii\r\n" \
  "m=aaaaaaaaaaaaaaaaaaaa\r\n" \
  "i=aiaiaiaiaiaiaiaiaiai\r\n" \
  "m=cccccccccccccccccccc\r\n" \
  "i=77777777777777777777\r\n" \
  "m=dddddddddddddddddddd\r\n" \
  "i=overridden\r\n" \
  "i=88888888888888888888\r\n"
  "m=ignored\r\n" \
  "i=ignored\r\n" \
  "i=ignored"
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(sdp.num_m == 1);
  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[0].i.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].i, "iiiiiiiiiiiiiiiiiiii") == PSDP_TRUE);

  //
  // XXX this test assumes that PSDP_MAX_BANDWIDTH_INFO is 4
  //
  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(sdp.num_m == 4);
  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[0].i.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].i, "iiiiiiiiiiiiiiiiiiii") == PSDP_TRUE);

  CU_ASSERT(sdp.media[1].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].m, "aaaaaaaaaaaaaaaaaaaa") == PSDP_TRUE);
  CU_ASSERT(sdp.media[1].i.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].i, "aiaiaiaiaiaiaiaiaiai") == PSDP_TRUE);

  CU_ASSERT(sdp.media[2].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].m, "cccccccccccccccccccc") == PSDP_TRUE);
  CU_ASSERT(sdp.media[2].i.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].i, "77777777777777777777") == PSDP_TRUE);

  CU_ASSERT(sdp.media[3].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].m, "dddddddddddddddddddd") == PSDP_TRUE);
  CU_ASSERT(sdp.media[3].i.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].i, "88888888888888888888") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(sdp.num_m == 4);
  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[0].i.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].i, "iiiiiiiiiiiiiiiiiiii") == PSDP_TRUE);

  CU_ASSERT(sdp.media[1].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].m, "aaaaaaaaaaaaaaaaaaaa") == PSDP_TRUE);
  CU_ASSERT(sdp.media[1].i.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].i, "aiaiaiaiaiaiaiaiaiai") == PSDP_TRUE);

  CU_ASSERT(sdp.media[2].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].m, "cccccccccccccccccccc") == PSDP_TRUE);
  CU_ASSERT(sdp.media[2].i.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].i, "77777777777777777777") == PSDP_TRUE);

  CU_ASSERT(sdp.media[3].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].m, "dddddddddddddddddddd") == PSDP_TRUE);
  CU_ASSERT(sdp.media[3].i.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].i, "88888888888888888888") == PSDP_TRUE);
}

static void
psdp_test_m_c(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;

  static const char*    sdp_msg1 = \
  "m=12345678901234567890\r\n" \
  "c=iiiiiiiiiiiiiiiiiiii"
  ;

  static const char*    sdp_msg2 = \
  "m=12345678901234567890\r\n" \
  "c=iiiiiiiiiiiiiiiiiiii\r\n" \
  "m=aaaaaaaaaaaaaaaaaaaa\r\n" \
  "c=aiaiaiaiaiaiaiaiaiai\r\n" \
  "m=cccccccccccccccccccc\r\n" \
  "c=77777777777777777777\r\n" \
  "m=dddddddddddddddddddd\r\n" \
  "c=overriden\r\n" \
  "c=88888888888888888888\r\n"
  ;

  static const char*    sdp_msg3 = \
  "m=12345678901234567890\r\n" \
  "c=iiiiiiiiiiiiiiiiiiii\r\n" \
  "m=aaaaaaaaaaaaaaaaaaaa\r\n" \
  "c=aiaiaiaiaiaiaiaiaiai\r\n" \
  "m=cccccccccccccccccccc\r\n" \
  "c=77777777777777777777\r\n" \
  "m=dddddddddddddddddddd\r\n" \
  "c=overridden\r\n" \
  "c=88888888888888888888\r\n"
  "m=ignored\r\n" \
  "c=ignored\r\n" \
  "c=ignored"
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(sdp.num_m == 1);
  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[0].c.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].c, "iiiiiiiiiiiiiiiiiiii") == PSDP_TRUE);

  //
  // XXX this test assumes that PSDP_MAX_BANDWIDTH_INFO is 4
  //
  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(sdp.num_m == 4);
  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[0].c.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].c, "iiiiiiiiiiiiiiiiiiii") == PSDP_TRUE);

  CU_ASSERT(sdp.media[1].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].m, "aaaaaaaaaaaaaaaaaaaa") == PSDP_TRUE);
  CU_ASSERT(sdp.media[1].c.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].c, "aiaiaiaiaiaiaiaiaiai") == PSDP_TRUE);

  CU_ASSERT(sdp.media[2].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].m, "cccccccccccccccccccc") == PSDP_TRUE);
  CU_ASSERT(sdp.media[2].c.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].c, "77777777777777777777") == PSDP_TRUE);

  CU_ASSERT(sdp.media[3].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].m, "dddddddddddddddddddd") == PSDP_TRUE);
  CU_ASSERT(sdp.media[3].c.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].c, "88888888888888888888") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(sdp.num_m == 4);
  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[0].c.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].c, "iiiiiiiiiiiiiiiiiiii") == PSDP_TRUE);

  CU_ASSERT(sdp.media[1].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].m, "aaaaaaaaaaaaaaaaaaaa") == PSDP_TRUE);
  CU_ASSERT(sdp.media[1].c.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].c, "aiaiaiaiaiaiaiaiaiai") == PSDP_TRUE);

  CU_ASSERT(sdp.media[2].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].m, "cccccccccccccccccccc") == PSDP_TRUE);
  CU_ASSERT(sdp.media[2].c.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].c, "77777777777777777777") == PSDP_TRUE);

  CU_ASSERT(sdp.media[3].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].m, "dddddddddddddddddddd") == PSDP_TRUE);
  CU_ASSERT(sdp.media[3].c.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].c, "88888888888888888888") == PSDP_TRUE);
}

static void
psdp_test_m_b(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;

  static const char*    sdp_msg1 = \
  "m=12345678901234567890\r\n" \
  ;

  static const char*    sdp_msg2 = \
  "m=12345678901234567890\r\n" \
  "b=b1b1b1b1b1b1b1b1b1b1\r\n" \
  "m=aaaaaaaaaaaaaaaaaaaa\r\n" \
  "b=b1b1b1b1b1b1b1b1b1b1\r\n" \
  "b=b2b2b2b2b2b2b2b2b2b2\r\n" \
  "m=mmmmmmmmmmmmmmmmmmmm\r\n" \
  "b=b1b1b1b1b1b1b1b1b1b1\r\n" \
  "b=b2b2b2b2b2b2b2b2b2b2\r\n" \
  "b=b3b3b3b3b3b3b3b3b3b3\r\n" \
  "m=nnnnnnnnnnnnnnnnnnnn\r\n" \
  "b=b1b1b1b1b1b1b1b1b1b1\r\n" \
  "b=b2b2b2b2b2b2b2b2b2b2\r\n" \
  "b=b3b3b3b3b3b3b3b3b3b3\r\n" \
  "b=b4b4b4b4b4b4b4b4b4b4\r\n" \
  "b=not ignored\r\n" \
  "m=ignored\r\n" \
  "b=ignored\r\n"
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(sdp.num_m == 1);
  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[0].num_b == 0);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(sdp.num_m == 4);

  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[0].num_b == 1);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].b[0], "b1b1b1b1b1b1b1b1b1b1") == PSDP_TRUE);

  CU_ASSERT(sdp.media[1].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].m, "aaaaaaaaaaaaaaaaaaaa") == PSDP_TRUE);
  CU_ASSERT(sdp.media[1].num_b == 2);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].b[0], "b1b1b1b1b1b1b1b1b1b1") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].b[1], "b2b2b2b2b2b2b2b2b2b2") == PSDP_TRUE);

  CU_ASSERT(sdp.media[2].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].m, "mmmmmmmmmmmmmmmmmmmm") == PSDP_TRUE);
  CU_ASSERT(sdp.media[2].num_b == 3);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].b[0], "b1b1b1b1b1b1b1b1b1b1") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].b[1], "b2b2b2b2b2b2b2b2b2b2") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].b[2], "b3b3b3b3b3b3b3b3b3b3") == PSDP_TRUE);

  CU_ASSERT(sdp.media[3].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].m, "nnnnnnnnnnnnnnnnnnnn") == PSDP_TRUE);
  CU_ASSERT(sdp.media[3].num_b == 5);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].b[0], "b1b1b1b1b1b1b1b1b1b1") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].b[1], "b2b2b2b2b2b2b2b2b2b2") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].b[2], "b3b3b3b3b3b3b3b3b3b3") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].b[3], "b4b4b4b4b4b4b4b4b4b4") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].b[4], "not ignored") == PSDP_TRUE);
}

static void
psdp_test_m_k(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;

  static const char*    sdp_msg1 = \
  "m=12345678901234567890\r\n" \
  "k=iiiiiiiiiiiiiiiiiiii"
  ;

  static const char*    sdp_msg2 = \
  "m=12345678901234567890\r\n" \
  "k=iiiiiiiiiiiiiiiiiiii\r\n" \
  "m=aaaaaaaaaaaaaaaaaaaa\r\n" \
  "k=aiaiaiaiaiaiaiaiaiai\r\n" \
  "m=cccccccccccccccccccc\r\n" \
  "k=77777777777777777777\r\n" \
  "m=dddddddddddddddddddd\r\n" \
  "k=overriden\r\n" \
  "k=88888888888888888888\r\n"
  ;

  static const char*    sdp_msg3 = \
  "m=12345678901234567890\r\n" \
  "k=iiiiiiiiiiiiiiiiiiii\r\n" \
  "m=aaaaaaaaaaaaaaaaaaaa\r\n" \
  "k=aiaiaiaiaiaiaiaiaiai\r\n" \
  "m=cccccccccccccccccccc\r\n" \
  "k=77777777777777777777\r\n" \
  "m=dddddddddddddddddddd\r\n" \
  "k=overridden\r\n" \
  "k=88888888888888888888\r\n"
  "m=ignored\r\n" \
  "k=ignored\r\n" \
  "k=ignored"
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(sdp.num_m == 1);
  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[0].k.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].k, "iiiiiiiiiiiiiiiiiiii") == PSDP_TRUE);

  //
  // XXX this test assumes that PSDP_MAX_BANDWIDTH_INFO is 4
  //
  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(sdp.num_m == 4);
  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[0].k.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].k, "iiiiiiiiiiiiiiiiiiii") == PSDP_TRUE);

  CU_ASSERT(sdp.media[1].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].m, "aaaaaaaaaaaaaaaaaaaa") == PSDP_TRUE);
  CU_ASSERT(sdp.media[1].k.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].k, "aiaiaiaiaiaiaiaiaiai") == PSDP_TRUE);

  CU_ASSERT(sdp.media[2].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].m, "cccccccccccccccccccc") == PSDP_TRUE);
  CU_ASSERT(sdp.media[2].k.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].k, "77777777777777777777") == PSDP_TRUE);

  CU_ASSERT(sdp.media[3].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].m, "dddddddddddddddddddd") == PSDP_TRUE);
  CU_ASSERT(sdp.media[3].k.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].k, "88888888888888888888") == PSDP_TRUE);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg3, strlen(sdp_msg3));
  CU_ASSERT(sdp.num_m == 4);
  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[0].k.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].k, "iiiiiiiiiiiiiiiiiiii") == PSDP_TRUE);

  CU_ASSERT(sdp.media[1].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].m, "aaaaaaaaaaaaaaaaaaaa") == PSDP_TRUE);
  CU_ASSERT(sdp.media[1].k.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].k, "aiaiaiaiaiaiaiaiaiai") == PSDP_TRUE);

  CU_ASSERT(sdp.media[2].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].m, "cccccccccccccccccccc") == PSDP_TRUE);
  CU_ASSERT(sdp.media[2].k.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].k, "77777777777777777777") == PSDP_TRUE);

  CU_ASSERT(sdp.media[3].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].m, "dddddddddddddddddddd") == PSDP_TRUE);
  CU_ASSERT(sdp.media[3].k.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].k, "88888888888888888888") == PSDP_TRUE);
}

static void
psdp_test_m_a(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;

  static const char*    sdp_msg1 = \
  "m=12345678901234567890\r\n" \
  ;

  static const char*    sdp_msg2 = \
  "m=12345678901234567890\r\n" \
  "a=b1b1b1b1b1b1b1b1b1b1\r\n" \
  "m=aaaaaaaaaaaaaaaaaaaa\r\n" \
  "a=b1b1b1b1b1b1b1b1b1b1\r\n" \
  "a=b2b2b2b2b2b2b2b2b2b2\r\n" \
  "m=mmmmmmmmmmmmmmmmmmmm\r\n" \
  "a=b1b1b1b1b1b1b1b1b1b1\r\n" \
  "a=b2b2b2b2b2b2b2b2b2b2\r\n" \
  "a=b3b3b3b3b3b3b3b3b3b3\r\n" \
  "m=nnnnnnnnnnnnnnnnnnnn\r\n" \
  "a=b1b1b1b1b1b1b1b1b1b1\r\n" \
  "a=b2b2b2b2b2b2b2b2b2b2\r\n" \
  "a=b3b3b3b3b3b3b3b3b3b3\r\n" \
  "a=b4b4b4b4b4b4b4b4b4b4\r\n" \
  "a=not ignored\r\n" \
  "m=ignored\r\n" \
  "a=ignored\r\n"
  ;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));
  CU_ASSERT(sdp.num_m == 1);
  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[0].num_a == 0);

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg2, strlen(sdp_msg2));
  CU_ASSERT(sdp.num_m == 4);

  CU_ASSERT(sdp.media[0].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "12345678901234567890") == PSDP_TRUE);
  CU_ASSERT(sdp.media[0].num_a == 1);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].a[0], "b1b1b1b1b1b1b1b1b1b1") == PSDP_TRUE);

  CU_ASSERT(sdp.media[1].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].m, "aaaaaaaaaaaaaaaaaaaa") == PSDP_TRUE);
  CU_ASSERT(sdp.media[1].num_a == 2);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].a[0], "b1b1b1b1b1b1b1b1b1b1") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].a[1], "b2b2b2b2b2b2b2b2b2b2") == PSDP_TRUE);

  CU_ASSERT(sdp.media[2].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].m, "mmmmmmmmmmmmmmmmmmmm") == PSDP_TRUE);
  CU_ASSERT(sdp.media[2].num_a == 3);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].a[0], "b1b1b1b1b1b1b1b1b1b1") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].a[1], "b2b2b2b2b2b2b2b2b2b2") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[2].a[2], "b3b3b3b3b3b3b3b3b3b3") == PSDP_TRUE);

  CU_ASSERT(sdp.media[3].m.val_len == 20);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].m, "nnnnnnnnnnnnnnnnnnnn") == PSDP_TRUE);
  CU_ASSERT(sdp.media[3].num_a == 5);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].a[0], "b1b1b1b1b1b1b1b1b1b1") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].a[1], "b2b2b2b2b2b2b2b2b2b2") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].a[2], "b3b3b3b3b3b3b3b3b3b3") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].a[3], "b4b4b4b4b4b4b4b4b4b4") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[3].a[4], "not ignored") == PSDP_TRUE);
}

static void
psdp_test_overflow(void)
{
  static const char*    sdp_msg1 = \
  "b=1\r\n" \
  "b=2\r\n" \
  "b=3\r\n" \
  "b=4\r\n" \
  "b=5\r\n" \
  "b=6\r\n" \
  "b=7\r\n" \
  "b=8\r\n" \
  "b=9-ignored\r\n"   \
  "b=10-ignored\r\n"  \
  "a=1\r\n" \
  "a=2\r\n" \
  "a=3\r\n" \
  "a=4\r\n" \
  "a=5\r\n" \
  "a=6\r\n" \
  "a=7\r\n" \
  "a=8\r\n" \
  "a=9-ignored\r\n" \
  "a=10-ignored\r\n" \
  "m=1234\r\n" \
  "b=1\r\n" \
  "b=2\r\n" \
  "b=3\r\n" \
  "b=4\r\n" \
  "b=5\r\n" \
  "b=6\r\n" \
  "b=7\r\n" \
  "b=8\r\n" \
  "b=9-ignored\r\n" \
  "b=10-ignored\r\n" \
  "a=1\r\n" \
  "a=2\r\n" \
  "a=3\r\n" \
  "a=4\r\n" \
  "a=5\r\n" \
  "a=6\r\n" \
  "a=7\r\n" \
  "a=8\r\n" \
  "a=9-ignored\r\n" \
  "a=10-ignored";

  const char* pattern[] =  {"1", "2", "3", "4", "5", "6", "7", "8" };

  psdp_parser_t   parser;
  psdp_t          sdp;

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg1, strlen(sdp_msg1));

  CU_ASSERT(sdp.num_b == 8);
  CU_ASSERT(sdp.num_a == 8);
  CU_ASSERT(sdp.num_m == 1);
  CU_ASSERT(sdp.media[0].num_b == 8);
  CU_ASSERT(sdp.media[0].num_a == 8);

  for(int i = 0; i < 8; i++)
  {
    CU_ASSERT(psdp_str_cmp(&sdp.b[i], pattern[i]) == PSDP_TRUE);
    CU_ASSERT(psdp_str_cmp(&sdp.a[i], pattern[i]) == PSDP_TRUE);
    CU_ASSERT(psdp_str_cmp(&sdp.media[0].b[i], pattern[i]) == PSDP_TRUE);
    CU_ASSERT(psdp_str_cmp(&sdp.media[0].a[i], pattern[i]) == PSDP_TRUE);
  }
}

static void
psdp_test_total_1(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;

  const static char*    sdp_msg = \
"v=0\r\n" \
"o=- 123456 11 IN IP4 192.168.100.2\r\n" \
"s=Example of a SMPTE ST2110-20 signal\r\n" \
"i=this example is for 720p video at 59.94\r\n" \
"t=0 0\r\n" \
"a=recvonly\r\n" \
"a=group:DUP primary secondary\r\n" \
"m=video 50000 RTP/AVP 112\r\n" \
"c=IN IP4 239.100.9.10/32\r\n" \
"a=source-filter:incl IN IP4 239.100.9.10 192.168.100.2\r\n" \
"a=rtpmap:112 raw/90000\r\n" \
"a=fmtp:112 sampling=YCbCr-4:2:2; width=1280; height=720; exactframerate=60000/1001; depth=10; TCS=SDR; colorimetry=BT709; PM=2110GPM; TP=2110TPN; SSN=ST2110-20:2017;\r\n"\
"a=ts-refclk:ptp=IEEE1588-2008:39-A7-94-FF-FE-07-CB-D0:37\r\n" \
"a=mediaclk:direct=0\r\n" \
"a=mid:primary\r\n" \
"m=video 50020 RTP/AVP 112\r\n" \
"c=IN IP4 239.101.9.10/32\r\n" \
"a=source-filter:incl IN IP4 239.101.9.10 192.168.101.2\r\n" \
"a=rtpmap:112 raw/90000\r\n" \
"a=fmtp:112 sampling=YCbCr-4:2:2; width=1280; height=720; exactframerate=60000/1001; depth=10; TCS=SDR; colorimetry=BT709; PM=2110GPM; TP=2110TPN; SSN=ST2110-20:2017;\r\n" \
"a=ts-refclk:ptp=IEEE1588-2008:39-A7-94-FF-FE-07-CB-D0:37\r\n" \
"a=mediaclk:direct=0\r\n" \
"a=mid:secondary\r\n";

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg, strlen(sdp_msg));
  CU_ASSERT(psdp_str_cmp(&sdp.v, "0") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.o, "- 123456 11 IN IP4 192.168.100.2") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.s, "Example of a SMPTE ST2110-20 signal") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.i, "this example is for 720p video at 59.94") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.t, "0 0") == PSDP_TRUE);
  CU_ASSERT(sdp.num_a == 2);
  CU_ASSERT(psdp_str_cmp(&sdp.a[0], "recvonly") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.a[1], "group:DUP primary secondary") == PSDP_TRUE);

  CU_ASSERT(sdp.num_m == 2);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "video 50000 RTP/AVP 112") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].c, "IN IP4 239.100.9.10/32") == PSDP_TRUE);

  CU_ASSERT(sdp.media[0].num_a == 6);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].a[0], "source-filter:incl IN IP4 239.100.9.10 192.168.100.2") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].a[1], "rtpmap:112 raw/90000") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].a[2], "fmtp:112 sampling=YCbCr-4:2:2; width=1280; height=720; exactframerate=60000/1001; depth=10; TCS=SDR; colorimetry=BT709; PM=2110GPM; TP=2110TPN; SSN=ST2110-20:2017;") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].a[3], "ts-refclk:ptp=IEEE1588-2008:39-A7-94-FF-FE-07-CB-D0:37") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].a[4], "mediaclk:direct=0") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].a[5], "mid:primary") == PSDP_TRUE);

  CU_ASSERT(psdp_str_cmp(&sdp.media[1].m, "video 50020 RTP/AVP 112") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].c, "IN IP4 239.101.9.10/32") == PSDP_TRUE);

  CU_ASSERT(sdp.media[1].num_a == 6);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].a[0], "source-filter:incl IN IP4 239.101.9.10 192.168.101.2") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].a[1], "rtpmap:112 raw/90000") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].a[2], "fmtp:112 sampling=YCbCr-4:2:2; width=1280; height=720; exactframerate=60000/1001; depth=10; TCS=SDR; colorimetry=BT709; PM=2110GPM; TP=2110TPN; SSN=ST2110-20:2017;") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].a[3], "ts-refclk:ptp=IEEE1588-2008:39-A7-94-FF-FE-07-CB-D0:37") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].a[4], "mediaclk:direct=0") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].a[5], "mid:secondary") == PSDP_TRUE);

}

static void
psdp_test_unknown(void)
{
  psdp_parser_t   parser;
  psdp_t          sdp;

  const static char*    sdp_msg = \
"  1231\r\n"
"v=0\r\n" \
"A=unknown unkown\n"
"o=- 123456 11 IN IP4 192.168.100.2\r\n" \
"s=Example of a SMPTE ST2110-20 signal\r\n" \
"i=this example is for 720p video at 59.94\r\n" \
"\r\n" \
"\r\n" \
"\r\n" \
"\r\n" \
"t=0 0\r\n" \
"a=recvonly\r\n" \
"a=group:DUP primary secondary\r\n" \
"m=video 50000 RTP/AVP 112\r\n" \
"\r\n" \
"MM\r\n"\
"c=IN IP4 239.100.9.10/32\r\n" \
"a=source-filter:incl IN IP4 239.100.9.10 192.168.100.2\r\n" \
"a=rtpmap:112 raw/90000\r\n" \
"a=fmtp:112 sampling=YCbCr-4:2:2; width=1280; height=720; exactframerate=60000/1001; depth=10; TCS=SDR; colorimetry=BT709; PM=2110GPM; TP=2110TPN; SSN=ST2110-20:2017;\r\n"\
"a=ts-refclk:ptp=IEEE1588-2008:39-A7-94-FF-FE-07-CB-D0:37\r\n" \
"a=mediaclk:direct=0\r\n" \
"Z=another unknown\r\n"\
"a=mid:primary\r\n" \
"m=video 50020 RTP/AVP 112\r\n" \
"c=IN IP4 239.101.9.10/32\r\n" \
"a=source-filter:incl IN IP4 239.101.9.10 192.168.101.2\r\n" \
"\n" \
"Z=wacky\r\n"\
"\n" \
"a=rtpmap:112 raw/90000\r\n" \
"\n" \
"a=fmtp:112 sampling=YCbCr-4:2:2; width=1280; height=720; exactframerate=60000/1001; depth=10; TCS=SDR; colorimetry=BT709; PM=2110GPM; TP=2110TPN; SSN=ST2110-20:2017;\r\n" \
"\n" \
"a=ts-refclk:ptp=IEEE1588-2008:39-A7-94-FF-FE-07-CB-D0:37\r\n" \
"\n" \
"a=mediaclk:direct=0\r\n" \
"a=mid:secondary\r\n" \
"                   \r\n";

  psdp_parse(&parser, &sdp, (uint8_t*)sdp_msg, strlen(sdp_msg));
  CU_ASSERT(psdp_str_cmp(&sdp.v, "0") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.o, "- 123456 11 IN IP4 192.168.100.2") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.s, "Example of a SMPTE ST2110-20 signal") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.i, "this example is for 720p video at 59.94") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.t, "0 0") == PSDP_TRUE);
  CU_ASSERT(sdp.num_a == 2);
  CU_ASSERT(psdp_str_cmp(&sdp.a[0], "recvonly") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.a[1], "group:DUP primary secondary") == PSDP_TRUE);

  CU_ASSERT(sdp.num_m == 2);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].m, "video 50000 RTP/AVP 112") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].c, "IN IP4 239.100.9.10/32") == PSDP_TRUE);

  CU_ASSERT(sdp.media[0].num_a == 6);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].a[0], "source-filter:incl IN IP4 239.100.9.10 192.168.100.2") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].a[1], "rtpmap:112 raw/90000") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].a[2], "fmtp:112 sampling=YCbCr-4:2:2; width=1280; height=720; exactframerate=60000/1001; depth=10; TCS=SDR; colorimetry=BT709; PM=2110GPM; TP=2110TPN; SSN=ST2110-20:2017;") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].a[3], "ts-refclk:ptp=IEEE1588-2008:39-A7-94-FF-FE-07-CB-D0:37") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].a[4], "mediaclk:direct=0") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[0].a[5], "mid:primary") == PSDP_TRUE);

  CU_ASSERT(psdp_str_cmp(&sdp.media[1].m, "video 50020 RTP/AVP 112") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].c, "IN IP4 239.101.9.10/32") == PSDP_TRUE);

  CU_ASSERT(sdp.media[1].num_a == 6);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].a[0], "source-filter:incl IN IP4 239.101.9.10 192.168.101.2") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].a[1], "rtpmap:112 raw/90000") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].a[2], "fmtp:112 sampling=YCbCr-4:2:2; width=1280; height=720; exactframerate=60000/1001; depth=10; TCS=SDR; colorimetry=BT709; PM=2110GPM; TP=2110TPN; SSN=ST2110-20:2017;") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].a[3], "ts-refclk:ptp=IEEE1588-2008:39-A7-94-FF-FE-07-CB-D0:37") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].a[4], "mediaclk:direct=0") == PSDP_TRUE);
  CU_ASSERT(psdp_str_cmp(&sdp.media[1].a[5], "mid:secondary") == PSDP_TRUE);
}

int
main()
{
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("Suite_success", init_suite_success, clean_suite_success);

  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_add_test(pSuite, "psdp_test_v", psdp_test_v);
  CU_add_test(pSuite, "psdp_test_o", psdp_test_o);
  CU_add_test(pSuite, "psdp_test_s", psdp_test_s);
  CU_add_test(pSuite, "psdp_test_i", psdp_test_i);
  CU_add_test(pSuite, "psdp_test_u", psdp_test_u);
  CU_add_test(pSuite, "psdp_test_e", psdp_test_e);
  CU_add_test(pSuite, "psdp_test_p", psdp_test_p);
  CU_add_test(pSuite, "psdp_test_c", psdp_test_c);
  CU_add_test(pSuite, "psdp_test_b", psdp_test_b);
  CU_add_test(pSuite, "psdp_test_z", psdp_test_z);
  CU_add_test(pSuite, "psdp_test_k", psdp_test_k);
  CU_add_test(pSuite, "psdp_test_a", psdp_test_a);
  CU_add_test(pSuite, "psdp_test_m", psdp_test_m);
  CU_add_test(pSuite, "psdp_test_m_i", psdp_test_m_i);
  CU_add_test(pSuite, "psdp_test_m_c", psdp_test_m_c);
  CU_add_test(pSuite, "psdp_test_m_b", psdp_test_m_b);
  CU_add_test(pSuite, "psdp_test_m_k", psdp_test_m_k);
  CU_add_test(pSuite, "psdp_test_m_a", psdp_test_m_a);
  CU_add_test(pSuite, "psdp_test_overflow", psdp_test_overflow);
  CU_add_test(pSuite, "psdp_test_total_1", psdp_test_total_1);
  CU_add_test(pSuite, "psdp_test_unknown", psdp_test_unknown);

  /* Run all tests using the basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  printf("\n");
  CU_basic_show_failures(CU_get_failure_list());
  printf("\n\n");

  /* Clean up registry and return */
  CU_cleanup_registry();
  return CU_get_error();
}
