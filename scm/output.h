/*
  Copyright (c) 2014 Xianfei Shen
  All rights reserved.

  Permission is hereby granted, without written agreement and without
  license or royalty fees, to use, copy, modify, and distribute this
  software and its documentation for any purpose, provided that the
  above copyright notice and the following two paragraphs appear in
  all copies of this software.
 
  IN NO EVENT SHALL XIANFEI SHEN BE LIABLE TO ANY PARTY FOR DIRECT,
  INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF XIANFEI
  SHEN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  XIANFEI SHEN SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT
  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER
  IS ON AN "AS IS" BASIS, AND XIANFEI SHEN HAS NO OBLIGATION TO
  PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
  MODIFICATIONS.
*/

#include "scm.h"

/*  procedure: (write obj) or (write obj port)

	Writes a written representation of obj to the given port.
	Strings that appear in the written representation are en-
	closed in doublequotes, and within those strings backslash
	and doublequote characters are escaped by backslashes.
	Character objects are written using the #\ notation. Write
	returns an unspecified value. The port argument may be
	omitted, in which case it defaults to the value returned by
	current-output-port.
*/
extern scm_obj *out_write(const scm_obj *obj);

/*  procedure: (display obj) or (display obj port)

	Writes a representation of obj to the given port. Strings
	that appear in the written representation are not enclosed
	in doublequotes, and no characters are escaped within
	those strings. Character objects appear in the represen-
	tation as if written by write-char instead of by write.
	Display returns an unspecified value. The port argument
	may be omitted, in which case it defaults to the value re-
	turned by current-output-port.
*/
extern scm_obj *out_display(const scm_obj *obj);

/*	procedure: (newline) or (newline port)

	Writes an end of line to port . Exactly how this is done
	differs from one operating system to another. Returns
	an unspecified value. The port argument may be omit-
	ted, in which case it defaults to the value returned by
	current-output-port.
*/
extern scm_obj *out_newline(const scm_obj *obj);

/*	procedure: (write-char char) or (write-char char port)  

	Writes the character char (not an external representa-
	tion of the character) to the given port and returns an
	unspecified value. The port argument may be omit-
	ted, in which case it defaults to the value returned by
	current-output-port.
*/
extern scm_obj *out_write_char(const scm_obj *obj);

extern scm_obj *out_error(const scm_obj *obj);

extern void scm_init_output();
 
#endif




