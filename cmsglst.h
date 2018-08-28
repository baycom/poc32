class CMsg
{
public:

  time_t m_time;
  DWORD m_type;
  DWORD m_bitrate;
  DWORD m_adr;
  DWORD m_fct;
  DWORD m_func;
  BOOL m_displayed;
  CString m_msg;
/*		
		const CMsg& operator=(const CMsg& m)
		{
			m_adr=m.m_adr;
			m_fct=m.m_fct;
			m_func=m.m_func;
			m_type=m.m_type;
			m_msg=m.m_msg;
			return *this;
		}
*/
};
typedef CArray < CMsg, CMsg & >CMsgList;
