#pragma once

#ifndef FUNC_H__
#define FUNC_H__

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "bot.h"

#include <pthread.h>

extern bool g_glob;
/**
 * Ukonci beh programu.
 */

void checkSignal( int numSignal );

void initSignal();


bool signalTerm();

void initThread();

void *funkce(void *vlakno);

#endif //FUNC_H__
