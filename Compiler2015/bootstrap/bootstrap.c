//
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

int INS_ADD = 1,
		INS_SUB = 2,
		INS_MUL = 3,
		INS_DIV = 4,
		INS_OR = 5,
		INS_XOR = 6,
		INS_AND = 7,
		INS_SLLV = 8,
		INS_SRLV = 9,
		INS_SNE = 10,
		INS_SEQ = 11,
		INS_SGT = 12,
		INS_SLT = 13,
		INS_SGE = 14,
		INS_SLE = 15,
		INS_NEG = 16,
		INS_MOVE = 19,
		INS_BNEZ = 20,
		INS_BEQZ = 21,
		INS_PARA = 22,
		INS_CALL = 23,
		INS_PRINT_INT = 24,
		INS_PRINT_STRING = 25,
		INS_MALLOC = 27,
		INS_GETCHAR = 28,
		INS_PUTCHAR = 29,
		INS_REM = 30,
		INS_NOT = 31,
		INS_LD_ADDR = 32,
		INS_RET = 33,
		INS_HALT = 34,
		INS_ARRAY_WRITE = 35,
		INS_ARRAY_READ = 36,
		INS_BLE = 37,
		INS_BGE = 38,
		INS_BLT = 39,
		INS_BGT = 40,
		INS_BNE = 41,
		INS_BEQ = 42;

typedef struct Token Token;
typedef struct Function Function;
typedef struct Array Array;
typedef struct Identifier Identifier;
typedef struct Type Type;
typedef struct Environment Environment;
typedef struct Instruction Instruction;
typedef struct ReturnType ReturnType;
typedef struct Declarator Declarator;
typedef struct Block Block;
typedef struct InitPair InitPair;
typedef struct Operand Operand;
typedef struct Action Action;

char *src_code = 0, *src_tail = 0, *cur_scan = 0;
int src_buffer_len, col = 1, row = 1;
int add_args = 0, blck_cnt = 0, code_changed, *blck_hsh, bfs_cnt, str_const_cnt, arg_num;
int ins_cnt, para_offset, parsing;
int wan_cnt = 0;

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

struct Block {
	int id, in_deg;
	int ins_size, buffer_size;
	Instruction *ins;
	Block *non_condi;
	Block *condi;
} *block_top, *global_init, *opt_que[1000], *cnt_que[1000]; //wait for enhance

struct Function {
	Type *type;
	int level;
	int tmp_cnt;
	char *id;
	Identifier *args;
	Function *nxt;
	Block *block;
	Block *end;
	ReturnType *regs;
} *func_head, *cur_func;

struct Array {
	int num, mul;
	Array *nxt, *pre;
};

int INIT_NONE = 1, INIT_STR = 2, INIT_LIST = 3;

struct Identifier {
	char *id;
	int level, from, is_var;
	int arg_num;
	Array *array;
	Type *type;
	Identifier *nxt;
	int init_type;
	char *init_str;
	char *str_val;
	InitPair *init_list;
	Environment *env_belong;
	Type *type_belong;
} *o_buffer;

struct Type {
	int is_struct;
	int width;
	char *_literal;
	Type *nxt;
	Identifier *mem;
} *type_int, *type_char, *type_void;

struct Environment {
	Environment *pre;
	Type *types;
	Identifier *ids;
} *global, *cur_env;

struct Instruction {
	int ins;
	int ord;
	ReturnType *des, *a, *b;
} *ins_buffer[30000], *cur_ins;

int VIRTUAL_REG = 1, ARRAY_ACCESS = 2, CONST_VAL = 3;

struct ReturnType {
	int ret_type;
	int is_left;
	int const_val;
	Function *func;
	ReturnType *nxt;
	Identifier *ref;
	int reg_num;
	int sp_offset;
	Function *belong;
} *const_one, *const_zero, *nd_buffer[10], *printer;

struct Declarator {
	char *_literal;
	int level;
	Declarator *nxt;
	int is_func;
	Identifier *args;
	Array *dim;
} *empty_decl;

struct InitPair {
	int pos, num;
	char *label;
	InitPair *nxt;
};

struct Register {
	char *_literal;
	ReturnType *ref;
} regs[22], reg_v0, reg_v1;

void my_assert(int, char *);
int my_strcmp(char *, char *);
int my_strlen(char *);
void initialize();
int is_basic_type(Type *);
int str_start_with(char *, char *);
void eat_chars(int);
void eat_useless_chars();
char analy_and_jump(char **);
Token next_token();
void read_src();
Declarator *parse_plain_declarator();
Array *parse_array();
Declarator *parse_declarator();
Declarator *parse_declarators();
Type *parse_type_specifier(Declarator *);
Identifier *parse_parameters();
void parse_initializer(Identifier *var);
void parse_init_declarators(Type *, Declarator *);
void parse_compound_stmt(Block *, Block *);
void parse_stmt(Block *, Block *);
void parse_program();
ReturnType *parse_expr();
ReturnType *parse_assign_expr();
ReturnType *parse_const_expr();
ReturnType *parse_logic_or_expr();
ReturnType *parse_logic_and_expr();
ReturnType *parse_or_expr();
ReturnType *parse_xor_expr();
ReturnType *parse_and_expr();
ReturnType *parse_equality_expr();
ReturnType *parse_relational_expr();
ReturnType *parse_shift_expr();
ReturnType *parse_additive_expr();
ReturnType *parse_cast_expr();
ReturnType *parse_unary_expr();
ReturnType *parse_postfix_expr();
ReturnType *parse_primary_expr();
ReturnType *parse_arguments(Function *);
int can_add(ReturnType *, ReturnType *);
int can_mul(ReturnType *, ReturnType *);
int can_sub(ReturnType *, ReturnType *);
int is_pointer(ReturnType *);
int is_int(ReturnType *);
int is_type();
Function *Function_(Type *, Declarator *, Declarator *);
Array *Array_();
int var_width(Identifier *);
Identifier *Identifier_(Type *, int, Declarator *, Declarator *);
Type *Type_();
void add_var_to_type(Type *, Identifier *);
Environment *Environment_(Environment *);
void add_var_to_env(Identifier *);
void add_to_func(Function *);
ReturnType *ReturnType_();
Declarator *Declarator_();
ReturnType *parse_postfix(ReturnType *);
int can_assign(ReturnType *, ReturnType *);
int is_string(ReturnType *);
void show_ReturnType(ReturnType *);
void show_Variable(Identifier *);
void show_Type(Type *);
int max2(int, int);
Declarator *merge_decl(Declarator *, Declarator *);
void show_Decl(Declarator *);
int can_pass(ReturnType *, ReturnType *);
Identifier *find_id(Identifier *, char *);
Identifier *add_id(Identifier **, Identifier *);
Type *find_type(Type *, char *);
Type *add_type(Type **, Type *);
char *to_string(int);
char *str_cat(char *, char *);
Block *Block_();
void append_ins(Block *, Instruction *ins);
ReturnType *make_const_ReturnType(int x);
Instruction *ins_cons(int, ReturnType *, ReturnType *, ReturnType *);
Instruction *Instruction_();
void show_IR();
char *ReturnType_to_string(ReturnType *);
void show_Instruction(Instruction *);
void show_blck(Block *);
InitPair *InitPair_(int, int, char *);
int cannot_delete(int);
ReturnType *load_address(ReturnType *);
ReturnType *make_func_ReturnType(Function *);
ReturnType *parse_multi_expr();
ReturnType *make_tmp_ReturnType();
ReturnType *array_read(ReturnType *);
ReturnType *array_write(ReturnType *, ReturnType *);
ReturnType *make_var_ReturnType(Identifier *var);
int is_one_dim(ReturnType *);
int para_width(ReturnType *);
char *real_global(char *);
int is_branch(int);
int is_eqiv(ReturnType *, ReturnType *);

int para_width(ReturnType *this) {
	if (this->ref->array || this->ref->level) {
		return 4;
	} else if (this->ref->type == type_int) {
		return 4;
	} else {
		return this->ref->type->width;
	}
}


ReturnType *array_write(ReturnType *l, ReturnType *r) {
	if (r->ret_type == ARRAY_ACCESS) {
		r = array_read(r);
	}
	append_ins(block_top, ins_cons(INS_ARRAY_WRITE, l, r, 0));
	return r;
}

ReturnType *malloc_instruction(ReturnType *size) {
	ReturnType *res = make_tmp_ReturnType();
	res->ref = Identifier_(type_void, 0, 0, empty_decl);
	res->ref->level = 1;
	res->ref->type = type_void;
	append_ins(block_top, ins_cons(INS_MALLOC, res, size, 0));
	return res;
}

ReturnType *binary_instruction(int op, ReturnType *l, ReturnType *r) {
	if (l->ret_type == ARRAY_ACCESS) {
		l = array_read(l);
	}
	if (r->ret_type == ARRAY_ACCESS) {
		r = array_read(r);
	}
	ReturnType *res = make_tmp_ReturnType();
	append_ins(block_top, ins_cons(op, res, l, r));
	res->ref = Identifier_(0, 0, 0, empty_decl);
	return res;
}

InitPair *InitPair_(int idx, int num, char *label) {
	InitPair *res = (InitPair *) malloc(sizeof(InitPair));
	res->pos = idx;
	res->num = num;
	res->label = label;
	res->nxt = 0;
	return res;
}

Instruction *ins_cons(int ins, ReturnType *des, ReturnType *a, ReturnType *b) {
	//my_assert(ins >= 0 && ins <= 40, "???");
	Instruction *res = Instruction_();
	res->ins = ins;
	res->des = des;
	res->a = a;
	res->b = b;
	ins_buffer[ins_cnt++] = res;
	res->ord = ins_cnt;
	return res;
}

ReturnType *make_const_ReturnType(int x) {
	ReturnType *res = ReturnType_();
	res->const_val = x;
	res->ret_type = CONST_VAL;
	res->ref = Identifier_(type_int, 0, 0, Declarator_());
	return res;
}

ReturnType *make_tmp_ReturnType() {
	ReturnType *res = ReturnType_();
	res->ret_type = VIRTUAL_REG;
	res->belong = cur_func;
	res->reg_num = ++cur_func->tmp_cnt;
	res->nxt = cur_func->regs;
	res->sp_offset = 0;
	cur_func->regs = res;
	return res;
}

Block *Block_() {
	Block *res = (Block *) malloc(sizeof(Block));
	res->id = ++blck_cnt;
	res->in_deg = 0;
	res->condi = 0;
	res->non_condi = 0;
	res->ins_size = 0;
	res->buffer_size = 0;
	res->ins = 0;
	return res;
}

void append_ins(Block *this, Instruction *ins) {
	if (cur_env == global && parsing) {
		this = global_init;
	}
	my_assert(this != 0, "where do you want to append?!");
	my_assert(ins != 0, "what ins do you want to append");
	if (this->ins_size + 1 > this->buffer_size) {
		this->buffer_size = this->buffer_size * 2 + 1;
		Instruction *new = malloc(this->buffer_size * sizeof(Instruction));
		Instruction *old = this->ins;
		int i;
		for (i = 0; i < this->ins_size; ++i) {
			new[i].a = old[i].a;
			new[i].b = old[i].b;
			new[i].des = old[i].des;
			new[i].ins = old[i].ins;
			new[i].ord = old[i].ord;
		}
		this->ins = new;
	}
	if (ins->ins == INS_MOVE && ins->des->ref && !ins->des->ref->id && ins->des->reg_num == -1 && ins->des->ref->arg_num == -1) {
		my_assert(0, "smg!");
	}
	this->ins[this->ins_size].a = ins->a;
	this->ins[this->ins_size].b = ins->b;
	this->ins[this->ins_size].des = ins->des;
	this->ins[this->ins_size].ins = ins->ins;
	this->ins[this->ins_size].ord = ins->ord;
	++this->ins_size;
}

char *str_cat(char *a, char *b) {
	if (!a) {
		return b;
	}
	if (!b) {
		return a;
	}
	char *res = malloc(my_strlen(a) + my_strlen(b) + 1), *head = res;
	while (*a) {
		*head++ = *a++;
	}
	while (*b) {
		*head++ = *b++;
	}
	*head = 0;
	return res;
}

char *to_string(int x) {
	if (x < 0) {
		return str_cat("-", to_string(-x));
	}
	int len = 1, pow = 1;
	while (pow * 10 <= x) {
		pow = pow * 10;
		++len;
	}
	char *res = malloc(len + 1), *head = res;
	while (len--) {
		*head++ = (char) (x / pow + '0');
		x %= pow;
		pow /= 10;
	}
	*head = 0;
	return res;
}

Function *find_func(char *id) {
	Function *iter = func_head;
	while (iter) {
		if (!my_strcmp(iter->id, id)) {
			return iter;
		}
		iter = iter->nxt;
	}
	return 0;
}

Identifier *find_id(Identifier *iter, char *id) {
	while (iter && my_strcmp(iter->id, id)) {
		iter = iter->nxt;
	}
	return iter;
}

Identifier *add_id(Identifier **head, Identifier *id) {
	if (!find_id(*head, id->id)) {
		id->nxt = *head;
		*head = id;
		return id;
	}
	return 0;
}

Type *find_type(Type *iter, char *id) {
	while (iter) {
		if (!my_strcmp(iter->_literal, id)) {
			return iter;
		}
		iter = iter->nxt;
	}
	return 0;
}

Type *add_type(Type **head, Type *type) {
	if (!find_type(*head, type->_literal) || !my_strcmp(type->_literal, "")) {
		type->nxt = *head;
		*head = type;
		return type;
	}
	return 0;
}

int can_pass(ReturnType *a, ReturnType *b) {
	//show_ReturnType(a);
	//show_ReturnType(b);
	if (can_assign(a, b)) {
		return 1;
	}
	if (a->ref->array && b->ref->array) {
		Array *_a = a->ref->array->nxt, *_b = b->ref->array->nxt;
		while (_a && _b) {
			if (_a->num != _b->num) {
				return 0;
			}
			_a = _a->nxt;
			_b = _b->nxt;
		}
		return 1;
	}
	//printf("%d %d\n", is_one_dim(a), is_one_dim(b));
	return is_one_dim(a) && is_one_dim(b);
}

void show_Decl(Declarator *decl) {
	printf("%s %d ", decl->_literal, decl->level);
	if (decl->args) {
		Identifier *var = decl->args;
		printf(" (");
		while (var) {
			if (var->nxt) {
				printf("%s,", var->id);
			} else {
				printf("%s) ", var->id);
			}
			var = var->nxt;
		}
	}
	if (decl->dim) {
		Array *iter = decl->dim;
		while (iter) {
			printf("[%d]", iter->num);
			iter = iter->nxt;
		}
	}
	printf("\n");
}

Declarator *merge_decl(Declarator *a, Declarator *b) {
	if (!a) {
		return b;
	}
	Declarator *res = Declarator_();
	res->_literal = b->_literal;
	res->level = a->level + b->level;
	res->nxt = 0;
	res->is_func = b->is_func;
	res->args = b->args;
	Array *iter = a->dim, *tmp, *tail;
	if (a->dim) {
		tail = res->dim = Array_();
		res->dim->num = a->dim->num;
		iter = iter->nxt;
		while (iter) {
			tmp = Array_();
			tmp->num = iter->num;
			tail->nxt = tmp;
			tmp->pre = tail;
			tail = tmp;
			iter = iter->nxt;
		}
		if (b->dim) {
			b->dim->pre = tail;
			tail->nxt = b->dim;
		}
		tail = tail->pre;
		while (tail) {
			tail->mul = tail->nxt->mul * tail->num;
			tail = tail->pre;
		}
	} else {
		res->dim = b->dim;
	}
	return res;
}

