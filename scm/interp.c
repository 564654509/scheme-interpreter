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

#include "header.h"

/*  Working with setjmp and longjmp.  */
jmp_buf env_buf;

static void scm_init();

/*  Catching the ctrl + c signal.  */
static void catch_int(int sig);

/*  the main function of interpreter  */
int main(int argc, char **argv)
{
	scm_obj *input;
	scm_obj *output;
	
	/*  This function should be called before using bdwgc C/C++
	    garbage collector. Generally we do this in the main 
	    fuction body. See more details in http://hboehm.info/gc/
	*/
	GC_init();
	
	/*  Initialize the interpreter's environment before starting it.  */
	scm_init();	
	
	printf("Welcome to scheme interpreter.\n");
	printf("Copyright (c) 2014 Xianfei Shen.\n");
	
	/*  Using setjmp and longjmp to handle the errors and catch.  */
	setjmp(env_buf);
	
	/*  Type ctrl + c to stop current interaction.   */
	signal(SIGINT, catch_int);
	
	/*  Read-Eval-Print loop  */	
	while (1) {
	    
	    /*  Read part. See in_read function in input.c file.  */
		printf("> ");
		input = in_read(scm_null);
		
		/*  Type ctrl + d to exit.  */
		if (input == scm_eof) {
			printf("user exit\n");
			exit(0);
		}
		
		/*  Eval part. See eval function in eval.c file.  */
		output = eval(input, init_env);
		
		/*  Print part. See out_write function in output.c file.  */
		out_write(cons(output, scm_null));
	}

	return 0;
}

static void scm_init()
{
	scm_init_flags();
	scm_init_env();
	scm_init_oblist();
	scm_init_syntax();
	
	scm_init_boolean();
	scm_init_char();
	scm_init_control();
	scm_init_eval();
	scm_init_input();
	scm_init_list();
	scm_init_number();
	scm_init_pair();
	scm_init_port();
	scm_init_output();
	scm_init_string();
	scm_init_symbol();
	scm_init_system();
	scm_init_vector();	
}

static void catch_int(int sig)
{
	if (sig == SIGINT) {
		printf("\nuser break\n");
		
		/*  go to the entry point of while loop and start a new interaction  */
		longjmp(env_buf, 1);
	}
}









