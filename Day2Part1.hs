folder :: (Int,Int) -> [String] -> (Int,Int)
folder (x,y) [instruction,amount] 
  | instruction == "forward" = (x+a,y)
  | instruction == "down" = (x,y+a)
  | instruction == "up" = (x,y-a) 
  where a = read amount :: Int

solve :: String -> String
solve inp = (show $ x*y)++"\n" 
  where (x,y) = foldl folder (0,0) (map words $ lines inp)

main = interact solve
