# Especificação de Linguagem
**Linguagem**: Winter Programming Language  
**Extensão**: .wpl  
**Compilador**: Spring Compiler  
**IDE**: Winter IDE (Wide)  

```

/-
 - @authors
 - Israel Efraim de Oliveira
 - José Carlos Zancanaro
 -/

def main() -> Integer {
	Float magro = 18.5, normal = 25.0, gordinho = 30.0;	
	Float altura = 1.75, peso = 72.1;
	Float imc = peso / altura ** 2;
	
	String mensagem = choose from
				|> imc <= magro = "Abaixo do peso.";
				|> imc <= normal = "Está normal.";
				|> imc <= gordinho = "Acima do peso.";
				|> otherwise = "Alien!";

	print("IMC: ", imc);
	print("Classificação: ", mensagem);
	

	return 0;
}

```

## Diretivas

### Regras para nomes de variável
Deve iniciar com uma letra (independente de caixa) ou um underscore, os caracteres subsequentes podem ser letras, números ou underscores. Não é possível utilizar os demais caracteres especiais.

### Sub-rotinas (Funções e procedimentos)
Deve-se iniciar com a keyword **def**, em seguida, o nome da função deve iniciar com uma letra (independente de caixa) ou um underscore, os caracteres subsequentes podem ser letras, números ou underscores, além de ser possível utilizar do caracter especial  **'** (aspas simples). Ademais caracteres especiais não podem ser utilizados. Adiante deve especificar os parâmetros da função (possuí argumentos ou não), e o tipo de retorno da função. O tipo de retorno é especificado após os caracteres **->**.

```
def main() -> Integer { ... }
```
```
def MinhaFuncao(Integer num, Float[] val) -> Bool { ... }
```
### Entrada e saída de dados
Para a entrada de dados, utiliza-se o procedimento **read()**, e para a saída de dados é necessário o uso da função **print()**
```
read(meuValor);
print(meuValor);
```

### Comentários
Comentários de apenas uma linha (ou resto de linha) devem ser precedidos por dois hífens "--".  
*Ex:*  
-- isto é um comentário.

Comentários de linhas múltiplas devem ser precedidos por "\-" e finalizar com "-/".  
*Ex:*  
/- Isto é  
 um comentário -/

### Operadores
| Classe | Operador | Significado |
|--|--| -- |
| Atribuição | = | Associação de valor |
| Aritmético | + | Adição |
| Aritmético | - | Subtração |
| Aritmético | * | Multiplicação |
| Aritmético | / | Divisão |
| Aritmético | ** | Exponenciação |
| Aritmético | % | Módulo (resto) |
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
Desvio lógico com case-of e choose-from.

```
choose from {
	|> condition -> ...;
	|> condition -> ...;
	|> otherwise -> ...;
}
```

```
case variavel of {
    |> valor -> ...;
    |> valor -> ...;
    |> otherwise -> ...;
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

### Vetor
Um vetor é identificado com a inserção dos caracteres **[]** após a definição de seu tipo.
```
Double[] vetor;
```


### Delimitadores e pontuadores
- As instruções são delimitadas por um caractere de ";" (ponto e vírgula).
- O for-range utiliza o caractere de ":" para definir a associação de iteração.
- Vetores podem ser definidos através de colchetes ([...]).
- Os escopos são delimitados por chaves ({ ... }).
- Vírgulas são utilizadas para separar parâmetros de função, valores em vetores e nomes em declarações de variáveis.
- O operador de '.' acessa um membro de um struct.
