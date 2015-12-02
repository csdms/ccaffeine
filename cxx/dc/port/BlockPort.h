#ifndef BlockPort_seen
#define BlockPort_seen

//requires
//#include "CCA_Block.h"
/* interface */

/** BlockPort for use in applications exchanging data via
    contiguous blocks
    @author Ben Allan, 11/04/1999, Sandia National Laboratories.
    @version $Id: BlockPort.h,v 1.9 2004/10/16 05:53:21 baallan Exp $
 */
class BlockPort 
#ifdef HAVE_CLASSIC
: public virtual classic::gov::cca::Port
#endif // HAVE_CLASSIC
{

  public:

  BlockPort() 
#ifdef HAVE_CLASSIC
	  : classic::gov::cca::Port()
#endif
	  {}
    virtual ~BlockPort(){}

      /** Request that the owner of the vector do whatever it does
       to recompute the vector associated with this port.
       (This may be a NOP).  Ben wants this to go away. */
    virtual void compute() =0;

      /** Tell the owner of the vector that you have done something
       to the data in the vector associated with this port.  Freshen the dirty data.
       (This may be a NOP). */
    virtual void update() =0;

      /** Sets the minimum overlap needed when answering a future request
      /// for the CCA_Block. The request is known by its pointer, so
      /// in your code e.g.
        | class foo {
        |   private: CCA_Block *myBlock; ...
        |   func() {
        |     do(bp->setOverlapsUnivorm(2,&myBlock);
        |     bp->getBlock(&myBlock);
        |     bd = myBlock->getDescription(); ...
        |     bp->releaseBlock(&myBlock);
        |   }
        | }
        | */
    virtual void setOverlapUniform(int radius, CCA_Block **b)=0;

    /** Need more advanced/flexible interface for non-uniform
     overlaps written here. */
      
      /** Extract the data object from this port. The component
       implementation will reference count based on this.
      
       The component implementation *shall* persist based on
       this, meaning that while a getBlock is outstanding the
       component cannot respond to another getBlock() on the
       same port without sending back the same object and that
       while a getBlock is outstanding, the component will not
       under the table destroy the object that is outstanding.
      
       The component implementation *may* lock on this,
       meaning it chooses not to perform any functions that 
       require changing the data values in the object. */
    virtual void getBlock(CCA_Block **b) =0;

      /** Opposite of getBlock. After a release call,
       the vector pointer previously obtained becomes
       undefined.*/
    virtual void releaseBlock(CCA_Block **b)=0;
};
#endif //BlockPort_seen
