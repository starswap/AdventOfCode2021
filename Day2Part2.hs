folder :: (Int,Int,Int) -> [String] -> (Int,Int,Int)
folder (x,y,aim) [instruction,amount] 
  | instruction == "forward" = (x+a,y+aim*a,aim)
  | instruction == "down" = (x,y,aim+a)
  | instruction == "up" = (x,y,aim-a) 
  where a = read amount :: Int

solve :: String -> String
solve inp = (show $ x*y)++"\n" 
  where (x,y,_) = foldl folder (0,0,0) (map words $ lines inp)

main = interact solve
