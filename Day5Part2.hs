import qualified Data.Map as Map 

splitOn :: Char -> String ->  [String]
splitOn _ "" = [""]
splitOn c (x:xs) 
  | x == c = "":(splitOn c xs)
  | otherwise = let (s:ss) = splitOn c xs in (x:s):ss

traversePoints :: [Int] -> [Int] -> Map.Map [Int] Int -> Map.Map [Int] Int
traversePoints [x1,y1] [x2,y2] myMap
  | (x1 == x2) && (y1 == y2) = resultMap
  | otherwise = traversePoints [x1+dx,y1+dy] [x2,y2] resultMap
  where resultMap = (case Map.lookup [x1,y1] myMap of
                          Nothing -> Map.insert [x1,y1] 1 myMap
                          Just x -> Map.insert [x1,y1] (x+1) myMap)
        dx = if (x1 == x2) then 0 else (if (x1 < x2) then 1 else -1)
        dy = if (y1 == y2) then 0 else (if (y1 < y2) then 1 else -1)

numberOfOccurrences :: [[[Int]]] -> Map.Map [Int] Int
numberOfOccurrences = foldl (\myMap [[x1,y1],[x2,y2]] -> traversePoints [x1,y1] [x2,y2] myMap) Map.empty
  
part2 :: String -> String
part2 inp = show (Map.size (Map.filter (>= 2) $ numberOfOccurrences inputCoords)) ++ "\n"
  where inputCoords = map (map (map (\x -> read x :: Int). splitOn ',').filter (/= "->") . words) $ lines inp
    
main = interact part2
