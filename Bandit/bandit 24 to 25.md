# bandit 24 to 25

A daemon is listening on port 30002 and will give you the password for bandit25 if given the password for bandit24 and a secret numeric 4-digit pincode. There is no way to retrieve the pincode except by going through all of the 10000 combinations, called brute-forcing.

---

### solve

> This time, I have to make a shell script connecting and sending a message.
>
> I make a shell script like this.
>
> ```bash
> #!/bin/bash
> 
> for i in {0000..9999}
> do
> 		echo "UoMYTrfrBFHyQXmg6gzctqAwOmw1IohZ ${i}" >> text
> done
> 
> cat text | nc localhost 30002 >> tt
> 
> echo sort tt | uniq -u
> ```
>
> but it responds sending "Timeout. Exiting". 
>
> I don't know why and I found some write-up ,but they did like me.