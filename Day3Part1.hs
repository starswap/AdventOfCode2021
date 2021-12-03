import Data.List
counter :: [[Char]] -> [Int]
counter strings = map count $ transpose strings
  where count :: [Char] -> Int
        count bits = sum $ map (\a -> read [a] :: Int) bits

listToBinary :: [Bool] -> (Int,Int)
listToBinary [] = (0,1)
listToBinary (x:xs) = (total+m*bitValue,bitValue*2)
  where m = if x then 1 else 0 
        (total,bitValue) = listToBinary xs 

genGammaEpsilon :: [Int] -> Int -> Int
genGammaEpsilon bitCounts total = g*e
  where (g,_) = listToBinary $ (map (> (total `div` 2)) bitCounts)
        (e,_) = listToBinary $ (map (<= (total `div` 2)) bitCounts) 

part1 :: String -> String
part1 input = (show $ genGammaEpsilon (counter . lines $ input) (length. lines $ input)) ++ ['\n']

main = interact part1
