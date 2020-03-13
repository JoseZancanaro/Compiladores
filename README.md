
# Especificação de Linguagem

**Linguagem**: Winter Programming Language
**Extensão**: .wpl
**Compilador**: Spring Compiler
**IDE**: Winter IDE (Wide)

## Diretivas

### Regras para nomes de variável
Deve iniciar com uma letra (independente de caixa) ou um underscore, os caracteres subsequentes podem ser letras, números ou underscores. Não é possível utilizar os demais caracteres especiais.

### Comentários
Comentários de apenas uma linha (ou resto de linha) devem ser precedidos por "//" (--), isto é, barra dupla.
*Ex:*
// isto é um comentário.

Comentários de linhas múltiplas devem ser precedidos por "/\*" e finalizar com "\*/"
*Ex:*
/* Isto é
 um comentário */

### Operadores
| Classe | Operador | Significado |
|--|--| -- |
| Atribuição | = | Associação de valor |
| Aritmético | + | Adição |
| Aritmético | - | Subtração |
| Aritmético | * | Multiplicação |
| Aritmético | / | Divisão |
| Aritmético | ** | Exponenciação |
| Relacional | > | Maior que |
| Relacional | < | Menor que |
| Relacional | >= | Maior ou igual a |
| Relacional | <= | Menor ou igual a |
| Relacional | == | Igualdade |
| Relacional | /= | Diferença |
| Lógico | && | E |
| Lógico | \|\| | Ou|
| Lógico | ! | Negação|
| Bit a bit | >> | Deslocamento a direita |
| Bit a bit | << | Deslocamento a esquerda |
| Bit a bit | & | E |
| Bit a bit | \| | Ou |
| Bit a bit | ~ | Complemento |
| Bit a bit | ^ | Ou exclusivo (Xor) |

### Tipos
Os identificadores de tipo iniciam sempre com uma letra maiúscula e são tidos como palavras reservadas.
- Inteiro: Integer
- Ponto flutuante: Float
- Ponto flutuante de dupla precisão: Double
- Booleano: Bool
- Caractere: Char
- Cadeia de caractere: String

### Desvios Condicionais
Desvio lógico típico: if-then, if-then-else, if-then-elseif-else.
```
if (condição) { ... }
if (condição) { ... } else { ... }
if (condição) { ... } else if { ... } else { ... }
```

```
choose {
	| condition = ...;
	| condition = ...;
	| otherwise = ...;
}
```

Desvio de caso: switch case.
```
switch (variavel) {
	case valor:
		...
		break;
	default:
}
```

### Laços de repetição
A linguagem abrange algumas formas tradicionais de laços, como: for, for-range, while, do-while.

```
for (Integer x = 0; x <= MAX; x++) {
	...
}
```

```
for (Integer x : vetor) {
	...
}
```

```
while (x > 0) {
	...
}
```

```
do {
	...
} while (x > 0)
```

### Atribuição
Como listado anteriormente, a associação (ou atribuição) é feita através do operador "=".

```
Integer x = 20;
```

### Delimitadores e pontuadores
- As instruções são delimitadas por um caractere de ";" (ponto e vírgula).
- O for-range utiliza o caractere de ":" para definir a associação de iteração.
- Vetores podem ser definidos através de colchetes ([...]).
- Os escopos são delimitados por chaves ({ ... }).

## Características Léxicas

### Palavras chave

#### Tipos
KW_INT    : "Integer"
KW_FLOAT  : "Float"
KW_DOUBLE : "Double"
KW_BOOL   : "Bool"
KW_CHAR   : "Char"
KW_STR    : "String"

#### Condicionais
KW_IF     : "if"
KW_ELSE   : "else"
KW_ELSEIF : "else if"

KW_SWITCH  : "switch"
KW_CASE    : "case"
KW_BREAK   : "break"
KW_DEFAULT : "default"

#### Laços de repetição
KW_FOR   : "for"
KW_WHILE : "while"
KW_DO    : "do"

#### Retorno
KW_RETURN : "return"

### Operadores

#### Atribuição
OP_ATT  : "="

#### Aritmética
OP_ADD  : "+"
OP_SUB  : "-"
OP_MULT : "*"
OP_DIV  : "/"
OP_EXP  : "**"

#### Relacionais
OP_GT  : ">"
OP_LT  : "<"
OP_GTE : ">="
OP_LTE : "<="
OP_EQ  : "=="
OP_NEQ : "/="

#### Lógicos
OP_AND : "&&"
OP_OR  : "||"
OP_NOT : "!"

#### Bit a bit
OP_BW_SR   : ">>"
OP_BW_SL   : "<<"
OP_BW_AND  : "&"
OP_BW_OR   : "|"
OP_BW_COMP : "~"
OP_BW_XOR  : "^"

### Identificadores
ID_VAR : {ID_NAME}
ID_FUNC: {ID_FUNC}

### Valores constantes
VAL_INT       : {SYM_DEC}+
VAL_INT_BIN   : 0b{SYM_BIN}+
VAL_INT_HEX   : 0x{SYM_HEX}+
VAL_REAL      : {SYM_DEC}+\.{SYM_DEC}+
VAL_CHAR      : ('{SYM_CHAR}')|('')
VAL_STR       : \"{SYM_STR}*\"
VAL_BOOL_TRUE  = ID_VAR : "true"
VAL_BOOL_FALSE = ID_VAR : "false"

### Comentários
COMM_SL : {SYM_SLASH}{SYM_SLASH}[^\n]*
COMM_ML : {SYM_CML_B}((\*[^/])|[^\*])*{SYM_CML_E}

### Delimitadores e pontuações
DEL_COMMA : ","
DEL_COLON : ":"
DEL_SEMI_COLON : ";"

DEL_LP  : "("
DEL_RP  : ")"

DEL_LSB : "["
DEL_RSB : "]"

DEL_LCB : "{"
DEL_RCB : "}"
