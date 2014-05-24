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

#ifndef _PORT_H
#define _PORT_H

#include "scm.h"


/*	default value: stdin  */
extern scm_obj *scm_cur_input_port;

/*  default value: stdout  */
extern scm_obj *scm_cur_output_port;

/*  procedure: (call-with-input-file string proc)
	procedure: (call-with-output-file string proc)
	
	String should be a string naming a file, and proc should be a
	procedure that accepts one argument. For call-with-input-file, 
	the file should already exist; for call-with-output-file, the 
	effect is unspecified if the file already exists. These procedures
	call proc with one argument: the port obtained by opening the
	named file for input or output. If the file cannot be opened, 
	an error is signalled. If proc returns, then the port is closed 
	automatically and the value(s) yielded by the proc is(are) returned.
	If proc does not return, then the port will not be closed
	automatically unless it is possible to prove that the port will
	never again be used for a read or write operation.
*/
extern scm_obj *port_call_with_input_file(const scm_obj *obj);
extern scm_obj *port_call_with_output_file(const scm_obj *obj);

/* 	procedure: (input-port? obj)
	procedure: (output-port? obj)
	
	Returns #t if obj is an input port or output port respectively,
	otherwise returns #f.
*/
extern scm_obj *port_pred_input_port(const scm_obj *obj);
extern scm_obj *port_pred_output_port(const scm_obj *obj);

/* 	procedure: (current-input-port)
	procedure: (current-output-port)

	Returns the current default input or output port.
*/
extern scm_obj *port_current_input_port(const scm_obj *obj);
extern scm_obj *port_current_output_port(const scm_obj *obj);

/* 	procedure: (with-input-from-file string thunk )
	procedure: (with-output-to-file string thunk )

	String should be a string naming a file, and proc should be
	a procedure of no arguments. For with-input-from-file,
	the file should already exist; for with-output-to-file,
	the effect is unspecified if the file already exists. The
	file is opened for input or output, an input or output
	port connected to it is made the default value returned
	by current-input-port or current-output-port (and is used by
	(read), (write obj ), and so forth), and the thunk is called 
	with no arguments. When the thunk returns, the port is closed 
	and the previous default is restored. With-input-from-file and
	with-output-to-file return(s) the value(s) yielded by thunk. If
	an escape procedure is used to escape from the continuation of 
	these procedures, their behavior is implementation dependent.
*/
extern scm_obj *port_with_input_from_file(const scm_obj *obj);
extern scm_obj *port_with_output_to_file(const scm_obj *obj);

/*  procedure: (open-input-file filename)

	Takes a string naming an existing file and returns an input
	port capable of delivering characters from the file. If the
	file cannot be opened, an error is signalled.
*/
extern scm_obj *port_open_input_file(const scm_obj *obj);

/*	procedure: (open-outport-file filename)

	Takes a string naming an output file to be created and
	returns an output port capable of writing characters to a
	new file by that name. If the file cannot be opened, an
	error is signalled. If a file with the given name already
	exists, the effect is unspecified.
*/
extern scm_obj *port_open_output_file(const scm_obj *obj);

/*	procedure: (close_input_port port)
	procedure: (close_output_port port)
	
	Closes the file associated with port , rendering the port in-
	capable of delivering or accepting characters. These rou-
	tines have no effect if the file has already been closed. The
	value returned is unspecified.
*/
extern scm_obj *port_close_input_port(const scm_obj *obj);
extern scm_obj *port_close_output_port(const scm_obj *obj);

extern void scm_init_port();

#endif
