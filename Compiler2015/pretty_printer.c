// Working for pretty printer...
// Created by おうけん on 公元15-04-12.
//

#include <stdio.h>
#include <stdlib.h>

//key 0
//id 1
//int_const 2
//char_const 3
//string_const 4
//op 5

char *src_code = 0, *src_tail = 0, *cur_scan = 0;
int src_buffer_len, col = 1, row = 1, is_cast = 0, pre_else = 0;
int is_ms, tab_cnt;
FILE *input, *output;

struct Token {
	int type;
	int col, row;
	char *_literal;
	union {
		int int_val;
		int char_val;
		char *str_val;
	};
} look;

void put_tabs(int);
void my_assert(int, char *);
int my_strcmp(char *, char *);
int str_start_with(char *, char *);
void eat_chars(int);
void eat_useless_chars();
char analy_and_jump(char **);
struct Token next_token();
void read_src();
void parse_plain_declarator();
void parse_array();
void parse_declarator();
void parse_declarators();
void parse_type_specifier();
void parse_parameters();
void parse_initializer();
void parse_init_declarators();
void parse_compound_stmt();
void parse_stmt();
void parse_program();
void parse_expr();
void parse_assign_expr();
void parse_const_expr();
void parse_logic_or_expr();
void parse_logic_and_expr();
void parse_or_expr();
void parse_xor_expr();
void parse_and_expr();
void parse_equality_expr();
void parse_relational_expr();
void parse_shift_expr();
void parse_additive_expr();
void parse_multi_expr();
void parse_cast_expr();
void parse_unary_expr();
void parse_postfix_expr();
void parse_primary_expr();
int is_type();
void parse_postfix();

void put_tabs(int n) {
	while (n--) {
		fprintf(output, "\t");
	}
}

void parse_const_expr() {
//TODO: parse expression (grammar) & check if const (meaning)
	parse_assign_expr();
}

void parse_assign_expr() {
	parse_logic_or_expr();
	//char *cur = look._literal;
	while (look._literal[0] == '=' || look._literal[1] == '=') {
		fprintf(output, " %s ", look._literal);
		look = next_token();
		parse_assign_expr();
	}
}

void parse_logic_or_expr() {
	parse_logic_and_expr();
	while (!my_strcmp(look._literal, "||")) {
		fprintf(output, " %s ", look._literal);
		look = next_token();
		parse_logic_and_expr();
	}
}

void parse_logic_and_expr() {
	parse_and_expr();
	while (!my_strcmp(look._literal, "&&")) {
		fprintf(output, " %s ", look._literal);
		look = next_token();
		parse_and_expr();
	}
}

void parse_and_expr() {
	parse_xor_expr();
	while (!my_strcmp(look._literal, "&")) {
		fprintf(output, " %s ", look._literal);
		look = next_token();
		parse_xor_expr();
	}
}

void parse_xor_expr() {
	parse_or_expr();
	while (!my_strcmp(look._literal, "^")) {
		fprintf(output, " %s ", look._literal);
		look = next_token();
		parse_or_expr();
	}
}

void parse_or_expr() {
	parse_equality_expr();
	while (!my_strcmp(look._literal, "|")) {
		fprintf(output, " %s ", look._literal);
		look = next_token();
		parse_equality_expr();
	}
}

void parse_equality_expr() {
	parse_relational_expr();
	while (!my_strcmp(look._literal, "==") || !my_strcmp(look._literal, "!=")) {
		fprintf(output, " %s ", look._literal);
		look = next_token();
		parse_relational_expr();
	}
}

void parse_relational_expr() {
	parse_shift_expr();
	while (!my_strcmp(look._literal, "<") || !my_strcmp(look._literal, ">") || !my_strcmp(look._literal, ">=") || !my_strcmp(look._literal, "<=")) {
		fprintf(output, " %s ", look._literal);
		look = next_token();
		parse_shift_expr();
	}
}

void parse_shift_expr() {
	parse_additive_expr();
	while (!my_strcmp(look._literal, "<<") || !my_strcmp(look._literal, ">>")) {
		fprintf(output, " %s ", look._literal);
		look = next_token();
		parse_additive_expr();
	}
}

