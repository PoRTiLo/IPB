#pragma once

#ifndef FUNC_H__
#define FUNC_H__

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "bot.h"

//#include <ncurses.h>
#include <pthread.h>

extern bool f_global;
/**
 * Ukonci beh programu.
 */

void checkSignal( int numSignal );

void initSignal();

void signalTerm();

void initThread();

void *thread(void *mThread);

//string getPassTerminal();

#endif //FUNC_H__
