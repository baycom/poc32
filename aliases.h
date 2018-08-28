// Aliases.h: interface for the CAliases class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALIASES_H__997A1E51_CBA9_11D1_B577_0000CB280102__INCLUDED_)
#define AFX_ALIASES_H__997A1E51_CBA9_11D1_B577_0000CB280102__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
class CAlias
{
public:
  int m_adr;
  int m_protocol;
  CString m_alias;
  CString m_programname;
};
typedef CArray < CAlias, CAlias & >CAliasList;

class CAliases:public CObject
{
public:
  CAliases ();
  virtual ~ CAliases ();
  CString LookupAlias (int addr);
  CString LookupProgramname (int addr);
  void AddAlias (int addr, CString str);
  void AddAlias (CAlias & a);
  void DelAlias (int addr);
  BOOL LoadAliases (CString filename);
  BOOL SaveAliases (CString filename);
  CAlias m_a;
protected:
    CAliasList m_al;
};

#endif // !defined(AFX_ALIASES_H__997A1E51_CBA9_11D1_B577_0000CB280102__INCLUDED_)
