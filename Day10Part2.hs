import Data.Maybe (fromMaybe)
import Data.List (sort)

type Stack = String

solve :: String -> Stack -> Maybe String
solve "" stack = Just stack --Suggested autocomplete
solve ('(':str) stack = solve str (')':stack)
solve ('<':str) stack = solve str ('>':stack)
solve ('{':str) stack = solve str ('}':stack)
solve ('[':str) stack = solve str (']':stack) 
solve (s:str) (x:stack) 
  | x == s = solve str stack
  | otherwise = Nothing --Invalid line so can't complete

scoreChar :: Char -> Int
scoreChar c 
  | c == ')' = 1
  | c == ']' = 2
  | c == '}' = 3
  | c == '>' = 4

scoreString :: String -> Int
scoreString = foldl (\acc c -> acc*5 + (scoreChar c)) 0

part2 :: String -> String
part2 inp = (show (sorted !! (div (length (sorted)) 2 ))) ++ "\n"
  where sorted = sort . map (scoreString . fromMaybe "") . filter (/= Nothing) .  map (flip solve "") $ lines inp
  
main = interact part2
