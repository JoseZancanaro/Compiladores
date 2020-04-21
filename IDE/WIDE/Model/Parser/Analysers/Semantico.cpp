#include "Semantico.hpp"
#include "Constants.hpp"

#include <iostream>
#include <functional>

namespace wpl {

auto getTypeName(Type const& type) -> std::string  {
    switch (type) {
    case VOID:
        return "Void";
    case INTEGER:
        return "Integer";
    case FLOAT:
        return "Float";
    case DOUBLE:
        return "Double";
    case BOOL:
        return "Bool";
    case CHAR:
        return "Char";
    case STRING:
        return "String";
    case ANY:
        return "Any";
    }
}

auto decodeAction(int action) -> std::pair<int, int> {
    return { action / 100, action % 100 };
}

void Semantico::executeAction(int action, const Token *token)
{
    auto [ prefix, suffix ] = decodeAction(action);
    switch (prefix) {
    case 0:
        this->doScopeAction(suffix, token);
        break;
    case 1:
        this->doTypeAction(suffix, token);
        break;
    case 2:
        this->doDeclareAction(suffix, token);
        break;
    default:
        std::puts("se tu leres isso, é pq fez cagada.");
    }
}

void Semantico::doScopeAction(int suffix, Token const* token)
{
    switch (suffix) {
    case 0:
        this->scopes.push("__global__");
        break;
    case 1:
        this->scopes.pop();

        for (auto const& n : this->nameTable) {
            std::cout << n.id << " " << n.scope << " " << n.type << " " << n.inferred << std::endl;
        }

        break;
    default:
        std::puts("O meooo...");
    }
}

void Semantico::doTypeAction(int suffix, Token const* token)
{
    switch (suffix) {
    case 0:
        this->types.push(token->getLexeme());
        break;
    default:
        std::puts("hey buddy, not supported.");
    }
}

void Semantico::doDeclareAction(int suffix, Token const* token)
{
    switch (suffix) {
    case 0:
        // this->names.push(token->getLexeme()); @TODO When inserting values, uncomment.
        this->try_put_name({ token->getLexeme(), this->scopes.top(), this->types.top(), this->types.top() });
        break;
    case 1:
        std::puts("<expression>");
        break;
    case 2:
        this->types.pop();
        break;
    }
}

void Semantico::try_put_name(const Name& name)
{
    this->name_table.push_back(name);
}

} //namespace wpl

