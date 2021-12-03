import Data.List (transpose)

--Define required type synonyms for readability
type BinString = [Int]
type Counts = [Int]

--Counts the number of 1s at each position of the binary strings 
counter :: [BinString] -> Counts
counter strings = map sum $ transpose strings

--Converts the binary list representation of a BinString into a decimal number (discard second tuple output, which is the highest power of 2 + 1 in the string given, even if there is a padding zero there.)
listToBinary :: BinString -> (Int,Int)
listToBinary [] = (0,1)
listToBinary (x:xs) = (total+x*bitValue, bitValue*2)
  where (total,bitValue) = listToBinary xs

--Takes the given String input and represents it as a List of Ints, the format used for this program
convertToList :: String -> BinString
convertToList = map mapper
  where mapper '0' = 0
        mapper '1' = 1

--Find the gamma rate from the numbers of 1s at each bit position
mostCommon :: Counts -> Int -> BinString
mostCommon bitCounts total = map mapper bitCounts
  where mapper a = if (a >= (total-a)) then 1 else 0

--Find the epsilon rate from the numbers of 1s at each bit position
leastCommon :: Counts -> Int -> BinString
leastCommon bitCounts total = map mapper bitCounts
  where mapper a = if (a < (total-a)) then 1 else 0

--Finds the generator rating or CO2 scrubber rating depending on if the mostCommon or leastCommon helper function is passed.
getOxygenOrCO :: [BinString] -> (Counts -> Int -> BinString) -> BinString
getOxygenOrCO binNos mostLeast = 
  case filtered of
    [ans] -> m:ans --We found the final answer so we need the bit we just removed as if we were going to the next level, plus the rest of the number 
    remainingOptions -> (m:(getOxygenOrCO remainingOptions mostLeast)) --Continue filtering on the rest of the number, and once we have our final number add back the bit that was removed at this level.
    where (m:ms) = mostLeast (counter binNos) (length binNos) --Get the epsilon/gamma for the remaining numbers and select the bit we are interested in.
          filtered = [bs | (b:bs) <- binNos, b == m] --Filter any that don't match at this bit, and remove the front bit so we always operate on the front of the list.
  
--Computes final answer 
part2 :: String -> String
part2 input = (show $ co*ox) ++ ['\n'] --Output the product, with a new line
  where (ox,_) = (listToBinary $ getOxygenOrCO (map convertToList (lines input)) mostCommon) --Convert all numbers to BinString   representation, get oxygen level and convert back to integer
        (co,_) = (listToBinary $ getOxygenOrCO (map convertToList (lines input)) leastCommon) --Convert all numbers to BinString representation, get CO2 level and convert back to integer.

main = interact part2
