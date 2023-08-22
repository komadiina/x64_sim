- everything simulator-related is contained in the `x64` namespace.

lexing process was ripped out of the pre-prealpha version of the project
everything else is either based upon, or totally different from the original idea.
  
in code:  
`MOV | ADD | SUB | ...`  
`CMP | JMP | JLE | ...`  
`IN | OUT | BREAKPOINT`  

`IN <register> <value>`,  e.g. `IN RAX, 50`  
`OUT <register>`, e.g. `OUT RAX` -> `"RAX = 50"`

labels **must start** with '`_`' (a single underscore)