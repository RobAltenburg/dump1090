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
#include <string.h>
#include <sys/time.h>

#include "database.h"
#include "dump1090.h"
/* 1}}} */


int interactiveEnhanceAircraft(struct aircraft *acft) {

    int rc;
    sqlite3 *db=NULL;
    sqlite3_stmt *res=NULL;
    char hexaddr[7];    // printable ICAO address

    snprintf(hexaddr,sizeof(hexaddr),"%06x",(int)acft->addr);

    sqlite3_open("icao/icao.db", &db);
    rc = sqlite3_prepare_v2(db, "select tail_num, model from aircraft where mode_s = ?", -1, &res, 0);     
    
    if (rc != SQLITE_OK) 
        fprintf(stderr, "SQL error (prepare) on line:%d msg:%s \n",__LINE__, sqlite3_errmsg(db));

    rc = sqlite3_bind_text(res, 1, hexaddr, -1, 0);
    if (rc != SQLITE_OK) 
        fprintf(stderr, "SQL error (bind) on line:%d msg:%s \n",__LINE__, sqlite3_errmsg(db));

    rc = sqlite3_step(res);
        
    if (rc == SQLITE_ROW) {
        if (sqlite3_column_text(res,0) != NULL)
            strncpy(acft->tailnum, (char *) sqlite3_column_text(res, 0), MAX_TAIL_STRING -1);
            acft->tailnum[MAX_TAIL_STRING -1] = '\0';
        if (sqlite3_column_text(res,1) != NULL)
            strncpy(acft->type, (char *) sqlite3_column_text(res, 1), MAX_TYPE_STRING -1);
            acft->type[MAX_TYPE_STRING -1] = '\0';

        }
    
    sqlite3_finalize(res);
    sqlite3_close(db);
    
    return 0;
}

