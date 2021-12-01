folder :: (Int,Int) -> Int -> (Int,Int)
folder (prev,count) x
  | x > prev = (x,count+1)
  | otherwise = (x,count)

windows :: [Int] -> [Int]
windows [] = []
windows xs = (sum . take 3 $ xs):(windows . drop 1 $ xs) 

solve :: String -> String
solve inp = (show . snd $ foldl folder (10000,0) ints)++"\n"
  where ints = windows $ map (\a -> read a :: Int) (lines inp)  

main = interact solve