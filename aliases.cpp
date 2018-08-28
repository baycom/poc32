// Aliases.cpp: implementation of the CAliases class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pex32.h"
#include "Aliases.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAliases::CAliases ()
{

}

CAliases::~CAliases ()
{

}

CString CAliases::LookupAlias (int addr)
{
  int
    i;
  int
    max = m_al.GetSize ();

  m_a.m_alias.Empty ();
  m_a.m_programname.Empty ();

  for (i = 0; i < max; i++)
    if (m_al[i].m_adr == addr) {
      m_a = m_al[i];
      return m_a.m_alias;
    }

  m_a.m_adr = addr;
  return CString ("");
}

CString CAliases::LookupProgramname (int addr)
{
  int
    i;
  int
    max = m_al.GetSize ();
  m_a.m_alias.Empty ();
  m_a.m_programname.Empty ();
  for (i = 0; i < max; i++)
    if (m_al[i].m_adr == addr) {
      m_a = m_al[i];
      return m_a.m_programname;
    }
  m_a.m_adr = addr;
  return CString ("");
}

void
CAliases::AddAlias (int addr, CString str)
{
  CAlias a;
  if (str.IsEmpty ())
    return;

  a.m_adr = addr;
  a.m_alias = str;
  a.m_protocol = 0;

  m_al.Add (a);
}

void
CAliases::AddAlias (CAlias & a)
{
  if (a.m_adr && !a.m_alias.IsEmpty ())
    m_al.Add (a);
}

void
CAliases::DelAlias (int addr)
{
  int i;
  for (i = 0; i < m_al.GetSize (); i++)
    if (m_al[i].m_adr == addr) {
      m_al.RemoveAt (i);
      i--;
    }
  return;
}

BOOL CAliases::LoadAliases (CString filename)
{
  CAlias
    a;

  m_al.RemoveAll ();

  FILE *
    f = fopen (filename, "rt");
  if (f == NULL)
    return FALSE;

  char
    line[256];

  while (!feof (f)) {
    if (fgets (line, sizeof (line), f) == NULL)
      break;
    char *
      s = strtok (line, "\t");
    a.m_alias.Empty ();
    a.m_programname.Empty ();
    a.m_adr = atoi (line);
    if ((s = strtok (NULL, "\t")) && strlen (s)) {
      sscanf (s, "%d", &a.m_protocol);
      if (s = strtok (NULL, "\t")) {
	int
	  i;
	a.m_alias = s;
	while ((i = a.m_alias.FindOneOf ("\r\n")) != -1)
	  a.m_alias.SetAt (i, 0);
      }
      if ((s = strtok (NULL, "\t")) && strlen (s) > 1) {
	int
	  i;
	a.m_programname = s;
	while ((i = a.m_programname.FindOneOf ("\r\n")) != -1)
	  a.m_programname.SetAt (i, 0);
      }
    }
    AddAlias (a);
  }
  fclose (f);
  return TRUE;

}

BOOL CAliases::SaveAliases (CString filename)
{
  int
    i;
  FILE *
    f = fopen (filename, "wt");
  if (f == NULL)
    return FALSE;

  int
    max = m_al.GetSize ();
  for (i = 0; i < max; i++)
    if (m_al[i].m_adr && !m_al[i].m_alias.IsEmpty ())
      fprintf (f, "%d\t%d\t%s\t%s\n", m_al[i].m_adr, m_al[i].m_protocol,
	       m_al[i].m_alias, m_al[i].m_programname);

  fclose (f);
  return FALSE;
}
