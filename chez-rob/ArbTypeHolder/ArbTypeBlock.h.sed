#ifndef CCA_@@TypeName@@BLOCKH
#define CCA_@@TypeName@@BLOCKH

/** Arbitrary typed block data. 
*/
class CCA_@@TypeName@@Block : public virtual CCA_Block {
private:
  @@Type@@ *master;
  @@Type@@ *data;
  @@Type@@ **stack;
  @@Type@@ bmagic;
  @@Type@@ emagic;
  CCA_BlockDescription *bd_;
  int msize;

public:

  CCA_@@TypeName@@Block(CCA_BlockDescription *bd) ;

  virtual ~CCA_@@TypeName@@Block() ;

  virtual CCA_BlockDescription *getDescription() ;

  virtual @@Type@@ *getData() ;

 private:
  int isEndMagicNumberOK(@@Type@@ magicTest);

};

#endif // CCA_@@TypeName@@BLOCKH
