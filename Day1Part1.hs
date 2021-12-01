folder :: (Int,Int) -> Int -> (Int,Int)
folder (prev,count) x
  | x > prev = (x,count+1)
  | otherwise = (x,count)

solve :: String -> String
solve inp = (show . snd $ foldl folder (10000,0) ints)++"\n"
  where ints = map (\a -> read a :: Int) (lines inp)  

main = interact solve