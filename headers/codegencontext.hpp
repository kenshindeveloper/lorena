#ifndef CODE_GEN_CONTEXT_HPP
#define CODE_GEN_CONTEXT_HPP

#include <string>
#include <stack>
#include <map>
#include "block.hpp"
#include "identifier.hpp"
#include "function.hpp"
#include "funclist.hpp"
#include "error.hpp"

namespace april
{
    

    enum class Scope
    {
        BLOCK,
        FUNCTION
    };

    class CodeGenContext
    {
        public:
            Scope scope_type;

        private:
            Block* current_block;
            std::stack<Block*> stack_block;
            int errors;
            Function* current_function;
            std::stack<Function*>* func_stack;
            std::vector<Symbol*> globals;

        public:
            CodeGenContext();
            ~CodeGenContext();
            bool runCode(Block*);
            std::vector<Symbol*>& getGlobals() { return globals; } 
            std::stack<Function*>*& getStackFunc() { return func_stack; }
            Block*& getCurrentBlock() { return current_block; }
            Symbol*& findIdentLocals(std::string);
            Symbol* existIdenLocals(std::string);
            Symbol*& findIdentGlobals(std::string);
            Symbol* existIdenGlobals(std::string);
            Type typeOf(std::string);
            void addError() { ++errors; }
			int& getError() { return errors; }
            void push_block(Block*);
            void pop_block();
            void setCurrentBlock(Block*);
            void popCurrentBlock();
            std::stack<Block*>& getStackBlock() { return stack_block; }
            bool deleteIdentLocals(std::string);
            void setCurrentFunction(Function* func) { current_function = func; }
            Function*& getCurrentFunction() { return current_function; }
            void stopRootBlock();
            void stopBreakBlock();
            void printLocals();
    };
}
#endif //CODE_GEN_CONTEXT_HPP