#ifndef COMPILER_PARSER
#define COMPILER_PARSER

#include "lexer.h"
#include "symtable.h"
#include "ast.h"

class Parser
{
private:
    SymTable * symtable;
    Token * lookahead;
    
    Node * Program();
    Statement * Block();
    void Decls();
    void Decl();
    Statement * Stmts();
    Statement * Stmt();
    Expression * Local();
    Expression * Bool();
    Expression * Join();        // ← VERIFICAR QUE EXISTA
    Expression * Equality();
    Expression * Rel();
    Expression * Ari();
    Expression * Term();
    Expression * Unary();
    Expression * Factor();
    Expression * CheckBoolContext(Expression *e);  // ← NUEVO MÉTODO
    bool Match(int tag);
	

public:
	Parser();
	Node * Start();
	static int LineNo();
};

#endif
