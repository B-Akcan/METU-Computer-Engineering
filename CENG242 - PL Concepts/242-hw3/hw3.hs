{-# LANGUAGE FlexibleInstances #-}

module PE3 where

import Data.List (sort, sortBy)
import Text.Printf (printf)

data Term = Const Integer | Pw Integer Power | Trig Integer Power Trigonometric | Exp Integer Power Exponential

data Power = Power Integer
data Polynomial = Polynomial [(Integer, Power)]
data Exponential = Exponential Polynomial
data Trigonometric = Sin Polynomial | Cos Polynomial

class Evaluable a where
    function :: a -> (Integer -> Double)

class Differentiable a where
    derivative :: a -> [Term]

-- You can use this as is
getRounded :: Double -> Double 
getRounded x = read s :: Double
               where s = printf "%.2f" x

-- You don't have to follow the order the functions appear in the file
-- For example, you could first define all Show instances, then all Eq instances etc.
-- if that implementation order is more convenient for you.

-- Utility functions
join sep xs = foldr (\a b-> a ++ if b=="" then b else sep ++ b) "" xs

sumList :: [Double] -> Double
sumList [] = 0
sumList (x:xs) = x + sumList xs

myRound :: Double -> Int -> Double
myRound x n = (fromInteger $ round $ x * (10^n)) / (10.0^^n)

returnPower :: Power -> Integer
returnPower (Power p) = p

returnIntPow (Pw a b) = a
returnPowPow (Pw a b) = b

returnIntTrig (Trig a b c) = a
returnPowTrig (Trig a b c) = b
returnTrigTrig (Trig a b c) = c

returnIntExp (Exp a b c) = a
returnPowExp (Exp a b c) = b
returnExpExp (Exp a b c) = c

-- INSTANCES FOR POWER

instance Show Power where
    show (Power p) | p == 0 = "1"
                   | p == 1 = "x"
                   | otherwise = (printf "x^%v" p)

instance Eq Power where
    (Power p) == (Power q) | p == q = True
                           | otherwise = False

instance Ord Power where
    (Power p) <= (Power q) | p <= q = True
                           | otherwise = False
    (Power p) < (Power q) | p < q = True
                           | otherwise = False
    (Power p) >= (Power q) | p >= q = True
                           | otherwise = False
    (Power p) > (Power q) | p > q = True
                           | otherwise = False

instance Evaluable Power where
    function (Power p) a = fromInteger (a^p)

instance Differentiable Power where
    derivative (Power p) | p == 0 = [Const 0]
                         | otherwise = [Pw (p) (Power (p-1))]



-- INSTANCES FOR POLYNOMIAL

instance Show Polynomial where
    show (Polynomial list) = let arr = [let res | fst tpl == 0 = ""
                                                | fst tpl == 1 = (show (snd tpl))
                                                | fst tpl == -1 = printf "-%v" (show (snd tpl))
                                                | show (snd tpl) == "1" = (show (fst tpl))
                                                | otherwise = (show (fst tpl) ++ show (snd tpl))
                                        in res | tpl <- list]
                             in join " + " arr

instance Evaluable Polynomial where
    function (Polynomial list) a = sumList [(function (snd tpl) a) * (fromInteger (fst tpl)) | tpl <- list]

instance Differentiable Polynomial where
    derivative (Polynomial list) = let arr = [let res | snd tpl == (Power 0) = Pw 0 (Power 0)
                                                      | snd tpl == (Power 1) = Pw (fst tpl) (Power 0)
                                                      | otherwise = Pw ((fst tpl) * (returnPower (snd tpl))) (Power (returnPower(snd tpl)-1))
                                              in res  | tpl <- list]
                                   in filter (/= (Pw 0 (Power 0))) arr

instance Eq Polynomial where
    (Polynomial list1) /= (Polynomial list2) = let arr = [((fst x1) /= (fst x2)) || ((snd x1) /= (snd x2)) | x1 <- list1, x2 <- list2]
                                                   falseCount = filter (== False) arr
                                                   len = length falseCount
                                                   res | len == 0 = True
                                                       | otherwise = False
                                               in res
                                               


-- INSTANCES FOR TRIGONOMETRIC

instance Show Trigonometric where
    show (Sin (Polynomial [(a, b)])) | a == 0 = printf "sin0"
                                     | (a == 1) && ((show b) == "1") = printf "sin1"
                                     | (a == 1) && ((show b) == "x") = printf "sinx"
                                     | (a == 1) = printf "sin(%v)" (show b)
                                     | (a == -1) && ((show b) == "1") = printf "sin(-1)"
                                     | (a == -1) && ((show b) == "x") = printf "sin(-x)"
                                     | (a == -1) = printf "sin(-%v)" (show b)
                                     | (show b) == "1" = printf "sin%d" a
                                     | (show b) == "x" = printf "sin%dx" a
                                     | otherwise = printf "sin(%d%v)" a (show b)
    show (Sin p) = printf "sin(%v)" (show p)
    show (Cos (Polynomial [(a, b)])) | a == 0 = printf "cos0"
                                     | (a == 1) && ((show b) == "1") = printf "cos1"
                                     | (a == 1) && ((show b) == "x") = printf "cosx"
                                     | (a == 1) = printf "cos(%v)" (show b)
                                     | (a == -1) && ((show b) == "1") = printf "cos(-1)"
                                     | (a == -1) && ((show b) == "x") = printf "cos(-x)"
                                     | (a == -1) = printf "cos(-%v)" (show b)
                                     | (show b) == "1" = printf "cos%d" a
                                     | (show b) == "x" = printf "cos%dx" a
                                     | otherwise = printf "cos(%d%v)" a (show b)
    show (Cos p) = printf "cos(%v)" (show p)

instance Evaluable Trigonometric where
    function (Sin (Polynomial list)) a = myRound (sin (sumList [(function (snd tpl) a) * (fromInteger (fst tpl)) | tpl <- list])) 2
    function (Cos (Polynomial list)) a = myRound (cos (sumList [(function (snd tpl) a) * (fromInteger (fst tpl)) | tpl <- list])) 2

instance Differentiable Trigonometric where
    derivative (Sin (Polynomial list)) = [Trig (returnIntPow ((derivative (Polynomial list)) !! 0)) (returnPowPow ((derivative (Polynomial list)) !! 0)) (Cos (Polynomial list))]
    derivative (Cos (Polynomial list)) = [Trig ((-1) * returnIntPow ((derivative (Polynomial list)) !! 0)) (returnPowPow ((derivative (Polynomial list)) !! 0)) (Sin (Polynomial list))]
    
instance Eq Trigonometric where
    (Sin a) /= (Cos b) = True
    (Cos a) /= (Sin b) = True
    (Sin a) /= (Sin b) | a /= b = True
                       | otherwise = False
    (Cos a) /= (Cos b) | a /= b = True
                       | otherwise = False




-- INSTANCES FOR EXPONENTIAL

instance Show Exponential where
    show (Exponential (Polynomial [(a, b)])) | a == 0 = printf "e^0"
                                             | (a == 1) && ((show b) == "1") = printf "e^1"
                                             | (a == 1) && ((show b) == "x") = printf "e^x"
                                             | (a == 1) = printf "e^(%v)" (show b)
                                             | (a == -1) && ((show b) == "1") = printf "e^(-1)"
                                             | (a == -1) && ((show b) == "x") = printf "e^(-x)"
                                             | (a == -1) = printf "e^(-%v)" (show b)
                                             | (show b) == "1" = printf "e^%d" a
                                             | (show b) == "x" = printf "e^%dx" a
                                             | otherwise = printf "e^(%d%v)" a (show b)
    show (Exponential p) = printf "e^(%v)" (show p)

instance Evaluable Exponential where
    function (Exponential (Polynomial list)) a = myRound (exp (sumList [(function (snd tpl) a) * (fromInteger (fst tpl)) | tpl <- list])) 2

instance Differentiable Exponential where
    derivative (Exponential (Polynomial list)) = [Exp (returnIntPow ((derivative (Polynomial list)) !! 0)) (returnPowPow ((derivative (Polynomial list)) !! 0)) (Exponential (Polynomial list))]
    
instance Eq Exponential where
    (Exponential a) /= (Exponential b) | a /= b = True
                                       | otherwise = False



-- INSTANCES FOR TERM

instance Show Term where
    show (Const a) = printf "%d" a
    show (Pw a b) | a == 0 = "0"
                  | a == 1 = (show b)
                  | a == -1 = printf "-%v" (show b)
                  | (show b) == "1" = printf "%d" a
                  | otherwise = printf "%d%v" a (show b)
    show (Trig a b c) | a == 0 = "0"
                      | a == 1 = printf "%v%v" (show b) (show c)
                      | a == -1 = printf "-%v%v" (show b) (show c)
                      | (show b) == "1" = printf "%d%v" a (show c)
                      | otherwise = printf "%d%v%v" a (show b) (show c)
    show (Exp a b c) | a == 0 = "0"
                     | a == 1 = printf "%v%v" (show b) (show c)
                     | a == -1 = printf "-%v%v" (show b) (show c)
                     | (show b) == "1" = printf "%d%v" a (show c)
                     | otherwise = printf "%d%v%v" a (show b) (show c)

instance Evaluable Term where
    function (Const a) b = fromInteger a
    function (Pw a b) c = (fromInteger a) * (function b c)
    function (Trig a b c) d = fromInteger a * (function b d) * (function c d)
    function (Exp a b c) d = fromInteger a * (function b d) * (function c d)

instance Differentiable Term where
    derivative (Const a) = [Const 0]
    derivative (Pw a b) = [Pw (a * returnIntPow ((derivative b) !! 0)) (returnPowPow ((derivative b) !! 0))]
    derivative (Trig a b c) = [Trig (a * returnIntTrig ((derivative c) !! 0)) (Power ((returnPower b) * returnPower (returnPowTrig ((derivative c) !! 0)))) (returnTrigTrig ((derivative c) !! 0))]
    derivative (Exp a b c) = [Exp (a * returnIntExp ((derivative c) !! 0)) (Power ((returnPower b) * returnPower (returnPowExp ((derivative c) !! 0)))) (returnExpExp ((derivative c) !! 0))]

instance Eq Term where
    (Const a) /= (Const b) | a /= b = True
                           | otherwise = False
    (Const a) /= (Pw b c) = True
    (Const a) /= (Trig b c d) = True
    (Const a) /= (Exp b c d) = True
    (Pw a b) /= (Const c) = True
    (Pw a b) /= (Pw c d) | a /= c || b /= d = True
                         | otherwise = False
    (Pw a b) /= (Trig c d e) = True
    (Pw a b) /= (Exp c d e) = True
    (Trig a b c) /= (Const d) = True
    (Trig a b c) /= (Pw d e) = True
    (Trig a b c) /= (Trig d e f) | a /= d || b /= e || c /= f = True
                                 | otherwise = False
    (Trig a b c) /= (Exp d e f) = True
    (Exp a b c) /= (Const d) = True
    (Exp a b c) /= (Pw d e) = True
    (Exp a b c) /= (Trig d e f) = True
    (Exp a b c) /= (Exp d e f) | a /= d || b /= e || c /= f = True
                               | otherwise = False




-- INSTANCES FOR [TERM]

instance Evaluable [Term] where
    function list a = myRound (sumList [function el a | el <- list]) 2

instance Differentiable [Term] where
    derivative list = [(derivative el) !! 0 | el <- list]
