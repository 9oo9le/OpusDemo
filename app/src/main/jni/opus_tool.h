/*****************************************************************************
 # -*- coding:utf-8 -*-
 # author: ione
 # create date: 2014-11-27
 *****************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "include/opus_types.h"
#include "include/opus.h"

int encode(char* in, int len, unsigned char* opus, int* opus_len);

int decode(unsigned char* in, int len, short* out, int* out_len);