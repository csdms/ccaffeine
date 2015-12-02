#ifndef Cart2DPort_h_seen
#define Cart2DPort_h_seen

// requires CCA_Block.h

/** Interface called by physics at start to setup cumulvs. */
class Cart2DPort 
#ifdef HAVE_CLASSIC
: public virtual classic::gov::cca::Port 
#endif
{ 

public:

	virtual ~Cart2DPort(){}

	/** Set up array of x coordinates. */
        virtual void setXAxis(double *x, struct CCA_dimenMap *mapX) =0;

	/** Set array of y coordinates. */
        virtual void setYAxis(double *y, struct CCA_dimenMap *mapY) =0;

	/** Set up a field extractable from the CCA_Block for viewing in
        VIZ code.
        @param b the data, in which the field will be found. 
        @param name the name of a field that will be found in the block
               description. Only those fields within the block nominated
               via the setField call will be viz-enabled.
      */
        virtual void setField(CCA_Block *b, char *name) =0;

	/** Start the visualization routine going again. */
	virtual int visualize()=0; 
};
#endif //Cart2DPort_h_seen