void parse_additive_expr() {
	parse_multi_expr();
	while (!my_strcmp(look._literal, "+") || !my_strcmp(look._literal, "-")) {
		fprintf(output, " %s ", look._literal);
		look = next_token();
		parse_multi_expr();
	}
}

void parse_multi_expr() {
	parse_cast_expr();
	while (!my_strcmp(look._literal, "*") || !my_strcmp(look._literal, "/") || !my_strcmp(look._literal, "%")) {
		fprintf(output, " %s ", look._literal);
		look = next_token();
		parse_cast_expr();
	}
}

int is_type() {
	return !my_strcmp(look._literal, "int") || !my_strcmp(look._literal, "char") || !my_strcmp(look._literal, "void") || !my_strcmp(look._literal, "struct") || !my_strcmp(look._literal, "union");
}

void parse_cast_expr() {
	if (!my_strcmp(look._literal, "(")) {
		fprintf(output, "(");
		look = next_token();
		if (is_type()) {
			is_cast = 1;
			parse_type_specifier();
			is_cast = 0;
			while (!my_strcmp(look._literal, "*")) {
				fprintf(output, "*");
				look = next_token();
			}
			my_assert(!my_strcmp(look._literal, ")"), "Not closed cast type name!");
			fprintf(output, ") ");
			look = next_token();
			parse_cast_expr();
		} else {
		//This is primary...
			parse_expr();
			my_assert(!my_strcmp(look._literal, ")"), "Not closed paren, ) expected!");
			fprintf(output, ")");
			look = next_token();
			parse_postfix();
		}
	} else {
		parse_unary_expr();
	}
}

int unary_operator() {
	return !my_strcmp(look._literal, "&") || !my_strcmp(look._literal, "*") || !my_strcmp(look._literal, "+") || !my_strcmp(look._literal, "-") || !my_strcmp(look._literal, "~") || !my_strcmp(look._literal, "!");
}

void parse_unary_expr() {
	if (!my_strcmp(look._literal, "++") || !my_strcmp(look._literal, "--")) {
		fprintf(output, "%s", look._literal);
		look = next_token();
		parse_unary_expr();
	} else if (!my_strcmp(look._literal, "sizeof")) {
		fprintf(output, "sizeof ");
		look = next_token();
		if (!my_strcmp(look._literal, "(")) {
			fprintf(output, "(");
			look = next_token();
			parse_type_specifier();
			while (!my_strcmp(look._literal, "*")) {
				fprintf(output, "*");
				look = next_token();
			}
			my_assert(!my_strcmp(look._literal, ")"), ") when sizeof!");
			fprintf(output, ")");
			look = next_token();
		} else {
			parse_unary_expr();
		}
	} else if (unary_operator()) {
		fprintf(output, "%s", look._literal);
		look = next_token();
		parse_cast_expr();
	} else {
		parse_postfix_expr();
	}
}

void parse_arguments() {
	while (my_strcmp(look._literal, ")")) {
		parse_assign_expr();
		if (!my_strcmp(look._literal, ",")) {
			fprintf(output, ", ");
			look = next_token();
		}
	}
}

void parse_postfix() {
	for (;;) {
		if (!my_strcmp(look._literal, "(")) {
			fprintf(output, "(");
			look = next_token();
			parse_arguments();
			fprintf(output, ")");
			look = next_token();
		} else if (!my_strcmp(look._literal, "[")) {
			fprintf(output, "[");
			look = next_token();
			parse_expr();
			my_assert(!my_strcmp(look._literal, "]"), "Array access ] expected!");
			fprintf(output, "]");
			look = next_token();
		} else if (!my_strcmp(look._literal, ".")) {
			fprintf(output, ".");
			look = next_token();
			my_assert(look.type == 1, "member access identifier expected!");
			fprintf(output, "%s", look._literal);
			look = next_token();
		} else if (!my_strcmp(look._literal, "->")) {
			fprintf(output, "->");
			look = next_token();
			my_assert(look.type == 1, "ptr member access identifer expected!");
			fprintf(output, "%s", look._literal);
			look = next_token();
		} else if (!my_strcmp(look._literal, "++") || !my_strcmp(look._literal, "--")) {
			look = next_token();
		} else {
			break;
		}
	}
}

