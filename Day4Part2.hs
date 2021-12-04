import qualified Data.Map as Map
import Data.Bits
import Data.Array
import Data.Either
import Data.List
import Control.Monad


--Define type synonyms for documentation
type Rows = Array Int Int --List of Bitmasks (Could adjust type for improved efficiency as note that array updates are O(n))
type Cols = Array Int Int --List of Bitmasks
type BoardMap = Map.Map String (Int,Int) --Maps a number to its coordinates


--Define Board data type with the following attributes:
--  bmap = Maps number to its coordinates on the given board
--  rows = Array of kBoardSize bitmasks, with each one representing a row
--  cols = Array of kBoardSize bitmasks, with each one representing a column
--  crossed = List of all the numbers that have been crossed out on the board so we can later compute the answer by summing all the numbers we haven't crossed out. 
data Board = Board {bmap :: BoardMap, rows :: Rows, cols :: Cols,crossed :: [String]} deriving Show


--Ways to make a Board: First make the BoardMap and use boardFromMap, or construct the emptyBoard
boardFromMap :: BoardMap -> Board
boardFromMap mapp = Board mapp (array (0,kBoardSize-1) $ zip [0..(kBoardSize-1)] (repeat 0)) (array (0,kBoardSize-1) $ zip [0..(kBoardSize-1)]  (repeat 0)) []

emptyBoard :: Board
emptyBoard = boardFromMap Map.empty


--Constants representing size of board and a full bitmask of size kBoardSize
kBoardSize :: Int
kBoardSize = 5

kFull ::Int
kFull = 2^kBoardSize-1


--Utility function for csv
splitOn :: Char -> String ->  [String]
splitOn _ "" = [""]
splitOn c (x:xs) 
  | x == c = "":(splitOn c xs)
  | otherwise = let (s:ss) = splitOn c xs in (x:s):ss


--Take a row of the bingo card and represent it as a BoardMap, adding the keys to an existing BoardMap from the other rows
representRow :: [String] -> Int -> Int -> BoardMap -> BoardMap
representRow [] _ _ board = board
representRow (num:nums) colNo rowNo board = representRow nums (colNo+1) rowNo (Map.insert num (rowNo,colNo) board)


--Represent the whole of a bingo card as a BoardMap
mapRepresent :: [[String]] -> BoardMap
mapRepresent inp = snd (foldl (\(rowNo,boardMap) row -> (rowNo+1,representRow row 0 rowNo boardMap)) (0,Map.empty) inp)


--Represent all boards as a list of boards
genBoardRepresentation :: [[String]] -> [Board]
genBoardRepresentation [] = []
genBoardRepresentation input = (boardFromMap.mapRepresent $ (take kBoardSize input)):(genBoardRepresentation (drop kBoardSize input))


--Perform one time step for one board of crossing the number off and checking if the board has been completed (and returning score if yes)
processOneNumberOneBoard :: String -> Board -> Either Int Board
processOneNumberOneBoard numToFind board@(Board bm rs cs crsd) = let {numberJustDone = read numToFind :: Int;newCrossed = numToFind:crsd} in (
  case (Map.lookup numToFind bm) of
    Nothing -> Right board
    Just (r,c) | (rs//[(r,((rs!r) .|. 2^c))])!r == kFull -> Left (numberJustDone*(sum $ map (\x -> read x :: Int) (Map.keys bm \\ newCrossed)))
               | (cs//[(c,((cs!c) .|. 2^r))])!c == kFull -> Left (numberJustDone*(sum $ map (\x -> read x :: Int) (Map.keys bm \\ newCrossed)))
               | otherwise -> Right (Board bm (rs//[(r,(rs!r) .|. 2^c)]) (cs//[(c,(cs!c) .|. 2^r)]) newCrossed)
  )


--THIS IS THE ONLY FUNCTION WHICH CHANGES FROM PART 1
--Perform one time step over all the boards
oneTimeStep :: String -> [Board] -> Either Int [Board]
oneTimeStep n bBoards = 
  case processed of 
    [Left singleton] -> Left singleton --Left Int (score); only board remaining so answer
    longerList -> Right $ map (\(Right x) -> x) (filter filterer longerList) --remove any finished boards and then proceed.   
  where 
    processed = map (processOneNumberOneBoard n) bBoards
    filterer (Right x) = True
    filterer (Left x) = False


--Perform all time steps over all boards
processAllNums :: String -> [Board] -> Int 
processAllNums toCrossOut boards = let Left ans = foldl (\acc toCross -> acc >>= (oneTimeStep toCross)) (Right boards) (splitOn ','  toCrossOut) in ans 


--Perform input, conversion, answer generation and output.
part1 :: String -> String
part1 inp = (show $ processAllNums nums internalBoards) ++ "\n"
  where (nums:boards) = filter (/= "") $ lines inp
        internalBoards = genBoardRepresentation (map words boards)

main = interact part1
