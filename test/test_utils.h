#pragma once
#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "crandom.h"

#include <stdarg.h>
#include <stdio.h>

#include <assert.h>
#include <locale.h>
#include <math.h>
#include <wchar.h>

#ifdef COLORED_OUTPUT
#define CSI L"\x1b["
#define RESET CSI L"0m"

#define BLACK CSI L"30m"
#define RED CSI L"31m"
#define GREEN CSI L"32m"
#define YELLOW CSI L"33m"
#define BLUE CSI L"34m"
#define MAGENTA CSI L"35m"
#define CYAN CSI L"36m"
#define WHITE CSI L"37m"

#define BRIGHT_BLACK CSI L"90m"
#define BRIGHT_RED CSI L"91m"
#define BRIGHT_GREEN CSI L"92m"
#define BRIGHT_YELLOW CSI L"93m"
#define BRIGHT_BLUE CSI L"94m"
#define BRIGHT_MAGENTA CSI L"95m"
#define BRIGHT_CYAN CSI L"96m"
#define BRIGHT_WHITE CSI L"97m"

#else

#define CSI L""
#define RESET L""
#define BLACK L""
#define RED L""
#define GREEN L""
#define YELLOW L""
#define BLUE L""
#define MAGENTA L""
#define CYAN L""
#define WHITE L""
#define BRIGHT_BLACK L""
#define BRIGHT_RED L""
#define BRIGHT_GREEN L""
#define BRIGHT_YELLOW L""
#define BRIGHT_BLUE L""
#define BRIGHT_MAGENTA L""
#define BRIGHT_CYAN L""
#define BRIGHT_WHITE L""

#endif

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>

int set_wide_stream(FILE *stream) {
  return _setmode(_fileno(stream), _O_U16TEXT);
}

#else

int set_wide_stream(FILE *stream) { return fwide(stream, 1); }

#endif

void init(void) {
  setlocale(LC_ALL, "");
  set_wide_stream(stdout);
}

typedef int (*generator_fn)(random_engine_t *engine, va_list args);
typedef wchar_t *(*label_fn)(int value);

void generate_samples(random_engine_t *engine, int *results, size_t len,
                      int samples, generator_fn generator, ...) {
  va_list ap;
  wprintf(L"Generating " BRIGHT_WHITE L"%d" RESET L" samples\n", samples);
  for (int i = 0; i < samples; i++) {
    va_start(ap, generator);
    int result = (int)generator(engine, ap);
    va_end(ap);
    int index = fmin(fmax(result, 0), len - 1); // ensure index is within bounds
    // assert(result == index); // ensure the generator is working correctly
    ++results[index];
  }
}

static const wchar_t BLOCKS[8] = {L'▏', L'▎', L'▍', L'▌',
                                  L'▋', L'▊', L'▉', L'█'};

wchar_t *default_label(int value) {
  static wchar_t buffer[32];
  swprintf(buffer, 32, L"%d", value);
  return buffer;
}

bool display_zero_in_histogram = false;

void display_histogram(int *results, size_t len, int samples, label_fn label) {
  wprintf(L"Results:\n");
  if (label == NULL) {
    label = default_label;
  }
  for (size_t i = 0; i < len; i++) {
    if (results[i] == 0 && !display_zero_in_histogram) {
      continue;
    }
    wprintf(L"%*ls ", 6, label(i));
    if (results[i]) {
      const double scale = (double)results[i] / samples;
      const double percentage = scale * 100;
      const int full_block_count = (int)floor(percentage);
      size_t bar_len = full_block_count +
                       2; // + 1 for partial block, + 1 for null terminator
      wchar_t bar[bar_len];
      for (int j = 0; j < full_block_count; j++) {
        bar[j] = BLOCKS[7];
      }
      const double remain = percentage - full_block_count;

      size_t partial_block = (size_t)round(remain * 7);
      bar[full_block_count] = BLOCKS[partial_block];
      bar[full_block_count + 1] = L'\0';
      wprintf(L"%ls " BLUE L"%.2g%%" RESET, bar, percentage);
    } else {
      wprintf(L"  " BLUE L"0%%" RESET);
    }
    putwchar(L'\n');
  }
}

#endif