void parse_postfix_expr() {
	parse_primary_expr();
//This is postfixes
	parse_postfix();
}

void parse_primary_expr() {
	if (look.type >= 1 && look.type <= 4) {
		fprintf(output, "%s", look._literal);
		look = next_token();
	} else if (!my_strcmp(look._literal, "(")) {
		fprintf(output, "(");
		look = next_token();
		parse_expr();
		fprintf(output, ")");
		look = next_token();
	} else {
		my_assert(0, "WTF in primary expr");
	}
}

void parse_expr() {
	parse_assign_expr();
	while (!my_strcmp(look._literal, ",")) {
		fprintf(output, ", ");
		look = next_token();
		parse_assign_expr();
	}
}

void my_assert(int condition, char *s) {
	if (!condition) {
		fputs(s, output);
		fputs("\n", output);
		char *tmp = cur_scan;
		while (*tmp != '\n' && tmp < src_tail) {
			fputc(*tmp++, output);
		}
		fprintf(output, "\n<%d, %d> %s\n", look.row, look.col, look._literal);
		for(;;);
	}
}

int my_strcmp(char *s1, char *s2) {
	my_assert(s1 && s2, "Try to compare empty string!!");
	while (*s1 && *s2 && *s1 == *s2) {
		++s1, ++s2;
	}
	return *s1 - *s2;
}

int str_start_with(char *s1, char *s2) {
	while (*s1 && *s2) {
		if (*s1++ != *s2++) {
			return 0;
		}
	}
	return 1;
}

void eat_chars(int num) {
	while (num--) {
		if (*cur_scan == '\n') {
			++row;
			col = 0;
		}
		if (*cur_scan == '\t') {
			if (col % 4) {
				col += 4 - col % 4;
			} else {
				col += 8;
			}
		} else {
			++col;
		}
		++cur_scan;
	}
}

void eat_useless_chars() {
	char *before = 0;
	while (before != cur_scan) {
		before = cur_scan;
		while (cur_scan < src_tail && (*cur_scan == '\n' || *cur_scan == '\t' || *cur_scan == ' ')) {
			//fputc(*cur_scan, output);
			eat_chars(1);
		}
		if (cur_scan < src_tail && *cur_scan == '#') {
			while (cur_scan < src_tail && *cur_scan != '\n') {
				fputc(*cur_scan, output);
				eat_chars(1);
			}
			fputc(*cur_scan, output);
			eat_chars(1);
		}
		if (cur_scan < src_tail && *cur_scan == '/' && cur_scan[1] == '/') {
			while (cur_scan < src_tail && *cur_scan != '\n') {
				fputc(*cur_scan, output);
				eat_chars(1);
			}
			fputc(*cur_scan, output);
			eat_chars(1);
		}
		if (cur_scan < src_tail && *cur_scan == '/' && cur_scan[1] == '*') {
			while ((*cur_scan != '*' || cur_scan[1] != '/')) {
				fputc(*cur_scan, output);
				eat_chars(1);
			}
			fputc(*cur_scan, output);
			fputc(cur_scan[1], output);
			eat_chars(2);
			fputc('\n', output);
		}
	}
}

char analy_and_jump(char **s) {
	if (**s != '\\') {
		(*s) += 1;
		return **s;
	} else if ((*s)[1] == 'a') {
		(*s) += 2;
		return '\a';
	} else if ((*s)[1] == 'b') {
		(*s) += 2;
		return '\b';
	} else if ((*s)[1] == 'f') {
		(*s) += 2;
		return '\f';
	} else if ((*s)[1] == 'n') {
		(*s) += 2;
		return '\n';
	} else if ((*s)[1] == 't') {
		(*s) += 2;
		return '\t';
	} else if ((*s)[1] == 'v') {
		(*s) += 2;
		return '\v';
	} else if ((*s)[1] == 'r') {
		(*s) += 2;
		return '\r';
	} else if ((*s)[1] == '\"') {
		(*s) += 2;
		return '\"';
	} else if ((*s)[1] == '\'') {
		(*s) += 2;
		return '\'';
	} else if ((*s)[1] == '\'') {
		(*s) += 2;
		return '\'';
	} else if ((*s)[1] == '\\') {
		(*s) += 2;
		return '\\';
	} else if ((*s)[1] == 'X' || (*s)[1] == 'x') {
		char *tail = *s + 2;
		char val = 0;
		while(*tail != '\0' && ((*tail >= '0' && *tail <= '9') || (*tail >= 'A' && *tail <= 'F'))) {
			val = val * 16;
			if (*tail >= '0' && *tail <= '9') {
				val += *tail - '0';
			} else {
				val += *tail - 'A' + 10;
			}
			++tail;
		}
		*s = tail;
		return val;
	} else {
		char *tail = *s + 1;
		char val = 0;
		while(*tail >= '0' && *tail <= '7') {
			val = val * 8 + *tail - '0';
			++tail;
		}
		*s = tail;
		return val;
	}
	return 0;
}

