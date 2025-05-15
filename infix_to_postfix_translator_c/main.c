#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define BSIZE 128
#define NONE -1
#define EOS '\0'

#define NUM 256
#define DIV 257
#define MOD 258
#define ID 259
#define DONE 260

int tokenval;
int lineno;
int lookahead;

struct entry {
  char *lexptr;
  int token;
};

struct entry const keywords[] = {{"div", DIV}, {"mod", MOD}, {0, 0}};

#define STRMAX 999 // size of lexemes array
#define SYMMAX 100 // size of symtable

char lexemes[STRMAX];
int lastchar = -1; // last used position in lexemes
struct entry symtable[SYMMAX];
int lastentry = 0; // last used position in symtable

void emit(int t, int tval);
void error(char *m);
void init(void);
int insert(char s[], int tok);
int lexan(void);
int lookup(char s[]);

void parse(void);
void expr(void);
void factor(void);
void match(int t);
void term(void);

int main(void) {
  init();
  parse();
  return 0;
}

void init() {
  for (struct entry *p = keywords; p->token; p++) {
    insert(p->lexptr, p->token);
  }
}

void parse(void) {
  lookahead = lexan();
  while (lookahead != DONE) {
    expr();
    match(';');
  }
}

void expr(void) {
  int t;
  term();
  while (1) {
    switch (lookahead) {
    case '+':
    case '-':
      t = lookahead;
      match(lookahead);
      term();
      emit(t, NONE);
      continue;
    default: return;
    }
  }
}

void term(void) {
  int t;
  factor();
  while (1) {
    switch (lookahead) {
    case '*':
    case '/':
    case DIV:
    case MOD:
      t = lookahead;
      match(lookahead);
      factor();
      emit(t, NONE);
      continue;
    default: return;
    }
  }
}

void factor(void) {
  switch (lookahead) {
  case '(':
    match('(');
    expr();
    match(')');
    break;
  case NUM:
    emit(NUM, tokenval);
    match(NUM);
    break;
  case ID:
    emit(ID, tokenval);
    match(ID);
    break;
  default: error("syntax error");
  }
}

void match(int t) {
  if (lookahead == t) {
    lookahead = lexan();
  } else {
    error("syntax error");
  }
}

int lookup(char s[]) {
  for (int p = lastentry; p > 0; --p) {
    if (strcmp(symtable[p].lexptr, s) == 0) {
      return p;
    }
  }
  return 0;
}

int insert(char s[], int tok) {
  int len = strlen(s);

  if (lastentry + 1 >= SYMMAX) {
    error("symbol table is full");
  }
  if (lastchar + len + 1 >= STRMAX) {
    error("lexemes array full");
  }

  lastentry += 1;
  symtable[lastentry].token = tok;
  symtable[lastentry].lexptr = &lexemes[lastchar + 1];
  lastchar = lastentry + len + 1;
  strcpy(symtable[lastentry].lexptr, s);
  return lastentry;
}

char lexbuf[BUFSIZ];
int lineno = 1;
int tokenval = NONE;

int lexan(void) {
  int t;
  while (1) {
    t = getchar();
    if (t == ' ' || t == '\t') {
    } else if (t == '\n') {
      lineno++;
    } else if (isdigit(t)) {
      ungetc(t, stdin);
      // scanf("%d", &tokenval);
      return NUM;
    } else if (isalpha(t)) {
      int p = 0;
      int b = 0;
      while (isalnum(t)) {
        lexbuf[b] = t;
        t = getchar();
        b += 1;
        if (b >= BSIZE) {
          error("compiler error");
        }
      }
      lexbuf[b] = EOS;
      if (t != EOF) {
        ungetc(t, stdin);
      }
      p = lookup(lexbuf);
      if (p == 0) {
        p = insert(lexbuf, ID);
      }
      tokenval = p;
      return symtable[p].token;
    } else if (t == EOF) {
      return DONE;
    }
  }
}

void emit(const int t, const int tval) {
  switch (t) {
  case '+':
  case '-':
  case '*':
  case '/': printf("%c\n", t); break;
  case DIV: printf("DIV\n"); break;
  case MOD: printf("MOD\n"); break;
  case NUM: printf("%d\n", tval); break;
  case ID: printf("%s\n", symtable[tval].lexptr); break;
  default: printf("token %d, tokenval %d\n", t, tval);
  }
}
