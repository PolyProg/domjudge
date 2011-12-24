%baseclass-preinclude "parsetype.h"

%filenames parser
%scanner scanner.h

%lsp-needed
%lines
//%debug

%stype parse_t

%token TEST_EOF TEST_MATCH
%token CMP_LT CMP_GT CMP_LE CMP_GE CMP_EQ CMP_NE
%token CMD_SPACE CMD_NEWLINE CMD_EOF CMD_INT CMD_FLOAT CMD_STRING CMD_REGEX
%token CMD_REP CMD_WHILE CMD_END
%token VARIABLE INTEGER FLOAT STRING
%token OPT_FIXED OPT_SCIENTIFIC

%left '&' '|'
%left '+' '-'
%left '*' '/' '%'
%left '^'

%%

commands:
	// empty
|
	commands command
{
	program.push_back($2);
}
;

command:
	command_noargs
|
	command_args
;

command_noargs:
	CMD_SPACE   { $$ = parse_t($1); }
|	CMD_NEWLINE { $$ = parse_t($1); }
|	CMD_EOF     { $$ = parse_t($1); }
|	CMD_END     { $$ = parse_t($1); }
;

command_args:
	CMD_INT '(' expr ',' expr ')'              { $$ = parse_t($1,$3,$5); }
|	CMD_INT '(' expr ',' expr ',' VARIABLE ')' { $$ = parse_t($1,$3,$5,$7); }
|	CMD_FLOAT '(' expr ',' expr ')'            { $$ = parse_t($1,$3,$5); }
|	CMD_FLOAT '(' expr ',' expr ',' VARIABLE ')' { $$ = parse_t($1,$3,$5,$7); }
|	CMD_FLOAT '(' expr ',' expr ',' VARIABLE ',' opt_float ')' { $$ = parse_t($1,$3,$5,$7,$9); }
|	CMD_STRING '(' STRING ')'                  { $$ = parse_t($1,$3); }
|	CMD_REGEX  '(' STRING ')'                  { $$ = parse_t($1,$3); }
| 	CMD_REP '(' expr ')'                       { $$ = parse_t($1,$3); }
| 	CMD_REP '(' expr ',' command ')'           { $$ = parse_t($1,$3,$5); }
| 	CMD_WHILE '(' test ')'                     { $$ = parse_t($1,$3); }
| 	CMD_WHILE '(' test ',' command ')'         { $$ = parse_t($1,$3,$5); }
;

opt_float: OPT_FIXED | OPT_SCIENTIFIC ;

value: INTEGER | FLOAT | VARIABLE ;

compare: CMP_LT | CMP_GT | CMP_LE | CMP_GE | CMP_EQ | CMP_NE ;

expr:
	term          { $$ = parse_t($1); }
|	expr '+' term { $$ = parse_t('+',$1,$3); }
|	expr '-' term { $$ = parse_t('-',$1,$3); }
;

term:
	fact          { $$ = parse_t($1); }
|	term '*' fact { $$ = parse_t('*',$1,$3); }
|	term '/' fact { $$ = parse_t('/',$1,$3); }
|	term '%' fact { $$ = parse_t('%',$1,$3); }
;

fact:
	value         { $$ = parse_t($1); }
|	'-' fact      { $$ = parse_t('n',$2); }
|	'(' expr ')'  { $$ = parse_t($2); }
|	fact '^' fact { $$ = parse_t('^',$1,$3); }
;

test:
	'!' test      { $$ = parse_t('!',$2); }
|	'(' test ')'  { $$ = parse_t($2); }
|	test '&' test { $$ = parse_t('&',$1,$3); }
|	test '|' test { $$ = parse_t('|',$1,$3); }
|	expr compare expr         { $$ = parse_t('?',$2,$1,$3); }
|	TEST_EOF                  { $$ = parse_t('E'); }
|	TEST_MATCH '(' STRING ')' { $$ = parse_t('M',$3); }
;
