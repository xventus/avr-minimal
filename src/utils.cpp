

//
// vim: ts=4 et
// Copyright (c) 2021 Vanek
//
/// @file   utils.cpp
/// @author Vanek

#include <stdio.h>
#include "utils.h"

void ui64toa(uint64_t v, char * buf, uint8_t base) {
  int idx = 0;
  uint64_t w = 0;
  while (v > 0)
  {
    w = v / base;
    buf[idx++] = (v - w * base) + '0';
    v = w;
  }
  buf[idx] = 0;
  for (int i = 0, j = idx - 1; i < idx / 2; i++, j--) {
    char c = buf[i];
    buf[i] = buf[j];
    buf[j] = c;
  }
}