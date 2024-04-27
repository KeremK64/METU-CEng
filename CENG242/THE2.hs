data Tree k v = EmptyTree | Node k v [Tree k v] deriving (Show, Eq)

-- Question 1
selectiveMap :: (a -> Bool) -> (a -> a) -> [a] -> [a]
selectiveMap func1 func2 arr = [if func1 var then func2 var else var | var <- arr]

-- Question 2
tSelectiveMap :: (k -> Bool) -> (v -> v) -> Tree k v -> Tree k v
tSelectiveMap func1 func2 (Node key value children) = 
        let childAppend = map (tSelectiveMap func1 func2) children 
        in Node key (newValue) childAppend
        where newValue = if func1 key then func2 value else value

tSelectiveMap _ _ EmptyTree = EmptyTree

-- Question 3
tSelectiveMappingFold :: (k -> Bool) -> (k -> v -> r) -> (r -> r -> r) -> r -> Tree k v -> r
tSelectiveMappingFold decider mapper operator accum (Node key value children) =
  if decider key
    then let mappedElement = mapper key value
         in foldl (\acc child -> operator acc (tSelectiveMappingFold decider mapper operator accum child)) mappedElement children
    else foldl (\acc child -> operator acc (tSelectiveMappingFold decider mapper operator accum child)) accum children
