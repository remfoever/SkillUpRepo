#ifndef TYPEDEF_H
#define TYPEDEF_H
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define STRING_SIZE 32
#define WX_MODBUS_IPV6_SIZE 16
/*
 * basic data type typedef for better compatibility
 */
typedef uint8_t UINT8;      /**< unsigned 8-bit */
typedef char INT8;          /**< signed 8-bit */
typedef char CHAR;          /**< signed 8-bit */
typedef uint16_t UINT16;    /**< unsigned 16-bit */
typedef short INT16;        /**< signed 16-bit */
typedef uint32_t UINT32;    /**< unsigned 32-bit */
typedef int INT32;          /**< signed 32-bit */
typedef float FLOAT32;      /**< 32-bit floating point */
typedef double FLOAT64;     /**< 64-bit double precision FP */
typedef unsigned char BOOL; /**< boolean (XTRUE or XFALSE) */
typedef unsigned long long UINT64;
typedef void VOID;

#define INLINE static __inline__
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
/*
 * basic macro define
 */
#define U64_MAX (0XFFFFFFFFFFFFFFFF)
#define U32_MAX (0xFFFFFFFF)
#define U16_MAX (0xFFFF)
#define U8_MAX (0xFF)

#define MS_PER_SEC (1000)
#define US_PER_MS (1000)
#define MS (1)
#define SECOND (1000 * MS)
#define MINUTE (60 * SECOND)
#define HOUR (60 * MINUTE)
#define DAY (24 * HOUR)
#define WEEK (7 * DAY)

#define KBYTE (1024)
#define MBYTE (1024*1024)
#define GBYTE (1024*1024*1024)
#define INVALID_DEVICE_ID U32_MAX
/* the msg header the head is 8 bytes pleace keep 8 byte align */
/* the msg header the head is 8 bytes pleace keep 8 byte align */
#define INHERIT_MSG_HEADER                                                                      \
    UINT8 sender;        /* message sender ID, see WxModuleId */                                   \
    UINT8 receiver;      /* message receiver ID, see WxModuleId */                                 \
    UINT8 isFromISR : 1; /* is ISR malloc the message, 1-yes, 0-no */                              \
    UINT8 resv : 7;      /* resv bit */                                                            \
    UINT8 magicKey;      /* message maigc key, used for check data: 0x55 */                        \
    UINT16 msgType;      /* message type, see WxMsgType */                                         \
    UINT16 subMsgType;   /* sub message type */

#endif
