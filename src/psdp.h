#ifndef __PSDP_DEF_H__
#define __PSDP_DEF_H__

#include <stdint.h>
#include <string.h>

#define PSDP_TRUE                   1
#define PSDP_FALSE                  0

#define PSDP_MAX_BANDWIDTH_INFO     8
#define PSDP_MAX_SESSION_ATTR       8
#define PSDP_MAX_MEDIA              4

typedef struct
{
  uint8_t*            val;
  uint32_t            val_len;
} psdp_str;

typedef struct
{
  psdp_str            m;      // media name and transport address
  psdp_str            i;      // media title
  psdp_str            c;      // connection information

  // zero or more bandwidth information lines
  uint32_t            num_b;
  psdp_str            b[PSDP_MAX_BANDWIDTH_INFO];      

  psdp_str            k;      // encryption key

  // zero or more session attribute lines
  uint32_t            num_a;
  psdp_str            a[PSDP_MAX_SESSION_ATTR];
} psdp_media_desc_t;

typedef struct
{
  psdp_str            v;      // protocol version
  psdp_str            o;      // originator and session identifier
  psdp_str            s;      // session name
  psdp_str            i;      // session information
  psdp_str            u;      // URI of description
  psdp_str            e;      // email address
  psdp_str            p;      // phone number
  psdp_str            c;      // connection information

  // zero or more bandwidth information lines
  uint32_t            num_b;
  psdp_str            b[PSDP_MAX_BANDWIDTH_INFO];      

  psdp_str            z;      // time zone adjustments
  psdp_str            k;      // encryption key

  // zero or more session attribute lines
  uint32_t            num_a;
  psdp_str            a[PSDP_MAX_SESSION_ATTR];

  psdp_str            t;      // time the session is active
  psdp_str            r;      // zero or more repeat times

  uint32_t            num_m;
  psdp_media_desc_t   media[PSDP_MAX_MEDIA];
} psdp_t;

typedef struct
{
  uint32_t            ndx;
  uint32_t            msg_len;
  uint8_t*            msg;
  uint8_t             parsing_session;
  psdp_media_desc_t*  cm;               // current media descriptor if valid, NULL if not
} psdp_parser_t;

extern void psdp_parse(psdp_parser_t* parser, psdp_t* psdp, uint8_t* sdp_msg, uint32_t sdp_msg_len);

static inline uint8_t
psdp_str_cmp(psdp_str* psdp_str, const char* str)
{
  int l = strlen(str);

  if(l != psdp_str->val_len)
  {
    return PSDP_FALSE;
  }

  if(strncmp((char*)psdp_str->val, str, l) == 0)
  {
    return PSDP_TRUE;
  }

  return PSDP_FALSE;
}

#endif /* !__PSDP_DEF_H__ */
