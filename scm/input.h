/*
  Copyright (c) 2014 Xianfei Shen
  All rights reserved.

  Permission is hereby granted, without written agreement and without
  license or royalty fees, to use, copy, modify, and distribute this
  software and its documentation for any purpose, provided that the
  above copyright notice and the following two paragraphs appear in
  all copies of this software.
 
  IN NO EVENT SHALL BRENT BENSON BE LIABLE TO ANY PARTY FOR DIRECT,
  INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF BRENT
  BENSON HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  BRENT BENSON SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT
  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER
  IS ON AN "AS IS" BASIS, AND BRENT BENSON HAS NO OBLIGATION TO
  PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
  MODIFICATIONS.
*/

#ifndef _INPUT_H
#define _INPUT_H

#include "scm.h"

/*	procedure: (read) or (read port)

	Read converts external representations of Scheme objects
	into the objects themselves. That is, it is a parser for the
	nonterminal datum (see sections 7.1.2 and 6.3.2). Read
	returns the next object parsable from the given input port,
	updating port to point to the first character past the end
	of the external representation of the object.
	
	If an end of file is encountered in the input before any char-
	acters are found that can begin an object, then an end of
	file object is returned. The port remains open, and fur-
	ther attempts to read will also return an end of file object.
	If an end of file is encountered after the beginning of an
	object’s external representation, but the external represen-
	tation is incomplete and therefore not parsable, an error is
	signalled.
	
	The port argument may be omitted, in which case it de-
	faults to the value returned by current-input-port. It is
	an error to read from a closed port.
*/
extern scm_obj *in_read(const scm_obj *obj);

/*	procedure: (read-char) or (read-char port)

	Returns the next character available from the input port,
	updating the port to point to the following character. If
	no more characters are available, an end of file object is
	returned. Port may be omitted, in which case it defaults
	to the value returned by current-input-port.
*/
extern scm_obj *in_read_char(const scm_obj *obj);

/*	procedure: (peek-char) or (peek-char port)

	Returns the next character available from the input port,
	without updating the port to point to the following char-
	acter. If no more characters are available, an end of file
	object is returned. Port may be omitted, in which case it
	defaults to the value returned by current-input-port.
*/
extern scm_obj *in_peek_char(const scm_obj *obj);

/*	procedure: (eof-object? obj)

	Returns #t if obj is an end of file object, otherwise returns
	#f. The precise set of end of file objects will vary among
	implementations, but in any case no end of file object will
	ever be an object that can be read in using read.
*/
extern scm_obj *in_pred_eof_object(const scm_obj *obj);

/*	procedure: (char-ready?) or (char-ready? port)

	Returns #t if a character is ready on the input port and
	returns #f otherwise. If char-ready returns #t then the
	next read-char operation on the given port is guaranteed
	not to hang. If the port is at end of file then char-ready?
	returns #t. Port may be omitted, in which case it defaults
	to the value returned by current-input-port.
*/
extern scm_obj *in_pred_char_ready(const scm_obj *obj);

extern void scm_init_input();

#endif
