import Data.List (sort)

-- Define type synonyms
type Coords = (Float,Float)  

--Utility functions to split a string on a character and compute the delta between array elements respectively
splitOn :: Char -> String ->  [String]
splitOn _ "" = [""]
splitOn c (x:xs) 
  | x == c = "":(splitOn c xs)
  | otherwise = let (s:ss) = splitOn c xs in (x:s):ss

computeDeltas :: [Float] -> [Float]
computeDeltas [] = []
computeDeltas [singleton] = []
computeDeltas (a:b:cs) = (b-a):(computeDeltas (b:cs))

--Finds the point at which the derivative crosses the x axis, i.e. the minimum. See this for the thinking: https://www.desmos.com/calculator/5herqump2c
findXIntercept :: [Float] -> Coords -> Float -> Float
findXIntercept (d:ds) (x,y) n
  | newY == 0 = newX --This line segment caused the derivative to hit 0, so we found the minimum 
  | newY > 0 = newX - (newY/n) --This line segment pushed the derivative past 0, so we need to correct overshooting on derivative
  | newY + 1 > 0 = newX -- When we jump up to the next line segment, we pass 0, so this is the right answer
  | otherwise = findXIntercept ds (newX,newY+1) n -- Keep on going with the next line segment.
  where (newX,newY) = (x+d,y+d*n)

--Generate nth triangular number
triangle :: Int -> Int
triangle n = (n*(n+1)) `div` 2

--Interpret input as floating point numbers, find the x value leading to the minimum cost, and calculate the cost at this point to return as the answer. 
part2 :: String -> String
part2 inp = (show cost) ++ "\n"
  where sorted = sort (map (\x -> read x :: Float) $ splitOn ',' inp)
        n = fromIntegral $ length sorted
        total = sum sorted
        yIntercept = 0-total-(0.5*n)
        xIntercept = round $ findXIntercept (computeDeltas sorted) (0,yIntercept) n
        cost = sum . map (\x -> triangle . abs $ (xIntercept - (round x))) $ sorted --total cost for moving each number to the point we want to

main = interact part2
