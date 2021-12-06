import qualified Data.Map as Map
import Data.Maybe

type FishMap = Map.Map Int Int --Day of cycle to number of fish.

--Utility functions
splitOn :: Char -> String ->  [String]
splitOn _ "" = [""]
splitOn c (x:xs) 
  | x == c = "":(splitOn c xs)
  | otherwise = let (s:ss) = splitOn c xs in (x:s):ss

count :: Eq a => a -> [a] -> Int
count v = length . filter (v==) 


--All fish for one day
applyOneDay :: FishMap -> FishMap
applyOneDay fm = breed $ Map.mapKeys (\x -> x-1) fm  
  where breed:: FishMap -> FishMap
        breed fm = Map.delete (-1) (Map.insert 6 (breeders+(fromMaybe 0 existing6)) (Map.insert 8 (breeders+(fromMaybe 0 existing8)) fm))
          where breeders = fromMaybe 0 (Map.lookup (-1) fm)  
                existing6 = Map.lookup (6) fm
                existing8 = Map.lookup (8) fm

--All fish for all days
allDays :: Int -> FishMap -> FishMap
allDays 0 fish = fish
allDays x fish = allDays (x-1) (applyOneDay fish) 

part2 :: String -> String
part1 inp = (show . sum . Map.elems $ allDays 256 (Map.fromList [(a,count a (map (\x -> read x :: Int)(splitOn ',' inp))) | a <- [1..7]])) ++ "\n"


main = interact part2
