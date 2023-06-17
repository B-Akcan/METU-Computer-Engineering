module PE1 where

import Text.Printf

-- PE1: Recipe Calculator
-- The premise of this homework if to write a recipe calculator that
-- calculates: how much a recipe costs to make, what can be made with the
-- ingredients already available, and how much extra ingredients need to
-- be bought in order to make a recipe.

-- Recipe = Recipe Name [(Ingredient, Quantity)]
data Recipe = Recipe String [(String, Double)] deriving Show

-- Price = Price Ingredient Quantity Price
data Price = Price String Double Double deriving Show

-- Utility functions
getRounded :: Double -> Double 
getRounded x = read s :: Double
               where s = printf "%.2f" x
               
getIngredient :: Price -> String
getIngredient (Price ing _ _) = ing 

getQuantity :: Price -> Double
getQuantity (Price _ q _) = q

getPrice :: Price -> Double
getPrice (Price _ _ p) = p

getRecipeName :: Recipe -> String
getRecipeName (Recipe nm _) = nm

getRecipeList :: Recipe -> [(String, Double)]
getRecipeList (Recipe _ ls) = ls

sumElements :: [Double] -> Double
sumElements [] = 0
sumElements (f:r) = f + sumElements r

missingIng :: Recipe -> (String, Double) -> [(String, Double)]
missingIng rcp tpl = [(fst tpl, getRounded(snd x - snd tpl)) | x <- (getRecipeList rcp), (fst tpl) == (fst x), (snd tpl) < (snd x)]

isEmpty :: [(String, Double)] -> Bool
isEmpty lst | lst == [] = True
            | otherwise = False

isInList :: (String, Double) -> [(String, Double)] -> Bool
isInList tpl lst | isEmpty [x | x <- lst, (fst tpl) == (fst x)] = False
                 | otherwise = True
                
excessIng :: Recipe -> (String, Double) -> (String, Double)
excessIng rcp tpl | not (isInList tpl (getRecipeList rcp)) = tpl
                  | otherwise = head [((fst tpl), getRounded((snd tpl) - (snd x))) | x <- (getRecipeList rcp), (fst tpl) == (fst x)]

makeShoppingListForOneRecipe :: [(String, Double)] -> Recipe -> [Price] -> [(String, Double, Double)]
makeShoppingListForOneRecipe lst rcp prices = [(fst x, snd x, (getIngredientCost x prices)) | x <- (missingIngredients rcp lst)]


-- Calculate how much the given amount of the given ingredient costs
getIngredientCost :: (String, Double) -> [Price] -> Double
getIngredientCost tpl lst = let obj = [x | x <- lst, (getIngredient x) == (fst tpl)]
                            in getRounded ((snd tpl) * (getPrice (head obj)) / (getQuantity (head obj)))

-- Calculate how much it costs to buy all the ingredients of a recipe
recipeCost :: Recipe -> [Price] -> Double
recipeCost rcp lst = sumElements [getIngredientCost x lst | x <- (getRecipeList rcp)]

-- Given a list of how much you already have of each ingredient,
-- calculate how much of which ingredients are missing for a recipe
missingIngredients :: Recipe -> [(String, Double)] -> [(String, Double)]
missingIngredients rcp lst = (concat [missingIng rcp x | x <- lst]) ++ [x | x <- (getRecipeList rcp), not (isInList x lst)]

-- Given a list of ingredients in your kitchen, calculate what you would
-- have left after making the given recipe. If there isn't enough of an
-- ingredient, the recipe cannot be made! You shouldn't change the amount
-- of ingredient in that case.
makeRecipe :: [(String, Double)] -> Recipe -> [(String, Double)]
makeRecipe lst rcp | missingIngredients rcp lst /= [] = lst 
                   | otherwise = [excessIng rcp x | x <- lst]

-- Given a list of ingredients you already have, and a list of recipes,
-- make a shopping list showing how much of each ingredient you need
-- to buy, and its cost. Each ingredient mush appear in the shopping list
-- at most once (no duplicates!).
makeShoppingList :: [(String, Double)] -> [Recipe] -> [Price] -> [(String, Double, Double)]
makeShoppingList lst recipes prices = concat [makeShoppingListForOneRecipe lst x prices | x <- recipes]
                                        









