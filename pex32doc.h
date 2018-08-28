// pex32Doc.h : interface of the CPex32Doc class
//
/////////////////////////////////////////////////////////////////////////////
#include "TxDialog.h"
#include "CMsgLst.h"

// CPocInterface thread
#define _BUFMAX 32
#define _BUFLEN 2048

#define _MAXMSGLEN 4096

#define DCD_MOSTNEGATIVE -30
#define DCD_MOSTPOSITIVE 30
#define DCD_POSTHRESHOLD 10
#define DCD_NEGTHRESHOLD 10
#define DCD_POSCHANGE 1
#define DCD_NEGCHANGE 2
//#define DCD_TOLERANCE 0x2000
#define DCD_TOLERANCE 0x4000

struct pocsag_rx
{
  unsigned int ph_update;
  unsigned long phase;
  int dcd;
  int channel;
  unsigned char last_sample;
  unsigned char rx_sync;
  unsigned char rx_word;
  unsigned char rx_bit;
  unsigned long rx_data;

  short filter[16];
  batch_t b;
};

typedef struct pocsag_rx pocsag_rx_t;

class CPex32Doc:public CDocument
{
protected:			// create from serialization only
  CPex32Doc ();
  DECLARE_DYNCREATE (CPex32Doc)
  CMainFrame *m_mainfrm;
  time_t m_last_saved;
  CString m_lastlistname;
  CListenSocket *m_pListen;
// Attributes
public:
    CMsgList m_msg;
  CTxDialog m_txdlg;
  CString m_srvstr[5];
  CString m_bitstr[3];
  CString m_funcstr[3];
  CString m_source[3];
  CSet m_s;
  CSetGeneral m_sg;
  int m_colwidth[8];
  CString m_tblname;
  CString m_homedir;
  CFont m_f;
  LOGFONT m_lf;
  CAliases m_alias;

  HWAVEIN m_WavIn;
  HANDLE m_hCVxD;

  LPSTR m_DataBuf[_BUFMAX];
  BOOL m_Alloctable[_BUFMAX];
  BOOL m_enablesound;
  BOOL m_8bps;

  pocsag_rx_t m_rx_512l, m_rx_1200l, m_rx_2400l,
    m_rx_512r, m_rx_1200r, m_rx_2400r;

  int m_srate;
  int m_medleftch;
  int m_medrightch;
  int m_buferr;
  int m_msgerr;
  int m_msgrx;
  int m_hyst;

  CString m_transtbl[FILENAME_MAX];

  time_t m_timespan;
  //---   POCSAG.C Insertion
  int m_verbose_level;
  unsigned char m_invert_rx;
  unsigned char m_service_mask;
  unsigned char m_baudrate_mask;
  unsigned char m_do_filter;
  unsigned char m_correct_bits;

  void GetPrefs (void);
  void SetPrefs (void);
  char txtbl (char c);
  BOOL InitSerial (void);
  BOOL InitHardware (void);
  BOOL InitWavIn (BOOL state);
  BOOL poc_getsnddcd (void);
  WORD poc_getdcd (void);
  WORD poc_getready (void);
  WORD poc_getptt (void);
  void poc_setrx (void);
  void poc_setmode (WORD baud, WORD txdel, WORD inv, WORD deb,
		    DWORD syncword);
  WORD poc_config (config_t * buf);
  WORD poc_startirq (txbatch_t * b);
  WORD poc_getversion (void);
  WORD poc_getstate (void);
  WORD poc_activate (WORD buf);
  unsigned bitrate (unsigned u);
  unsigned long crc (unsigned long data);
  int poc_beep (unsigned baud, unsigned long adr, unsigned function);
  int poc_numerik (unsigned baud, unsigned long adr, unsigned function,
		   CString & s);
  int poc_alphanum (unsigned baud, unsigned long adr, unsigned function,
		    CString & s);

  BOOL LoadTransTbl (CString filename);
  void OnTimer (UINT nIDEvent);
  LONG OnNewWavData (UINT wParam, LONG lParam);

  BOOL m_shareware;
protected:
    CMyMessageBox * m_mmb;

  // Operations
public:
  void AddToList (CMsg & m);
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CPex32Doc)
public:
    virtual BOOL OnNewDocument ();
  virtual void Serialize (CArchive & ar);
  virtual BOOL OnOpenDocument (LPCTSTR lpszPathName);
  //}}AFX_VIRTUAL

// Implementation
public:
  void datetimestr (LPTSTR Buf, int BufSize, time_t & unixtime);
  CString CPex32Doc::GetExeDir();
  BOOL OnShutdown ();
  BOOL OnStartup ();
  void StopListening (void);
  BOOL StartListening (void);
    virtual ~ CPex32Doc ();
#ifdef _DEBUG
  virtual void AssertValid () const;
  virtual void Dump (CDumpContext & dc) const;
#endif

protected:
  void AddBuffer (void);
  void xprintf (int verb_level, const char *fmt, ...);
  inline unsigned char even_parity (unsigned long data);
  void do_one_rxbit (pocsag_rx_t * rx, unsigned char rxbit);
  inline void do_one_demodulator (pocsag_rx_t * rx,
				  unsigned char this_sample);
  inline void do_one_filter (pocsag_rx_t * rx, const char coeffs[],
			     short sample);
  void demodulator (LPSTR sound_buffer);
  BOOL GetBit (int val, BOOL ch);
  unsigned int pocsag_syndrome (unsigned long data);
  unsigned int pocsag_correct (unsigned long *data);
//-----------------
  int open_device (void);
  void close_device (void);
  void poc_copyrxb (batch_t * buf);
  WORD poc_getpnp (void);
  void five2text (unsigned long d, char *msg, BOOL & bad);
  int num2text (unsigned long *t, int imax, char *msg, BOOL & bad);
  int getbit (unsigned long *s, unsigned bit);
  char num2char (unsigned long *s, unsigned ch);
  int str2text (unsigned long *t, int imax, char *out, BOOL mode);
  void decode_msg (pocsag_rx_t * rx);

  unsigned long getword (char *s, unsigned word);
  int getbit (char *s, unsigned bit);
  unsigned long fivetol (char *s);
  void idlefill (unsigned long *b, unsigned len);
  int poc_checkdata (unsigned baud, unsigned long *d, int len);
  void CyclicUpdate (void);

// Generated message map functions
protected:
  //{{AFX_MSG(CPex32Doc)
  // NOTE - the ClassWizard will add and remove member functions here.
  //    DO NOT EDIT what you see in these blocks of generated code !
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()
};

/////////////////////////////////////////////////////////////////////////////
