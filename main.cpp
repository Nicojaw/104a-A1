//Nico Williams
//nijowill
//Assignment 1 - String Set and PreProcessor
// Use cpp to scan a file and print line numbers.
// Print out each input line read in, then strtok it for
// tokens.

#include <fstream>
#include <unordered_set>
using namespace std;
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <string>
using namespace std;

#include "stringset.h"
#include "auxlib.h"


const string CPP = "/usr/bin/cpp";
const size_t LINESIZE = 1024;
int exit_status = 0;
//extern int yy_flex_debug;
//extern int yydebug;
//extern FILE *yyin;
//extern int yylex(void);
//extern int yyparse(void);
//extern const char *get_yytname (int symbol);



// Chomp the last character from a buffer if it is delim.
void chomp (char* string, char delim) {
   size_t len = strlen (string);
   if (len == 0) return;
   char* nlpos = string + len - 1;
   if (*nlpos == delim) *nlpos = '\0';
}

// Run cpp against the lines of the file.
void cpplines (FILE* pipe, char* filename) {
   int linenr = 1;
   char inputname[LINESIZE];
   strcpy (inputname, filename);
   for (;;) {
      char buffer[LINESIZE];
      char* fgets_rc = fgets (buffer, LINESIZE, pipe);
      if (fgets_rc == NULL) break;
      chomp (buffer, '\n');
      printf ("%s:line %d: [%s]\n", filename, linenr, buffer);
      // http://gcc.gnu.org/onlinedocs/cpp/Preprocessor-Output.html
      int sscanf_rc = sscanf (buffer, "# %d \"%[^\"]\"",
                              &linenr, filename);
      if (sscanf_rc == 2) {
         printf ("DIRECTIVE: line %d file \"%s\"\n", linenr, filename);
         continue;
      }
      char* savepos = NULL;
      char* bufptr = buffer;
      for (int tokenct = 1;; ++tokenct) {
         char* token = strtok_r (bufptr, " \t\n", &savepos);
         bufptr = NULL;
         if (token == NULL) break;
         printf ("token %d.%d: [%s]\n",
                 linenr, tokenct, token);
      }
      ++linenr;
   }
}

int main (int argc, char** argv) {


    int opts;
    //int strNum = 0;
//    char bufferr[LINESIZE];
    string debug;
    string tmps;
    string dws;
//    FILE * tmp;
//    FILE * pps;
//    char *fgetsBLP;
//    char *buffs;
//    char *svr;
    //yy_flex_debug = 0;
  
/*Get options. code based off
gnu.org/software/libc/manual/html_node/Example-of-Getopt.html#Example-of-Getopt
*/
//  printf("test1\n");
  
    while((opts = getopt(argc, argv, "ly::@::D"))!=-1){
 //   printf("test2\n");
      switch(opts){
    
        case 'l':
          //yy_flex_debug = 1;
          printf("case L\n");
          break;
        
        case 'y':
          //yydebug = 1;
          printf("case Y\n");
          break;
        
        case '@':
          set_debugflags(optarg);
          printf("case @\n");
          //strNum = 1;
          break;
        
        case 'D':
        //Pass this option and its argument to cpp. 
        //This is mostly useful as-D__OCLIB_OH__ to suppress inclusion of the code from oclib.oh
        //when testing a program
          printf("case -D\n");
          break;
      
        default:
          fprintf(stderr, "Option: [-ly] [-@flag...] [-D string]\n");
          exit_status = 1;
          exit(exit_status);        
      }
    }
    return get_exitstatus();
}

/*    set_execname (argv[0]);
   for (int argi = 1; argi < argc; ++argi) {
      char* filename = argv[argi];
      string command = CPP + " " + filename;
      printf ("command=\"%s\"\n", command.c_str());
      FILE* pipe = popen (command.c_str(), "r");
      if (pipe == NULL) {
         syserrprintf (command.c_str());
      }else {
         cpplines (pipe, filename);
         int pclose_rc = pclose (pipe);
         eprint_status (command.c_str(), pclose_rc);
      }
   } 
   return get_exitstatus();
}
*/


