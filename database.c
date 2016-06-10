/* database.c -- Look up tail number and acft information from mode_s code {{{1
 * 
 * Copyright (c) 2016, Robert Altenburg <r at qrpc dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 1}}}*/

/* includes {{{1 */
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

#include "database.h"
#include "dump1090.h"
/* 1}}} */

//From the SQLite manual:
#define ERRCHECK {if (err!=NULL) {printf("%s\n",err);  return 0;}}

sqlite3 *db=NULL;

int interactiveEnhanceAircraft(struct aircraft*);
static int db_open(char *);
int db_query(char *);
int db_callback(void *, int , char **, char **);

static int db_open(char *filename){
    sqlite3_open(filename,&db);
    if (!db)
        printf("Not sure why, but the database didn't open.\n");
    return 0;
}

int db_callback(void *a_param, int argc, char **argv, char **column){
        for (int i=0; i< argc; i++)
                    printf("%s,\t", argv[i]);
            printf("\n");
                return 0;
}

int db_query(char *query){
  char *err = NULL;
    if (db==NULL) 
        db_open(NULL);
    sqlite3_exec(db, query, db_callback, NULL, &err); 
    ERRCHECK
        return(0);
}


/* testing and debugging {{{1*/

int testdb(void) {
    db_open("icao/icao.db");
    db_query("select * from aircraft;");
    return 0;
}

// 1}}}


