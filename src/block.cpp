#include "../headers/block.hpp"
#include "../headers/codegencontext.hpp"


namespace april
{
    Block::~Block()
    {
        //std::cout << "destructor Block" << std::endl;
        for (Statement* stmt: statements)
        {
            if (stmt != nullptr)
            {
                delete stmt;
                stmt = nullptr;
            }
        }
        statements.clear();

        //std::cout << "symbol block size: " << locals.size() << std::endl;
		//std::cout << "-------------------------------" << std::endl;
		for (Symbol* sym : locals)
        {
            if (sym != nullptr)
            {
                // std::cout << "Eliminando locales..." << std::endl;
                Symbol* aux = sym;
                while (aux != nullptr)
                {
					//std::cout << "(I)eliminando: >>" << aux->name << "<< " << std::endl;
                    Symbol* tmp = aux;
                    aux = aux->prox;
                    delete tmp; 
                    tmp = nullptr;
                }
            }
        }
        locals.clear();
		//std::cout << "-------------------------------" << std::endl;

        //std::cout << "fin destructor block" << std::endl;
    }

    Symbol* Block::codeGen(CodeGenContext& context)
    {
        // std::cout << ">> ini block <<" << std::endl;
        Symbol* last = new Symbol{};
        
        for (Statement*& stmt: statements)
        {
            if (!stop)
            {
                last = stmt->codeGen(context);
                if (last == nullptr) return nullptr;
            }
            else
                break;
        }

        
        if (type_scope != BlockScope::FOR)
            stop = false;
            
        // if (last == nullptr)
        //     std::cout << ">> fin block(NULLPTR)<<" << std::endl;
        // else
        // std::cout << ">> fin block << " << std::endl;

        return last;
    }
}