struct Token next_token() {
	if (look._literal && !my_strcmp(look._literal, "else")) {
		pre_else = 1;
	} else {
		pre_else = 0;
	}
	int ans = 0;
	struct Token res;
	eat_useless_chars();
	res.row = row;
	res.col = col;
	if (str_start_with(cur_scan, "void") && 4 > ans) { //KEY
		ans = 4;
		res.type = 0;
	}
	if (str_start_with(cur_scan, "char") && 4 > ans) {
		ans = 4;
		res.type = 0;
	}
	if (str_start_with(cur_scan, "int") && 3 > ans) {
		ans = 3;
		res.type = 0;
	}
	if (str_start_with(cur_scan, "typedef") && 7 > ans) {
		ans = 7;
		res.type = 0;
	}
	if (str_start_with(cur_scan, "for") && 3 > ans) {
		ans = 3;
		res.type = 0;
	}
	if (str_start_with(cur_scan, "continue") && 8 > ans) {
		ans = 8;
		res.type = 0;
	}
	if (str_start_with(cur_scan, "struct") && 6 > ans) {
		ans = 6;
		res.type = 0;
	}
	if (str_start_with(cur_scan, "return") && 6 > ans) {
		ans = 6;
		res.type = 0;
	}
	if (str_start_with(cur_scan, "sizeof") && 6 > ans) {
		ans = 6;
		res.type = 0;
	}
	if (str_start_with(cur_scan, "union") && 5 > ans) {
		ans = 5;
		res.type = 0;
	}
	if (str_start_with(cur_scan, "while") && 5 > ans) {
		ans = 5;
		res.type = 0;
	}
	if (str_start_with(cur_scan, "if") && 2 > ans) {
		ans = 2;
		res.type = 0;
	}
	if (str_start_with(cur_scan, "else") && 4 > ans) {
		ans = 4;
		res.type = 0;
	}
	if (str_start_with(cur_scan, "break") && 5 > ans) {
		ans = 5;
		res.type = 0;
	}
	if ((*cur_scan >= 'a' && *cur_scan <= 'z') || (*cur_scan >= 'A' && *cur_scan <= 'Z') || *cur_scan == '_') { //IDENTIFIER
		char *tail = cur_scan + 1;
		while (tail < src_tail && ((*tail >= 'a' && *tail <= 'z') || (*tail >= 'A' && *tail <='Z') || *tail == '_' || (*tail >= '0' && *tail <= '9'))) {
			++tail;
		}
		if (tail - cur_scan > ans) { //IDENTIFIER
			ans = tail - cur_scan;
			res.type = 1;//id
		}
	}
	if (*cur_scan >= '0' && *cur_scan <= '9') { //INT_CONST
		int val = *cur_scan - '0';
		char *tail = cur_scan + 1;
		while (tail < src_tail && (*tail >= '0' && *tail <= '9')) {
			val = val * 10 + *tail - '0';
			++tail;
		}
		if (tail - cur_scan > ans) {
			ans = tail - cur_scan;
			res.type = 2;
			res.int_val = val;
		}
	}
	if (str_start_with(cur_scan, "0x") || str_start_with(cur_scan, "0X")) { //INT_CONST heximal
		int val = cur_scan[2] - '0';
		char *tail = cur_scan + 3;
		while (tail < src_tail && ((*tail >= '0' && *tail <= '9') || (*tail >= 'A' && *tail <= 'F'))) {
			val = val * 16;
			if (*tail >= '0' && *tail <= '9') {
				val += *tail - '0';
			} else {
				val += *tail - 'A' + 10;
			}
			++tail;
		}
		if (tail - cur_scan > ans) {
			ans = tail - cur_scan;
			res.type = 2;
			res.int_val = val;
		}
	}
	if (*cur_scan == '\'') { //CHAR_CONST
		char *tail = cur_scan + 1;
		char val = analy_and_jump(&tail);
		my_assert(*tail == '\'', "Not a closed char!");
		++tail;
		if (tail - cur_scan > ans) {
			ans = tail - cur_scan;
			res.type = 3;
			res.char_val = val;
		}
	}
	if (*cur_scan == '\"') { //STRING_CONST
		char *tail = cur_scan + 1;
		while (tail < src_tail && (*tail != '\"' || tail[-1] == '\\')) {
			my_assert(*tail != '\n', "Enter exists in pair of quotes!");
			++tail;
		}
		my_assert(*cur_scan == '\"', "Not a closed string!");
		if (tail + 1 - cur_scan > ans) {
			ans = tail + 1 - cur_scan;
			res.type = 4;
			char *tmp = res.str_val = (char *) malloc(tail + 5 - cur_scan + 1);
			tail = cur_scan + 1;
			while (tail < src_tail && (*tail != '\"' || tail[-1] == '\\')) {
				*tmp++ = analy_and_jump(&tail);
			}
			*tmp = 0;
		}
	}
	if (*cur_scan == '(' && 1 > ans) { //OP
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == ')' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == ';' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == ',' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '=' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '{' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '}' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '[' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == ']' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '*' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '|' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '^' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '&' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '<' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '>' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '+' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '-' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '/' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '%' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '~' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '!' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (*cur_scan == '.' && 1 > ans) {
		ans = 1;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "||") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "&&") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "==") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "!=") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "<=") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, ">=") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "<<") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, ">>") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "++") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "--") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "->") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "+=") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "-=") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "*=") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "/=") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "%=") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "|=") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "^=") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "|=") && 2 > ans) {
		ans = 2;
		res.type = 5;
	}
	if (str_start_with(cur_scan, ">>=") && 3 > ans) {
		ans = 3;
		res.type = 5;
	}
	if (str_start_with(cur_scan, "<<=") && 3 > ans) {
		ans = 3;
		res.type = 5;
	}
	my_assert(ans, "Token unknown error!");
	char *j = res._literal = (char *) malloc(ans + 1), *i;
	for (i = cur_scan; i - cur_scan < ans; ) {
		*j++ = *i++;
	}
	//fprintf(output, "<%d, %d> %s\n", res.row, res.col, res._literal);
	*j = 0;
	eat_chars(ans);
	//eat_useless_chars();
	return res;
}

