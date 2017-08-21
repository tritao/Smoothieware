/*
 * Copyright (c) 2003, Adam Dunkels.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack
 *
 * $Id: telnetd.c,v 1.2 2006/06/07 09:43:54 adam Exp $
 *
 */

#include "telnetd.h"
#include "shell.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "net/PassiveSocket.h"

void Telnetd::close()
{
}

int Telnetd::sendline(char *line)
{
    return 0;
}

void Telnetd::output_prompt(const char *str)
{
    if(prompt) output(str);
}

int Telnetd::output(const char *str)
{
    socket->Send((const uint8 *) "\r", 1);
    int sent = socket->Send((const uint8 *) str, strlen(str));
    return sent;
}

// check if we can queue or if queue is full
int Telnetd::can_output()
{
    return 0;
}

void Telnetd::acked(void)
{

}

void Telnetd::senddata(void)
{

}

void Telnetd::get_char(uint8_t c)
{

}

void Telnetd::newdata(void)
{

}

void Telnetd::poll()
{

}

Telnetd::Telnetd()
{
    shell= new Shell(this);
}

Telnetd::~Telnetd()
{
    delete shell;
}

// static
void Telnetd::appcall(void)
{

}

// static
void Telnetd::init(void)
{

}
