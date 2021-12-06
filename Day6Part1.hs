splitOn :: Char -> String ->  [String]
splitOn _ "" = [""]
splitOn c (x:xs) 
  | x == c = "":(splitOn c xs)
  | otherwise = let (s:ss) = splitOn c xs in (x:s):ss

applyOneDay :: [Int] -> [Int]
applyOneDay = concat . map (progress) 
  where progress :: Int -> [Int]
        progress 0 = [6,8]
        progress x = [x-1]  

allDays :: Int -> [Int] -> [Int]
allDays 0 fish = fish
allDays x fish = allDays (x-1) (applyOneDay fish) 

part1 :: String -> String
part1 inp = (show . length $ allDays 80 (map (\x -> read x :: Int)(splitOn ',' inp))) ++ "\n"

main = interact part1
