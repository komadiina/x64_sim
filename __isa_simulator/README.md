# x64 ISA Simulator

## TODO:
[x] deabstract `functions.hpp`: move `bytecode` namespace (*initialize()* function) into `encoding.hpp`   
[-] add imgui integration (maybe)?  
[-] improve tokenizing when comments are encountered (pop_back() (== token), while size > numargs[instruction_ids[token]])  
[x] test register indirect addressing functionality --> [works!]  
[-] moral dilemma: treat `value` as value in the pointed address  
___

file reading process:
1. lex each line in file
2. extract lines
3. convert each line into bytecode
4. if 'BRK': pause, start debugging via CLI  
