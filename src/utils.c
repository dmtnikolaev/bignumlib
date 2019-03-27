#include "utils.h"

#include <ctype.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bignat.h"
#include "bignumlib-error.h"

error_t freadline(char **str, size_t *str_len, FILE *f)
{
    size_t buf_size, new_buf_size, i;
	char c, *new_str;
	int will_overflow;

	if (*str_len == SSIZE_MAX) {
		return PE_OVERFLOW;
	}

	if (*str != NULL && *str_len > 0) {
		buf_size = *str_len;
	}
	else {
		buf_size = 256;
		*str = (char *)malloc(buf_size * sizeof(char));
	}

	i = 0;
	while (1) {
		if (buf_size == i) {
			if (buf_size == SSIZE_MAX) {
				return PE_OVERFLOW;
			}

			// Удваиваем текущий размер строки, но проверяем не превысит ли он
			// SSIZE_MAX.
			will_overflow = (buf_size >> (sizeof(size_t) * 8 - 1)) == 1;
			new_buf_size = will_overflow ? SSIZE_MAX : buf_size*2;

			new_str = (char *)realloc(*str, new_buf_size);
			if (new_str == NULL) {
				return PE_ALLOC;
			}
			*str_len = strlen(*str);
			*str = new_str;
		}

		c = fgetc(f);
		if (c == '\n' || c == EOF) {
			*str_len = i;
			(*str)[i++] = '\0';
			return SUCCESS;
		}
		
		(*str)[i++] = c;
		*str_len = strlen(*str);
	}
}

error_t readline(char **str, size_t *str_len) {
	return freadline(str, str_len, stdin);
}

void swap(void *a, void *b) {
	void *t;
	t = a;
	a = b;
	b = t;
}

char digit_to_char(digit d) {
	return d + '0';
}

error_t str_to_digit(const char *str, digit *d) {
	size_t i, str_len;
	error_t err;

	str_len = strlen(str);
	for (i = 0; i < str_len; i++) {
		if (str[i] == '0' && i != str_len - 1) {
			continue;
		}
		if (str_len - i > 1) {
			return PE_PARSING;
		}
		err = char_to_digit(str[i], d);
	}

	return err;
}

error_t char_to_digit(const char ch, digit *d) {
	if (isdigit(ch) == 0) {
		return PE_PARSING;
	}
	*d = ch - '0';

	return SUCCESS;
}