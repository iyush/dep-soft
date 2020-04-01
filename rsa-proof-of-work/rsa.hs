import Text.Printf
import Data.Char

data Key = Key Integer Integer deriving (Show)


{-| 
 - Functions defined for generating decryption key given (e, n)
 -}

getFactors :: Integer -> [Integer]
getFactors n = [x | x <- 2:[3,5..n-1], n `mod` x == 0]

-- for a b calculate d and s and t such that d = gcd(a,b) and d = s*a + t*b
egcd :: Integer -> Integer -> (Integer, Integer, Integer)
egcd a 0 = (abs a, signum a, 0)
egcd a b = (d, t, s - (a `div` b) * t)
    where (d, s, t) = egcd b (a `mod` b)


getPhi :: Integer -> Integer
getPhi n =  foldl (\acc x -> acc * x) 1  $ map ((-)1) (getFactors n)

sec':: (a, a, a) -> a
sec' (_, x, _) = x

getDecryption :: Integer -> Integer -> Integer
getDecryption n e = sec' $ egcd e $ getPhi n


{-| 
 - Functions defined for decryption given (d,n)
 -}

dec :: Integer -> Key -> Integer 
dec c (Key n d) = c^d `mod` n

decList :: [Integer] -> Key -> [Integer]
decList ml k = map (\x -> dec x k) ml

ordList :: [Integer] -> [Char]
ordList l = map (chr . fromIntegral) l


{-| 
 - Initializing variables
 -}

encryptedList = [21556870,12228498,25056229,38800351,19503311,12228498,38800351,24444405,35051831,24444405,30059578,38800351,5811028,12228498,27948437,12228498,1365184,24444405,38800351,18162318,14922283,27948437,23749280,12351750,42881586]

n = 44331583
e = 15852553

decryptionKey = getDecryption n e


decryptedList = decList encryptedList (Key n decryptionKey)

main = do
        printf "Encryption Key:\t %d\n" e
        printf "N:\t\t %d\n" n
        printf "Decryption Key:\t %d\n" decryptionKey
        printf "Decrypted List:\t %s\n" (show $ decryptedList)
        printf "In strings:\t %s\n" (ordList decryptedList)
