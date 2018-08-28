class CPex32Doc;

class CListenSocket:public CAsyncSocket
{
  DECLARE_DYNCREATE (CListenSocket)
  CListenSocket (void);
public:
    CListenSocket (CPex32Doc * pDoc);
protected:
    CPex32Doc * m_pDoc;
  virtual void OnAccept (int nErrorCode);
};
