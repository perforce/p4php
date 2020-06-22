/*
 * Copyright (c) 2001-2008, Perforce Software, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL PERFORCE SOFTWARE, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * php_mergedata.h - Provides support for merge tools.
 * 
 * Methods:
 * 
 *  PHPMergeData::GetYourName() - The name of "your" file in the merge.
 *  PHPMergeData::GetTheirName() - The name of "their" file in the merge.
 *  PHPMergeData::GetBaseName() - The name of "base" file in the merge.
 *  PHPMergeData::GetYourPath() - The path of "your" file in the merge.
 *  PHPMergeData::GetTheirPath() - The path of "their" file in the merge.
 *  PHPMergeData::GetBasePath() - The path of the "base" file in the merge.
 *  PHPMergeData::GetResultPath() - The path to the merge result. 
 *  PHPMergeData::GetMergeHint() - Hint from the server as to how best resolve.
 *  PHPMergeData::RunMergeTool() - Run the merge program.
 */

#ifndef PHP_MERGE_DATA_H
#define PHP_MERGE_DATA_H

class PHPMergeData
{
    public:
        
        PHPMergeData( ClientUser *ui, ClientMerge *m, StrPtr &hint );
        
        void SetDebug( int d )     { debug = d; }
        
        void GetYourName(zval *return_value);
        void GetTheirName(zval *return_value);
        void GetBaseName(zval *return_value);

        void GetYourPath(zval *return_value);
        void GetTheirPath(zval *return_value);
        void GetBasePath(zval *return_value);
        void GetResultPath(zval *return_value);

        void GetMergeHint(zval *return_value);
    
        void RunMergeTool(zval *return_value);

    private:
        int           debug;
        ClientUser   *ui;
        StrBuf        hint; 
        ClientMerge  *merger;
        StrBuf        yours;
        StrBuf        theirs;
        StrBuf        base;  
};

#endif /* PHP_MERGE_DATA_H */
