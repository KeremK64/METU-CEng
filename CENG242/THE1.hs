findInList :: (Eq a) => [a] -> [a] -> [Int]
findInList pattern list = reverse (helper pattern list 0 [])

helper :: (Eq a) => [a] -> [a] -> Int -> [Int] -> [Int]
helper [] _ _ acc = acc
helper (p:pa) [] _ _ = []
helper (p:pa) (a:ar) i acc =
    if p == a
        then
            helper pa ar (i+1)(i:acc)
        else
            helper (p:pa) ar (i+1) acc