void parse_plain_declarator() {
	while (!my_strcmp(look._literal, "*")) {
		fprintf(output, "*");
		look = next_token();
	}
	my_assert(look.type == 1, "parse plain decl IDENTIFIER expected!");
	fprintf(output, "%s", look._literal);
	look = next_token();
}

void parse_array() {
	if (!my_strcmp(look._literal, "[")) {
		while (!my_strcmp(look._literal, "[")) {
			fprintf(output, "[");
			look = next_token();
			if (my_strcmp(look._literal, "]")) {
				parse_const_expr();
			}
			my_assert(!my_strcmp(look._literal, "]"), "] expected!");
			fprintf(output, "]");
			look = next_token();
		}
	}
}

void parse_declarator() {
	parse_plain_declarator();
	parse_array();
	parse_parameters();
}

void parse_declarators() {
	for (parse_declarator(); !my_strcmp(look._literal, ","); parse_declarator()) {
		fprintf(output, ", ");
		look = next_token();
	}
}

void parse_type_specifier() {
	if (!is_cast) {
		put_tabs(tab_cnt);
	}
	if (!my_strcmp(look._literal, "FILE")) {
		look = next_token();
		if (!my_strcmp(look._literal, ",") || !my_strcmp(look._literal, ")")) {
			fprintf(output, "FILE");
		} else {
			fprintf(output, "FILE ");
		}
		return ;
	}else if (!my_strcmp(look._literal, "int")) {
		look = next_token();
		if (!my_strcmp(look._literal, ",") || !my_strcmp(look._literal, ")")) {
			fprintf(output, "int");
		} else {
			fprintf(output, "int ");
		}
		return ;
	} else if (!my_strcmp(look._literal, "char")) {
		look = next_token();
		if (!my_strcmp(look._literal, ",") || !my_strcmp(look._literal, ")")) {
			fprintf(output, "char");
		} else {
			fprintf(output, "char ");
		}
		return ;
	} else if (!my_strcmp(look._literal, "void")) {
		look = next_token();
		if (!my_strcmp(look._literal, ",") || !my_strcmp(look._literal, ")")) {
			fprintf(output, "void");
		} else {
			fprintf(output, "void ");
		}
		return ;
	} else if (!my_strcmp(look._literal, "struct") || !my_strcmp(look._literal, "union")) {
		fprintf(output, "%s ", look._literal);
		look = next_token();
		if (look.type == 1 || !my_strcmp(look._literal, "{")) {
			if (look.type == 1) {
				fprintf(output, "%s ", look._literal);
				look = next_token();
			}
			if (!my_strcmp(look._literal, "{")){
				if (is_ms) {
					fprintf(output, "\n");
					put_tabs(tab_cnt);
				}
				char *left_brace;
				if (is_ms) {
					left_brace = "{\n";
				} else {
					left_brace = " {\n";
				}
				fprintf(output, left_brace);
				look = next_token();
				++tab_cnt;
				while (my_strcmp(look._literal, "}")) {
					//put_tabs(tab_cnt);
					parse_type_specifier();
					if (my_strcmp(look._literal, ";")) {
						parse_declarators();
					} else {
						//puts("anonymous gadget inside!");
					}
					my_assert(!my_strcmp(look._literal, ";"), "Unexpected end of delarators!");
					fprintf(output, ";\n");
					look = next_token();
				}
				put_tabs(--tab_cnt);
				fprintf(output, "}");
				look = next_token();
			} else {
				//puts("anonymous type!");
			}
		}
	} else {
		my_assert(0, "Not a type specifier!");
	}
	return ;
}

