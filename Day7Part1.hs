import Data.List

splitOn :: Char -> String ->  [String]
splitOn _ "" = [""]
splitOn c (x:xs) 
  | x == c = "":(splitOn c xs)
  | otherwise = let (s:ss) = splitOn c xs in (x:s):ss


part1 :: String -> String
part1 inp = (show . sum . map (\x -> abs (median - x)) $ sorted) ++ "\n"
  where sorted = sort (map (\x -> read x :: Int) $ splitOn ',' inp)
        median = sorted !! (div (length sorted) 2)
        
main = interact part1
