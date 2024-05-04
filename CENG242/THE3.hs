data Expression = Variable String 
    | Constant Float
    | Sine Expression
    | Cosine Expression
    | Negation Expression
    | Addition Expression Expression
    | Multiplication Expression Expression

class Differential a where
    diff :: a -> a -> a

instance Show Expression where
    show (Variable x) = "Variable '" ++ x ++ "'"
    show (Constant c) = "Constant " ++ show c
    show (Sine expr) = "sin " ++ show expr
    show (Cosine expr) = "cos " ++ show expr
    show (Negation expr) = "-" ++ show expr
    show (Addition expr1 expr2) = "(" ++ show expr1 ++ " + " ++ show expr2 ++ ")"
    show (Multiplication expr1 expr2) = "(" ++ show expr1 ++ " * " ++ show expr2 ++ ")"

instance Eq Expression where
    (Variable x1) == (Variable x2) = x1 == x2
    (==) (Constant c1)(Constant c2) = c1 == c2
    (==) (Sine expr1)(Sine expr2) = expr1 == expr2
    (==) (Cosine expr1)(Cosine expr2) = expr1 == expr2
    (==) (Negation expr1)(Negation expr2) = expr1 == expr2
    (==) (Addition expr11 expr12)(Addition expr21 expr22) = expr11 == expr21 && expr12 == expr22
    (==) (Multiplication expr11 expr12)(Multiplication expr21 expr22) = expr11 == expr21 && expr12 == expr22
    (==) _ _ = False
    
 
instance Num Expression where
    fromInteger = Constant . fromInteger
    (*) 0 expr1 = (Constant 0)
    (*) expr1 0 = (Constant 0)
    (*) 1 expr1 = expr1
    (*) expr1 1 = expr1
    (*) expr1 expr2 = Multiplication expr1 expr2
    (+) expr1 0 = expr1
    (+) 0 expr1 = expr1
    (+) expr1 expr2 = Addition expr1 expr2
    negate (Constant c) = (Constant (-c))
    negate (expr) = Negation (expr)


instance Differential Expression where
    diff (Constant c) _ = Constant 0
    diff _ (Constant c) = Constant 0
    diff (Variable v) (Variable v2) = if (v == v2) then Constant 1 else Constant 0
    diff (Sine expr) (Variable v) = Multiplication (Cosine expr) (diff expr (Variable v))
    diff (Cosine expr) (Variable v) = (Multiplication (Negation(Sine expr)) (diff expr (Variable v)))
    diff (Negation expr) (Variable v) = Negation (diff expr (Variable v))
    diff (Addition expr1 expr2) (Variable v) = Addition (diff expr1 (Variable v))(diff expr2 (Variable v))
    diff (Multiplication expr1 expr2) (Variable v) = Addition (Multiplication (diff expr1 (Variable v)) expr2) (Multiplication expr1 (diff expr2 (Variable v)))