void parse_parameters() {
	if (!my_strcmp(look._literal, "(")) {
		fprintf(output, "(");
		for (look = next_token(); my_strcmp(look._literal, ")");) {
			parse_type_specifier();
			if (!my_strcmp(look._literal, "*") || look.type == 1) {
				//parse_declarator();
				while (!my_strcmp(look._literal, "*")) {
					fprintf(output, "*");
					look = next_token();
				}
				if (look.type == 1) {
					fprintf(output, "%s", look._literal);
					look = next_token();
					parse_array();
				}
			}
			if (!my_strcmp(look._literal, ",")) {
				fprintf(output, ", ");
				look = next_token();
			}
		}
		fprintf(output, ")");
		look = next_token();
	}
}

void parse_initializer() {
	if (!my_strcmp(look._literal, "{")) {
		int not_closed = 1;
		look = next_token();
		fprintf(output, "{");
		while (not_closed) {
			if (!my_strcmp(look._literal, "}")) {
				fprintf(output, "}");
				look = next_token();
				--not_closed;
				continue;
			} else if (!my_strcmp(look._literal, "{")) {
				fprintf(output, "{");
				look = next_token();
				++not_closed;
				continue;
			} else {
				parse_assign_expr();
				if (!my_strcmp(look._literal, ",")) {
					fprintf(output, ", ");
					look = next_token();
				}
			}
		}
	} else {
		parse_assign_expr();
	}
}

void parse_init_declarators() {
	for (parse_declarator(); ; parse_declarator()) {
		if (!my_strcmp(look._literal, "=")) {
			fprintf(output, " = ");
			look = next_token();
			parse_initializer();
		}
		if (my_strcmp(look._literal, ",")) {
			break;
		} else {
			fprintf(output, ", ");
			look = next_token();
		}
	}
}

