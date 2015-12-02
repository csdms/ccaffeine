// ACL:license
// ----------------------------------------------------------------------------
// This software and ancillary information (herein called "SOFTWARE")
// called SILOON is made available under the terms described here.  The
// SOFTWARE has been approved for release with associated LA-CC Number
// LA-CC-98-32.
// 
// Unless otherwise indicated, this SOFTWARE has been authored by an
// employee or employees of the University of California, operator of the
// Los Alamos National Laboratory under Contract No.  W-7405-ENG-36 with
// the U.S. Department of Energy.  The U.S. Government has rights to use,
// reproduce, and distribute this SOFTWARE, and to allow others to do so.
// The public may copy, distribute, prepare derivative works and publicly
// display this SOFTWARE without charge, provided that this Notice and
// any statement of authorship are reproduced on all copies.  Neither the
// Government nor the University makes any warranty, express or implied,
// or assumes any liability or responsibility for the use of this
// SOFTWARE.
// 
// If SOFTWARE is modified to produce derivative works, such modified
// SOFTWARE should be clearly marked, so as not to confuse it with the
// version available from LANL.  
// 
// For more information about SILOON, send e-mail to
// siloon-team@acl.lanl.gov, or visit the SILOON web page at
// http://www.acl.lanl.gov/siloon/.
// ----------------------------------------------------------------------------
// ACL:license
//-----------------------------------------------------------------------------
// Complex.h -- classes to copy Fortran complex classes
//-----------------------------------------------------------------------------
#ifndef _COMPLEX_H_
#define _COMPLEX_H_

namespace Siloon {

class ComplexDouble {
 public:
  double real;
  double imag;

  ComplexDouble(double r, double i) : real(r), imag(i)  { }
  ComplexDouble(const ComplexDouble& c) : real(c.real), imag(c.imag) { }
  ComplexDouble& operator=(const ComplexDouble& c);
};


class ComplexFloat {
 public:
  float real;
  float imag;

  ComplexFloat(float r, float i) : real(r), imag(i)  { }
  ComplexFloat(const ComplexFloat& c) : real(c.real), imag(c.imag) { }
  ComplexFloat& operator=(const ComplexFloat& c);
};


} // namespace Siloon

#endif // _COMPLEX_H

