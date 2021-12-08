import Data.List
splitOn :: Char -> String ->  [String]
splitOn _ "" = [""]
splitOn c (x:xs) 
  | x == c = "":(splitOn c xs)
  | otherwise = let (s:ss) = splitOn c xs in (x:s):ss

mapper :: String -> Int
mapper str = (case length str of 
  2 -> 1
  4 -> 1
  7 -> 1
  3 -> 1
  _ -> 0)

part1 :: String -> String
part1 inp = (show . sum . map (mapper) $ concat outputNumbers) ++ "\n" 
  where [patterns,outputNumbers] = transpose $ map (map words . splitOn '|') (lines inp)

main = interact part1