void parse_compound_stmt() {
	my_assert(!my_strcmp(look._literal, "{"), "compound statement{ expected!");
	if (is_ms) {
		fprintf(output, "\n");
		put_tabs(tab_cnt - 1);
	}
	char *left_brace;
	if (is_ms) {
		left_brace = "{\n";
	} else {
		left_brace = " {\n";
	}
	fprintf(output, left_brace);
	look = next_token();
	while (my_strcmp(look._literal, "}")) {
		if (!my_strcmp(look._literal, "struct") || !my_strcmp(look._literal, "union") || !my_strcmp(look._literal, "char") || !my_strcmp(look._literal, "int") || !my_strcmp(look._literal, "void")) {
			parse_type_specifier();
			parse_init_declarators();
			my_assert(!my_strcmp(look._literal, ";"), "compound stmt expected ; for declaration...");
			fprintf(output, ";\n");
			look = next_token();
		} else {
			parse_stmt();
		}
	}
	put_tabs(tab_cnt - 1);
	fprintf(output, "}\n");
	look = next_token();
}

void parse_stmt() {
	if (!my_strcmp(look._literal, ";")) {
		put_tabs(tab_cnt);
		fprintf(output, ";\n");
		look = next_token();
	} else if (!my_strcmp(look._literal, "{")) {
		++tab_cnt;
		parse_compound_stmt();
		--tab_cnt;
	} else if (!my_strcmp(look._literal, "if")){
		if (!pre_else) {
			put_tabs(tab_cnt);
		}
		fprintf(output, "if ");
		look = next_token();
		my_assert(!my_strcmp(look._literal, "("), "parse if ( expected!");
		fprintf(output, "(");
		look = next_token();
		parse_expr();
		my_assert(!my_strcmp(look._literal, ")"), "parse if) expected!");
		fprintf(output, ")");
		look = next_token();
		int flag = 0;
		if (my_strcmp(look._literal, "{")) {
			--tab_cnt;
			flag = 1;
			//fprintf(output, "\n\t");
		}
		parse_stmt();
		if (flag) ++tab_cnt;
		if (!my_strcmp(look._literal, "else")) {
			put_tabs(tab_cnt);
			fprintf(output, "else");
			look = next_token();
			int else_flag = 0;
			if (my_strcmp(look._literal, "{")) {
				--tab_cnt;
				if (my_strcmp(look._literal, "if")) {
					fprintf(output, "\n");
				} else {
					fprintf(output, " ");
				}
				//if (is_ms) {
					//fprintf(output, "\n");
				//}
				//fprintf(output, "\n\t");
				else_flag = 1;
			}
			if (else_flag) ++tab_cnt;
			//++tab_cnt;
			//pre_else = 1;
			parse_stmt();
			//pres_else = 0;
			//--tab_cnt;
		}
	} else if (!my_strcmp(look._literal, "for")) {
		put_tabs(tab_cnt);
		fprintf(output, "for ");
		look = next_token();
		my_assert(!my_strcmp(look._literal, "("), "parse for( expected!");
		fprintf(output, "(");
		look = next_token();
		if (my_strcmp(look._literal, ";")) {
			parse_expr();
		}
		my_assert(!my_strcmp(look._literal, ";"), "for ;1 expected!");
		fprintf(output, "; ");
		look = next_token();
		if (my_strcmp(look._literal, ";")) {
			parse_expr();
		}
		my_assert(!my_strcmp(look._literal, ";"), "for ;2 expected!");
		fprintf(output, "; ");
		look = next_token();
		if (my_strcmp(look._literal, ")")) {
			parse_expr();
		}
		my_assert(!my_strcmp(look._literal, ")"), "parse for) expected!");
		fprintf(output, ")");
		look = next_token();
		if (my_strcmp(look._literal, "{")) {
			fprintf(output, "\n\t");
		}
		//++tab_cnt;
		parse_stmt();
		//--tab_cnt;
	} else if (!my_strcmp(look._literal, "while")) {
		put_tabs(tab_cnt);
		fprintf(output, "while ");
		look = next_token();
		my_assert(!my_strcmp(look._literal, "("), "parse while ( expected!");
		fprintf(output, "(");
		look = next_token();
		parse_expr();
		my_assert(!my_strcmp(look._literal, ")"), "parse while ) expected!");
		fprintf(output, ")");
		look = next_token();
		if (my_strcmp(look._literal, "{")) {
			fprintf(output, "\n\t");
		}
		//++tab_cnt;
		parse_stmt();
		//--tab_cnt;
	} else if (!my_strcmp(look._literal, "continue")) {
		put_tabs(tab_cnt);
		look = next_token();
		my_assert(!my_strcmp(look._literal, ";"), "continue ; expected!");
		look = next_token();
		fprintf(output, "continue;\n");
	} else if (!my_strcmp(look._literal, "break")) {
		put_tabs(tab_cnt);
		look = next_token();
		my_assert(!my_strcmp(look._literal, ";"), "break ; expected!");
		look = next_token();
		fprintf(output, "break;\n");
	} else if (!my_strcmp(look._literal, "return")) {
		put_tabs(tab_cnt);
		look = next_token();
		fprintf(output, "return ");
		if (!my_strcmp(look._literal, ";")) {
			fprintf(output, ";\n");
			look = next_token();
		} else {
			parse_expr();
			my_assert(!my_strcmp(look._literal, ";"), "return ; expected!");
			fprintf(output, ";\n");
			look = next_token();
		}
	} else {
		put_tabs(tab_cnt);
		parse_expr();
		//fprintf(output, "!!!!");
		fprintf(output, ";\n");
		my_assert(!my_strcmp(look._literal, ";"), "End of statement expr should be ;!");
		look = next_token();
	}
}

