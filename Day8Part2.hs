import Data.List
import qualified Data.Map as Map
import Data.Maybe (fromMaybe)

--Utility function to read in data based on format
splitOn :: Char -> String ->  [String]
splitOn _ "" = [""]
splitOn c (x:xs) 
  | x == c = "":(splitOn c xs)
  | otherwise = let (s:ss) = splitOn c xs in (x:s):ss

{-Identify letter combinations for each digit on the principle that:
   -We know 1,4,7,8 straight away as they use different numbers of segments to each other digit
   -We can then split the remaining digits into 5,2,3 which use 5 of the 7 segments and 0,6,9 which use 6 of the 7 segments
   -Then, divide each of these two groups up based on set differences:
     -3 is the only digit d E 5,2,3 such that d n 1 == 1
     -9 is the only digit d E 0,6,9 such that d n 3 == 3
     -0 is the only digit d E 0,6 such that d n 1 == 1
     -6 is now given for free as it is the only one left that is non-allocated from its group
     -5 is the only digit d E 2,5 which is missing the same segments as 6
     -2 is now given for free    
  We create a Map which converts the string representation into the digit it represents
-}
identifyDigits :: [String] -> Map.Map String Int
identifyDigits digitStrings = Map.insert two 2 (Map.insert five 5 (Map.insert six 6 (Map.insert zero 0 (Map.insert nine 9 (Map.insert three 3 prelimAlloc)))))
  where (one:seven:four:rest) = sortOn length digitStrings
        prelimAlloc = Map.insert (last rest) 8 (Map.insert four 4 (Map.insert seven 7 (Map.insert one 1 Map.empty)))
        fiveTwoThree = (take 3 rest)
        zeroSixNine = take 3 (drop 3 rest)
        [three] = filter (\x -> (one \\ x) == "") fiveTwoThree
        [nine] = filter (\x -> (three \\ x) == "") zeroSixNine
        [zero] = filter (\x -> (one \\ x) == "") $ zeroSixNine \\ [nine] 
        [six] = (zeroSixNine \\ [nine]) \\ [zero]
        [five] = filter (\x -> (head ("abcdefg" \\ six)) `elem` ("abcdefg" \\ x)) fiveTwoThree 
        [two] = (fiveTwoThree \\ [five]) \\ [three]

--Converts a list of x digits into a base 10 number, such that the first digit represents place value 10^x and so on. 
toBase10Number :: Int -> [Int] -> Int
toBase10Number _ [] = 0
toBase10Number x (n:ns) = 10^x*n + (toBase10Number (x-1) ns)

--Converts the unique signal patterns into a Map and then uses this to generate the numerical answer for the output value on this input line.
solveOneOutputValue :: [[String]] -> Int
solveOneOutputValue [knownData,outputString] = result 
  where digitMap = identifyDigits knownData
        result = (toBase10Number 3) . map (\x -> fromMaybe 0 (Map.lookup x digitMap)) $ outputString

--Solve the problem by reading in the input, sorting each string (so that equality of set testing becomes easier and set difference gains a speedup), and then applying the solveOneOutputValue function to each line before totalling up the answers to give the ouput for the puzzle.
part2 :: String -> String
part2 inp = (show . sum . map solveOneOutputValue $ dataIn) ++ "\n"
  where dataIn = map ((map ((map sort) . words)) . splitOn '|') (lines inp)

main = interact part2
