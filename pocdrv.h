#define _RX 1
#define _TX 0

#define _SYNC 0x7cd215d8L
#define _SYNCINFO 0x7cf21436L
#define _IDLE 0x7a89c197L

//-------------
#define QUIX    0
#define TMOBIL  1
#define TELMI   2
#define UNKNOWN 3
#define OWNMSG  4

#define _MAXBATCHES 16384
#define _MAXTXBATCHES 20

#define TMOBILSTR "TMOBIL"
#define TELMISTR  "TELMI"
#define QUIXSTR   "QUIX"

#define ALPHASTR "Alpha"
#define NUMSTR   "Num"
#define BEEPSTR  "Beep"
#define BEEP  0
#define NUM   1
#define ALPHA 2
#define AUTO  3
//--------------
#define VERSION 0x1b

#ifndef WANTVXDWRAPS
enum
{ api_debug = 1, api_getdcd, api_getready, api_getptt, api_startirq,
  api_setrx, api_setmode, api_copyrxb, api_config, api_getstate,
  api_getversion, api_activate, api_getpnp
};
#endif
typedef struct
{
  WORD port;
  WORD irq;
  WORD correct_bits;
} config_t;
typedef struct
{
  WORD baud, txdel, inv, deb;
  DWORD syncword;
} pocfg_t;
typedef struct
{
  DWORD b[_MAXBATCHES];
  WORD p;
  WORD br;
} batch_t;
typedef struct
{
  DWORD b[_MAXTXBATCHES][16];
  DWORD baud;
} txbatch_t;

void poc_setmode (pocfg_t * cfg);
WORD poc_getptt (void);
WORD poc_getready (void);
WORD poc_getdcd (void);
WORD poc_activate (WORD state);
WORD poc_config (config_t * cfg);
void poc_copyrxb (batch_t * buf);
WORD poc_startirq (txbatch_t * b);
void poc_setrx (void);
WORD poc_getstate (void);
