STEP 1 :  B's activities

Encrypt m using vig key, results  Cs  = E(m, k)
Encrypt Cs||k using public key of A, results  "E(Cs||k, PkA)"
send " E(Cs||k, PkA) " to A

STEP 2:   A's activities 
Decrypt " E(Cs||k, PkA) " using SkA, results Cs||k
Encrypt  Cs||k using PkB, results  "E("Cs||k, PkB)"
send "E("Cs||k, PkB)" to B

STEP 3: B's activities
Decrypt " E(Cs||k, PkB) " using SkB, results Cs||k, 
Decrypt  Cs using k, results Lets say X and if it equals m, output m 
