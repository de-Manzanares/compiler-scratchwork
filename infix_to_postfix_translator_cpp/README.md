<div align='center'>

## Infix to postfix translator

</div>

```cpp
/**
* @brief A simple one pass compiler:
* translating infix expressions to reverse polish notation (postfix) form.
* @details A syntax directed translator: uses a simple lexical analyzer
* that feeds a top-down-recursive-descent-predictive parser, all the while
* printing translations (or error messages) to stdout.
* @return translation
*/

/**
* Syntax-directed translation scheme
*       start -> list myEOF
*        list -> expr ; list | empty
*        expr -> term moreterms
*   moreterms -> + term { print('+') } moreterms
*              | - term { print('-') } moreterms
*              | empty
*        term -> factor morefactors
* morefactors -> * factor { print('*') } morefactors
*              | / factor { print('/') } morefactors
*              | div factor { print('DIV') } morefactors
*              | mod factor { print('MOD') } morefactors
*              | empty
*      factor -> ( expr )
*              | id { print(id.lexeme) }
*              | num { print(num.value) }
*/
```

### Resources

“Backus–Naur form,” Wikipedia. May 22, 2024. Accessed: Jul. 19, 2024. [Online]. Available: [here](https://en.wikipedia.org/w/index.php?title=Backus%E2%80%93Naur_form&oldid=1225174908)

A. V. Aho, R. Sethi, and J. D. Ullman, Compilers, principles, techniques, and tools. Reading, Mass: Addison-Wesley Pub. Co, 1986.

R. Nystrom, Crafting interpreters. Daryaganj Delhi: Genever Benning, 2021.