void parse_program() {
	look = next_token();
	while (cur_scan < src_tail) {
		parse_type_specifier();
		if (!my_strcmp(look._literal, ";")) {
			fprintf(output, ";\n");
			look = next_token();
			continue;
		}
		parse_declarator();
		if (!my_strcmp(look._literal, "{")) {
			if (is_ms) {
				put_tabs(tab_cnt);
			}
			++tab_cnt;
			parse_compound_stmt();
			--tab_cnt;
		} else {
			if (!my_strcmp(look._literal, ";")) {
				fprintf(output, ";\n");
				look = next_token();
				continue;
			} else if (!my_strcmp(look._literal, ",")){
				fprintf(output, ", ");
				look = next_token();
			} else {
				parse_array();
				if (!my_strcmp(look._literal, "=")) {
					fprintf(output, " = ");
					look = next_token();
					parse_initializer();
				}
				if (!my_strcmp(look._literal, ",")) {
					fprintf(output, ", ");
					look = next_token();
				} else if (!my_strcmp(look._literal, ";")){
					fprintf(output, ";\n");
					look = next_token();
					continue;
				} else {
					my_assert(0, "Unknown error!");
				}
			}
			parse_init_declarators();
			my_assert(!my_strcmp(look._literal, ";"), "Not the end of declarations.");
			fprintf(output, ";\n");
			look = next_token();
		}
	}
}

void read_src() {
	char ch;
	while ((ch = fgetc(input)) != EOF) {
		if (src_tail - src_code + 5 >= src_buffer_len) {
			src_buffer_len = src_buffer_len * 2 + 10;
			char *tmp = (char *) malloc(src_buffer_len);
			int i;
			for (i = 0; i < src_tail - src_code; ++i) {
				tmp[i] = src_code[i];
			}
			src_code = tmp;
			src_tail = tmp + i;
		}
		*src_tail++ = ch;
		*src_tail = 0;
	}
}

int main(int argv, char *args[]) {
	if (argv < 3) {
		puts("Usage: ./main <input file name|\"stdin\"> <output file name|\"stdout\"> [-kr|-ms]");
		puts("Default is k&r style.");
		return 0;
	}
	if (!my_strcmp(args[1], "stdin")) {
		input = stdin;
	} else {
		input = fopen(args[1], "r");
	}
	if (!my_strcmp(args[2], "stdout")) {
		output = stdout;
	} else {
		output = fopen(args[2], "w");
	}
	if (argv == 4 && !my_strcmp(args[3], "-ms")) {
		is_ms = 1;
	}
	read_src();
	cur_scan = src_code;
	parse_program();
	return 0;
}