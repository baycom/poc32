#define LMAX   260
#define PMAX   200
#define CHAR   1
#define BOL    2
#define EOL    3
#define ANY    4
#define CLASS  5
#define NCLASS 6
#define STAR   7
#define PLUS   8
#define RANGE  9
#define REGEX  10
#define QUICK  11
#define CASESENSE 12
#define TOUPPER   13
#define ENDPAT    14

typedef unsigned long bitfeld;
// Bits fuer die Optionen
//             
#define o_a (0x00000001L)
#define o_b (0x00000002L)
#define o_c (0x00000004L)
#define o_d (0x00000008L)
#define o_e (0x00000010L)
#define o_f (0x00000020L)
#define o_g (0x00000040L)
#define o_h (0x00000080L)
#define o_i (0x00000100L)
#define o_j (0x00000200L)
#define o_k (0x00000400L)
#define o_l (0x00000800L)
#define o_m (0x00001000L)
#define o_n (0x00002000L)
#define o_o (0x00004000L)
#define o_p (0x00008000L)
#define o_q (0x00010000L)
#define o_r (0x00020000L)
#define o_s (0x00040000L)
#define o_t (0x00080000L)
#define o_u (0x00100000L)
#define o_v (0x00200000L)
#define o_w (0x00400000L)
#define o_x (0x00800000L)
#define o_y (0x01000000L)
#define o_z (0x02000000L)

/*---------------------------------------------------------------------------*/
class CRegEx
{
public:
  int regex_compile (char *source);
  int grepfile (FILE * fp);
  int regex_match (char *line);
  int regex_match (char *pattern, char *line);
    CRegEx ();
  char m_pattern[PMAX];
  bitfeld m_options;

private:
  char *pmatch (char *begin, char *line, char *pattern);
};
