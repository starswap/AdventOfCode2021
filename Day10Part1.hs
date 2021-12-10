type Stack = String

solve :: String -> Stack -> Int
solve "" _ = 0
solve ('(':str) stack = solve str (')':stack)
solve ('<':str) stack = solve str ('>':stack)
solve ('{':str) stack = solve str ('}':stack)
solve ('[':str) stack = solve str (']':stack) 
solve (s:str) (x:stack) 
  | x == s = solve str stack
solve (s:str) _ 
  | s == ')' = 3
  | s == ']' = 57
  | s == '}' = 1197
  | s == '>' = 25137
  
part1 :: String -> String
part1 inp = (show . sum . map (flip solve "") $ lines inp) ++ "\n"

main = interact part1
