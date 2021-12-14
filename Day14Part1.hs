import Data.List (sort, group)
kSteps = 10

type Rules = [[String]]

processRulesForOneStep :: String -> Rules -> Rules -> String
processRulesForOneStep "" _ _ = ""
processRulesForOneStep [singleton] _ _ = [singleton]
processRulesForOneStep (x:xs) [] allRules = processRulesForOneStep xs allRules allRules  
processRulesForOneStep (x:y:ys) ([a:[b],[d]]:rs) allRules 
  | x == a && y == b = x:(d:(processRulesForOneStep (y:ys) allRules allRules))
  | otherwise = processRulesForOneStep (x:y:ys) rs allRules

completeAllSteps :: Int -> Rules -> String -> String
completeAllSteps 0 _ str = str
completeAllSteps stepsToGo rules str = completeAllSteps (stepsToGo-1) rules (processRulesForOneStep str rules rules)

computeAnswer :: String -> Int
computeAnswer polymer = (maximum counts) - (minimum counts)
  where counts = (map length (group (sort polymer)))

part1 :: String -> String
part1 inp = (show $ computeAnswer (completeAllSteps kSteps rules pattern)) ++ "\n"
  where (pattern:_:rulesIn) = lines inp
        rules = map (filter (/= "->") . words) rulesIn

main = interact part1
