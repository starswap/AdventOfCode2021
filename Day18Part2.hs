import Data.Char (digitToInt)

data SnailNumber = P Int | R SnailNumber SnailNumber deriving Show --Primitive/Recursive
data Side = L | Ri --Left/Right 
type Stack = []

reduceOnce :: SnailNumber -> Maybe SnailNumber
reduceOnce sn = (case (explode sn 0) of --1?
  Nothing -> (case (split sn) of 
      Nothing -> Nothing
      Just sn' -> Just sn'
    )
  Just (sn',_,_) -> Just sn'
 )
 
reduce :: SnailNumber -> SnailNumber
reduce sn = (case reduceOnce sn of 
    Nothing -> sn
    Just red -> reduce red
  )

explode :: SnailNumber -> Int -> Maybe (SnailNumber,Side,Maybe Int)
explode (P x) _ = Nothing -- didn't hit required depth
explode (R (R (P x) (P y)) sn) 3 = Just ((R (P 0) (augmentLeftMost sn y)),L,Just x)
explode (R sn (R (P x) (P y))) 3 = Just ((R (augmentRightMost sn x) (P 0)),Ri,Just y)
explode (R a b) depth = 
  (case (explode a (depth+1)) of
    Nothing -> (case (explode b (depth+1)) of
        Nothing -> Nothing
        Just (res,L,amt) ->  (case amt of 
            Nothing -> Just (R a res,L,Nothing)
            Just amnt -> Just (R (augmentRightMost a amnt) res,L,Nothing)
          )
        Just (res,Ri,amt) -> Just (R a res,Ri,amt)         
      )

    Just (res,Ri,amt) ->  (case amt of 
        Nothing -> Just (R res b,Ri,Nothing)
        Just amnt -> Just (R res (augmentLeftMost b amnt),Ri,Nothing)
      )
    Just (res,L,amt) -> Just (R res b,L,amt)
  )

split :: SnailNumber -> Maybe SnailNumber
split (P x) 
  | x >= 10 = Just (R (P (x `div` 2)) (P ((x `div` 2) + x `rem` 2)))
  | otherwise = Nothing
split (R x y) = (
  case (split x) of 
    Nothing -> (case (split y) of 
        Nothing -> Nothing
        Just sn -> Just (R x sn)
      )
    Just sn -> Just (R sn y)
  )

augmentLeftMost :: SnailNumber -> Int -> SnailNumber
augmentLeftMost (P x) amt = P (x+amt)
augmentLeftMost (R x y) amt = R (augmentLeftMost x amt) y

augmentRightMost :: SnailNumber -> Int -> SnailNumber
augmentRightMost (P y) amt = P (y+amt)
augmentRightMost (R x y) amt = R x (augmentRightMost y amt)

add :: SnailNumber -> SnailNumber -> SnailNumber
add snx sny = reduce (R snx sny)

magnitude :: SnailNumber -> Int
magnitude (P x) = x
magnitude (R x y) = 3*(magnitude x) + 2*(magnitude y)
 
constructSn :: String -> SnailNumber
constructSn = head . foldl foldinConstructSn []
  where 
    foldinConstructSn :: Stack SnailNumber -> Char -> Stack SnailNumber 
    foldinConstructSn stack '[' = stack 
    foldinConstructSn stack ',' = stack
    foldinConstructSn (s:t:stack) ']' = (R t s):stack
    foldinConstructSn stack d = (P (digitToInt d)):stack

generatePairs :: [a] -> [(a,a)]
generatePairs [] = []
generatePairs (x:xs) = (map (\a -> (x,a)) xs) ++ generatePairs xs

part2 :: String -> String
part2 str = (show best) ++ "\n"
  where numbers = (map constructSn (lines str))
        allPairs = (generatePairs numbers) ++ (generatePairs $ (reverse numbers))
        best = maximum (map (\(a,b) -> magnitude (add a b)) allPairs)

main = interact part2