int max2(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

int is_string(ReturnType *this) {
	if (this->ref->array && !this->ref->array->nxt && this->ref->type == type_char) {
		return 1;
	}
	if (this->ref->type == type_char && this->ref->level == 1) {
		return 1;
	}
	return 0;
}

int can_assign(ReturnType *l, ReturnType *r) {
	if (l->ref->array || r->ref->array) {
		return 0;
	}
	if (l->ref->type == r->ref->type && !l->ref->level && !r->ref->level) {
		return 1;
	}
	if (is_int(l) && is_int(r)) {
		return 1;
	}
	if ((is_int(l) || l->ref->level) && (is_int(r) || r->ref->level)) {
		return 1;
	}
	return 0;
	/*
	if (l)
	return can_add(l, r) || (l->type == r->type && !l->level && !r->level) || (is_pointer(l) && is_pointer(r)) ||
		   (is_string(l) && is_string(r)) || (is_int(l) && is_pointer(r));
		   */
}

void show_ReturnType(ReturnType *this) {
	if (this->ret_type == CONST_VAL) {
		printf("\tconst value: %d\n", this->const_val);
		return ;
	}
	if (this->func) {
		printf("function: %s\n", this->func->id);
		return ;
	}
	if (this->ref->env_belong == global) {
		printf("%s\n", this->ref->id);
	} else {
		if (this->ref->env_belong) {
			printf("%s %s\n", this->belong->id, this->ref->id);
		} else {
			printf("tmp reg %d\n", (int) this);
		}
	}
	printf("{\n\ttype name: %s\n", this->ref->type->_literal);
	printf("\tpointer level: %d\n", this->ref->level);
	if (this->ref->array) {
		printf("\tarray: ");
		Array *cur = this->ref->array;
		while (cur) {
			printf("[%d]", cur->num);
			cur = cur->nxt;
		}
		printf("\n");
	}
	if (this->is_left) {
		printf("\tleft value\n");
	} else {
		printf("\tright value\n");
	}
	printf("}\n");
}

void show_Variable(Identifier *this) {
	if (cur_env == global) {
		printf("@global ");
	}
	char *tab;
	if (cur_env == global) {
		tab = "";
	} else {
		tab = "\t";
	}
	printf("%s%s %d %s %d ", tab, this->type->_literal, this->level, this->id, this->from);
	if (this->array) {
		printf(" array: ");
		Array *cur = this->array;
		while (cur) {
			printf("[%d]", cur->num);
			cur = cur->nxt;
		}
	}
	printf("\n");
}

int is_int(ReturnType *this) {
	return (this->ref->type == type_char || this->ref->type == type_int) && !this->ref->array && !this->ref->level;
}

int is_pointer(ReturnType *this) {
	return this->ref->level || this->ref->array;
}

int is_one_dim(ReturnType *this) {
	return (this->ref->level || (this->ref->array && !this->ref->array->nxt)) && !(this->ref->level && (this->ref->array && !this->ref->array->nxt));
}

int will_be_consume(ReturnType *this) {
	if (this->ref->array) {
		return !this->ref->array->nxt && !this->ref->level;
	} else if (this->ref->level) {
		return this->ref->level == 0;
	} else {
		my_assert(0, "you should pass a pointer type!");
	}
	return 0;
}

int can_add(ReturnType *l, ReturnType *r) {
	if (can_mul(l, r)) {
		return 1;
	}
	if (is_pointer(l) && is_int(r)) {
		return 1;
	}
	return 0;
}

int can_mul(ReturnType *l, ReturnType *r) {
	return is_int(l) && is_int(r);
}

int can_sub(ReturnType *l, ReturnType *r) {
	if (can_mul(l, r)) {
		return 1;
	}
	if ((is_pointer(l) || l->ref->type == type_int || l->ref->type == type_char) && (r->ref->type == type_int || r->ref->type == type_char)) {
		return 1;
	}
	if (is_pointer(l) && is_pointer(r)) {
		return 1;
	}
	return 0;
}

Function *Function_(Type *type, Declarator *a, Declarator *b) {
	Function *res = (Function *) malloc(sizeof(Function));
	Declarator *c = merge_decl(a, b);
	res->type = type;
	res->level = c->level;
	res->args = c->args;
	res->id = c->_literal;
	res->nxt = 0;
	res->block = 0;
	res->end = Block_();
	res->regs = 0;
	return res;
}

Array *Array_() {
	Array *res = (Array *) malloc(sizeof(Array));
	res->num = 0;
	res->mul = 1;
	res->nxt = 0;
	res->pre = 0;
	return res;
}

int var_width(Identifier *var) {
	int width = -1;
	if (var->level) {
		width = 4;
	} else {
		width = var->type->width;
	}
	my_assert(width != -1, "Try to get the width of an undefined type!");
	if (var->array) {
		width *= var->array->mul * var->array->num;
	}
	return width;
}

Identifier *Identifier_(Type *type, int is_var, Declarator *a, Declarator *b) {
	Identifier *res = (Identifier *) malloc(sizeof(Identifier));
	Declarator *c = merge_decl(a, b);
	res->arg_num = -1;
	res->id = c->_literal;
	res->level = c->level;
	res->type = type;
	res->from = 0;
	res->is_var = is_var;
	res->nxt = 0;
	res->array = c->dim;
	res->init_type = INIT_NONE;
	res->init_str = res->str_val = 0;
	res->init_list = 0;
	return res;
}

Type *Type_() {
	Type *res = (Type *) malloc(sizeof(Type));
	res->is_struct = 0;
	res->mem = 0;
	res->width = -1; //The symbol of empty Type
	res->_literal = ""; //Anon with empty string, prevent re
	res->nxt = 0;
	return res;
}

void add_var_to_type(Type *type, Identifier *var) {
	my_assert(var != 0, "Unknown error in add var to env!");
	my_assert(!(var->level == 0 && var->type == type_void), "cannot define a void variable in struct!");
	my_assert(add_id(&type->mem, var) != 0, "Variable & Variable name constradiction in type!");
	var->type_belong = type;
}

int my_strlen(char *s) {
	int len = 0;
	while (*s) {
		++s;
		++len;
	}
	return len;
}

Environment *Environment_(Environment *pre) {
	Environment *res = (Environment *) malloc(sizeof(Environment));
	res->types = 0;
	res->ids = 0;
	if (pre) {
		res->pre = pre;
	} else {
		res->pre = 0;
	}
	return res;
}

void add_var_to_env(Identifier *var) {
	my_assert(var != 0, "Unknown error in add var to env!");
	my_assert(!(var->level == 0 && var->type == type_void), "cannot define a void variable!");
	if (cur_env == global) {
		my_assert(!find_func(var->id), "func name & id contradiction!");
	}
	if (add_args) {
		var->arg_num = ++arg_num;
	}
	var->env_belong = cur_env;
	my_assert(add_id(&cur_env->ids, var) != 0, "cannot add identifier in current environment!");
}

void add_type_to_env(Type *type) {
	my_assert(!my_strcmp(type->_literal, "") || !find_type(cur_env->types, type->_literal), "type name contradiction!");
	my_assert(add_type(&cur_env->types, type) != 0, "cannot add type in current environment!");
}

void add_to_func(Function *this) {
	my_assert(!find_func(this->id), "rename among func names!");
	my_assert(!find_id(cur_env->ids, this->id), "func and identifier has the same name!");
	this->nxt = func_head;
	func_head = this;
}

Instruction *Instruction_() {
	Instruction *res = (Instruction *) malloc(sizeof(Instruction));
	res->ins = 0;
	res->a = 0;
	res->b = 0;
	res->ins = 0;
	return res;
}

ReturnType *ReturnType_() {
	ReturnType *res = (ReturnType *) malloc(sizeof(ReturnType));
	res->func = 0;
	res->is_left = 0;
	res->ref = 0;
	res->const_val = 0;
	res->nxt = 0;
	res->reg_num = -1;
	return res;
}

Declarator *Declarator_() {
	Declarator *res = (Declarator *) malloc(sizeof(Declarator));
	res->_literal = "";
	res->level = 0;
	res->nxt = 0;
	res->is_func = 0;
	res->args = 0;
	res->dim = 0;
	return res;
}

void show_Type(Type *this) {
	if (this->width != -1) {
		printf("%s [un defined type specifier!]\n", this->_literal);
		return;
	}
	if (!is_basic_type(this)) {
		if (this->is_struct) {
			printf("struct");
		} else {
			printf("union");
		}
		printf(" %s", this->_literal);
		printf(" { ");
		Identifier *mem = this->mem;
		while (mem) {
			printf("%s %s %d ", mem->type->_literal, mem->id, mem->level);
			Array *array = mem->array;
			while (array) {
				printf("[%d]", array->num);
				array = array->nxt;
				if (!array) {
					printf(" ");
				}
			}
			mem = mem->nxt;
		}
		printf(" }\n");
	} else {
		printf("%s\n", this->_literal);
	}
}

int is_basic_type(Type *this) {
	return this == type_char || this == type_void || this == type_int;
}

ReturnType *parse_const_expr() {
//TODO: parse expression (grammar) & check if const (meaning)
	ReturnType *res = parse_logic_or_expr();
	//printf("%s\n", ReturnType_to_string(res));
	my_assert(res->ret_type == CONST_VAL, "Not a const!");
	return res;
}

Identifier *clone_identifier(Identifier *id) {
	Identifier *res = (Identifier *) malloc(sizeof (Identifier));
	res->type = id->type;
	res->level = id->level;
	res->array = id->array;
	res->env_belong = 0;
	res->nxt = 0;
	res->arg_num = -1;
	res->from = 0;
	res->id = "";
	res->init_list = 0;
	res->init_str = 0;
	res->init_type = INIT_NONE;
	res->type_belong = 0;
	return res;
}

ReturnType *parse_assign_expr() {
	ReturnType *l = parse_logic_or_expr();
	char *op;
	if (look._literal[0] == '=' || look._literal[1] == '=' || look._literal[2] == '=') {
		my_assert(l->is_left, "only left value can be assigned!");
		op = look._literal;
		look = next_token();
		ReturnType *r = parse_assign_expr();
		ReturnType *res = 0;
		if (!my_strcmp(op, "+=")) {
			res = binary_instruction(INS_ADD, l, r);
			res->ref = clone_identifier(l->ref);
		} else if (!my_strcmp(op, "-=")) {
			res = binary_instruction(INS_SUB, l, r);
			res->ref = clone_identifier(l->ref);
		} else if (!my_strcmp(op, "*=")) {
			res = binary_instruction(INS_MUL, l, r);
			res->ref = clone_identifier(l->ref);
		} else if (!my_strcmp(op, "/=")) {
			res = binary_instruction(INS_DIV, l, r);
			res->ref = clone_identifier(l->ref);
		} else if (!my_strcmp(op, "%=")) {
			res = binary_instruction(INS_REM, l, r);
			res->ref = clone_identifier(l->ref);
		} else if (!my_strcmp(op, "<<=")) {
			res = binary_instruction(INS_SLLV, l, r);
			res->ref = clone_identifier(l->ref);
		} else if (!my_strcmp(op, ">>=")) {
			res = binary_instruction(INS_SRLV, l, r);
			res->ref = clone_identifier(l->ref);
		} else if (!my_strcmp(op, "&=")) {
			res = binary_instruction(INS_AND, l, r);
			res->ref = clone_identifier(l->ref);
		} else if (!my_strcmp(op, "^=")) {
			res = binary_instruction(INS_XOR, l, r);
			res->ref = clone_identifier(l->ref);
		} else if (!my_strcmp(op, "|=")) {
			res = binary_instruction(INS_OR, l, r);
			res->ref = clone_identifier(l->ref);
		} else {
			res = r;
		}
		if (l->ret_type == ARRAY_ACCESS) {
			array_write(l, res);
		} else {
			if (res->ret_type == ARRAY_ACCESS) {
				res = array_read(res);
			}
			append_ins(block_top, ins_cons(INS_MOVE, l, res, 0));
		}
		l = res;
	}
	return l;
}

ReturnType *parse_logic_or_expr() {
	ReturnType *l = parse_logic_and_expr();
	if (!my_strcmp(look._literal, "||")) {
		Block *one = Block_(), *the_block = block_top, *converge = Block_(), *zero = Block_();
		ReturnType *res = make_tmp_ReturnType();
		res->ref = clone_identifier(const_one->ref);
		block_top = one;
		append_ins(block_top, ins_cons(INS_MOVE, res, const_one, 0));
		block_top = zero;
		append_ins(block_top, ins_cons(INS_MOVE, res, const_zero, 0));
		block_top = the_block;
		if (l->ret_type != CONST_VAL) {
			if (l->ret_type == ARRAY_ACCESS) {
				l = array_read(l);
			}
			append_ins(block_top, ins_cons(INS_BNEZ, 0, l, 0));
			block_top->condi = one;
			block_top = block_top->non_condi = Block_();
		} else {
			if (l->const_val) {
				block_top->non_condi = one;
			}
		}
		while (!my_strcmp(look._literal, "||")) {
			look = next_token();
			ReturnType *r = parse_logic_and_expr();
			my_assert(can_sub(l, r) || can_sub(r, l), "Cannot logic or these 2 types!");
			if ((l->ret_type == CONST_VAL && l->const_val) || (l->ret_type == CONST_VAL && r->ret_type == CONST_VAL)) {
				ReturnType *tmp = make_const_ReturnType(l->const_val || r->const_val);
				r = tmp;
			} else {
				//TODO: short cruit or!
				if (r->ret_type == ARRAY_ACCESS) {
					r = array_read(r);
				}
				append_ins(block_top, ins_cons(INS_BNEZ, 0, r, 0));
				block_top->condi = one;
				block_top = block_top->non_condi = Block_();
			}
			l = r;
		}
		if (l->ret_type == CONST_VAL && l->const_val) {
			block_top->non_condi = one;
		} else {
			block_top->non_condi = zero;
		}
		zero->non_condi = converge;
		one->non_condi = converge;
		block_top = converge;
		return res;
	} else {
		return l;
	}
}

ReturnType *parse_logic_and_expr() {
	ReturnType *l = parse_and_expr();
	if (!my_strcmp(look._literal, "&&")) {
		Block *one = Block_(), *zero = Block_(), *converge = Block_(), *the_block = block_top;
		ReturnType *res = make_tmp_ReturnType();
		res->ref = clone_identifier(const_one->ref);
		block_top = one;
		append_ins(block_top, ins_cons(INS_MOVE, res, const_one, 0));
		block_top = zero;
		append_ins(block_top, ins_cons(INS_MOVE, res, const_zero, 0));
		block_top = the_block;
		if (l->ret_type != CONST_VAL) {
			if (l->ret_type == ARRAY_ACCESS) {
				l = array_read(l);
			}
			append_ins(block_top, ins_cons(INS_BEQZ, 0, l, 0));
			block_top->condi = zero;
			block_top = block_top->non_condi = Block_();
		} else {
			if (l->ret_type == CONST_VAL && !l->const_val) {
				block_top->non_condi = zero;
			}
		}
		while (!my_strcmp(look._literal, "&&")) {
			look = next_token();
			ReturnType *r = parse_and_expr();
			my_assert(can_sub(l, r) || can_sub(r, l), "Cannot logic and these types!");
			if ((l->ret_type == CONST_VAL && !l->const_val) || (l->ret_type == CONST_VAL && r->ret_type == CONST_VAL)) {
				ReturnType *tmp = make_const_ReturnType(l->const_val && r->const_val);
				r = tmp;
			} else {
				//TODO: short cruit and!
				if (r->ret_type == ARRAY_ACCESS) {
					r = array_read(r);
				}
				append_ins(block_top, ins_cons(INS_BEQZ, 0, r, 0));
				block_top->condi = zero;
				block_top = block_top->non_condi = Block_();
			}
			l = r;
		}
		if (l->const_val == CONST_VAL && !l->const_val) {
			block_top->non_condi = zero;
		} else {
			block_top->non_condi = one;
		}
		zero->non_condi = converge;
		one->non_condi = converge;
		block_top = converge;
		return res;
	} else {
		return l;
	}
}

ReturnType *parse_and_expr() {
	ReturnType *l = parse_xor_expr();
	while (!my_strcmp(look._literal, "&")) {
		look = next_token();
		ReturnType *r = parse_xor_expr(), *res = 0;
		my_assert(can_mul(l, r), "Unaddable types!");
		if (l->ret_type == CONST_VAL && r->ret_type == CONST_VAL) {
			res = make_const_ReturnType(l->const_val & r->const_val);
		} else {
			//TODO: instruction and!
			res = binary_instruction(INS_AND, l, r);
			res->ref = clone_identifier(const_one->ref);
		}
		l = res;
	}
	return l;
}

ReturnType *parse_xor_expr() {
	ReturnType *l = parse_or_expr();
	while (!my_strcmp(look._literal, "^")) {
		look = next_token();
		ReturnType *r = parse_or_expr(), *res = 0;
		my_assert(can_mul(l, r), "Unaddable types!");
		if (l->ret_type == CONST_VAL && r->ret_type == CONST_VAL) {
			res = make_const_ReturnType(l->const_val ^ r->const_val);
		} else {
			//TODO: instruction xor!
			res = binary_instruction(INS_XOR, l, r);
			res->ref = clone_identifier(const_one->ref);
		}
		l = res;
	}
	return l;
}

ReturnType *parse_or_expr() {
	ReturnType *l = parse_equality_expr();
	while (!my_strcmp(look._literal, "|")) {
		look = next_token();
		ReturnType *r = parse_equality_expr(), *res = 0;
		my_assert(can_mul(l, r), "cannot | types!");
		if (l->ret_type == CONST_VAL && r->ret_type == CONST_VAL) {
			res = make_const_ReturnType(l->const_val | r->const_val);
		} else {
			//TODO: instruction or
			res = binary_instruction(INS_OR, l, r);
			res->ref = clone_identifier(const_one->ref);
		}
		l = res;
	}
	return l;
}

ReturnType *parse_equality_expr() {
	ReturnType *l = parse_relational_expr();
	while (!my_strcmp(look._literal, "==") || !my_strcmp(look._literal, "!=")) {
		int op = -1;
		if (!my_strcmp(look._literal, "==")) {
			op = INS_SEQ;
		} else {
			op = INS_SNE;
		}
		look = next_token();
		ReturnType *r = parse_relational_expr(), *res = 0;
//		show_ReturnType(l);
//		show_ReturnType(r);
		my_assert(can_sub(l, r), "cannot compare == != types!");
		if (l->ret_type == CONST_VAL && r->ret_type == CONST_VAL) {
			if (op == INS_SEQ) {
				res = make_const_ReturnType(l->const_val == r->const_val);
			} else {
				res = make_const_ReturnType(l->const_val != r->const_val);
			}
		} else {
			//TODO: T_T
			res = binary_instruction(op, l, r);
			res->ref = clone_identifier(const_zero->ref);
		}
		l = res;
	}
	return l;
}

ReturnType *parse_relational_expr() {
	ReturnType *l = parse_shift_expr();
	while (!my_strcmp(look._literal, "<") || !my_strcmp(look._literal, ">") || !my_strcmp(look._literal, ">=") ||
		   !my_strcmp(look._literal, "<=")) {
		int op = -1;
		if (!my_strcmp(look._literal, "<")) {
			op = INS_SLT;
		} else if (!my_strcmp(look._literal, ">")) {
			op = INS_SGT;
		} else if (!my_strcmp(look._literal, ">=")) {
			op = INS_SGE;
		} else {
			op = INS_SLE;
		}
		look = next_token();
		ReturnType *r = parse_shift_expr(), *res = 0;
		//show_ReturnType(l);
		//show_ReturnType(r);
		my_assert(can_sub(l, r), "cannot compare lg types!");
		if (l->ret_type == CONST_VAL && r->ret_type == CONST_VAL) {
			if (op == INS_SLT) {
				res = make_const_ReturnType(l->const_val < r->const_val);
			} else if (op == INS_SGT) {
				res = make_const_ReturnType(l->const_val > r->const_val);
			} else if (op == INS_SLE) {
				res = make_const_ReturnType(l->const_val <= r->const_val);
			} else {
				res = make_const_ReturnType(l->const_val >= r->const_val);
			}
		} else {
			res = binary_instruction(op, l, r);
			res->ref = clone_identifier(const_zero->ref);
		}
		l = res;
	}
	return l;
}

ReturnType *parse_shift_expr() {
	ReturnType *l = parse_additive_expr();
	while (!my_strcmp(look._literal, "<<") || !my_strcmp(look._literal, ">>")) {
		int op = -1;
		if (!my_strcmp(look._literal, "<<")) {
			op = INS_SLLV;
		} else {
			op = INS_SRLV;
		}
		look = next_token();
		ReturnType *r = parse_additive_expr(), *res = 0;
		my_assert(can_mul(l, r), "cannot shift types!");
		if (l->ret_type == CONST_VAL && r->ret_type == CONST_VAL) {
			if (op == INS_SLLV) {
				res = make_const_ReturnType(l->const_val << r->const_val);
			} else {
				res = make_const_ReturnType(l->const_val >> r->const_val);
			}
		} else {
			res = binary_instruction(op, l, r);
			res->ref = clone_identifier(const_zero->ref);
		}
		l = res;
	}
	return l;
}

ReturnType *delta_multipler(ReturnType *this) {
	int width = 1;
	if (is_int(this)) {
		return const_one;
	}
	if (this->ref->array) {
		width = this->ref->array->mul;
		if (this->ref->level) {
			return make_const_ReturnType(width * 4);
		} else {
			my_assert(this->ref->type->width != -1, "width not defined!");
			return make_const_ReturnType(width * this->ref->type->width);
		}
	}
	if (this->ref->level > 1) {
		return make_const_ReturnType(4);
	} else {
		if (this->ref->level) {
			my_assert(this->ref->type->width != -1, "width not defined!");
			width = this->ref->type->width;
		} else {
			my_assert(0, "has no delta!");
		}
	}
	return make_const_ReturnType(width);
}

ReturnType *parse_additive_expr() {
	ReturnType *l = parse_multi_expr();
	while (!my_strcmp(look._literal, "+") || !my_strcmp(look._literal, "-")) {
		int op = -1;
		if (!my_strcmp(look._literal, "+")) {
			op = INS_ADD;
		} else {
			op = INS_SUB;
		}
		look = next_token();
		ReturnType *r = parse_multi_expr(), *res = 0;
		if (l->ret_type == CONST_VAL && r->ret_type == CONST_VAL) {
			if (op == INS_ADD) {
				res = make_const_ReturnType(l->const_val + r->const_val);
			} else {
				res = make_const_ReturnType(l->const_val - r->const_val);
			}
		} else {
			if (op == INS_ADD) {
				if (is_int(l) && is_int(r)) {
					res = binary_instruction(op, l, r);
					res->ref = clone_identifier(const_zero->ref);
				} else if (is_pointer(l) && is_int(r)) {
					res = binary_instruction(INS_MUL, r, delta_multipler(l));
					res->ref = clone_identifier(const_zero->ref);
					res = binary_instruction(op, l, res);
					res->ref = clone_identifier(l->ref);
				} else {
					my_assert(0, "cannot add!");
				}
			} else {
				if (is_int(l) && is_int(r)) {
					res = binary_instruction(op, l, r);
					res->ref = clone_identifier(const_zero->ref);
				} else if (is_pointer(l) && is_int(r)) {
					res = binary_instruction(INS_MUL, r, delta_multipler(l));
					res->ref = clone_identifier(const_zero->ref);
					res = binary_instruction(op, l, r);
					res->ref = clone_identifier(l->ref);
				} else if (is_pointer(l) && is_pointer(r)) {
					res = binary_instruction(op, l, r);
					res->ref = clone_identifier(const_one->ref);
					res = binary_instruction(INS_DIV, res, delta_multipler(l));
					res->ref = clone_identifier(const_one->ref);
				} else {
					my_assert(0, "cannot add!");
				}
			}
		}
		l = res;
	}
	return l;
}

ReturnType *parse_multi_expr() {
	ReturnType *l = parse_cast_expr();
	while (!my_strcmp(look._literal, "*") || !my_strcmp(look._literal, "/") || !my_strcmp(look._literal, "%")) {
		int op = -1;
		if (!my_strcmp(look._literal, "*")) {
			op = INS_MUL;
		} else if (!my_strcmp(look._literal, "/")) {
			op = INS_DIV;
		} else if (!my_strcmp(look._literal, "%")) {
			op = INS_REM;
		}
		look = next_token();
		ReturnType *r = parse_cast_expr(), *res = 0;
		if (l->ret_type == CONST_VAL && r->ret_type == CONST_VAL) {
			if (op == INS_MUL) {
				res = make_const_ReturnType(l->const_val * r->const_val);
			} else if (op == INS_DIV) {
				my_assert(r->const_val, "Try to div 0!");
				res = make_const_ReturnType(l->const_val / r->const_val);
			} else {
				my_assert(r->const_val, "Try to mod 0!");
				res = make_const_ReturnType(l->const_val % r->const_val);
			}
		} else {
			res = binary_instruction(op, l, r);
			res->ref = clone_identifier(const_one->ref);
		}
		l = res;
	}
	return l;
}

int is_type() {
	if (!my_strcmp(look._literal, "int") || !my_strcmp(look._literal, "char") || !my_strcmp(look._literal, "void") ||
		!my_strcmp(look._literal, "struct") || !my_strcmp(look._literal, "union")) {
		return 1;
	}
	if (look.type != 1) {
		return 0;
	}
	Environment *env = cur_env;
	Identifier *id;
	while (env) {
		id = find_id(env->ids, look._literal);
		if (id && !id->is_var) {
			return 1;
		}
		env = env->pre;
	}
	return 0;
}

ReturnType *parse_cast_expr() {
	if (!my_strcmp(look._literal, "(")) {
		look = next_token();
		if (is_type()) {
			ReturnType *res = ReturnType_();
			Declarator *def = Declarator_();
			Type *type = parse_type_specifier(def);
			while (!my_strcmp(look._literal, "*")) {
				++def->level;
				look = next_token();
			}
			res->ref = Identifier_(type, 0, 0, def);
			my_assert(!my_strcmp(look._literal, ")"), "Not closed cast type name!");
			look = next_token();
			ReturnType *this = parse_cast_expr();
			my_assert((this->ref->level || this->ref->type == type_int || this->ref->type == type_char) &&
					  (res->ref->level || res->ref->type == type_int || res->ref->type == type_char), "cannot cast it!");
			this->ref = clone_identifier(res->ref);
			return this;
		} else {
			//This is primary...
			ReturnType *this = parse_expr();
			my_assert(!my_strcmp(look._literal, ")"), "Not closed paren, ) expected!");
			look = next_token();
			return parse_postfix(this);
		}
	} else {
		return parse_unary_expr();
	}
}

ReturnType *parse_unary_expr() {
	if (!my_strcmp(look._literal, "++") || !my_strcmp(look._literal, "--")) {
		int op = -1;
		if (!my_strcmp(look._literal, "++")) {
			op = INS_ADD;
		} else {
			op = INS_SUB;
		}
		look = next_token();
		ReturnType *this = parse_unary_expr(), *res;
		my_assert(this->is_left, "++ or -- expect a left value!");
		if (this->ret_type == ARRAY_ACCESS) {
			//must be a basic type
			res = binary_instruction(op, array_read(this), const_one);
			res->ref = clone_identifier(this->ref);
			array_write(this, res);
		} else {
			if (is_pointer(this)) {
				res = binary_instruction(op, this, delta_multipler(this));
				res->ref = clone_identifier(this->ref);
				append_ins(block_top, ins_cons(INS_MOVE, this, res, 0));
			} else {
				append_ins(block_top, ins_cons(op, this, this, const_one));
				res = this;
			}
		}
		return res;
	} else if (!my_strcmp(look._literal, "sizeof")) {
		look = next_token();
		if (!my_strcmp(look._literal, "(")) {
			look = next_token();
			if (is_type()) {
				Declarator *def = Declarator_();
				Type *type = parse_type_specifier(def);
				int is_pointer = def && def->level, res = 0;
				while (!my_strcmp(look._literal, "*")) {
					look = next_token();
					is_pointer = 1;
				}
				my_assert(!my_strcmp(look._literal, ")"), ") when sizeof!");
				look = next_token();
				if (is_pointer) {
					res = 4;
				} else {
					my_assert(type->width != -1, "try to get the size of incomplete type");
					res = type->width;
				}
				if (def && def->dim) {
					res *= def->dim->num * def->dim->mul;
				}
				return make_const_ReturnType(res);
			} else {
				ReturnType *res = parse_expr();
				my_assert(!my_strcmp(")", look._literal), "here should be a closed expr!");
				look = next_token();
				return res;
			}
		} else {
			ReturnType *this = parse_unary_expr();
			int res = 0;
			if (this->ref->level) {
				res = 4;
			} else {
				my_assert(this->ref->type->width != -1, "try to get the size of incomplete type");
				res = this->ref->type->width;
			}
			return make_const_ReturnType(res);
		}
	} else if (!my_strcmp(look._literal, "&")) {
		//TODO: left value is not the iff condition of address fetch
		look = next_token();
		ReturnType *this = parse_cast_expr();
		my_assert(this->is_left, "has not address!");
		return load_address(this);
	} else if (!my_strcmp(look._literal, "*")) {
		//TODO: T_T
		look = next_token();
		ReturnType *this = parse_cast_expr(), *res = make_tmp_ReturnType();
		if (this->ret_type == ARRAY_ACCESS) {
			this = array_read(this);
		}
		my_assert(this->ref->level || this->ref->array, "only array and pointer can be add *");
		res->ref = clone_identifier(this->ref);
		append_ins(block_top, ins_cons(INS_MOVE, res, this, 0));
		if (res->ref->array) {
			res->ref->array = res->ref->array->nxt;
			if (!res->ref->array) {
				res->is_left = 1;
			}
			if (is_int(res) || res->ref->level) {
				res->ret_type = ARRAY_ACCESS;
			}
		} else {
			res->is_left = 1;
			if (--res->ref->level || is_int(res)) {
				res->ret_type = ARRAY_ACCESS;
			} else {
				res->ret_type = VIRTUAL_REG;
			}
		}
		return res;
	} else if (!my_strcmp(look._literal, "+")) {
		look = next_token();
		ReturnType *this = parse_cast_expr();
		if (this->ret_type == CONST_VAL) {
			return this;
		}
		my_assert(is_int(this), "cannot postivise it!");
		if (this->ret_type == ARRAY_ACCESS) {
			this = array_read(this);
		}
		return this;
	} else if (!my_strcmp(look._literal, "-")) {
		look = next_token();
		ReturnType *this = parse_cast_expr();
		if (this->ret_type == CONST_VAL) {
			this->const_val = -this->const_val;
			return this;
		}
		my_assert(is_int(this), "cannot negtivise it!");
		if (this->ret_type == ARRAY_ACCESS) {
			this = array_read(this);
		}
		ReturnType *res = make_tmp_ReturnType();
		res->ref = clone_identifier(this->ref);
		append_ins(block_top, ins_cons(INS_NEG, res,this, 0));
		return res;
	} else if (!my_strcmp(look._literal, "~")) {
		look = next_token();
		ReturnType *this = parse_cast_expr();
		my_assert(is_int(this), "cannot postivise it!");
		if (this->ret_type == CONST_VAL) {
			this->const_val = ~this->const_val;
			return this;
		}
		if (this->ret_type == ARRAY_ACCESS) {
			this = array_read(this);
		}
		ReturnType *res = make_tmp_ReturnType();
		res->ref = clone_identifier(this->ref);
		append_ins(block_top,ins_cons(INS_NOT, res, this, 0));
		return res;
	} else if (!my_strcmp(look._literal, "!")) {
		look = next_token();
		ReturnType *this = parse_cast_expr();
		my_assert(is_int(this) || is_pointer(this), "cannot postivise it!");
		if (this->ret_type == CONST_VAL) {
			this->const_val = !this->const_val;
			return this;
		} else {
			Block *one = Block_(), *zero = Block_(), *converge = Block_(), *the_block = block_top;
			if (this->ret_type == ARRAY_ACCESS) {
				this = array_read(this);
			}
			ReturnType *res = make_tmp_ReturnType();
			res->ref = clone_identifier(const_one->ref);
			block_top = one;
			append_ins(block_top, ins_cons(INS_MOVE, res, const_one, 0));
			block_top = zero;
			append_ins(block_top, ins_cons(INS_MOVE, res, const_zero, 0));
			block_top = the_block;
			append_ins(block_top, ins_cons(INS_BEQZ, 0, this, 0));
			block_top->condi = one;
			block_top->non_condi = zero;
			block_top = one->non_condi = zero->non_condi = converge;
			return res;
		}
	} else {
		return parse_postfix_expr();
	}
	return 0;
}

ReturnType *load_address(ReturnType *this) {
	ReturnType *res = make_tmp_ReturnType();
	append_ins(block_top, ins_cons(INS_LD_ADDR, res, this, 0));
	res->ref = clone_identifier(this->ref);
	++res->ref->level;
	return res;
}

ReturnType *array_read(ReturnType *this) {
	my_assert(this->ret_type == ARRAY_ACCESS, "only an consumed value can be read!");
	ReturnType *res = make_tmp_ReturnType();
	res->ref = clone_identifier(this->ref);
	append_ins(block_top, ins_cons(INS_ARRAY_READ, res, this, 0));
//	printf("array read\n");
	//show_ReturnType(res);
	return res;
}

ReturnType *parse_postfix(ReturnType *this) {
	for (; ;) {
		if (!my_strcmp(look._literal, "(")) {
			my_assert(this->func != 0, "Not a function! only functions can pass args!");
			look = next_token();
			this = parse_arguments(this->func);
			my_assert(!my_strcmp(look._literal, ")"), "here is a )!"); //TODO: wo zhenshi ri le goule
			look = next_token();
		} else if (!my_strcmp(look._literal, "[")) {
			my_assert(this->ref->level || this->ref->array, "This is not a arrayable type!");
			look = next_token();
			ReturnType *idx = parse_expr();
			my_assert(!idx->ref->level, "Cannot pass a pointer into a array");
			my_assert(idx->ref->type == type_int || idx->ref->type == type_char, "Cannot pass a non-integer to a array");
			if (idx->ret_type == ARRAY_ACCESS) {
				idx = array_read(idx);
			}
			if (idx->ret_type == CONST_VAL) {
				idx = make_const_ReturnType(idx->const_val * delta_multipler(this)->const_val);
			} else {
				if (delta_multipler(this)->const_val != 1) {
					idx = binary_instruction(INS_MUL, idx, delta_multipler(this));
					idx->ref = clone_identifier(const_one->ref);
				}
			}
			if (this->ret_type == ARRAY_ACCESS) {
				if (this->ref->level) {
					this = array_read(this);
				} else {
					this->ret_type = VIRTUAL_REG;
				}
			}
			ReturnType *res = binary_instruction(INS_ADD, this, idx);
			res->ref = clone_identifier(this->ref);
			if (res->ref->array) {
				res->ref->array = res->ref->array->nxt;
				if (!res->ref->array) {
					res->is_left = 1;
				}
				if (is_int(res) || res->ref->level) {
					res->ret_type = ARRAY_ACCESS;
				}
			} else if (res->ref->level) {
				res->is_left = 1;
				if (--res->ref->level || is_int(res)) {
					res->ret_type = ARRAY_ACCESS;
				}
			}
			my_assert(!my_strcmp(look._literal, "]"), "Array access ] expected!");
			look = next_token();
			this = res;
		} else if (!my_strcmp(look._literal, ".")) {
			look = next_token();
			my_assert(!this->ref->level && !this->ref->array, "pointer cannot access members by .");
			my_assert(look.type == 1, "member access identifier expected!");
			Identifier *mem = this->ref->type->mem;
			while (mem && my_strcmp(mem->id, look._literal)) {
				mem = mem->nxt;
			}
			my_assert(mem != 0, "member not found!");
			ReturnType *res = binary_instruction(INS_ADD, this, make_const_ReturnType(mem->from));
			res->ref = clone_identifier(mem);
			res->is_left = !mem->array;
			if (!mem->array && (is_int(res) || res->ref->level)) {
				res->ret_type = ARRAY_ACCESS;
			}
			look = next_token();
			this = res;
		} else if (!my_strcmp(look._literal, "->")) {
			look = next_token();
			my_assert(this->ref->level == 1 || (this->ref->array && !this->ref->array->nxt), "only pointers with one * can access members by ->");
			my_assert(look.type == 1, "ptr member access identifier expected!");
			Identifier *mem = this->ref->type->mem;
			while (mem && my_strcmp(mem->id, look._literal)) {
				mem = mem->nxt;
			}
			my_assert(mem != 0, "has no such member!");
			if (this->ret_type == ARRAY_ACCESS) {
				//this->ret_type = VIRTUAL_REG;
				this = array_read(this);
			}
			ReturnType *res = binary_instruction(INS_ADD, this, make_const_ReturnType(mem->from));
			res->ref = clone_identifier(mem);
			res->is_left = !mem->array;
			if (!res->ref->array && (is_int(res) || res->ref->level)) {
				res->ret_type = ARRAY_ACCESS;
			}
			look = next_token();
			this = res;
//			printf("after ->\n");
//			show_ReturnType(this);
//			printf("%s\n", look._literal);
		} else if (!my_strcmp(look._literal, "++") || !my_strcmp(look._literal, "--")) {
			int op = -1;
			if (!my_strcmp(look._literal, "++")) {
				op = INS_ADD;
			} else {
				op = INS_SUB;
			}
			look = next_token();
			my_assert((this->ref->type == type_char || this->ref->type == type_int || this->ref->level) && !this->ref->array && this->is_left, "not a dec || inc able type");
			ReturnType *val, *res;
			if (this->ret_type == ARRAY_ACCESS) {
				res = array_read(this);
				val = binary_instruction(op, res, const_one);
				val->ref = clone_identifier(this->ref);
				array_write(this, val);
			} else {
				val = binary_instruction(op, this, delta_multipler(this));
				val->ref = clone_identifier(this->ref);
				res = make_tmp_ReturnType();
				append_ins(block_top, ins_cons(INS_MOVE, res, this, 0));
				append_ins(block_top, ins_cons(INS_MOVE, this, val, 0));
				res->ref = clone_identifier(this->ref);
			}
			this = res;
		} else {
			return this;
		}
	}
}

ReturnType *parse_arguments(Function *func) {
	//TODO: check if the arguments suit in the parameters
	if (!my_strcmp(func->id, "__print_int__")) {
		ReturnType *res = parse_assign_expr();
		if (res->ret_type == ARRAY_ACCESS) {
			res = array_read(res);
		}
		append_ins(block_top, ins_cons(INS_PRINT_INT, 0, res, 0));
		return 0;
	} else if (!my_strcmp(func->id, "__print_string__")) {
		ReturnType *res = parse_assign_expr();
		if (res->ret_type == ARRAY_ACCESS) {
			res = array_read(res);
		}
		append_ins(block_top, ins_cons(INS_PRINT_STRING, 0, res, 0));
		return 0;
	} else if (!my_strcmp(func->id, "printf")) {
		ReturnType *format = parse_assign_expr();
		my_assert(is_string(format), "the first para should be a string for printf");
		int arg_cnt = 0, i;
		if (!my_strcmp(look._literal, ",")) {
			look = next_token();
		}
		while (my_strcmp(look._literal, ")")) {
			ReturnType *tmp = parse_assign_expr();
			if (tmp->ret_type == ARRAY_ACCESS) {
				tmp = array_read(tmp);
			}
			nd_buffer[arg_cnt++] = tmp;
			if (!my_strcmp(look._literal, ",")) {
				look = next_token();
			}
		}
		if (arg_cnt) {
			ReturnType *para_buffer = make_var_ReturnType(o_buffer);
			for (i = 0; i < arg_cnt; ++i) {
				//my_assert(nd_buffer[i]->width == 4 || nd_buffer[i]->is_const, "cannot be passed!");
				ReturnType *addr = binary_instruction(INS_ADD, para_buffer, make_const_ReturnType(i * 4));
				addr->ret_type = ARRAY_ACCESS;
				array_write(addr, nd_buffer[i]);
			}
			append_ins(block_top, ins_cons(INS_PARA, 0, para_buffer, const_one));
			append_ins(block_top, ins_cons(INS_PARA, 0, format, const_one));
			append_ins(block_top, ins_cons(INS_CALL, 0, printer, 0));
		} else {
			append_ins(block_top, ins_cons(INS_PRINT_STRING, 0, format, 0));
		}
	} else if (!my_strcmp(func->id, "getchar")) {
		my_assert(!my_strcmp(look._literal, ")"), "getchar is a totally void arguments function!");
		ReturnType *res = make_tmp_ReturnType();
		res->ref = Identifier_(type_int, 0, 0, empty_decl);
		append_ins(block_top, ins_cons(INS_GETCHAR, res, 0, 0));
		return res;
	} else if (!my_strcmp(func->id, "putchar")) {
		ReturnType *tmp = parse_assign_expr();
		//show_ReturnType(tmp);
		//my_assert(is_int(tmp), "only int & char can be put as char");
		my_assert(!my_strcmp(look._literal, ")"), "putchar expect a closed arguments )!");
		if (tmp->ret_type == ARRAY_ACCESS) {
			tmp = array_read(tmp);
		}
		append_ins(block_top, ins_cons(INS_PUTCHAR, 0, tmp, 0));
		return 0;
	} else if (!my_strcmp(func->id, "exit")) {
		ReturnType *tmp = parse_assign_expr();
		my_assert(is_int(tmp), "how can you push a non-int value?");
		if (tmp->ret_type == ARRAY_ACCESS) {
			tmp = array_read(tmp);
		}
		append_ins(block_top, ins_cons(INS_HALT, 0, tmp, 0));
		my_assert(!my_strcmp(look._literal, ")"), "too many arguments pass to exit!");
		return 0;
	} else if (!my_strcmp(func->id, "malloc")) {
		ReturnType *tmp = parse_assign_expr();
		if (tmp->ret_type == ARRAY_ACCESS) {
			tmp = array_read(tmp);
		}
		my_assert(is_int(tmp), "malloc should pass a int!");
		my_assert(!my_strcmp(look._literal, ")"), "too many arguments pass to malloc!");
		return malloc_instruction(tmp);
	} else {
		int arg_cnt = 0, i;
		ReturnType *nd_buffer[20];
		while (my_strcmp(look._literal, ")")) {
			ReturnType *tmp = parse_assign_expr();
			nd_buffer[arg_cnt++] = tmp;
			if (!my_strcmp(look._literal, ",")) {
				look = next_token();
			}
		}
		ReturnType *l = ReturnType_();
		Identifier *arg;
		for (arg = func->args, i = arg_cnt - 1; arg && i >= 0; arg = arg->nxt, --i) {
			l->ref = clone_identifier(arg);
			my_assert(can_pass(l, nd_buffer[i]), "Cannot pass arguments due to type!");
			if (nd_buffer[i]->ret_type == ARRAY_ACCESS) {
				nd_buffer[i] = array_read(nd_buffer[i]);
			}
			ReturnType *bind = ReturnType_();
			bind->ref = arg;
			append_ins(block_top, ins_cons(INS_PARA, 0, nd_buffer[i], bind));
			//printf("push %s\n", arg->id);
		}
		my_assert((!arg && i < 0) /*|| !func->args*/, "arguments number error!");
		ReturnType *res = make_tmp_ReturnType();
		Declarator *decl = Declarator_();
		decl->level = func->level;
		res->ref = Identifier_(func->type, 0, 0, decl);
		append_ins(block_top, ins_cons(INS_CALL, res, make_func_ReturnType(func), 0));
		return res;
	}
	return 0;
}

ReturnType *parse_postfix_expr() {
//This is postfixes
	return parse_postfix(parse_primary_expr());
}

ReturnType *make_var_ReturnType(Identifier *var) {
	if (cur_func) {
		ReturnType *iter = cur_func->regs;
		while (iter && iter->ref != var) {
			iter = iter->nxt;
		}
		if (iter) {
			return iter;
		}
	}
//	printf("%d %s %d %s\n", (int) var, var->id, var->env_belong == global, cur_func->id);
//	printf("%d, %d\n", look.row - 1, look.col);
//	printf("%s\n", look._literal);
//	if (!my_strcmp(var->id, "result") && var->env_belong != global && !my_strcmp(cur_func->id, "main")) {
//		int x;
//		++x;
//	}
	my_assert(var->is_var, "a variable expected!");
	ReturnType *res = ReturnType_();
	res->ret_type = VIRTUAL_REG;
	res->ref = var;
	res->belong = cur_func;
	res->is_left = !var->array;
	if (var->env_belong != global) {
		res->nxt = cur_func->regs;
		cur_func->regs = res;
	}
	return res;
}

ReturnType *make_func_ReturnType(Function *func) {
	ReturnType *res = ReturnType_();
	res->func = func;
	Identifier *type_id = Identifier_(func->type, 0, 0, Declarator_());
	type_id->level = func->level;
	type_id->type = func->type;
	res->ref = type_id;
	return res;
}

ReturnType *parse_primary_expr() {
	if (look.type == 1) {
		Environment *env;
		Identifier *var;
		for (env = cur_env; env; env = env->pre) {
			for (var = env->ids; var; var = var->nxt) {
				if (!my_strcmp(var->id, look._literal)) {
					look = next_token();
					return make_var_ReturnType(var);
				}
			}
		}
		Function *func;
		for (func = func_head; func; func = func->nxt) {
			if (!my_strcmp(func->id, look._literal)) {
				look = next_token();
				return make_func_ReturnType(func);
			}
		}
		my_assert(0, "Undeclared variable!");
	} else if (look.type == 2) {
		ReturnType *res = make_const_ReturnType(look.int_val);
		look = next_token();
		return res;
	} else if (look.type == 3) {
		ReturnType *res = make_const_ReturnType(look.char_val);
		look = next_token();
		return res;
	} else if (look.type == 4) {
		//make a fake variable in global
		Declarator *tmp_decl = Declarator_();
		tmp_decl->_literal = str_cat("$string", to_string(++str_const_cnt));
		tmp_decl->dim = Array_();
		tmp_decl->dim->num = my_strlen(look.str_val) + 1;
		tmp_decl->dim->mul = 1;
		Identifier *id = Identifier_(type_char, 1, 0, tmp_decl);
		id->init_type = INIT_STR;
		id->init_str = look._literal;
		id->str_val = look.str_val;
		//printf("%s\n", look.str_val);
		//add it into the environment
		Environment *reservation = cur_env;
		cur_env = global;
		add_var_to_env(id);
		cur_env = reservation;
		//return the address
		look = next_token();
		return make_var_ReturnType(id);
	} else if (!my_strcmp(look._literal, "(")) {
		look = next_token();
		ReturnType *res = parse_expr();
		my_assert(!my_strcmp(look._literal, ")"), "not a close primary!");
		look = next_token();
		return res;
	} else {
		my_assert(0, "WTF in primary expr");
	}
	return 0;
}

ReturnType *parse_expr() {
	ReturnType *res = parse_assign_expr();
	while (!my_strcmp(look._literal, ",")) {
		look = next_token();
		res = parse_assign_expr();
	}
	return res;
}

void my_assert(int condition, char *s) {
	if (!condition) {
		printf("%s\n", s);
		char *tmp = cur_scan;
		while (*tmp != '\n' && tmp < src_tail) {
			putchar(*tmp++);
		}
		printf("\n<%d, %d> %s\n", look.row - 1, look.col, look._literal);
		exit(1);
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
		while (cur_scan < src_tail && (*cur_scan == '\n' || *cur_scan == '\t' || *cur_scan == ' ' || *cur_scan == '\r')) {
			eat_chars(1);
		}
		if (cur_scan < src_tail && *cur_scan == '#') {
			while (cur_scan < src_tail && *cur_scan != '\n') {
				eat_chars(1);
			}
			eat_chars(1);
		}
		if (cur_scan < src_tail && *cur_scan == '/' && cur_scan[1] == '/') {
			while (cur_scan < src_tail && *cur_scan != '\n') {
				eat_chars(1);
			}
			eat_chars(1);
		}
		if (cur_scan < src_tail && *cur_scan == '/' && cur_scan[1] == '*') {
			eat_chars(2);
			while ((*cur_scan != '*' || cur_scan[1] != '/')) {
				eat_chars(1);
			}
			eat_chars(2);
		}
	}
}

char analy_and_jump(char **s) {
	char res;
	if (**s != '\\') {
		res = **s;
		(*s) += 1;
		return res;
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
		int val = 0;
		my_assert((*tail >= '0' && *tail <= '9') || (*tail >= 'A' && *tail <= 'F') || (*tail >= 'a' && *tail <= 'f'),
				  "only \\x has no way to trans meaning!");
		while (*tail != '\0' &&
			   ((*tail >= '0' && *tail <= '9') || (*tail >= 'A' && *tail <= 'F') || (*tail >= 'a' && *tail <= 'f'))) {
			val = val * 16;
			if (*tail >= '0' && *tail <= '9') {
				val += *tail - '0';
			} else {
				val += *tail - 'A' + 10;
			}
			++tail;
		}
		*s = tail;
		return (char) val;
	} else {
		char *tail = *s + 1;
		int val = 0;
		my_assert(*tail >= '0' && *tail <= '7', "\\ should followed with oct numbers");
		while (*tail >= '0' && *tail <= '7') {
			val = val * 8 + *tail++ - '0';
		}
		*s = tail;
		return (char) val;
	}
	return 0;
}

Token next_token() {
	//printf("# get next token...\n");
	int ans = 0;
	Token res;
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
	if ((*cur_scan >= 'a' && *cur_scan <= 'z') || (*cur_scan >= 'A' && *cur_scan <= 'Z') ||
		*cur_scan == '_') { //IDENTIFIER
		char *tail = cur_scan + 1;
		while (tail < src_tail && ((*tail >= 'a' && *tail <= 'z') || (*tail >= 'A' && *tail <= 'Z') || *tail == '_' ||
								   (*tail >= '0' && *tail <= '9'))) {
			++tail;
		}
		if (tail - cur_scan > ans) { //IDENTIFIER
			ans = (int) (tail - cur_scan);
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
			ans = (int) (tail - cur_scan);
			res.type = 2;
			res.int_val = val;
		}
	}
	if (str_start_with(cur_scan, "0x") || str_start_with(cur_scan, "0X")) { //INT_CONST heximal
		int val = cur_scan[2] - '0';
		char *tail = cur_scan + 3;
		while (tail < src_tail &&
			   ((*tail >= '0' && *tail <= '9') || (*tail >= 'A' && *tail <= 'F') || (*tail >= 'a' && *tail <= 'f'))) {
			val = val * 16;
			if (*tail >= '0' && *tail <= '9') {
				val += *tail - '0';
			} else if (*tail >= 'a' && *tail <= 'f') {
				val += *tail - 'a' + 10;
			} else {
				val += *tail - 'A' + 10;
			}
			++tail;
		}
		if (tail - cur_scan > ans) {
			ans = (int) (tail - cur_scan);
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
			ans = (int) (tail - cur_scan);
			res.type = 3;
			res.char_val = val;
		}
	}
	if (*cur_scan == '\"') { //STRING_CONST
		char *tail = cur_scan + 1;
		while (tail < src_tail && (*tail != '\"' || tail[-1] == '\\')) {
			if (*tail == '\\' && tail[1] == '\n') {
				tail += 2;
				continue;
			}
			my_assert(*tail != '\n', "Enter exists in pair of quotes!");
			++tail;
		}
		my_assert(*cur_scan == '\"', "Not a closed string!");
		if (tail + 1 - cur_scan > ans) {
			ans = (int) (tail - cur_scan + 1);
			res.type = 4;
			char *tmp = res.str_val = (char *) malloc(tail - cur_scan + 1 + 5);
			tail = cur_scan + 1;
			while (tail < src_tail && (*tail != '\"' || tail[-1] == '\\')) {
				if (*tail == '\\' && tail[1] == '\n') {
					tail += 2;
					continue;
				}
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
	my_assert(ans, "Unknown error!");
	char *j = res._literal = (char *) malloc(ans + 1), *i;
	for (i = cur_scan; i - cur_scan < ans;) {
		if (res.type == 4 && *i == '\\' && i[1] == '\n') {
			i += 2;
		}
		*j++ = *i++;
	}
	*j = 0;
	//printf("# %d, %d: %s\n", res.row, res.col, res._literal);
	eat_chars(ans);
	eat_useless_chars();
	return res;
}

Declarator *parse_plain_declarator() {
	Declarator *res = Declarator_();
	while (!my_strcmp(look._literal, "*")) {
		look = next_token();
		++res->level;
	}
	my_assert(look.type == 1, "parse plain decl IDENTIFIER expected!");
	res->_literal = look._literal;
	look = next_token();
	return res;
}

Array *parse_array() {
	Array *res = 0;
	if (!my_strcmp(look._literal, "[")) {
		Array *tmp, *nxt;
		while (!my_strcmp(look._literal, "[")) {
			tmp = Array_();
			look = next_token();
			tmp->num = -1;
			if (my_strcmp(look._literal, "]")) {
				ReturnType *num = parse_const_expr();
				my_assert(num->ret_type == CONST_VAL, "Const expression for array definition expected!");
				my_assert(num->const_val >= 0, "Const expr should larger than 0!");
				tmp->num = num->const_val;
				tmp->nxt = res;
				res = tmp;
			} else {
				look = next_token();
				tmp->num = -1;
				tmp->nxt = res;
				res = tmp;
			}
			my_assert(!my_strcmp(look._literal, "]"), "] expected!");
			look = next_token();
		}
		nxt = tmp = 0;
		int mul = 1;
		while (res) {
			mul *= res->num;
			nxt = res->nxt;
			res->nxt = tmp;
			tmp = res;
			res = nxt;
			if (nxt) {
				nxt->mul = mul;
			}
		}
		res = tmp;
		while (tmp->nxt) {
			tmp->nxt->pre = tmp;
			tmp = tmp->nxt;
		}
	}
	return res;
}

Declarator *parse_declarator() {
	Declarator *res = parse_plain_declarator();
	if (!my_strcmp(look._literal, "(")) {
		res->is_func = 1;
		res->args = parse_parameters();
	}
	res->dim = parse_array();
	return res;
}

Declarator *parse_declarators() {
	Declarator *res = 0, *tmp = 0;
	for (res = parse_declarator(); !my_strcmp(look._literal, ",");) {
		look = next_token();
		tmp = parse_declarator();
		tmp->nxt = res;
		res = tmp;
	}
	return res;
}

Type *parse_type_specifier(Declarator *defs) {
	if (look.type == 1) {
		Environment *env = cur_env;
		Identifier *id;
//		printf("%s\n", look._literal);
		while (env) {
//			if (cur_env == global) {
//				printf("%d\n", find_type(cur_env->types, look._literal));
//				printf("%d\n", find_id(cur_env->ids, look._literal));
//			}
			if ((id = find_id(env->ids, look._literal)) != 0) {
				look = next_token();
				my_assert(!id->is_var, "variable cannot be used as type name!");
				defs->dim = id->array;
				defs->level = id->level;
				return id->type;
			}
			env = env->pre;
		}
		my_assert(0, "This id cannot be used as type specifier...");
	} else if (!my_strcmp(look._literal, "int")) {
		look = next_token();
		return type_int;
	} else if (!my_strcmp(look._literal, "char")) {
		look = next_token();
		return type_char;
	} else if (!my_strcmp(look._literal, "void")) {
		look = next_token();
		return type_void;
	} else if (!my_strcmp(look._literal, "struct") || !my_strcmp(look._literal, "union")) {
		int is_struct = !my_strcmp(look._literal, "struct");
		char *id = "";
		look = next_token();
		Type *res = 0;
		int same = 1;
		if (look.type == 1 || !my_strcmp(look._literal, "{")) {
			if (look.type == 1) {
				id = look._literal;
				look = next_token();
				Environment *env = cur_env;
				while (env && !res) {
					if ((res = find_type(env->types, id)) != 0) {
						break;
					}
					env = env->pre;
					same = 0;
				}
			}
			if (!res || (!same && res->width == -1)) {
				/*Only the struct or union in the same scope can be overide declaration*/
				res = Type_();
				res->_literal = id;
				res->is_struct = is_struct;
				add_type_to_env(res);
			}
			my_assert(res->is_struct == is_struct, "Contradict with declaration before!");
			if (!my_strcmp(look._literal, "{")) {
				my_assert(res->width == -1, "redifinition of this type");
				look = next_token();
				res->width = 0;
				while (my_strcmp(look._literal, "}")) {
					Declarator *def = Declarator_();
					Type *sub_type = parse_type_specifier(def);
					if (my_strcmp(look._literal, ";")) {
						Declarator *mem = parse_declarators();
						while (mem) {
							my_assert(!mem->is_func, "You cannot define function in struct or union");
							Identifier *this = Identifier_(sub_type, 1, def, mem);
							if (is_struct) {
								this->from = res->width;
								res->width += var_width(this);
							} else {
								this->from = 0;
								res->width = max2(var_width(this), sub_type->width);
							}
							add_var_to_type(res, this);
							mem = mem->nxt;
						}
					} else {
						//anonymous member exists
						if (!my_strcmp(sub_type->_literal, "")) {
							Identifier *mem = sub_type->mem, *tmp = 0;
							while (mem) {
								tmp = mem->nxt;
								if (is_struct) {
									mem->from += res->width;
								}
								add_var_to_type(res, mem);
								mem = tmp;
							}
							if (res->is_struct) {
								res->width += sub_type->width;
								if (res->width % 4) {
									res->width += 4 - res->width % 4;
								}
							} else {
								res->width = max2(res->width, sub_type->width);
							}
						} else {
							sub_type->nxt = cur_env->types;
							cur_env->types = sub_type;
						}
					}
					my_assert(!my_strcmp(look._literal, ";"), "Unexpected end of delarators, we need ;");
					look = next_token();
				}
				look = next_token();
				if (res->width % 4) {
					res->width += 4 - res->width % 4;
				}
				return res;
			} else {
				return res;
			}
		}
	} else {
		my_assert(0, "Not a type specifier!");
	}
	return 0;
}

Identifier *parse_parameters() {
	Identifier *res = 0;
	if (!my_strcmp(look._literal, "(")) {
		int cnt = 0;
		for (look = next_token(); my_strcmp(look._literal, ")");) {
			Declarator *def = Declarator_(), *decl = Declarator_();
			Type *type = parse_type_specifier(def);
			if (!my_strcmp(look._literal, "*") || look.type == 1) {
				while (!my_strcmp(look._literal, "*")) {
					look = next_token();
					++decl->level;
				}
				if (look.type == 1) {
					decl->_literal = look._literal;
					look = next_token();
					decl->dim = parse_array();
				}
			}
			Identifier *tmp = Identifier_(type, 1, def, decl);
			if (tmp->type == type_void && tmp->level == 0) {
				my_assert(!cnt && !my_strcmp(tmp->id, ""), "you cannot pass a pure void into a function!");
			}
			tmp->nxt = res;
			res = tmp;
			if (!my_strcmp(look._literal, ",")) {
				look = next_token();
			}
		}
		look = next_token();
	}
	return res;
}

Identifier *find_str(char *s) {
	Identifier *iter = global->ids;
	while (iter && my_strcmp(iter->id, s)) {
		iter = iter->nxt;
	}
	return iter;
}

void parse_initializer(Identifier *var) {
	InitPair *init = 0;
	//printf("# parse %s for initializer\n", var->id);
	if (!my_strcmp(look._literal, "{")) {
		Array *idx = Array_();
		int not_closed = 1, pre_expr = 0, dim = -1, ignore = 0;
		look = next_token();
		while (not_closed) {
			if (!my_strcmp(look._literal, "}")) {
				idx = idx->pre;
				look = next_token();
				if (--not_closed == 0) {
					break;
				}
			} else if (!my_strcmp(look._literal, "{")) {
				idx->nxt = Array_();
				idx->nxt->pre = idx;
				idx = idx->nxt;
				look = next_token();
				pre_expr = 0;
				++not_closed;
			} else if (!my_strcmp(look._literal, ",")) {
				my_assert(idx != 0, "where am i?");
				++idx->num;
				my_assert(pre_expr, ", expects expression before it!");
				look = next_token();
				pre_expr = 0;
			} else {
				ReturnType *res = parse_assign_expr();
				if (var->array) {
					Array *_array = var->array, *_idx = idx;
					while (_idx->pre) {
						_idx = _idx->pre;
					}
					int delta = 0;
					while (_idx) {
						if (_array) {
							delta += _idx->num * _array->mul;
							_array = _array->nxt;
						} else if (idx->num) {
							//printf("warning: hui jia kan kan ni ma zha mei zha\n");
							ignore = 1;
						}
						_idx = _idx->nxt;
					}
					if (ignore) {
						ignore = 0;
					} else {
						if (cur_env == global) {
							if (res->ret_type == CONST_VAL) {
								InitPair *tmp = InitPair_(delta, res->const_val, 0);
								tmp->nxt = init;
								init = tmp;
								//printf("# %s: %d, %d\n", var->id, delta, res->const_val);
							} else if (res->ref->env_belong == global && res->ref->id[0] == '$') {
								Identifier *str = find_str(res->ref->id);
								int i;
								for (i = 0; str->str_val[i]; ++i) {
									InitPair *tmp = InitPair_(delta + i, str->str_val[i], 0);
									tmp->nxt = init;
									init = tmp;
								}
							} else {
								Identifier *str = find_str(res->ref->id);
								int i, found = 0;
								if (res->ret_type == CONST_VAL) {
									for (i = global_init->ins_size - 1; i >= 0; --i) {
										if (global_init->ins[i].des == res && global_init->ins[i].ins == INS_LD_ADDR) {
											InitPair *tmp = InitPair_(delta + i, 0, str->id);
											tmp->nxt = init;
											init = tmp;
											found = 1;
											break;
										}
									}
								}
								my_assert(found, "what\'s up?");
							}
						} else {
							ReturnType *tar = make_var_ReturnType(var);
							if (var->level) {
								delta *= 4;
							} else if (var->type == type_int) {
								delta *= 4;
							} else if (var->type != type_char) {
								my_assert(0, "shen me gui!");
							}
							ReturnType *addr = binary_instruction(INS_ADD, tar, make_const_ReturnType(delta));
							addr->ret_type = ARRAY_ACCESS;
							addr->ref = Identifier_(var->type, 0, 0, empty_decl);
							array_write(addr, res);
						}
					}
				} else if (!ignore) {
					ReturnType *var_ret = make_var_ReturnType(var);
					if (cur_env == global) {
						my_assert(res->ref->id[0] == '$', "should be a const string!");
						Identifier *str = find_str(res->ref->id);
						if (is_string(res) && is_string(var_ret)) {
							//TODO: assign it!
							if (var->array && !var->nxt) {
								int i;
								for (i = 0; str->str_val[i]; ++i) {
									InitPair *tmp = InitPair_(i, str->str_val[i], 0);
									tmp->nxt = init;
									init = tmp;
								}
							} else if (var->level == 1) {
								InitPair *tmp = InitPair_(0, 0, str->id);
								tmp->nxt = init;
								init = tmp;
							}
						} else if (((var->type == type_int || var->type == type_char || var->level) && is_int(res)) ||
								   (var->level && res->ref->array)) {
							//TODO: assign it!
							InitPair *tmp = InitPair_(0, 0, str->id);
							tmp->nxt = init;
							init = tmp;
						} else {
							my_assert(0, "global initial assignment seem to be conservative!");
						}
					} else {
						my_assert(can_assign(var_ret, res), "Cannot assign the initializer to the variable!");
						if (res->ref->id[0] == '$' && var->array) {
							Identifier *str = find_str(res->ref->id);
							int i;
							for (i = 0; str->str_val[i]; ++i) {
								ReturnType *addr = binary_instruction(INS_ADD, var_ret, make_const_ReturnType(i));
								addr->ret_type = ARRAY_ACCESS;
								addr->ref = Identifier_(var->type, 0, 0, empty_decl);
								array_write(addr, make_const_ReturnType(str->str_val[i]));
							}
						} else {
							if (res->ret_type == ARRAY_ACCESS) {
								res = array_read(res);
							}
							append_ins(block_top, ins_cons(INS_MOVE, var_ret, res, 0));
						}
					}
					ignore = 1;
				} else {
					//printf("warning: hui jia kan kan ni ma zha mei zha\n");
				}
				pre_expr = 1;
			}
			if (!idx->pre) {
				dim = max2(dim, idx->num);
			}
		}
		if (var->array->num == -1) {
			var->array->num = dim;
		}
	} else {
		ReturnType *res = parse_assign_expr();
		my_assert(!var->array || res->ref->id[0] == '$', "array must be initilized by a list!");
		if (cur_env == global) {
			if (is_string(res) && (var->type == type_char && (var->level == 1 || (var->array && !var->array->nxt)))) {
				Identifier *str = find_str(res->ref->id);
				//TODO: assign it!
				if (var->type == type_char && var->level == 1) {
					InitPair *tmp = InitPair_(0, 0, str->id);
					tmp->nxt = init;
					init = tmp;
				} else {
					int i;
					for (i = 0; str->str_val[i]; ++i) {
						InitPair *tmp = InitPair_(i, str->str_val[i], 0);
						tmp->nxt = init;
						init = tmp;
					}
				}
			} else if ((var->type == type_int || var->type == type_char || var->level) && is_int(res)) {
				my_assert(res->ret_type == CONST_VAL, "In global variable should be initilized as a const!");
				//TODO: assign it!
				InitPair *tmp = InitPair_(0, res->const_val, 0);
				tmp->nxt = init;
				init = tmp;
			} else {
				my_assert(0, "single/global initial assignment seem to be conservative!");
			}
		} else {
			if (res->ref->id[0] == '$' && var->array) {
				Identifier *str = find_str(res->ref->id);
				ReturnType *var_ret = make_var_ReturnType(var);
				int i;
				for (i = 0; str->str_val[i]; ++i) {
					ReturnType *addr = binary_instruction(INS_ADD, var_ret, make_const_ReturnType(i));
					addr->ret_type = ARRAY_ACCESS;
					addr->ref = Identifier_(var->type, 0, 0, empty_decl);
					array_write(addr, make_const_ReturnType(str->str_val[i]));
				}
			} else {
				if (res->ret_type == ARRAY_ACCESS) {
					res = array_read(res);
				}
				append_ins(block_top, ins_cons(INS_MOVE, make_var_ReturnType(var), res, 0));
			}
		}
	}
	if (cur_env == global) {
		var->init_type = INIT_LIST;
		var->init_list = init;
	}
}

void parse_init_declarators(Type *this, Declarator *def) {
	Declarator *decl;
	for (decl = parse_declarator(); ; decl = parse_declarator()) {
		Identifier *var = Identifier_(this, 1, def, decl);
		add_var_to_env(var);
		if (!my_strcmp(look._literal, "=")) {
			look = next_token();
			my_assert(!(def && def->is_func) && !decl->is_func, "you cannot initilize a function! _parse_init_decls");
			//printf("# parse initializer!\n");
			parse_initializer(var);
			//printf("# prob @ initilizer?!\n");
		}
		if (my_strcmp(look._literal, ",")) {
			break;
		} else {
			look = next_token();
		}
	}
}

void parse_compound_stmt(Block *iter_strt, Block *iter_end) {
	cur_env = Environment_(cur_env);
	int is_func_body = 0;
	if (add_args) {
		arg_num = 0;
		my_assert(cur_func != 0, "Unknown error in add arguments!");
		Identifier *args = cur_func->args, *rev = 0, *nxt = 0;
		while (args) {
			Identifier *new = Identifier_(args->type, 1, empty_decl, empty_decl);
			new->id = args->id;
			new->array = args->array;
			new->level = args->level;
			new->type = args->type;
			add_var_to_env(new);
			args = args->nxt;
		}
		add_args = 0;
		is_func_body = 1;
	}
	my_assert(!my_strcmp(look._literal, "{"), "compound statement{ expected!");
	look = next_token();
	while (my_strcmp(look._literal, "}")) {
		if (my_strcmp(look._literal, "typedef")) {
			if (is_type()) {
				Declarator *def = Declarator_();
				Type *type = parse_type_specifier(def);
				if (!my_strcmp(look._literal, ";")) {
					look = next_token();
					continue;
				}
				parse_init_declarators(type, def);
				my_assert(!my_strcmp(look._literal, ";"), "compound stmt expected ; for declaration...");
				look = next_token();
			} else {
				parse_stmt(iter_strt, iter_end);
			}
		} else {
			look = next_token();
			Declarator *def = Declarator_(), *decl;
			Type *type = parse_type_specifier(def);
			decl = parse_declarators();
			while (decl) {
				add_var_to_env(Identifier_(type, 0, 0, decl));
				decl = decl->nxt;
			}
			my_assert(!my_strcmp(look._literal, ";"), "everything end with ;");
		}
	}
	if (is_func_body) {
		block_top = block_top->non_condi = cur_func->end;
	}
	look = next_token();
	cur_env = cur_env->pre;
}

void parse_stmt(Block *iter_strt, Block *iter_end) {
	if (!my_strcmp(look._literal, ";")) {
		look = next_token();
	} else if (!my_strcmp(look._literal, "{")) {
		parse_compound_stmt(iter_strt, iter_end);
	} else if (!my_strcmp(look._literal, "if")) {
		look = next_token();
		my_assert(!my_strcmp(look._literal, "("), "parse if ( expected!");
		look = next_token();
		ReturnType *expr = parse_expr();
		//show_ReturnType(expr);
		my_assert(is_pointer(expr) || is_int(expr), "cannot be used as logic expr! if");
		Block *the_block = block_top, *new_end = Block_();
		if (expr->ret_type == ARRAY_ACCESS) {
			expr = array_read(expr);
		}
		append_ins(block_top, ins_cons(INS_BNEZ, 0, expr, 0));
		my_assert(!my_strcmp(look._literal, ")"), "parse if) expected!");
		block_top = the_block->condi = Block_();
		look = next_token();
		parse_stmt(iter_strt, iter_end);
		block_top->non_condi = new_end;
		if (!my_strcmp(look._literal, "else")) {
			block_top = the_block->non_condi = Block_();
			look = next_token();
			parse_stmt(iter_strt, iter_end);
			block_top->non_condi = new_end;
		} else {
			the_block->non_condi = new_end;
		}
		block_top = new_end;
	} else if (!my_strcmp(look._literal, "for")) {
		look = next_token();
		my_assert(!my_strcmp(look._literal, "("), "parse for( expected!");
		look = next_token();
		if (my_strcmp(look._literal, ";")) {
			parse_expr();
		}
		my_assert(!my_strcmp(look._literal, ";"), "for ;1 expected!");
		look = next_token();
		Block *loop = Block_();
		block_top = block_top->non_condi = loop;
		if (my_strcmp(look._literal, ";")) {
			ReturnType *expr = parse_expr();
			if (expr->ret_type == ARRAY_ACCESS) {
				expr = array_read(expr);
			}
			append_ins(block_top, ins_cons(INS_BNEZ, 0, expr, 0));
			my_assert(is_pointer(expr) || is_int(expr), "cannot be used as logic expr! for");
		} else {
			append_ins(block_top, ins_cons(INS_BNEZ, 0, const_one, 0));
		}
		Block *end = Block_();
		Block *body = block_top->condi = Block_();
		block_top->non_condi = end;
		//show_blck(block_top);
		//show_blck(body);
		my_assert(!my_strcmp(look._literal, ";"), "for ;2 expected!");
		look = next_token();
		Block *done = Block_();
		if (my_strcmp(look._literal, ")")) {
			block_top = done;
			parse_expr();
			//show_blck(done);
		}
		my_assert(!my_strcmp(look._literal, ")"), "parse for) expected!");
		look = next_token();
		block_top = body;
		parse_stmt(done, end);
		//show_blck(body);
		block_top->non_condi = done;
		done->non_condi = loop;
		block_top = end;
	} else if (!my_strcmp(look._literal, "while")) {
		look = next_token();
		my_assert(!my_strcmp(look._literal, "("), "parse while ( expected!");
		look = next_token();
		Block *loop = Block_();
		Block *end = Block_();
		Block *condi = Block_();
		block_top = block_top->non_condi = condi;
		ReturnType *expr = parse_expr();
		//show_ReturnType(expr);
		my_assert(is_int(expr) || is_pointer(expr), "cannot use as condition");
		my_assert(is_pointer(expr) || is_int(expr), "cannot be used as logic expr! while");
		my_assert(!my_strcmp(look._literal, ")"), "parse while ) expected!");
		if (expr->ret_type == ARRAY_ACCESS) {
			expr = array_read(expr);
		}
		append_ins(block_top, ins_cons(INS_BNEZ, 0, expr, 0));
		block_top->condi = loop;
		block_top->non_condi = end;
		block_top = block_top->condi;
		look = next_token();
		parse_stmt(condi, end);
		block_top->non_condi = condi;
		block_top = end;
	} else if (!my_strcmp(look._literal, "continue")) {
		my_assert(iter_strt != 0, "you cannot continue out of an iteration");
		look = next_token();
		my_assert(!my_strcmp(look._literal, ";"), "continue ; expected!");
		look = next_token();
		block_top->non_condi = iter_strt;
		block_top = Block_();
	} else if (!my_strcmp(look._literal, "break")) {
		my_assert(iter_strt != 0, "you cannot break out of an iteration");
		look = next_token();
		my_assert(!my_strcmp(look._literal, ";"), "break ; expected!");
		look = next_token();
		block_top->non_condi = iter_end;
		block_top = Block_();
	} else if (!my_strcmp(look._literal, "return")) {
		my_assert((int) cur_func, "you cannot return out of a function");
		look = next_token();
		//TODO: block top = func end
		//block_top->non_condi = cur_func->end;
		if (!my_strcmp(look._literal, ";")) {
			my_assert(cur_func->type == type_void && cur_func->level == 0, "void function should have void return value");
			append_ins(block_top, ins_cons(INS_RET, 0, 0, 0));
			block_top->non_condi = cur_func->end;
			look = next_token();
		} else {
			ReturnType *expr = parse_expr();
			if (expr->ret_type == ARRAY_ACCESS) {
				expr = array_read(expr);
			}
			append_ins(block_top, ins_cons(INS_RET, 0, expr, 0));
			block_top->non_condi = cur_func->end;
			ReturnType *func_type = ReturnType_();
			func_type->ref = clone_identifier(const_one->ref);
			func_type->ref->type = cur_func->type;
			func_type->ref->level = cur_func->level;
			//show_ReturnType(func_type);
			//show_ReturnType(expr);
			my_assert(can_assign(func_type, expr), "cannot return it as the result!");
			my_assert(!my_strcmp(look._literal, ";"), "return ; expected!");
			look = next_token();
		}
		block_top = Block_();
	} else {
		parse_expr();
		my_assert(!my_strcmp(look._literal, ";"), "End of statement expr should be ;!");
		look = next_token();
	}
}

void show_Function(Function *func) {
	printf("@func %s(", func->id);
	Identifier *var = func->args;
	if (var) {
		while (var) {
			if (var->nxt) {
				printf("@[%s %d] %s %d, ", var->type->_literal, var->level, var->id, var->from);
			} else {
				printf("@[%s %d] %s %d)\n", var->type->_literal, var->level, var->id, var->from);
			}
			var = var->nxt;
		}
	} else {
		printf("):\n");
	}

}

void parse_program() {
	parsing = 1;
	look = next_token();
	while (cur_scan < src_tail) {
		if (my_strcmp(look._literal, "typedef")) {
			Declarator *def = Declarator_();
			Type *type = parse_type_specifier(def);
			if (!my_strcmp(look._literal, ";")) {
				look = next_token();
				continue;
			}
			Declarator *head = parse_declarator();
			if (head->is_func) {
				for (cur_func = func_head; cur_func; cur_func = cur_func->nxt) {
					if (!my_strcmp(cur_func->id, head->_literal)) {
						break;
					}
				}
				if (cur_func) {
					Identifier *a = cur_func->args;
					Identifier *b = head->args;
					my_assert(type == cur_func->type, "Diff ret type with pre def");
					while (a && b) {
						my_assert(a->type == b->type, "Diff with pre def type!");
						my_assert(a->level == b->level, "Diff with pre def pointer lv!");
						my_assert(a->array == b->array, "Diff with pre array!");
						a = a->nxt;
						b = b->nxt;
					}
				} else {
					cur_func = Function_(type, def, head);
					add_to_func(cur_func);
				}
			}
			if (!my_strcmp(look._literal, "{")) {
				if (!my_strcmp(cur_func->id, "__my_fake_printf__")) {
					printer = ReturnType_();
					printer->func = cur_func;
				}
				my_assert(type->mem || is_basic_type(type), "the return type has no instance!");
				cur_func->args = head->args;
				my_assert(head->is_func, "How do you define a function without parameters?!");
				add_args = 1;
				block_top = cur_func->block = Block_();
				cur_func->end = Block_();
				parse_compound_stmt(0, 0);
				my_assert(cur_env == global, "somewhere not exit?!");
			} else {
				if (!my_strcmp(look._literal, ";")) {
					if (!head->is_func) {
						Identifier *var = Identifier_(type, 1, def, head);
						add_var_to_env(var);
					}
					look = next_token();
					continue;
				} else if (!my_strcmp(look._literal, ",")) {
					if (!head->is_func) {
						Identifier *var = Identifier_(type, 1, def, head);
						add_var_to_env(var);
					}
					look = next_token();
				} else {
					my_assert(!head->dim || !head->is_func,
							  "An declarator cannot be a function and an array meanwhile");
					Identifier *var = Identifier_(type, 1, def, head);
					if (!my_strcmp(look._literal, "=")) {
						look = next_token();
						my_assert(!(def && def->is_func) && !head->is_func,
								  "you cannot initilize a function! _parse_program_head");
						add_var_to_env(var);
						parse_initializer(var);
					}
					if (!my_strcmp(look._literal, ",")) {
						look = next_token();
					} else if (!my_strcmp(look._literal, ";")) {
						look = next_token();
						continue;
					} else {
						my_assert(0, "Unknown error!");
					}
				}
				parse_init_declarators(type, def);
				my_assert(!my_strcmp(look._literal, ";"), "Not the end of declarations.");
				look = next_token();
			}
		} else {
			//TODO: I wanna get bonus!
			look = next_token();
			Declarator *def = Declarator_(), *decl;
			Type *type = parse_type_specifier(def);
			decl = parse_declarators();
			while (decl) {
				add_var_to_env(Identifier_(type, 0, 0, decl));
				decl = decl->nxt;
			}
			my_assert(!my_strcmp(look._literal, ";"), "everything end with ;");
			look = next_token();
		}
		cur_func = 0;
	}
	parsing = 0;
}

void read_src() {
	char ch;
	//TODO: %.4d
	src_code = "void __my_fake_printf__(char *format, int *args) {\
	int idx = 0;\
	while (*format) {\
		if (*format == '%') {\
			if (format[1] == 'd') {\
				__print_int__(args[idx++]);\
			} else if (format[1] == 'c') {\
				putchar(args[idx++]);\
			} else if (format[1] == 's') {\
				__print_string__(args[idx++]);\
			} else if (format[1] == '%') {\
				putchar('%');\
			} else if (format[1] == '0') {\
				int width = format[2] - '0', x = args[idx++], len = 0, y;\
				y = x;\
				if (x < 0) {\
					x = -x;\
					y = -y;\
					putchar('-');\
					--width;\
				}\
				while (x) {\
					x /= 10;\
					--width;\
				}\
				while (width > 0) {\
					putchar('0');\
					--width;\
				}\
				__print_int__(y);\
				format += 2;\
			} else {\
				int width = format[2] - '0', x = args[idx++], len = 0, y;\
				y = x;\
				if (x < 0) {\
					x = -x;\
					y = -y;\
					putchar('-');\
				}\
				while (x) {\
					x /= 10;\
					--width;\
				}\
				while (width > 0) {\
					putchar('0');\
					--width;\
				}\
				__print_int__(y);\
				format += 2;\
			}\
			++format;\
		} else {\
			putchar(*format);\
		}\
		++format;\
	}\
}\n";
	src_buffer_len = my_strlen(src_code);
	src_tail = src_code + src_buffer_len;

	while ((ch = getchar()) != -1) {
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
		//if (ch == '!' && !my_strcmp(src_tail - 21, "//end of my compiler!")) {
		if (ch == '!') {
			if (++wan_cnt == 30) {
				break;
			}
		} else {
			wan_cnt = 0;
		}
	}

}

void initialize() {
	cur_env = global = Environment_(0);

	type_int = Type_();
	type_int->_literal = "int";
	type_int->width = 4;
	type_char = Type_();
	type_char->_literal = "char";
	type_char->width = 1;
	type_void = Type_();
	type_void->width = 1;

	global->types = type_char;
	type_char->nxt = type_int;
	type_int->nxt = type_void;

	Declarator *tmp = Declarator_();
	tmp->level = 0;
	tmp->is_func = 1;
	tmp->_literal = "printf";
	add_to_func(Function_(type_void, 0, tmp));
	tmp->level = 0;
	tmp->is_func = 1;
	tmp->_literal = "getchar";
	add_to_func(Function_(type_char, 0, tmp));
	tmp->level = 0;
	tmp->is_func = 1;
	tmp->_literal = "puts";
	add_to_func(Function_(type_void, 0, tmp));
	tmp->level = 0;
	tmp->is_func = 1;
	tmp->_literal = "putchar";
	add_to_func(Function_(type_void, 0, tmp));
	tmp->level = 0;
	tmp->is_func = 1;
	tmp->_literal = "exit";
	add_to_func(Function_(type_void, 0, tmp));
	tmp->level = 0;
	tmp->is_func = 1;
	tmp->_literal = "freopen";
	add_to_func(Function_(type_void, 0, tmp));
	tmp->level = 1;
	tmp->is_func = 1;
	tmp->_literal = "malloc";
	add_to_func(Function_(type_void, 0, tmp));
	tmp->level = 1;
	tmp->is_func = 1;
	tmp->_literal = "__print_int__";
	add_to_func(Function_(type_void, 0, tmp));
	tmp->level = 1;
	tmp->is_func = 1;
	tmp->_literal = "__print_string__";
	add_to_func(Function_(type_void, 0, tmp));
	tmp->level = 1;
	tmp->is_func = 0;
	tmp->_literal = "stdin";
	add_var_to_env(Identifier_(type_void, 1, 0, tmp));
	//TODO: ___print_one_int___ ___print_the_string___ ___get_one_int___

	tmp->dim = Array_(); tmp->dim->num = 100;
	tmp->_literal = "__printf_buffer";
	o_buffer = Identifier_(type_int, 1, 0, tmp);
	add_var_to_env(o_buffer);

	empty_decl = Declarator_();

	const_one = make_const_ReturnType(1);
	const_zero = make_const_ReturnType(0);

	read_src();
	cur_scan = src_code;

	empty_decl = Declarator_();
}

void show_blck(Block *blck) {
	printf("__label%d:\n", blck->id);
	int i;
	for (i = 0; i < blck->ins_size; ++i) {
		printf("\t");
		show_Instruction(blck->ins + i);
		if (is_branch(blck->ins[i].ins)) {
			printf("__label%d\n", blck->condi->id);
			if (i + 1 != blck->ins_size) {
				show_Instruction(blck->ins + i + 1);
				my_assert(0, "what happened?");
			}
		}
	}
	if (blck->non_condi) {
		printf("\tj __label%d\n", blck->non_condi->id);
	} else {
		Function *iter = func_head;
		while (iter) {
			if (blck == iter->end) {
				return;
			}
			iter = iter->nxt;
		}
		my_assert(0, "???");
	}
}

char *ReturnType_to_string(ReturnType *res) {
	if (res->ret_type == CONST_VAL) {
		return to_string(res->const_val);
	}
	if (res->func) {
		return res->func->id;
	}
	if (res->reg_num == -1) {
		return res->ref->id;
	} else {
		return str_cat("$", to_string(res->reg_num));
	}
	my_assert(0, "undefined to string in ret-type");
	return 0;
}

void IR2ins_load_addr(char *reg, ReturnType *this) {
	if (this->reg_num == -1) {
		if (this->ref->env_belong == global) {
			printf("\tla %s, %s\n", reg, real_global(this->ref->id));
		} else {
			printf("\tla %s, %d($sp)\n", reg, this->sp_offset);
		}
	} else {
		printf("\tulw %s, %d($sp)\n", reg, this->sp_offset);
	}
}

int fit_in_word(ReturnType *this) {
	if (this->reg_num != -1) {
		return 4;
	}
	if (this->ref->array) {
		if (this->ref->arg_num != -1) {
			return 4;
		}
		return 0;
	}
	if (this->ref->level) {
		return 4;
	}
	if (this->ref->type == type_int) {
		return 4;
	}
	if (this->ref->type == type_char) {
		return 1;
	}
	return 0;
}

void IR2ins_load_value(char *reg, ReturnType *this) {
	if (this->ret_type == CONST_VAL) {
		printf("\tli %s, %d\n", reg, this->const_val);
		return;
	}
	int fit = fit_in_word(this);
	if (this->reg_num == -1) {
		if (this->ref->env_belong == global) {
			if (fit) {
				if (fit == 1) {
					printf("\tlb %s, %s\n", reg, real_global(this->ref->id));
				} else {
					printf("\tulw %s, %s\n", reg, real_global(this->ref->id));
				}
			} else {
				printf("\tla %s, %s\n", reg, real_global(this->ref->id));
			}
		} else {
			if (fit) {
				if (fit == 1) {
					printf("\tlb %s, %d($sp)\n", reg, this->sp_offset);
				} else {
					printf("\tulw %s, %d($sp)\n", reg, this->sp_offset);
				}
			} else {
				if (this->ref->arg_num != -1 && this->ref->array) {
					printf("\tulw %s, %d($sp)\n", reg, this->sp_offset);
				} else {
					printf("\tla %s, %d($sp)\n", reg, this->sp_offset);
				}
			}
		}
	} else {
		printf("\tulw %s, %d($sp)\n", reg, this->sp_offset);
	}
}

char *real_global(char *str) {
	if (str[0] == '$') {
		return str;
	} else {
		return str_cat("__", str);
	}
}

void IR2ins_store_back(ReturnType *this, char *reg) {
	if (this->reg_num == -1) {
		if (this->ref->env_belong == global) {
			if (fit_in_word(this) == 1) {
				printf("\tsb %s, %s\n", reg, this->ref->id);
			} else {
				printf("\tusw %s, %s\n", reg, real_global(this->ref->id));
			}
		} else {
			if (fit_in_word(this) == 1) {
				printf("\tsb %s, %d($sp)\n", reg, this->sp_offset);
			} else {
				printf("\tusw %s, %d($sp)\n", reg, this->sp_offset);
			}
		}
	} else {
		printf("\tusw %s, %d($sp)\n", reg, this->sp_offset);
	}
}

void show_Instruction(Instruction *ins) {
	if (INS_LD_ADDR == ins->ins) {
		printf("# %s = &%s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a));
		IR2ins_load_addr("$t1", ins->a);
		IR2ins_store_back(ins->des, "$t1");
	} else if (INS_MUL == ins->ins) {
		printf("# %s = %s * %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tmul $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_DIV == ins->ins) {
		printf("# %s = %s / %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tdiv $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_REM == ins->ins) {
		printf("# %s = %s %% %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\trem $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_ADD == ins->ins) {
		printf("# %s = %s + %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tadd $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_SUB == ins->ins) {
		printf("# %s = %s - %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tsub $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_SLLV == ins->ins) {
		printf("# %s = %s << %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tsllv $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_SRLV == ins->ins) {
		printf("# %s = %s >> %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tsrlv $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_AND == ins->ins) {
		printf("# %s = %s & %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tand $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_OR == ins->ins) {
		printf("# %s = %s | %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tor $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_XOR == ins->ins) {
		printf("# %s = %s ^ %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\txor $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_NOT == ins->ins) {
		printf("# %s = ~%s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a));
		IR2ins_load_value("$t1", ins->a);
		//IR2ins_load_value("$t2", ins->b);
		printf("\tnot $t0, $t1\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_SGT == ins->ins) {
		printf("# %s = %s > %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tsgt $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_SLT == ins->ins) {
		printf("# %s = %s < %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tslt $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_SGE == ins->ins) {
		printf("# %s = %s >= %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tsge $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_SLE == ins->ins) {
		printf("# %s = %s <= %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tsle $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_BNEZ == ins->ins) {
		printf("# if %s != 0 goto \n", ReturnType_to_string(ins->a));
		IR2ins_load_value("$t0", ins->a);
		printf("\tbnez $t0, ");
	} else if (INS_BEQZ == ins->ins) {
		printf("# if %s == 0 goto \n", ReturnType_to_string(ins->a));
		IR2ins_load_value("$t0", ins->a);
		printf("\tbeqz $t0, ");
	} else if (INS_PARA == ins->ins) {
		//TODO: T_T
		printf("# para %s\n", ReturnType_to_string(ins->a));
		para_offset += para_width(ins->b);
		printf("\t# %d($sp)\n", para_offset);
		IR2ins_load_value("$t0", ins->a);
		if (is_pointer(ins->b) || is_int(ins->b)) {
			if (ins->b->ref->level == 0 && ins->b->ref->type == type_char) {
				printf("\tsb $t0, -%d($sp)\n", para_offset);
			} else {
				printf("\tusw $t0, -%d($sp)\n", para_offset);
			}
		} else {
			int i;
			for (i = 0; i < ins->b->ref->type->width; i += 4) {
				printf("\tulw $t1, %d($t0)\n", i);
				printf("\tusw $t1, %d($sp)\n", i - para_offset);
			}
		}
	} else if (INS_CALL == ins->ins) {
		para_offset = 0;
		if (ins->des) {
			printf("# call %s %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a));
			printf("\tjal __func%s\n", ins->a->func->id);
			if (fit_in_word(ins->des)) {
				IR2ins_store_back(ins->des, "$v0");
			} else {
				IR2ins_load_value("$t1", ins->des);
				int i;
				for (i = 0; i < ins->des->ref->type->width; i += 4) {
					printf("\tulw $t0, %d($v0)\n", i);
					printf("\tusw $t0, %d($t1)\n", i);
				}
			}
		} else {
			printf("# call %s\n", ReturnType_to_string(ins->a));
			printf("\tjal __func%s\n", ins->a->func->id);
		}
	} else if (INS_RET == ins->ins) {
		if (ins->a) {
			printf("# ret %s\n", ReturnType_to_string(ins->a));
			IR2ins_load_value("$v0", ins->a);
			//printf("j __label%d\n", ins->a->belong->end->id);
		} else {
			printf("# ret \n");
			//printf("j __label%d\n", ins->a->belong->end->id);
		}
	} else if (INS_HALT == ins->ins) {
		printf("# exit \n");
		IR2ins_load_value("$a0", ins->a);
		printf("\tli $v0, 17\n");
		printf("\tsyscall\n");
	} else if (INS_MOVE == ins->ins) {
		printf("# %s <- %s, width: %d move\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a), ins->des->ref->type->width);
		IR2ins_load_value("$t1", ins->a);
		if (is_int(ins->des) || ins->des->ref->level) {
			IR2ins_store_back(ins->des, "$t1");
		} else {
			IR2ins_load_value("$t2", ins->des);
			int i;
			for (i = 0; i < ins->des->ref->type->width; i += 4) {
				printf("\tulw $t0, %d($t1)\n", i);
				printf("\tusw $t0, %d($t2)\n", i);
			}
		}
	} else if (INS_MALLOC == ins->ins) {
		printf("# malloc %s, %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a));
		IR2ins_load_value("$a0", ins->a);
		printf("\tli $v0, 9\n");
		printf("\tsyscall\n");
		IR2ins_store_back(ins->des, "$v0");
	} else if (INS_PRINT_INT == ins->ins) {
		printf("# printint %s\n", ReturnType_to_string(ins->a));
		IR2ins_load_value("$a0", ins->a);
		printf("\tli $v0, 1\n");
		printf("\tsyscall\n");
	} else if (INS_PRINT_STRING == ins->ins) {
		printf("# printstring %s\n", ReturnType_to_string(ins->a));
		IR2ins_load_value("$a0", ins->a);
		printf("\tli $v0, 4\n");
		printf("\tsyscall\n");
	} else if (INS_PUTCHAR == ins->ins) {
		printf("# putchar %s\n", ReturnType_to_string(ins->a));
		IR2ins_load_value("$a0", ins->a);
		printf("\tli $v0, 11\n");
		printf("\tsyscall\n");
	} else if (INS_GETCHAR == ins->ins) {
		printf("# getchar %s\n", ReturnType_to_string(ins->des));
		printf("\tli $v0, 12\n");
		printf("\tsyscall\n");
		IR2ins_store_back(ins->des, "$v0");
	} else if (INS_SNE == ins->ins) {
		printf("# %s = %s != %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tsne $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_SEQ == ins->ins) {
		printf("# %s = %s == %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a),
			   ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tseq $t0, $t1, $t2\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_NEG == ins->ins) {
		printf("# %s = -%s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a));
		IR2ins_load_value("$t1", ins->a);
		printf("\tneg $t0, $t1\n");
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_ARRAY_READ == ins->ins) {
		//TODO array read
		printf("# %s = *%s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a));
		IR2ins_load_value("$t1", ins->a);
		if (ins->a->ref->type == type_char && !ins->a->ref->level) {
			printf("\tlb $t0, 0($t1)\n");
		} else {
			printf("\tulw $t0, 0($t1)\n");
		}
		IR2ins_store_back(ins->des, "$t0");
	} else if (INS_ARRAY_WRITE == ins->ins) {
		//TODO array write
		printf("# *%s = %s\n", ReturnType_to_string(ins->des), ReturnType_to_string(ins->a));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t0", ins->des);
		if (ins->des->ref->type == type_char && !ins->des->ref->level) {
			printf("\tsb $t1, 0($t0)\n");
		} else {
			printf("\tusw $t1, 0($t0)\n");
		}
	} else if (INS_BLE == ins->ins) {
		printf("# if %s <= %s goto\n", ReturnType_to_string(ins->a), ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tble $t1, $t2, ");
	} else if (INS_BLT == ins->ins) {
		printf("# if %s < %s goto\n", ReturnType_to_string(ins->a), ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tblt $t1, $t2, ");
	} else if (INS_BGE == ins->ins) {
		printf("# if %s >= %s goto\n", ReturnType_to_string(ins->a), ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tbge $t1, $t2, ");
	} else if (INS_BGT == ins->ins) {
		printf("# if %s > %s goto\n", ReturnType_to_string(ins->a), ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tbgt $t1, $t2, ");
	} else if (INS_BEQ == ins->ins) {
		printf("# if %s == %s goto\n", ReturnType_to_string(ins->a), ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tbeq $t1, $t2, ");
	} else if (INS_BNE == ins->ins) {
		printf("# if %s != %s goto\n", ReturnType_to_string(ins->a), ReturnType_to_string(ins->b));
		IR2ins_load_value("$t1", ins->a);
		IR2ins_load_value("$t2", ins->b);
		printf("\tbne $t1, $t2, ");
	} else {
		printf("%d\n", ins->ins);
		my_assert(0, "try to show unknown ins");
	}
}

void show_static() {
	printf(".data\n");
	Identifier *iter = global->ids;
	while (iter) {
		if (iter->is_var) {
			if (iter->id[0] == '$') {
				printf("\t%s:\t", iter->id);
			} else {
				printf("\t__%s:\t", iter->id);
			}
			if (iter->init_type == INIT_STR) {
				printf(".asciiz\t%s\n", iter->init_str);
			} else if (iter->init_type == INIT_NONE) {
				printf(".space\t%d\n", var_width(iter));
			} else {
				int n = -1;
				if (iter->array) {
					n = iter->array->mul * iter->array->num;
				} else {
					n = 1;
				}
				InitPair **list = (InitPair **) malloc(n * sizeof(InitPair *)), *pair = iter->init_list;
				while (pair) {
					list[pair->pos] = pair;
					pair = pair->nxt;
				}
				int i;
				if (iter->type == type_char && iter->level == 0) {
					printf(".byte\t");
				} else {
					printf(".word\t");
				}
				for (i = 0; i < n; ++i) {
					if (list[i]) {
						if (list[i]->label) {
							printf("%s", real_global(list[i]->label));
						} else {
							printf("%d", list[i]->num);
						}
					} else {
						printf("0");
					}
					if (i + 1 < n) {
						printf(",");
					} else {
						printf("\n");
					}
				}
			}
		}
		iter = iter->nxt;
	}
	printf(".globl main\n");
}

void show_IR() {
	show_static();
	printf(".text\n");
	blck_hsh = (int *) malloc((blck_cnt + 1) * 4);
	int i;
	for (i = 0; i < blck_cnt + 1; ++i) {
		blck_hsh[i] = 0;
	}
	++bfs_cnt;
	Function *func = func_head;
	while (func) {
		if (func->block) {
			ReturnType *i;
			int stack_size = 4, ra;//4 for $ra!
			for (i = func->regs; i; i = i->nxt) {
				if (i->reg_num == -1) {
					if (i->ref->env_belong == global) {
					} else {
						if (i->ref->id) {
							if (i->ref->arg_num != -1) {
								stack_size += para_width(i);
							} else {
								stack_size += var_width(i->ref);
							};
						}
					}
				} else {
					stack_size += 4;
				}
			}
			ra = stack_size;
			for (i = func->regs; i; i = i->nxt) {
				if (i->ref->arg_num != -1) {
					ReturnType *j = func->regs;
					while (j) {
						if (j->ref->arg_num != -1 && j->ref->arg_num <= i->ref->arg_num) {
							i->sp_offset -= para_width(j);
						}
						j = j->nxt;
					}
					i->sp_offset += stack_size;
					if (i->sp_offset < ra) {
						ra = i->sp_offset;
					}
					//printf("arguments %s %d\n", i->ref->id, i->sp_offset);
				}
			}
			ra -= 4;
			int loc = ra;
			for (i = func->regs; i; i = i->nxt) if (i->ref->arg_num == -1 && i->ref->env_belong != global) {
					if (i->reg_num == -1) {
						loc -= var_width(i->ref);
						i->sp_offset = loc;
					} else if (i->reg_num != -1) {
						loc -= 4;
						i->sp_offset = loc;
					}
				}
			for (i = func->regs; i; i = i->nxt) {
				if (i->reg_num == -1) {
					if (i->ref->env_belong == global) {
						printf("\t# global variable %s\n", i->ref->id);
					} else {
						if (i->ref->arg_num != -1) {
							printf("\t# argument %s %d offset: %d\n", i->ref->id, i->ref->arg_num, i->sp_offset);
						} else {
							printf("\t# normal variable %s offset: %d\n", i->ref->id, i->sp_offset);
						};
					}
				} else {
					printf("\t# tmp variable $%d offset %d\n", i->reg_num, i->sp_offset);
				}
			}
			if (!my_strcmp(func->id, "main")) {
				printf("main:\n");
			} else {
				printf("__func%s:\n", func->id);
			}
			printf("\t# $ra @ %d($sp)\n", ra);
			printf("\t# stack size %d\n", stack_size);
			printf("\tadd $sp, -%d\n", stack_size);
			printf("\tusw $ra, %d($sp)\n", ra);
			int f = 0, t = 0;
			for (opt_que[t++] = func->block, blck_hsh[func->block->id] = bfs_cnt; f < t; ++f) {
				Block *a = opt_que[f]->condi, *b = opt_que[f]->non_condi;
				if (!a && !b && opt_que[f] != func->end) {
					opt_que[f]->non_condi = func->end;
					b = func->end;
				}
				if (a) {
					if (blck_hsh[a->id] != bfs_cnt) {
						opt_que[t++] = a;
						blck_hsh[a->id] = bfs_cnt;
					}
				}
				if (b) {
					if (blck_hsh[b->id] != bfs_cnt) {
						opt_que[t++] = b;
						blck_hsh[b->id] = bfs_cnt;
					}
				}
				show_blck(opt_que[f]);
				if (opt_que[f] == func->end) {
					printf("\t # end of function real return\n");
					printf("\tulw $ra, %d($sp)\n", ra);
					printf("\tadd $sp, %d\n", stack_size);
					if (!my_strcmp(func->id, "main")) {
						printf("\t # end of the program\n");
						printf("\tli $v0, 17\n");
						printf("\tli, $a0, 0\n");
						printf("\tsyscall\n");
					} else {
						printf("\tjr $ra\n");
					}
				}
			}
			printf("\n");
		}
		func = func->nxt;
	}
}

int cannot_delete(int ins) {
	if (is_branch(ins)) {
		return 1;
	}
	if (ins == INS_PARA || ins == INS_CALL) {
		return 1;
	}
	if (ins == INS_PRINT_STRING || ins == INS_PRINT_INT || ins == INS_PUTCHAR || ins == INS_GETCHAR) {
		return 1;
	}
	if (ins == INS_MOVE || ins == INS_ARRAY_WRITE) {
		return 1;
	}
	return 0;
}

int is_branch(int ins) {
	if (ins == INS_BNEZ || ins == INS_BEQZ || ins == INS_BLE || ins == INS_BLT || ins == INS_BGE || ins == INS_BGT || ins == INS_BNE || ins == INS_BEQ) {
		return 1;
	}
	return 0;
}

int is_compare(int ins) {
	if (ins == INS_SNE || ins == INS_SEQ || ins == INS_SLE || ins == INS_SLT || ins == INS_SGE || ins == INS_SGT) {
		return 1;
	}
	return 0;
}
/*
void optmization() {
	blck_hsh = (int *) malloc((blck_cnt + 1) * sizeof(int));
	int i;
	for (i = 0; i < blck_cnt + 1; ++i) {
		blck_hsh[i] = 0;
	}
	code_changed = 1;
	Function *func = func_head;
	while (func) {
		code_changed = 1;
		while (code_changed) {
			code_changed = 0;
			if (func->block) {
				++bfs_cnt;
				int f = 0, t = 0;
				for (opt_que[t++] = func->block, blck_hsh[func->block->id] = bfs_cnt; f < t; ++f) {
					Block *a = opt_que[f]->condi, *b = opt_que[f]->non_condi;
					if (a) {
						if (blck_hsh[a->id] != bfs_cnt) {
							opt_que[t++] = a;
							blck_hsh[a->id] = bfs_cnt;
							++a->in_deg;
						}
					}
					if (b) {
						if (blck_hsh[b->id] != bfs_cnt) {
							opt_que[t++] = b;
							blck_hsh[b->id] = bfs_cnt;
							++b->in_deg;
						}
					}
				}
				printf("# @branch merge...\n");
				for (i = 0; i < t; ++i) {
					if (opt_que[i]->ins_size >= 2) {
						Instruction *a = opt_que[i]->ins + opt_que[i]->ins_size - 2, *b = opt_que[i]->ins + opt_que[i]->ins_size - 1;
						printf("# %d, %d\n", a->ins, b->ins);
						if (is_compare(a->ins)) {
							if (b->ins == INS_BEQZ) {
								if (a->ins == INS_SNE) {
									a->ins = INS_BEQ;
									--opt_que[i]->ins_size;
									code_changed = 1;
								} else if (a->ins == INS_SEQ) {
									a->ins = INS_BNE;
									--opt_que[i]->ins_size;
									code_changed = 1;
								} else if (a->ins == INS_SGE) {
									a->ins = INS_BLT;
									--opt_que[i]->ins_size;
									code_changed = 1;
								} else if (a->ins == INS_SLE) {
									a->ins = INS_BGT;
									--opt_que[i]->ins_size;
									code_changed = 1;
								} else if (a->ins == INS_SLT) {
									a->ins = INS_BGE;
									--opt_que[i]->ins_size;
									code_changed = 1;
								} else if (a->ins == INS_SGT) {
									a->ins = INS_BLE;
									--opt_que[i]->ins_size;
									code_changed = 1;
								}
							}
							if (b->ins == INS_BNEZ) {
								if (a->ins == INS_SNE) {
									a->ins = INS_BNE;
									--opt_que[i]->ins_size;
									code_changed = 1;
								} else if (a->ins == INS_SEQ) {
									a->ins = INS_BEQ;
									--opt_que[i]->ins_size;
									code_changed = 1;
								} else if (a->ins == INS_SGE) {
									a->ins = INS_BGE;
									--opt_que[i]->ins_size;
									code_changed = 1;
								} else if (a->ins == INS_SLE) {
									a->ins = INS_BLE;
									--opt_que[i]->ins_size;
									code_changed = 1;
								} else if (a->ins == INS_SLT) {
									a->ins = INS_BLT;
									--opt_que[i]->ins_size;
									code_changed = 1;
								} else if (a->ins == INS_SGT) {
									a->ins = INS_BGT;
									--opt_que[i]->ins_size;
									code_changed = 1;
								}
							}
						}
					}
				}
				for (i = 0; i < t; ++i) {
					if (!opt_que[i]->condi && opt_que[i]->non_condi && opt_que[i]->non_condi != func->end && opt_que[i]->non_condi->in_deg == 1) {
						int j;
						Block *nxt = opt_que[i]->non_condi;
						for (j = 0; j < nxt->ins_size; ++j) {
							append_ins(opt_que[i], nxt->ins + j);
						}
						opt_que[i]->non_condi = nxt->non_condi;
						opt_que[i]->condi = nxt->condi;
						code_changed = 1;
					}
				}
				for (i = 0; i < t; ++i) {
					opt_que[i]->in_deg = 0;
				}
			}
		}
		func = func->nxt;
	}
}
*/
int main() {
	initialize();
	parse_program();
	//optmization();
	show_IR();
	return 0;
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!